#include "achatwindow.h"
#include "ui_achatwindow.h"

#include "achats/achatsui.h"
#include "achats/achatstyle.h"
#include "achats/facture/facture.h"
#include "achats/nouveau/nouveauachat.h"
#include "achats/suppression/supprimerachat.h"
#include "clients/client.h"
#include "materiels/materiel.h"

#include <QDate>
#include <QHeaderView>
#include <QIcon>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableWidgetItem>

#include <utility>

namespace {

QString sansEspaces(QString texte)
{
    texte.remove(QLatin1Char(' '));
    texte.remove(QChar(0x00A0));
    return texte;
}

QTableWidgetItem *creerCellule(const QString &texte, Qt::Alignment alignement)
{
    auto *cellule = new QTableWidgetItem(texte);
    cellule->setTextAlignment(alignement | Qt::AlignVCenter);
    return cellule;
}

}

AchatWindow::AchatWindow(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AchatWindow)
{
    ui->setupUi(this);

    setStyleSheet(AchatStyle::fenetreAchats());
    setWindowFlag(Qt::WindowMaximizeButtonHint, true);
    setSizeGripEnabled(true);

    configurerTable();
    ajouterIcones();

    connect(ui->btnAccueil, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->btnNouveau, &QPushButton::clicked, this, &AchatWindow::onNouveau);
    connect(ui->btnModifier, &QPushButton::clicked, this, &AchatWindow::onModifier);
    connect(ui->btnFacture, &QPushButton::clicked, this, &AchatWindow::onFacture);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &AchatWindow::onSupprimer);

    connect(ui->champRecherche, &QLineEdit::textChanged, this, &AchatWindow::rafraichir);

    chargerDonnees();
    rafraichir();
}

AchatWindow::~AchatWindow()
{
    delete ui;
}

void AchatWindow::chargerDonnees()
{
    m_clients.clear();
    m_materiels.clear();
    m_achats.clear();

    QSqlQuery clients;
    if (!clients.exec(QStringLiteral("SELECT id_client, nom FROM client ORDER BY nom"))) {
        ui->labelAide->setText(QStringLiteral("Impossible de charger les clients de la base."));
        return;
    }
    while (clients.next())
        m_clients.append(Client(clients.value(0).toString(), clients.value(1).toString()));

    QSqlQuery materiels;
    if (!materiels.exec(QStringLiteral(
            "SELECT id_materiel, designation, prix_unitaire, stock_actuel, stock_initial "
            "FROM materiel ORDER BY designation"))) {
        ui->labelAide->setText(QStringLiteral("Impossible de charger les matériels de la base."));
        return;
    }
    while (materiels.next()) {
        m_materiels.append(Materiel(materiels.value(0).toString(), materiels.value(1).toString(),
                                    materiels.value(2).toDouble(), materiels.value(3).toInt(),
                                    materiels.value(4).toInt()));
    }

    QSqlQuery achats;
    if (!achats.exec(QStringLiteral(
            "SELECT a.id_achat, c.id_client, c.nom, c.telephone, m.id_materiel, "
            "m.designation, a.qte, a.prix_unitaire_achat, a.date_achat "
            "FROM achat a "
            "JOIN client c ON c.id_client = a.id_client "
            "JOIN materiel m ON m.id_materiel = a.id_materiel "
            "ORDER BY a.date_achat DESC, a.id_achat DESC"))) {
        ui->labelAide->setText(QStringLiteral("Impossible de charger les achats de la base."));
        return;
    }
    while (achats.next()) {
        const QString dateTexte = achats.value(8).toString().left(10);
        m_achats.append(Achat(achats.value(0).toInt(), achats.value(1).toString(),
                              achats.value(2).toString(), achats.value(4).toString(),
                              achats.value(5).toString(), achats.value(6).toInt(),
                              achats.value(7).toDouble(), QDate::fromString(dateTexte, Qt::ISODate),
                              achats.value(3).toString()));
    }
}

void AchatWindow::setAchats(const ListeAchats &achats)
{
    m_achats = achats;
    rafraichir();
}

void AchatWindow::setClients(const ListeClients &clients)
{
    m_clients = clients;
}

void AchatWindow::setMateriels(const ListeMateriels &materiels)
{
    m_materiels = materiels;
}

void AchatWindow::configurerTable()
{
    QHeaderView *entete = ui->tableAchats->horizontalHeader();
    entete->setSectionResizeMode(QHeaderView::Stretch);
    entete->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    entete->setMinimumSectionSize(80);
    entete->setFixedHeight(48);
    entete->setHighlightSections(false);
    entete->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->tableAchats->verticalHeader()->setDefaultSectionSize(56);

    for (int colonne : {3, 5}) {
        if (QTableWidgetItem *titre = ui->tableAchats->horizontalHeaderItem(colonne))
            titre->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}

void AchatWindow::ajouterIcones()
{
    using AchatsUi::Icone;

    const QColor voile(255, 255, 255, 56);
    const QColor blanc(Qt::white);
    const int diametre = 48;
    const int marge = 14;
    const QSize tailleIcone(diametre + marge, diametre);

    ui->btnNouveau->setIcon(QIcon(AchatsUi::pastille(Icone::Plus, diametre, voile, voile, blanc, marge)));
    ui->btnModifier->setIcon(QIcon(AchatsUi::pastille(Icone::Crayon, diametre, voile, voile, blanc, marge)));
    ui->btnFacture->setIcon(QIcon(AchatsUi::pastille(Icone::Document, diametre, voile, voile, blanc, marge)));
    ui->btnSupprimer->setIcon(QIcon(AchatsUi::pastille(Icone::Corbeille, diametre, voile, voile, blanc, marge)));
    for (QPushButton *bouton : {ui->btnNouveau, ui->btnModifier, ui->btnFacture, ui->btnSupprimer})
        bouton->setIconSize(tailleIcone);

    ui->iconeTitre->setFixedSize(56, 56);
    ui->iconeTitre->setPixmap(AchatsUi::pastille(Icone::Panier, 56, QColor("#EA7210"), QColor("#D95F08"), blanc));

    ui->iconeRecherche->setFixedSize(24, 24);
    ui->iconeRecherche->setPixmap(AchatsUi::icone(Icone::Loupe, 24, QColor("#7A5C45")));
}

bool AchatWindow::correspond(const Achat &achat, const QString &recherche)
{
    if (recherche.isEmpty())
        return true;

    if (achat.nomClient().contains(recherche, Qt::CaseInsensitive))
        return true;
    const QString telephoneRecherche = sansEspaces(recherche);
    return !telephoneRecherche.isEmpty()
           && sansEspaces(achat.telephoneClient()).contains(telephoneRecherche);
}

void AchatWindow::rafraichir()
{
    const int idAGarder = idSelectionne();
    const QString recherche = ui->champRecherche->text().trimmed();

    ui->tableAchats->setRowCount(0);

    double total = 0.0;
    int ligneASelectionner = -1;

    for (const Achat &achat : std::as_const(m_achats)) {
        if (!correspond(achat, recherche))
            continue;

        const int ligne = ui->tableAchats->rowCount();
        ui->tableAchats->insertRow(ligne);

        QTableWidgetItem *cellNumero = creerCellule(QString::number(achat.idAchat()), Qt::AlignLeft);
        cellNumero->setData(Qt::UserRole, achat.idAchat());

        ui->tableAchats->setItem(ligne, 0, cellNumero);
        ui->tableAchats->setItem(ligne, 1, creerCellule(achat.nomClient(), Qt::AlignLeft));
        ui->tableAchats->setItem(ligne, 2, creerCellule(achat.designationMat(), Qt::AlignLeft));
        ui->tableAchats->setItem(ligne, 3, creerCellule(QString::number(achat.qte()), Qt::AlignRight));
        ui->tableAchats->setItem(ligne, 4, creerCellule(achat.dateAchat().toString(QStringLiteral("dd/MM/yyyy")), Qt::AlignLeft));
        ui->tableAchats->setItem(ligne, 5, creerCellule(AchatsUi::formatMontant(achat.montantTotal()), Qt::AlignRight));

        total += achat.montantTotal();
        if (achat.idAchat() == idAGarder)
            ligneASelectionner = ligne;
    }

    if (ligneASelectionner >= 0)
        ui->tableAchats->selectRow(ligneASelectionner);

    ui->labelTotalValeur->setText(AchatsUi::formatMontant(total));

    if (m_achats.isEmpty())
        ui->labelAide->setText(QStringLiteral("Aucun achat enregistré pour le moment."));
    else if (ui->tableAchats->rowCount() == 0)
        ui->labelAide->setText(QStringLiteral("Aucun achat ne correspond à cette recherche."));
    else
        ui->labelAide->setText(QStringLiteral("Sélectionnez un achat pour le modifier, le supprimer ou éditer sa facture."));
}

int AchatWindow::idSelectionne() const
{
    const QModelIndexList lignes = ui->tableAchats->selectionModel()->selectedRows();
    if (lignes.isEmpty())
        return -1;

    const QTableWidgetItem *cellule = ui->tableAchats->item(lignes.first().row(), 0);
    return cellule ? cellule->data(Qt::UserRole).toInt() : -1;
}

int AchatWindow::indexParId(int idAchat) const
{
    for (int i = 0; i < m_achats.size(); ++i) {
        if (m_achats.at(i).idAchat() == idAchat)
            return i;
    }
    return -1;
}

int AchatWindow::prochainId() const
{
    int maximum = 0;
    for (const Achat &achat : m_achats)
        maximum = qMax(maximum, achat.idAchat());
    return maximum + 1;
}

void AchatWindow::onNouveau()
{
    NouveauAchat dialogue(0, this);
    if (dialogue.exec() == QDialog::Accepted) {
        chargerDonnees();
        rafraichir();
    }
}

void AchatWindow::onModifier()
{
    const int index = indexParId(idSelectionne());
    if (index < 0) {
        QMessageBox::information(this, QStringLiteral("Modifier"),
                                 QStringLiteral("Sélectionnez d'abord un achat dans le tableau."));
        return;
    }

    NouveauAchat dialogue(m_achats.at(index).idAchat(), this);
    if (dialogue.exec() == QDialog::Accepted) {
        chargerDonnees();
        rafraichir();
    }
}

void AchatWindow::onFacture()
{
    const int index = indexParId(idSelectionne());
    if (index < 0) {
        QMessageBox::information(this, QStringLiteral("Facture PDF"),
                                 QStringLiteral("Sélectionnez un achat : la facture sera celle de son client."));
        return;
    }

    Facture dialogue({m_achats.at(index).idAchat()}, this);
    dialogue.exec();
}

void AchatWindow::onSupprimer()
{
    const int index = indexParId(idSelectionne());
    if (index < 0) {
        QMessageBox::information(this, QStringLiteral("Supprimer"),
                                 QStringLiteral("Sélectionnez d'abord un achat dans le tableau."));
        return;
    }

    SupprimerAchat dialogue(m_achats.at(index).idAchat(), this);
    if (dialogue.exec() == QDialog::Accepted) {
        chargerDonnees();
        rafraichir();
    }
}
