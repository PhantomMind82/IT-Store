#include "clientwindow.h"

#include <QLabel>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QRegularExpression>
#include <QDebug>
#include <QIcon>
#include <QStyle>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

// ============================================================
//  Fonctions utilitaires d'interface (locales à ce fichier)
// ============================================================
namespace {

QPushButton *creerBouton(QWidget *parent, const QString &texte,
                         QStyle::StandardPixmap icone, const QString &nom)
{
    auto *b = new QPushButton(texte, parent);
    b->setObjectName(nom);
    b->setIcon(parent->style()->standardIcon(icone));
    b->setIconSize(QSize(20, 20));
    b->setCursor(Qt::PointingHandCursor);
    b->setAutoDefault(false);   // évite que "Entrée" déclenche ce bouton
    return b;
}

QFrame *creerCarte(const QString &icone, const QString &titre, QWidget *corps)
{
    auto *carte = new QFrame;
    carte->setObjectName("carte");

    auto *lay = new QVBoxLayout(carte);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);

    auto *entete = new QWidget;
    entete->setObjectName("carteEntete");
    entete->setAttribute(Qt::WA_StyledBackground, true);
    entete->setFixedHeight(40);

    auto *ic = new QLabel(icone);
    ic->setObjectName("carteIcone");
    auto *tt = new QLabel(titre);
    tt->setObjectName("carteTitre");

    auto *layEnt = new QHBoxLayout(entete);
    layEnt->setContentsMargins(18, 0, 18, 0);
    layEnt->setSpacing(10);
    layEnt->addWidget(ic);
    layEnt->addWidget(tt);
    layEnt->addStretch();

    corps->setObjectName("carteCorps");
    corps->setAttribute(Qt::WA_StyledBackground, true);

    lay->addWidget(entete);
    lay->addWidget(corps, 1);
    return carte;
}

QHBoxLayout *creerLigneRecherche(QWidget *parent, QComboBox *&combo,
                                 QLineEdit *&champ, QPushButton *&btn)
{
    auto *lbl = new QLabel("Rechercher par :", parent);
    lbl->setObjectName("etiquetteGras");

    combo = new QComboBox(parent);
    combo->addItems({"Nom", "Numéro"});
    combo->setMinimumWidth(110);

    champ = new QLineEdit(parent);
    champ->setPlaceholderText("Entrez le nom ou numéro");

    btn = new QPushButton(QString::fromUtf8("🔍"), parent);
    btn->setObjectName("btnRecherche");
    btn->setCursor(Qt::PointingHandCursor);
    btn->setAutoDefault(false);
    btn->setFixedSize(58, 32);

    auto *lay = new QHBoxLayout;
    lay->setSpacing(8);
    lay->addWidget(lbl);
    lay->addWidget(combo);
    lay->addWidget(champ, 1);
    lay->addWidget(btn);
    return lay;
}

QFrame *creerBlocResultat(QWidget *parent, QLineEdit *&num, QLineEdit *&nom,
                          QLineEdit *&tel, bool lectureSeule)
{
    auto *bloc = new QFrame(parent);
    bloc->setObjectName("resultat");

    num = new QLineEdit("---", bloc);
    num->setReadOnly(true);
    nom = new QLineEdit(bloc);
    tel = new QLineEdit(bloc);
    nom->setReadOnly(lectureSeule);
    tel->setReadOnly(lectureSeule);

    auto *form = new QFormLayout(bloc);
    form->setContentsMargins(12, 8, 12, 8);
    form->setHorizontalSpacing(18);
    form->setVerticalSpacing(5);
    form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    form->addRow("N° Client :", num);
    form->addRow("Nom :", nom);
    form->addRow("Téléphone :", tel);
    return bloc;
}

} // namespace

// ============================================================
//  Fenêtre
// ============================================================
ClientWindow::ClientWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("IT Store"));

    // Boutons Windows standard : réduire, agrandir/restaurer, fermer
    setWindowFlags(Qt::Window
                   | Qt::WindowTitleHint
                   | Qt::WindowSystemMenuHint
                   | Qt::WindowMinMaxButtonsHint
                   | Qt::WindowCloseButtonHint);

    // Taille adaptée à l'écran
    const QRect dispo = QGuiApplication::primaryScreen()->availableGeometry();
    resize(qMin(1100, dispo.width() - 60), qMin(700, dispo.height() - 60));
    setMinimumSize(760, 480);

    creerUI();
    chargerStyle();

    // La connexion est ouverte une seule fois dans main() (voir database.h)
    if (QSqlDatabase::database().isOpen())
        chargerClients();
}

void ClientWindow::chargerStyle()
{
    const QStringList chemins = {
        QCoreApplication::applicationDirPath() + "/styles/client.qss",
        QString(STYLES_DIR) + "/client.qss"
    };

    for (const QString &chemin : chemins) {
        QFile file(chemin);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            setStyleSheet(QString::fromUtf8(file.readAll()));
            qDebug() << "QSS charge :" << chemin;
            return;
        }
        qWarning() << "QSS introuvable :" << chemin << file.errorString();
    }
}

// ============================================================
//  Base de données
// ============================================================
void ClientWindow::chargerClients()
{
    m_table->setRowCount(0);

    QSqlQuery q;
    if (!q.exec("SELECT id_client, nom, telephone FROM client ORDER BY id_client")) {
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Lecture des clients impossible :\n%1").arg(q.lastError().text()));
        return;
    }

    while (q.next()) {
        const int r = m_table->rowCount();
        m_table->insertRow(r);
        m_table->setItem(r, 0, new QTableWidgetItem(formaterId(q.value(0).toInt())));
        m_table->setItem(r, 1, new QTableWidgetItem(q.value(1).toString()));
        m_table->setItem(r, 2, new QTableWidgetItem(formaterTel(q.value(2).toString())));
    }
}

bool ClientWindow::rechercherClient(const QString &critere, const QString &texte,
                                    Client &resultat, int &total)
{
    total = 0;
    resultat = Client();

    QSqlQuery q;
    if (critere == "Nom") {
        q.prepare("SELECT id_client, nom, telephone FROM client "
                  "WHERE nom LIKE ? ORDER BY nom");
        q.addBindValue("%" + texte + "%");
    } else {
        const QString chiffres = nettoyerTel(texte);
        static const QRegularExpression courtNombre("^\\d{1,5}$");
        if (courtNombre.match(chiffres).hasMatch()) {
            // Numéro court : on cherche par identifiant (001, 2, ...)
            q.prepare("SELECT id_client, nom, telephone FROM client "
                      "WHERE id_client = ?");
            q.addBindValue(chiffres.toInt());
        } else {
            // Sinon : numéro de téléphone
            q.prepare("SELECT id_client, nom, telephone FROM client "
                      "WHERE telephone LIKE ? ORDER BY id_client");
            q.addBindValue("%" + chiffres + "%");
        }
    }

    if (!q.exec()) {
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Recherche impossible :\n%1").arg(q.lastError().text()));
        return false;
    }

    while (q.next()) {
        if (total == 0) {
            resultat.id  = q.value(0).toInt();
            resultat.nom = q.value(1).toString();
            resultat.tel = q.value(2).toString();
        }
        ++total;
    }
    return true;
}

// ============================================================
//  Actions
// ============================================================
void ClientWindow::ajouterClient()
{
    const QString nom = m_ajoutNom->text().trimmed();
    const QString tel = nettoyerTel(m_ajoutTel->text());

    if (nom.isEmpty()) {
        QMessageBox::warning(this, tr("Ajout"), tr("Veuillez saisir le nom du client."));
        m_ajoutNom->setFocus();
        return;
    }
    if (!telValide(tel)) {
        QMessageBox::warning(this, tr("Ajout"),
                             tr("Numéro de téléphone invalide (8 à 13 chiffres)."));
        m_ajoutTel->setFocus();
        return;
    }

    QSqlQuery q;
    q.prepare("INSERT INTO client(nom, telephone) VALUES(?, ?)");
    q.addBindValue(nom);
    q.addBindValue(tel);
    if (!q.exec()) {
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Ajout impossible :\n%1").arg(q.lastError().text()));
        return;
    }

    const int id = q.lastInsertId().toInt();
    chargerClients();            // mise à jour de la liste
    reinitialiserAjout();
    QMessageBox::information(this, tr("Ajout"),
                             tr("Client %1 ajouté avec succès.").arg(formaterId(id)));
}

void ClientWindow::rechercherPourModification()
{
    const QString texte = m_modRecherche->text().trimmed();
    if (texte.isEmpty()) {
        QMessageBox::warning(this, tr("Recherche"), tr("Veuillez saisir une valeur à rechercher."));
        return;
    }

    Client c;
    int total = 0;
    if (!rechercherClient(m_modCritere->currentText(), texte, c, total))
        return;

    if (total == 0) {
        reinitialiserModification();
        m_modRecherche->setText(texte);
        QMessageBox::information(this, tr("Recherche"), tr("Aucun client trouvé."));
        return;
    }

    m_modId = c.id;
    m_modNum->setText(formaterId(c.id));
    m_modNom->setText(c.nom);
    m_modTel->setText(formaterTel(c.tel));

    if (total > 1)
        QMessageBox::information(this, tr("Recherche"),
                                 tr("%1 clients correspondent. Le premier est affiché ; "
                                    "précisez la recherche si besoin.").arg(total));
}

void ClientWindow::modifierClient()
{
    if (m_modId < 0) {
        QMessageBox::warning(this, tr("Modification"),
                             tr("Recherchez d'abord le client à modifier."));
        return;
    }

    const QString nom = m_modNom->text().trimmed();
    const QString tel = nettoyerTel(m_modTel->text());

    if (nom.isEmpty()) {
        QMessageBox::warning(this, tr("Modification"), tr("Le nom ne peut pas être vide."));
        m_modNom->setFocus();
        return;
    }
    if (!telValide(tel)) {
        QMessageBox::warning(this, tr("Modification"),
                             tr("Numéro de téléphone invalide (8 à 13 chiffres)."));
        m_modTel->setFocus();
        return;
    }

    QSqlQuery q;
    q.prepare("UPDATE client SET nom = ?, telephone = ? WHERE id_client = ?");
    q.addBindValue(nom);
    q.addBindValue(tel);
    q.addBindValue(m_modId);
    if (!q.exec()) {
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Modification impossible :\n%1").arg(q.lastError().text()));
        return;
    }

    const int id = m_modId;
    chargerClients();            // mise à jour de la liste
    if (m_supId == id)           // la carte "Supprimer" affichait l'ancienne valeur
        reinitialiserSuppression();
    reinitialiserModification();
    QMessageBox::information(this, tr("Modification"),
                             tr("Client %1 modifié avec succès.").arg(formaterId(id)));
}

void ClientWindow::rechercherPourSuppression()
{
    const QString texte = m_supRecherche->text().trimmed();
    if (texte.isEmpty()) {
        QMessageBox::warning(this, tr("Recherche"), tr("Veuillez saisir une valeur à rechercher."));
        return;
    }

    Client c;
    int total = 0;
    if (!rechercherClient(m_supCritere->currentText(), texte, c, total))
        return;

    if (total == 0) {
        reinitialiserSuppression();
        m_supRecherche->setText(texte);
        QMessageBox::information(this, tr("Recherche"), tr("Aucun client trouvé."));
        return;
    }

    m_supId = c.id;
    m_supNum->setText(formaterId(c.id));
    m_supNom->setText(c.nom);
    m_supTel->setText(formaterTel(c.tel));

    if (total > 1)
        QMessageBox::information(this, tr("Recherche"),
                                 tr("%1 clients correspondent. Le premier est affiché ; "
                                    "précisez la recherche si besoin.").arg(total));
}

void ClientWindow::supprimerClient()
{
    if (m_supId < 0) {
        QMessageBox::warning(this, tr("Suppression"),
                             tr("Recherchez d'abord le client à supprimer."));
        return;
    }

    // Un client qui a des achats ne peut pas être supprimé (clé étrangère)
    QSqlQuery cnt;
    cnt.prepare("SELECT COUNT(*) FROM achat WHERE id_client = ?");
    cnt.addBindValue(m_supId);
    if (cnt.exec() && cnt.next() && cnt.value(0).toInt() > 0) {
        QMessageBox::warning(this, tr("Suppression impossible"),
                             tr("Le client %1 a %2 achat(s) enregistré(s).\n"
                                "Il ne peut pas être supprimé.")
                                 .arg(formaterId(m_supId)).arg(cnt.value(0).toInt()));
        return;
    }

    QMessageBox box(QMessageBox::Question, tr("Confirmation"),
                    tr("Supprimer définitivement le client %1 - %2 ?")
                        .arg(formaterId(m_supId), m_supNom->text()),
                    QMessageBox::NoButton, this);
    QPushButton *oui = box.addButton(tr("Supprimer"), QMessageBox::DestructiveRole);
    box.addButton(tr("Annuler"), QMessageBox::RejectRole);
    box.exec();
    if (box.clickedButton() != oui)
        return;

    QSqlQuery q;
    q.prepare("DELETE FROM client WHERE id_client = ?");
    q.addBindValue(m_supId);
    if (!q.exec()) {
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Suppression impossible :\n%1").arg(q.lastError().text()));
        return;
    }

    const int id = m_supId;
    chargerClients();            // mise à jour de la liste
    if (m_modId == id)           // la carte "Modifier" affichait ce client
        reinitialiserModification();
    reinitialiserSuppression();
    QMessageBox::information(this, tr("Suppression"),
                             tr("Client %1 supprimé.").arg(formaterId(id)));
}

void ClientWindow::reinitialiserAjout()
{
    m_ajoutNom->clear();
    m_ajoutTel->clear();
}

void ClientWindow::reinitialiserModification()
{
    m_modId = -1;
    m_modRecherche->clear();
    m_modNum->setText("---");
    m_modNom->clear();
    m_modTel->clear();
}

void ClientWindow::reinitialiserSuppression()
{
    m_supId = -1;
    m_supRecherche->clear();
    m_supNum->setText("---");
    m_supNom->clear();
    m_supTel->clear();
}

// ============================================================
//  Utilitaires
// ============================================================
QString ClientWindow::formaterId(int id)
{
    return QString("%1").arg(id, 3, 10, QChar('0'));   // 1 -> "001"
}

QString ClientWindow::nettoyerTel(const QString &t)
{
    static const QRegularExpression separateurs("[\\s.\\-]");
    QString r = t;
    return r.remove(separateurs);
}

bool ClientWindow::telValide(const QString &t)
{
    static const QRegularExpression re("^\\+?\\d{8,13}$");
    return re.match(t).hasMatch();
}

QString ClientWindow::formaterTel(const QString &t)
{
    // 0341234567 -> 034 12 345 67 ; autres formats : affichés tels quels
    static const QRegularExpression dixChiffres("^\\d{10}$");
    if (dixChiffres.match(t).hasMatch())
        return t.left(3) + " " + t.mid(3, 2) + " " + t.mid(5, 3) + " " + t.mid(8, 2);
    return t;
}

// ============================================================
//  Cartes
// ============================================================
QWidget *ClientWindow::creerCarteAjout()
{
    auto *corps = new QWidget;

    m_ajoutNom = new QLineEdit;
    m_ajoutNom->setPlaceholderText("Entrez le nom du client");
    m_ajoutTel = new QLineEdit;
    m_ajoutTel->setPlaceholderText("Entrez le numéro de téléphone");

    auto *btnEnreg = creerBouton(corps, "Enregistrer",
                                 QStyle::SP_DialogSaveButton, "btnPrimaire");
    auto *btnReset = creerBouton(corps, "Réinitialiser",
                                 QStyle::SP_BrowserReload, "btnSecondaire");

    auto *boutons = new QHBoxLayout;
    boutons->setSpacing(14);
    boutons->addWidget(btnEnreg);
    boutons->addWidget(btnReset);
    boutons->addStretch();

    auto *form = new QFormLayout(corps);
    form->setContentsMargins(22, 16, 22, 16);
    form->setHorizontalSpacing(22);
    form->setVerticalSpacing(12);
    form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    form->addRow("Nom :", m_ajoutNom);
    form->addRow("Téléphone :", m_ajoutTel);
    form->addRow(QString(), boutons);

    connect(btnEnreg, &QPushButton::clicked, this, &ClientWindow::ajouterClient);
    connect(btnReset, &QPushButton::clicked, this, &ClientWindow::reinitialiserAjout);
    connect(m_ajoutTel, &QLineEdit::returnPressed, btnEnreg, &QPushButton::click);

    return creerCarte(QString::fromUtf8("👤"), "1.  Ajouter un client", corps);
}

QWidget *ClientWindow::creerCarteModification()
{
    auto *corps = new QWidget;

    QPushButton *btnRech = nullptr;
    auto *ligne = creerLigneRecherche(corps, m_modCritere, m_modRecherche, btnRech);
    auto *bloc  = creerBlocResultat(corps, m_modNum, m_modNom, m_modTel, false);

    auto *btnEnreg = creerBouton(corps, "Enregistrer la modification",
                                 QStyle::SP_DialogSaveButton, "btnPrimaire");
    auto *btnReset = creerBouton(corps, "Réinitialiser",
                                 QStyle::SP_BrowserReload, "btnSecondaire");

    auto *boutons = new QHBoxLayout;
    boutons->setSpacing(14);
    boutons->addStretch();
    boutons->addWidget(btnEnreg);
    boutons->addWidget(btnReset);
    boutons->addStretch();

    auto *lay = new QVBoxLayout(corps);
    lay->setContentsMargins(18, 12, 18, 12);
    lay->setSpacing(8);
    lay->addLayout(ligne);
    lay->addWidget(bloc);
    lay->addLayout(boutons);
    lay->addStretch();

    connect(btnRech,        &QPushButton::clicked, this, &ClientWindow::rechercherPourModification);
    connect(m_modRecherche, &QLineEdit::returnPressed, btnRech, &QPushButton::click);
    connect(btnEnreg,       &QPushButton::clicked, this, &ClientWindow::modifierClient);
    connect(btnReset,       &QPushButton::clicked, this, &ClientWindow::reinitialiserModification);

    return creerCarte(QString::fromUtf8("✏️"), "2.  Modifier un client", corps);
}

QWidget *ClientWindow::creerCarteSuppression()
{
    auto *corps = new QWidget;

    QPushButton *btnRech = nullptr;
    auto *ligne = creerLigneRecherche(corps, m_supCritere, m_supRecherche, btnRech);
    auto *bloc  = creerBlocResultat(corps, m_supNum, m_supNom, m_supTel, true);

    auto *btnSuppr = creerBouton(corps, "Supprimer",
                                 QStyle::SP_TrashIcon, "btnDanger");
    auto *btnReset = creerBouton(corps, "Réinitialiser",
                                 QStyle::SP_BrowserReload, "btnSecondaire");

    auto *boutons = new QHBoxLayout;
    boutons->setSpacing(14);
    boutons->addStretch();
    boutons->addWidget(btnSuppr);
    boutons->addWidget(btnReset);
    boutons->addStretch();

    auto *lay = new QVBoxLayout(corps);
    lay->setContentsMargins(18, 12, 18, 12);
    lay->setSpacing(8);
    lay->addLayout(ligne);
    lay->addWidget(bloc);
    lay->addLayout(boutons);
    lay->addStretch();

    connect(btnRech,        &QPushButton::clicked, this, &ClientWindow::rechercherPourSuppression);
    connect(m_supRecherche, &QLineEdit::returnPressed, btnRech, &QPushButton::click);
    connect(btnSuppr,       &QPushButton::clicked, this, &ClientWindow::supprimerClient);
    connect(btnReset,       &QPushButton::clicked, this, &ClientWindow::reinitialiserSuppression);

    return creerCarte(QString::fromUtf8("🗑️"), "3.  Supprimer un client", corps);
}

QWidget *ClientWindow::creerCarteListe()
{
    auto *corps = new QWidget;

    m_table = new QTableWidget(0, 3, corps);
    m_table->setHorizontalHeaderLabels({"N° Client", "Nom", "Téléphone"});
    m_table->verticalHeader()->hide();
    m_table->verticalHeader()->setDefaultSectionSize(30);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setAlternatingRowColors(true);
    m_table->setShowGrid(false);
    m_table->setFocusPolicy(Qt::NoFocus);
    m_table->setMinimumHeight(170);

    auto *h = m_table->horizontalHeader();
    h->setSectionResizeMode(QHeaderView::Stretch);
    h->setSectionResizeMode(0, QHeaderView::Fixed);
    h->resizeSection(0, 110);
    h->setHighlightSections(false);
    h->setFixedHeight(30);

    auto *lay = new QVBoxLayout(corps);
    lay->setContentsMargins(18, 12, 18, 12);
    lay->addWidget(m_table);

    return creerCarte(QString::fromUtf8("📋"), "4.  Liste des clients", corps);
}

// ============================================================
//  Construction globale
// ============================================================
void ClientWindow::creerUI()
{
    // ===== Conteneur racine =====
    QWidget *central = new QWidget(this);
    central->setObjectName("central");
    central->setAttribute(Qt::WA_StyledBackground, true);

    QVBoxLayout *racine = new QVBoxLayout(this);
    racine->setContentsMargins(0, 0, 0, 0);
    racine->setSpacing(0);
    racine->addWidget(central);

    QVBoxLayout *principal = new QVBoxLayout(central);
    principal->setContentsMargins(0, 0, 0, 0);
    principal->setSpacing(0);

    // ===== En-tête =====
    QWidget *entete = new QWidget(central);
    entete->setObjectName("entete");
    entete->setAttribute(Qt::WA_StyledBackground, true);
    entete->setFixedHeight(64);

    QLabel *logo = new QLabel(QString::fromUtf8("🏷️  IT Store"), entete);
    logo->setObjectName("logo");

    QLabel *slogan = new QLabel(tr("Votre partenaire en matériel informatique"), entete);
    slogan->setObjectName("slogan");

    QHBoxLayout *layEntete = new QHBoxLayout(entete);
    layEntete->setContentsMargins(32, 0, 32, 0);
    layEntete->addWidget(logo);
    layEntete->addStretch();
    layEntete->addWidget(slogan);

    // ===== Titre de la page =====
    QWidget *titre = new QWidget(central);
    titre->setObjectName("titre");
    titre->setAttribute(Qt::WA_StyledBackground, true);
    titre->setFixedHeight(76);

    QLabel *icon_titre = new QLabel(QString::fromUtf8("👥"), titre);
    icon_titre->setObjectName("icon_titre");

    QLabel *text_titre = new QLabel(tr("Gestion des Clients"), titre);
    text_titre->setObjectName("text_titre");

    QLabel *sous_titre = new QLabel(tr("Ajouter, modifier, supprimer et consulter les clients"), titre);
    sous_titre->setObjectName("sous_titre");

    QVBoxLayout *textes = new QVBoxLayout;
    textes->setSpacing(0);
    textes->addStretch();
    textes->addWidget(text_titre);
    textes->addWidget(sous_titre);
    textes->addStretch();

    QHBoxLayout *titre_layout = new QHBoxLayout(titre);
    titre_layout->setContentsMargins(32, 0, 32, 0);
    titre_layout->setSpacing(12);
    titre_layout->addWidget(icon_titre);
    titre_layout->addLayout(textes);
    titre_layout->addStretch();

    // ===== Grille des 4 cartes (dans une zone défilante) =====
    QWidget *contenu = new QWidget;
    contenu->setObjectName("contenu");

    QGridLayout *grille = new QGridLayout(contenu);
    grille->setContentsMargins(32, 8, 32, 20);
    grille->setHorizontalSpacing(16);
    grille->setVerticalSpacing(12);
    grille->setColumnStretch(0, 1);
    grille->setColumnStretch(1, 1);

    grille->addWidget(creerCarteAjout(),        0, 0);
    grille->addWidget(creerCarteModification(), 0, 1);
    grille->addWidget(creerCarteSuppression(),  1, 0);
    grille->addWidget(creerCarteListe(),        1, 1);

    // Si la fenêtre est trop petite, un ascenseur apparaît au lieu de couper
    QScrollArea *zone = new QScrollArea(central);
    zone->setObjectName("zoneDefilement");
    zone->setWidgetResizable(true);
    zone->setFrameShape(QFrame::NoFrame);
    zone->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    zone->setWidget(contenu);

    // ===== Assemblage =====
    principal->addWidget(entete);
    principal->addWidget(titre);
    principal->addWidget(zone, 1);
}