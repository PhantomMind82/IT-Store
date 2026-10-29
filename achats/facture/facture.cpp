#include "facture.h"
#include "ui_facture.h"

#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFont>
#include <QHeaderView>
#include <QLocale>
#include <QMessageBox>
#include <QPageSize>
#include <QPdfWriter>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QStringList>
#include <QTextDocument>

namespace {

QString avecEspaces(double valeur)
{
    return QLocale::c().toString(valeur, 'f', 0).replace(',', QChar(0x00A0));
}

QString ligneInfo(const QString &titre, const QString &valeur)
{
    return QString("%1 <b style='color:#2B1608'>%2</b>").arg(titre, valeur.toHtmlEscaped());
}

QString moinsDeMille(int n, bool fin)
{
    static const QStringList petits = {"zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept",
                                       "huit", "neuf", "dix", "onze", "douze", "treize", "quatorze",
                                       "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
    static const QStringList dizaines = {"", "", "vingt", "trente", "quarante", "cinquante",
                                         "soixante", "soixante", "quatre-vingt", "quatre-vingt"};

    const int centaines = n / 100;
    const int reste = n % 100;
    QString texte;

    if (centaines > 0) {
        if (centaines == 1)
            texte = "cent";
        else
            texte = petits[centaines] + " cent";

        if (reste == 0)
            return (centaines > 1 && fin) ? texte + "s" : texte;
        texte += " ";
    }

    if (reste < 20)
        return texte + petits[reste];

    const int dizaine = reste / 10;
    const int unite = reste % 10;

    if (dizaine == 7 || dizaine == 9) {
        if (dizaine == 7 && unite == 1)
            return texte + "soixante et onze";
        return texte + dizaines[dizaine] + "-" + petits[10 + unite];
    }
    if (unite == 0) {
        if (dizaine == 8 && fin)
            return texte + "quatre-vingts";
        return texte + dizaines[dizaine];
    }
    if (unite == 1 && dizaine != 8)
        return texte + dizaines[dizaine] + " et un";
    return texte + dizaines[dizaine] + "-" + petits[unite];
}

QString enLettres(qint64 n)
{
    if (n == 0)
        return "zéro";
    if (n < 0 || n >= 1000000000)
        return QString::number(n);

    const int millions = n / 1000000;
    const int milliers = (n / 1000) % 1000;
    const int reste = n % 1000;

    QStringList mots;
    if (millions > 0)
        mots << moinsDeMille(millions, true) + (millions > 1 ? " millions" : " million");
    if (milliers == 1)
        mots << "mille";
    else if (milliers > 1)
        mots << moinsDeMille(milliers, false) + " mille";
    if (reste > 0)
        mots << moinsDeMille(reste, true);
    return mots.join(" ");
}

}

Facture::Facture(const QList<int> &identifiantsAchats, QWidget *parent)
    : QDialog(parent), ui(new Ui::Facture)
{
    ui->setupUi(this);

    QHeaderView *entete = ui->tableFacture->horizontalHeader();
    entete->setSectionResizeMode(QHeaderView::ResizeToContents);
    entete->setSectionResizeMode(0, QHeaderView::Stretch);
    entete->setFixedHeight(44);
    entete->setHighlightSections(false);
    entete->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    entete->setStyleSheet("QHeaderView::section { background-color: #FFF1E2; color: #70421F; border: 0; border-bottom: 2px solid #E8CFB8; padding: 10px 12px; font-weight: 700; }");
    ui->tableFacture->verticalHeader()->setDefaultSectionSize(64);
    ui->tableFacture->setWordWrap(true);

    QStringList marqueursIdentifiants;
    for (int identifiant : identifiantsAchats)
        marqueursIdentifiants.append("?");

    QSqlQuery requeteCommandes;
    requeteCommandes.prepare("SELECT DISTINCT numero_commande FROM achat WHERE id_achat IN ("
                             + marqueursIdentifiants.join(", ") + ")");
    for (int identifiant : identifiantsAchats)
        requeteCommandes.addBindValue(identifiant);

    QStringList numerosCommandes;
    if (!requeteCommandes.exec()) {
        QMessageBox::critical(this, "Facture", "Impossible de retrouver la commande sélectionnée.");
        reject();
        return;
    }
    while (requeteCommandes.next())
        numerosCommandes.append(requeteCommandes.value(0).toString());

    if (numerosCommandes.isEmpty()) {
        QMessageBox::critical(this, "Facture", "La commande sélectionnée est introuvable.");
        reject();
        return;
    }

    QStringList marqueursCommandes;
    for (const QString &numeroCommande : numerosCommandes)
        marqueursCommandes.append("?");

    QSqlQuery q;
    q.prepare("SELECT a.id_achat, a.numero_commande, c.id_client, c.nom, c.telephone, m.designation, a.prix_unitaire_achat, a.qte, strftime('%d/%m/%Y', a.date_achat) "
              "FROM achat a "
              "JOIN client c ON c.id_client = a.id_client "
              "JOIN materiel m ON m.id_materiel = a.id_materiel "
              "WHERE a.numero_commande IN (" + marqueursCommandes.join(", ") + ") "
              "ORDER BY a.date_achat, a.id_achat");
    for (const QString &numeroCommande : numerosCommandes)
        q.addBindValue(numeroCommande);
    if (!q.exec()) {
        QMessageBox::critical(this, "Facture", "Impossible de charger les articles de la commande.");
        reject();
        return;
    }

    QString numClient, nom, telephone, date, numeroCommande, lignesHtml;
    double total = 0;
    const int numeroFacture = identifiantsAchats.isEmpty() ? 0 : identifiantsAchats.first();

    while (q.next()) {
        const double prixUnitaire = q.value(6).toDouble();
        const int quantite = q.value(7).toInt();
        const double montant = prixUnitaire * quantite;

        if (numeroCommande.isEmpty())
            numeroCommande = q.value(1).toString();
        numClient = q.value(2).toString();
        nom = q.value(3).toString();
        telephone = q.value(4).toString().trimmed();
        date = q.value(8).toString();
        total += montant;

        const QStringList textes = {q.value(5).toString(), avecEspaces(prixUnitaire), QString::number(quantite), avecEspaces(montant)};
        const int ligne = ui->tableFacture->rowCount();
        ui->tableFacture->insertRow(ligne);
        for (int colonne = 0; colonne < 4; ++colonne) {
            auto *cellule = new QTableWidgetItem(textes[colonne]);
            if (colonne > 0)
                cellule->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->tableFacture->setItem(ligne, colonne, cellule);
        }

        lignesHtml += QString("<tr><td>%1</td><td class='droite'>%2</td><td class='centre'>%3</td>"
                      "<td class='droite'>%4</td></tr>")
                          .arg(textes[0].toHtmlEscaped(), textes[1], textes[2], textes[3]);
    }

    m_numero = numeroCommande.isEmpty()
        ? QString::number(numeroFacture).rightJustified(4, '0')
        : numeroCommande;
    const QString enMots = enLettres(qRound64(total));
    const QString totalTexte = avecEspaces(total) + QChar(0x00A0) + "Ar";

    ui->labelFactureTitre->setText("Facture N° " + m_numero);
    ui->labelNumClient->setText(ligneInfo("N° client :", numClient));
    ui->labelDate->setText(ligneInfo("Date :", date));
    ui->labelNom->setText(ligneInfo("Nom :", nom));
    ui->labelTelephone->setText(ligneInfo("Téléphone :", telephone.isEmpty() ? "Non renseigné" : telephone));
    ui->labelTotalVal->setText(totalTexte);
    ui->labelArretee->setText("Arrêtée la présente facture à la somme de <b style='color:#2B1608'>"
                              + enMots.toHtmlEscaped() + " ariary</b>.");

    QFile modele(QStringLiteral(":/factures/facture.html"));
    if (!modele.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Facture", "Impossible de charger le modèle HTML de la facture.");
        reject();
        return;
    }
    m_html = QString::fromUtf8(modele.readAll());
    m_html.replace("{{NUMERO_FACTURE}}", m_numero.toHtmlEscaped());
    m_html.replace("{{ID_CLIENT}}", numClient.toHtmlEscaped());
    m_html.replace("{{DATE}}", date.toHtmlEscaped());
    m_html.replace("{{NOM_CLIENT}}", nom.toHtmlEscaped());
    m_html.replace("{{TELEPHONE}}", (telephone.isEmpty() ? QString("Non renseigné") : telephone).toHtmlEscaped());
    m_html.replace("{{LIGNES_ACHAT}}", lignesHtml);
    m_html.replace("{{TOTAL}}", avecEspaces(total).toHtmlEscaped());
    m_html.replace("{{TOTAL_EN_LETTRES}}", enMots.toHtmlEscaped() + " ariary");

    connect(ui->btnFermerFacture, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->btnGenererPdf, &QPushButton::clicked, this, &Facture::genererPdf);
}

Facture::~Facture()
{
    delete ui;
}

void Facture::genererPdf()
{
    QString dossier = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if (dossier.isEmpty() || !QDir(dossier).exists())
        dossier = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    QFileDialog selecteur(this, "Enregistrer la facture",
                          QDir(dossier).filePath("facture_" + m_numero + ".pdf"),
                          "Fichier PDF (*.pdf)");
    selecteur.setAcceptMode(QFileDialog::AcceptSave);
    selecteur.setFileMode(QFileDialog::AnyFile);
    selecteur.setDefaultSuffix("pdf");
    selecteur.setOption(QFileDialog::DontUseNativeDialog, true);
    if (selecteur.exec() != QDialog::Accepted || selecteur.selectedFiles().isEmpty())
        return;

    QString chemin = selecteur.selectedFiles().first();
    if (QFileInfo(chemin).suffix().isEmpty())
        chemin += ".pdf";

    QPdfWriter pdf(chemin);
    pdf.setPageSize(QPageSize(QPageSize::A4));

    QTextDocument document;
    document.setDefaultFont(QFont(font().family(), 11));
    document.setHtml(m_html);
    document.print(&pdf);

    QMessageBox::information(this, "Facture PDF", "Facture enregistrée :\n" + chemin);
}
