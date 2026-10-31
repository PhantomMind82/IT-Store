#include "facturedialog.h"
#include "ui_facturedialog.h"

#include "achats/achatsui.h"
#include "achats/achatstyle.h"
#include "achats/facture/nombreenlettres.h"

#include <QFile>
#include <QFileDialog>
#include <QHeaderView>
#include <QMarginsF>
#include <QMessageBox>
#include <QPageLayout>
#include <QPageSize>
#include <QPdfWriter>
#include <QStandardPaths>
#include <QTableWidgetItem>
#include <QTextDocument>

#include <utility>

namespace {

QTableWidgetItem *creerCellule(const QString &texte, Qt::Alignment alignement)
{
    auto *cellule = new QTableWidgetItem(texte);
    cellule->setTextAlignment(alignement | Qt::AlignVCenter);
    return cellule;
}

// « Nom : <b>Nathan</b> » avec le texte protégé (toHtmlEscaped) au cas où il contiendrait < ou &.
QString ligneInfo(const QString &titre, const QString &valeur)
{
    return QStringLiteral("%1 <b style=\"color:#2B1608\">%2</b>").arg(titre, valeur.toHtmlEscaped());
}

} // namespace

FactureDialog::FactureDialog(const ListeAchats &achatsDuClient, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::FactureDialog),
      m_achats(achatsDuClient)
{
    ui->setupUi(this);
    setStyleSheet(AchatStyle::facture());

    // --- Tableau des lignes de la facture ---
    QHeaderView *entete = ui->tableFacture->horizontalHeader();
    entete->setSectionResizeMode(0, QHeaderView::Stretch);                  // « Désignation » prend la place restante
    entete->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    entete->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    entete->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    entete->setMinimumSectionSize(90);
    entete->setFixedHeight(36);
    entete->setHighlightSections(false);
    entete->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    for (int colonne : {1, 2, 3}) {                                         // PU, Qté, Montant : à droite
        if (QTableWidgetItem *titre = ui->tableFacture->horizontalHeaderItem(colonne))
            titre->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
    ui->tableFacture->verticalHeader()->setDefaultSectionSize(44);

    ui->tableFacture->setRowCount(m_achats.size());
    for (int ligne = 0; ligne < m_achats.size(); ++ligne) {
        const Achat &achat = m_achats.at(ligne);
        ui->tableFacture->setItem(ligne, 0, creerCellule(achat.designationMat(), Qt::AlignLeft));
        ui->tableFacture->setItem(ligne, 1, creerCellule(AchatsUi::formatNombre(achat.prixUnitaire()), Qt::AlignRight));
        ui->tableFacture->setItem(ligne, 2, creerCellule(QString::number(achat.qte()), Qt::AlignRight));
        ui->tableFacture->setItem(ligne, 3, creerCellule(AchatsUi::formatNombre(achat.montantTotal()), Qt::AlignRight));
    }

    // --- En-tête de la facture ---
    ui->labelFactureTitre->setText(QStringLiteral("Facture N° %1").arg(numeroFacture()));

    const QString numClient = m_achats.isEmpty() ? QStringLiteral("—") : m_achats.first().numClient();
    const QString nom = m_achats.isEmpty() ? QStringLiteral("—") : m_achats.first().nomClient();
    QString telephone = m_achats.isEmpty() ? QString() : m_achats.first().telephoneClient();
    if (telephone.isEmpty())
        telephone = QStringLiteral("—");

    ui->labelNumClient->setTextFormat(Qt::RichText);
    ui->labelDate->setTextFormat(Qt::RichText);
    ui->labelNom->setTextFormat(Qt::RichText);
    ui->labelTelephone->setTextFormat(Qt::RichText);
    ui->labelNumClient->setText(ligneInfo(QStringLiteral("N° client :"), numClient));
    ui->labelDate->setText(ligneInfo(QStringLiteral("Date :"), dateFacture().toString(QStringLiteral("dd/MM/yyyy"))));
    ui->labelNom->setText(ligneInfo(QStringLiteral("Nom :"), nom));
    ui->labelTelephone->setText(ligneInfo(QStringLiteral("Téléphone :"), telephone));

    // --- Total et montant en lettres ---
    const double total = totalGeneral();
    ui->labelTotalVal->setText(AchatsUi::formatMontant(total));

    const QString enLettres = QString::fromStdString(NombreEnLettres::enLettres(qRound64(total)));
    ui->labelArretee->setTextFormat(Qt::RichText);
    ui->labelArretee->setText(QStringLiteral("Arrêtée la présente facture à la somme de <b style=\"color:#2B1608\">%1 ariary</b>.")
                                  .arg(enLettres.toHtmlEscaped()));

    connect(ui->btnFermerFacture, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->btnGenererPdf, &QPushButton::clicked, this, &FactureDialog::genererPdf);
}

FactureDialog::~FactureDialog()
{
    delete ui;
}

// ---------------------------------------------------------------------------
// Calculs
// ---------------------------------------------------------------------------

QString FactureDialog::numeroFacture() const
{
    // Le numéro de facture est le numéro du client complété par des zéros : client 1 -> « 0001 ».
    if (m_achats.isEmpty())
        return QStringLiteral("0000");
    return m_achats.first().numClient().rightJustified(4, QLatin1Char('0'));
}

QDate FactureDialog::dateFacture() const
{
    QDate derniere;
    for (const Achat &achat : m_achats) {
        if (!derniere.isValid() || achat.dateAchat() > derniere)
            derniere = achat.dateAchat();
    }
    return derniere;
}

double FactureDialog::totalGeneral() const
{
    double total = 0.0;
    for (const Achat &achat : m_achats)
        total += achat.montantTotal();
    return total;
}

// ---------------------------------------------------------------------------
// PDF
// ---------------------------------------------------------------------------

QString FactureDialog::htmlPourPdf() const
{
    QString lignes;
    for (const Achat &achat : m_achats) {
        lignes += QStringLiteral("<tr><td>%1</td><td align=\"right\">%2</td><td align=\"right\">%3</td><td align=\"right\">%4</td></tr>")
                      .arg(achat.designationMat().toHtmlEscaped(),
                           AchatsUi::formatNombre(achat.prixUnitaire()),
                           QString::number(achat.qte()),
                           AchatsUi::formatNombre(achat.montantTotal()));
    }

    const QString nom = m_achats.isEmpty() ? QString() : m_achats.first().nomClient();
    const QString numClient = m_achats.isEmpty() ? QString() : m_achats.first().numClient();
    const QString telephone = m_achats.isEmpty() ? QString() : m_achats.first().telephoneClient();
    const QString enLettres = QString::fromStdString(NombreEnLettres::enLettres(qRound64(totalGeneral())));

    // QTextDocument comprend un sous-ensemble simple de HTML (titres, tableaux, couleurs).
    return QStringLiteral(
               "<h1 style=\"color:#B84A05\">IT Store</h1>"
               "<h2>Facture N° %1</h2>"
               "<p>N° client : <b>%2</b><br>Nom : <b>%3</b><br>Téléphone : <b>%4</b><br>Date : <b>%5</b></p>"
               "<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"6\">"
               "<tr bgcolor=\"#FFF8F1\"><th align=\"left\">Désignation</th><th align=\"right\">PU (Ar)</th>"
               "<th align=\"right\">Qté</th><th align=\"right\">Montant (Ar)</th></tr>"
               "%6"
               "</table>"
               "<h3 align=\"right\">Total : %7</h3>"
               "<p>Arrêtée la présente facture à la somme de <b>%8 ariary</b>.</p>")
        .arg(numeroFacture(),
             numClient.toHtmlEscaped(),
             nom.toHtmlEscaped(),
             telephone.toHtmlEscaped(),
             dateFacture().toString(QStringLiteral("dd/MM/yyyy")),
             lignes,
             AchatsUi::formatMontant(totalGeneral()),
             enLettres.toHtmlEscaped());
}

void FactureDialog::genererPdf()
{
    // 1. On demande à l'utilisateur où enregistrer le fichier.
    const QString dossier = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString nomParDefaut = dossier + QStringLiteral("/facture_") + numeroFacture() + QStringLiteral(".pdf");

    QString chemin = QFileDialog::getSaveFileName(this, QStringLiteral("Enregistrer la facture"),
                                                  nomParDefaut, QStringLiteral("Fichier PDF (*.pdf)"));
    if (chemin.isEmpty())
        return;                                   // l'utilisateur a annulé
    if (!chemin.endsWith(QStringLiteral(".pdf"), Qt::CaseInsensitive))
        chemin += QStringLiteral(".pdf");

    // 2. On ouvre le fichier en écriture (et on prévient si c'est impossible).
    QFile fichier(chemin);
    if (!fichier.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, QStringLiteral("Facture PDF"),
                             QStringLiteral("Impossible d'écrire le fichier :\n%1").arg(chemin));
        return;
    }

    // 3. QPdfWriter = « imprimante virtuelle » qui écrit dans le fichier, au format A4.
    QPdfWriter pdf(&fichier);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    // 4. QTextDocument transforme le HTML en pages, puis print() les envoie au PDF.
    QTextDocument document;
    document.setDefaultFont(QFont(font().family(), 11));
    document.setHtml(htmlPourPdf());
    document.print(&pdf);

    fichier.close();
    QMessageBox::information(this, QStringLiteral("Facture PDF"),
                             QStringLiteral("La facture a été enregistrée :\n%1").arg(chemin));
}
