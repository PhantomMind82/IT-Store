#include "achatwindow.h"
#include "ui_achatwindow.h"

<<<<<<< HEAD
#include "achats/achatsui.h"
#include "achats/achatstyle.h"
#include "achats/facture/facturedialog.h"
#include "achats/nouveau/nouveauachatdialog.h"
#include "achats/suppression/supprimerachatdialog.h"

#include <QHeaderView>
#include <QIcon>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QTableWidgetItem>

#include <utility>

namespace {

// Enlève les espaces d'un numéro de téléphone : "038 78 720 14" -> "0387872014".
QString sansEspaces(QString texte)
{
    texte.remove(QLatin1Char(' '));
    texte.remove(QChar(0x00A0));
    return texte;
}

// Crée une cellule de tableau avec le texte et l'alignement voulus.
QTableWidgetItem *creerCellule(const QString &texte, Qt::Alignment alignement)
{
    auto *cellule = new QTableWidgetItem(texte);
    cellule->setTextAlignment(alignement | Qt::AlignVCenter);
    return cellule;
}

} // namespace

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

    // « ← Accueil » ferme la fenêtre et revient au menu principal.
=======
#include "achats/facture/facture.h"
#include "achats/nouveau/nouveauachat.h"
#include "achats/suppression/supprimerachat.h"

#include <QDialog>
#include <QDir>
#include <QFrame>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLocale>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QRegularExpression>
#include <QMessageBox>
#include <QDebug>
#include <QSvgRenderer>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QTableWidgetItem>
#include <QVBoxLayout>

static QString enAriary(double valeur)
{
    return QLocale::c().toString(valeur, 'f', 0).replace(',', QChar(0x00A0)) + QChar(0x00A0) + "Ar";
}

static QPixmap chargerSvg(const QString &chemin, const QSize &taille)
{
    QSvgRenderer renderer(chemin);
    QPixmap pixmap(taille);
    pixmap.fill(Qt::transparent);
    if (renderer.isValid()) {
        QPainter painter(&pixmap);
        renderer.render(&painter);
    } else {
        qWarning() << "Impossible de charger le SVG:" << chemin;
    }
    return pixmap;
}

static void afficherAlerteSelection(QWidget *parent, const QString &action)
{
    QDialog fenetre(parent);
    fenetre.setWindowTitle(QObject::tr("Aucun achat sélectionné"));
    fenetre.setModal(true);
    fenetre.setFixedSize(410, 245);
    fenetre.setStyleSheet(QStringLiteral(
        "QDialog { background: #FFFFFF; }"
        "QFrame#bandeau { background: #E96F10; border-radius: 8px; }"
        "QLabel#icone { color: white; background: rgba(255,255,255,35); border-radius: 20px;"
        " font-size: 24px; font-weight: 700; }"
        "QLabel#titre { color: #2B1608; font-size: 20px; font-weight: 700; }"
        "QLabel#message { color: #72523C; font-size: 14px; }"
        "QPushButton { min-height: 44px; padding: 0 18px; border: 0; border-radius: 8px;"
        " font-size: 14px; font-weight: 700; }"
        "QPushButton#retour { color: white; background: #E96F10; }"
        "QPushButton#retour:hover { background: #D85E08; }"));

    auto *contenu = new QVBoxLayout(&fenetre);
    contenu->setContentsMargins(22, 20, 22, 20);
    contenu->setSpacing(15);

    auto *bandeau = new QFrame(&fenetre);
    bandeau->setObjectName("bandeau");
    bandeau->setFixedHeight(8);
    contenu->addWidget(bandeau);

    auto *entete = new QHBoxLayout;
    auto *icone = new QLabel(QStringLiteral("!"), &fenetre);
    icone->setObjectName("icone");
    icone->setAlignment(Qt::AlignCenter);
    icone->setFixedSize(40, 40);
    auto *titre = new QLabel(QObject::tr("Choisissez un achat"), &fenetre);
    titre->setObjectName("titre");
    entete->addWidget(icone);
    entete->addSpacing(4);
    entete->addWidget(titre, 1);
    contenu->addLayout(entete);

    auto *message = new QLabel(QObject::tr("Pour %1, sélectionnez d'abord une ligne dans le tableau des achats.")
                                   .arg(action), &fenetre);
    message->setObjectName("message");
    message->setWordWrap(true);
    contenu->addWidget(message, 1);

    auto *boutons = new QHBoxLayout;
    boutons->addStretch();
    auto *retour = new QPushButton(QObject::tr("Retour à la liste"), &fenetre);
    retour->setObjectName("retour");
    retour->setCursor(Qt::PointingHandCursor);
    boutons->addWidget(retour);
    contenu->addLayout(boutons);

    QObject::connect(retour, &QPushButton::clicked, &fenetre, &QDialog::accept);
    fenetre.exec();
}

AchatWindow::AchatWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::AchatWindow)
{
    ui->setupUi(this);

    ui->logo->setPixmap(chargerSvg(":/achats/assets/logo.svg", ui->logo->size()));
    ui->iconeTitre->setPixmap(chargerSvg(":/achats/assets/icone-panier.svg", ui->iconeTitre->size()));
    ui->iconeRecherche->setPixmap(chargerSvg(":/achats/assets/loupe.svg", ui->iconeRecherche->size()));
    ui->btnNouveau->setIcon(QIcon(chargerSvg(":/achats/assets/btn-plus.svg", QSize(62, 48))));
    ui->btnModifier->setIcon(QIcon(chargerSvg(":/achats/assets/btn-crayon.svg", QSize(62, 48))));
    ui->btnFacture->setIcon(QIcon(chargerSvg(":/achats/assets/btn-document.svg", QSize(62, 48))));
    ui->btnSupprimer->setIcon(QIcon(chargerSvg(":/achats/assets/btn-corbeille.svg", QSize(62, 48))));
    ui->btnNouveau->setIconSize(QSize(62, 48));
    ui->btnModifier->setIconSize(QSize(62, 48));
    ui->btnFacture->setIconSize(QSize(62, 48));
    ui->btnSupprimer->setIconSize(QSize(62, 48));

    setWindowFlag(Qt::WindowMaximizeButtonHint, true);
    setSizeGripEnabled(true);

    ui->tableAchats->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableAchats->verticalHeader()->setDefaultSectionSize(68);
    QHeaderView *entete = ui->tableAchats->horizontalHeader();
    entete->setSectionResizeMode(QHeaderView::Stretch);
    entete->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    entete->setFixedHeight(54);
    entete->setMinimumSectionSize(120);
    entete->setHighlightSections(false);
    entete->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

>>>>>>> 8c2295e (Crafting)
    connect(ui->btnAccueil, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->btnNouveau, &QPushButton::clicked, this, &AchatWindow::onNouveau);
    connect(ui->btnModifier, &QPushButton::clicked, this, &AchatWindow::onModifier);
    connect(ui->btnFacture, &QPushButton::clicked, this, &AchatWindow::onFacture);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &AchatWindow::onSupprimer);

<<<<<<< HEAD
    // À chaque lettre tapée dans la recherche, on redessine le tableau.
    connect(ui->champRecherche, &QLineEdit::textChanged, this, &AchatWindow::rafraichir);

    chargerDonnees();
    rafraichir();
=======
    connect(ui->champRecherche, &QLineEdit::textChanged, this, &AchatWindow::chargerTable);

    chargerTable();
>>>>>>> 8c2295e (Crafting)
}

AchatWindow::~AchatWindow()
{
    delete ui;
}

<<<<<<< HEAD
// ---------------------------------------------------------------------------
// Données
// ---------------------------------------------------------------------------

void AchatWindow::chargerDonnees()
{
    // POUR L'INSTANT : rien. Les trois listes restent vides, donc le tableau est vide.
    //
    // PLUS TARD (base de données) : c'est ici qu'on lira les tables avec QSqlQuery
    // et qu'on remplira m_achats, m_clients et m_materiels.
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

// ---------------------------------------------------------------------------
// Mise en forme
// ---------------------------------------------------------------------------

void AchatWindow::configurerTable()
{
    QHeaderView *entete = ui->tableAchats->horizontalHeader();
    entete->setSectionResizeMode(QHeaderView::Stretch);               // colonnes réparties sur toute la largeur
    entete->setSectionResizeMode(0, QHeaderView::ResizeToContents);   // sauf « N° » : juste la place utile
    entete->setMinimumSectionSize(80);
    entete->setFixedHeight(48);
    entete->setHighlightSections(false);
    entete->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->tableAchats->verticalHeader()->setDefaultSectionSize(56);     // lignes de 56 px comme la maquette

    // Les colonnes « Qté » (3) et « Montant » (5) sont alignées à droite, titre compris.
    for (int colonne : {3, 5}) {
        if (QTableWidgetItem *titre = ui->tableAchats->horizontalHeaderItem(colonne))
            titre->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}

void AchatWindow::ajouterIcones()
{
    using AchatsUi::Icone;

    // Dans les gros boutons : un rond blanc translucide (22 % d'opacité) avec l'icône en blanc.
    const QColor voile(255, 255, 255, 56);
    const QColor blanc(Qt::white);
    const int diametre = 48;
    const int marge = 14;     // espace entre le rond et le texte
    const QSize tailleIcone(diametre + marge, diametre);

    ui->btnNouveau->setIcon(QIcon(AchatsUi::pastille(Icone::Plus, diametre, voile, voile, blanc, marge)));
    ui->btnModifier->setIcon(QIcon(AchatsUi::pastille(Icone::Crayon, diametre, voile, voile, blanc, marge)));
    ui->btnFacture->setIcon(QIcon(AchatsUi::pastille(Icone::Document, diametre, voile, voile, blanc, marge)));
    ui->btnSupprimer->setIcon(QIcon(AchatsUi::pastille(Icone::Corbeille, diametre, voile, voile, blanc, marge)));
    for (QPushButton *bouton : {ui->btnNouveau, ui->btnModifier, ui->btnFacture, ui->btnSupprimer})
        bouton->setIconSize(tailleIcone);

    // Le rond orange avec le panier, à gauche du titre « Achats ».
    ui->iconeTitre->setFixedSize(56, 56);
    ui->iconeTitre->setPixmap(AchatsUi::pastille(Icone::Panier, 56, QColor("#EA7210"), QColor("#D95F08"), blanc));

    // La loupe dans le champ de recherche.
    ui->iconeRecherche->setFixedSize(24, 24);
    ui->iconeRecherche->setPixmap(AchatsUi::icone(Icone::Loupe, 24, QColor("#7A5C45")));
}

// ---------------------------------------------------------------------------
// Tableau
// ---------------------------------------------------------------------------

bool AchatWindow::correspond(const Achat &achat, const QString &recherche)
{
    if (recherche.isEmpty())
        return true;

    // On cherche dans le nom du client (sans tenir compte des majuscules)
    // ou dans son numéro de téléphone (sans tenir compte des espaces).
    if (achat.nomClient().contains(recherche, Qt::CaseInsensitive))
        return true;
    const QString telephoneRecherche = sansEspaces(recherche);
    return !telephoneRecherche.isEmpty()
           && sansEspaces(achat.telephoneClient()).contains(telephoneRecherche);
}

void AchatWindow::rafraichir()
{
    const int idAGarder = idSelectionne();                 // pour remettre la sélection ensuite
    const QString recherche = ui->champRecherche->text().trimmed();

    ui->tableAchats->setRowCount(0);                       // vide le tableau (supprime les anciennes cellules)

    double total = 0.0;
    int ligneASelectionner = -1;

    for (const Achat &achat : std::as_const(m_achats)) {
        if (!correspond(achat, recherche))
            continue;

        const int ligne = ui->tableAchats->rowCount();
        ui->tableAchats->insertRow(ligne);

        // La 1re cellule garde le numéro de l'achat en « donnée cachée » (Qt::UserRole).
        // Ainsi, même si la recherche change l'ordre des lignes, on retrouve le bon achat.
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
=======
void AchatWindow::chargerTable()
{
    const int idAchatAGarder = idSelectionne();
    ui->tableAchats->setRowCount(0);

    const QString texte = ui->champRecherche->text().trimmed();
    const QString motif = "%" + texte + "%";
    QString numeroTelephone = texte;
    numeroTelephone.remove(QRegularExpression("\\D"));
    const QString motifTelephone = numeroTelephone.isEmpty() ? QStringLiteral("!aucun-numero!")
                                                             : "%" + numeroTelephone + "%";
    QSqlQuery requete;
    requete.prepare("SELECT a.id_achat, COALESCE(c.nom, ''), COALESCE(m.designation, ''), "
              "a.qte, COALESCE(a.date_achat, ''), "
              "a.qte * COALESCE(m.prix_unitaire, 0) "
              "FROM achat a "
              "LEFT JOIN client c ON a.id_client = c.id_client "
              "LEFT JOIN materiel m ON a.id_materiel = m.id_materiel "
              "WHERE CAST(a.id_achat AS TEXT) LIKE ? OR c.nom LIKE ? "
              "OR m.designation LIKE ? OR a.date_achat LIKE ? "
              "OR REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(COALESCE(c.telephone, ''), ' ', ''), '-', ''), '(', ''), ')', ''), '+', ''), '.', ''), '/', '') LIKE ? "
              "ORDER BY a.id_achat ASC");
    requete.addBindValue(motif);
    requete.addBindValue(motif);
    requete.addBindValue(motif);
    requete.addBindValue(motif);
    requete.addBindValue(motifTelephone);
    if (!requete.exec()) {
        ui->labelAide->setText(tr("Impossible de charger les achats : %1").arg(requete.lastError().text()));
        ui->labelTotalValeur->setText(enAriary(0));
        return;
    }

    double total = 0;
    while (requete.next()) {
        const int ligne = ui->tableAchats->rowCount();
        ui->tableAchats->insertRow(ligne);

        for (int colonne = 0; colonne < 6; ++colonne) {
            QString contenu = requete.value(colonne).toString();
            if (colonne == 5)
                contenu = enAriary(requete.value(5).toDouble());

            auto *cellule = new QTableWidgetItem(contenu);
            if (colonne == 3 || colonne == 5)
                cellule->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->tableAchats->setItem(ligne, colonne, cellule);
        }

        total += requete.value(5).toDouble();
        if (requete.value(0).toInt() == idAchatAGarder)
            ui->tableAchats->selectRow(ligne);
    }

    ui->labelTotalValeur->setText(enAriary(total));

    if (ui->tableAchats->rowCount() > 0)
        ui->labelAide->setText(tr("Sélectionnez un achat pour le modifier, le supprimer ou éditer sa facture."));
    else if (texte.isEmpty())
        ui->labelAide->setText(tr("Aucun achat enregistré pour le moment."));
    else
        ui->labelAide->setText(tr("Aucun achat ne correspond à cette recherche."));
>>>>>>> 8c2295e (Crafting)
}

int AchatWindow::idSelectionne() const
{
<<<<<<< HEAD
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
    return maximum + 1;    // jamais de doublon, même après une suppression
}

// ---------------------------------------------------------------------------
// Les 4 actions
// ---------------------------------------------------------------------------

void AchatWindow::onNouveau()
{
    NouveauAchatDialog dialogue(this);
    dialogue.setClients(m_clients);
    dialogue.setMateriels(m_materiels);

    if (dialogue.exec() != QDialog::Accepted)
        return;

    Achat nouveau = dialogue.getAchat();
    nouveau.setIdAchat(prochainId());

    // PLUS TARD (base de données) :
    //   INSERT INTO Achat ...  puis  UPDATE Materiel SET stockActuel = stockActuel - qte
    m_achats.append(nouveau);
    rafraichir();
=======
    const QList<QTableWidgetItem *> choix = ui->tableAchats->selectedItems();
    if (choix.isEmpty())
        return -1;
    return ui->tableAchats->item(choix.first()->row(), 0)->text().toInt();
}

int AchatWindow::idChoisi(const QString &titre)
{
    const int id = idSelectionne();
    if (id < 0)
    {
        afficherAlerteSelection(this, titre.toLower());
        ui->tableAchats->setFocus();
    }
    return id;
}

void AchatWindow::onNouveau()
{
    NouveauAchat fenetre(0, this);
    if (fenetre.exec() == QDialog::Accepted)
        chargerTable();
>>>>>>> 8c2295e (Crafting)
}

void AchatWindow::onModifier()
{
<<<<<<< HEAD
    const int index = indexParId(idSelectionne());
    if (index < 0) {
        QMessageBox::information(this, QStringLiteral("Modifier"),
                                 QStringLiteral("Sélectionnez d'abord un achat dans le tableau."));
        return;
    }

    NouveauAchatDialog dialogue(this);
    dialogue.setClients(m_clients);          // d'abord les listes...
    dialogue.setMateriels(m_materiels);
    dialogue.setAchat(m_achats.at(index));   // ...ensuite l'achat à modifier (il présélectionne client et matériel)

    if (dialogue.exec() != QDialog::Accepted)
        return;

    // PLUS TARD (base de données) :
    //   UPDATE Achat ...  et ajuster le stock du matériel (différence entre ancienne et nouvelle quantité)
    m_achats[index] = dialogue.getAchat();   // getAchat() garde le même numéro d'achat
    rafraichir();
=======
    const int id = idChoisi(tr("modifier"));
    if (id < 0)
        return;

    NouveauAchat fenetre(id, this);
    if (fenetre.exec() == QDialog::Accepted)
        chargerTable();
>>>>>>> 8c2295e (Crafting)
}

void AchatWindow::onFacture()
{
<<<<<<< HEAD
    const int index = indexParId(idSelectionne());
    if (index < 0) {
        QMessageBox::information(this, QStringLiteral("Facture PDF"),
                                 QStringLiteral("Sélectionnez un achat : la facture sera celle de son client."));
        return;
    }

    // La facture regroupe TOUS les achats du client de la ligne sélectionnée.
    const QString numClient = m_achats.at(index).numClient();
    ListeAchats achatsDuClient;
    for (const Achat &achat : std::as_const(m_achats)) {
        if (achat.numClient() == numClient)
            achatsDuClient.append(achat);
    }

    FactureDialog dialogue(achatsDuClient, this);
    dialogue.exec();
=======
    auto *selection = ui->tableAchats->selectionModel();
    if (!selection || selection->selectedRows(0).isEmpty()) {
        afficherAlerteSelection(this, tr("générer une facture"));
        ui->tableAchats->setFocus();
        return;
    }

    QList<int> identifiants;
    const QModelIndexList lignes = selection->selectedRows(0);
    identifiants.reserve(lignes.size());
    for (const QModelIndex &index : lignes) {
        const auto *cellule = ui->tableAchats->item(index.row(), 0);
        if (cellule)
            identifiants.append(cellule->text().toInt());
    }

    if (identifiants.isEmpty()) {
        afficherAlerteSelection(this, tr("générer une facture"));
        ui->tableAchats->setFocus();
        return;
    }

    Facture fenetre(identifiants, this);
    fenetre.exec();
>>>>>>> 8c2295e (Crafting)
}

void AchatWindow::onSupprimer()
{
<<<<<<< HEAD
    const int index = indexParId(idSelectionne());
    if (index < 0) {
        QMessageBox::information(this, QStringLiteral("Supprimer"),
                                 QStringLiteral("Sélectionnez d'abord un achat dans le tableau."));
        return;
    }

    SupprimerAchatDialog dialogue(m_achats.at(index), this);
    if (dialogue.exec() != QDialog::Accepted)
        return;

    // PLUS TARD (base de données) :
    //   DELETE FROM Achat ...  puis  UPDATE Materiel SET stockActuel = stockActuel + qte
    m_achats.removeAt(index);
    rafraichir();
=======
    const int id = idChoisi(tr("supprimer"));
    if (id < 0)
        return;

    SupprimerAchat fenetre(id, this);
    if (fenetre.exec() == QDialog::Accepted)
        chargerTable();
>>>>>>> 8c2295e (Crafting)
}
