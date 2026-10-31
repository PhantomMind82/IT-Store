#include "nouveauachatdialog.h"
#include "ui_nouveauachatdialog.h"

#include "achats/achatsui.h"
#include "achats/achatstyle.h"

#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>

#include <utility>

NouveauAchatDialog::NouveauAchatDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::NouveauAchatDialog)
{
    ui->setupUi(this);
    setStyleSheet(AchatStyle::saisieAchat());

    // Texte grisé affiché tant que rien n'est choisi dans les menus déroulants.
    ui->comboClient->setPlaceholderText(QStringLiteral("Choisir un client"));
    ui->comboMateriel->setPlaceholderText(QStringLiteral("Choisir un matériel"));

    ui->dateEdit->setDate(QDate::currentDate());   // par défaut : aujourd'hui
    ui->labelErreur->hide();

    // Dès qu'on change le client, le matériel ou la quantité : on recalcule le résumé.
    connect(ui->comboClient, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &NouveauAchatDialog::mettreAJourResume);
    connect(ui->comboMateriel, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &NouveauAchatDialog::mettreAJourResume);
    connect(ui->spinQte, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &NouveauAchatDialog::mettreAJourResume);

    connect(ui->btnAnnuler, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btnEnregistrer, &QPushButton::clicked, this, &NouveauAchatDialog::onEnregistrer);

    mettreAJourResume();
}

NouveauAchatDialog::~NouveauAchatDialog()
{
    delete ui;
}

// ---------------------------------------------------------------------------
// Remplissage
// ---------------------------------------------------------------------------

void NouveauAchatDialog::setClients(const ListeClients &clients)
{
    m_clients = clients;
    remplirClients();
    appliquerPreselection();
}

void NouveauAchatDialog::setMateriels(const ListeMateriels &materiels)
{
    m_materiels = materiels;
    remplirMateriels();
    appliquerPreselection();
}

void NouveauAchatDialog::setAchat(const Achat &achat)
{
    m_modeEdition = true;
    m_achatInitial = achat;

    ui->titleLabel->setText(QStringLiteral("Modifier l'achat"));
    setWindowTitle(QStringLiteral("Modifier un achat"));
    ui->spinQte->setValue(qMax(1, achat.qte()));
    ui->dateEdit->setDate(achat.dateAchat().isValid() ? achat.dateAchat() : QDate::currentDate());

    appliquerPreselection();
    mettreAJourResume();
}

void NouveauAchatDialog::remplirClients()
{
    ui->comboClient->clear();
    for (const Client &client : std::as_const(m_clients)) {
        // Texte affiché : « 1 – Nathan » ; donnée cachée : le numéro du client.
        ui->comboClient->addItem(QStringLiteral("%1 – %2").arg(client.numClient(), client.nom()),
                                 client.numClient());
    }
    ui->comboClient->setCurrentIndex(-1);      // -1 = rien de choisi (le texte grisé s'affiche)
}

void NouveauAchatDialog::remplirMateriels()
{
    ui->comboMateriel->clear();
    for (const Materiel &materiel : std::as_const(m_materiels)) {
        // Texte affiché : « Moniteur – 190 000 Ar » ; donnée cachée : le numéro du matériel.
        ui->comboMateriel->addItem(QStringLiteral("%1 – %2")
                                       .arg(materiel.design(), AchatsUi::formatMontant(materiel.pu())),
                                   materiel.numMat());
    }
    ui->comboMateriel->setCurrentIndex(-1);
}

void NouveauAchatDialog::appliquerPreselection()
{
    if (!m_modeEdition)
        return;

    // findData() cherche dans les « données cachées » (ici les numéros).
    const int indexClient = ui->comboClient->findData(m_achatInitial.numClient());
    if (indexClient >= 0)
        ui->comboClient->setCurrentIndex(indexClient);

    const int indexMateriel = ui->comboMateriel->findData(m_achatInitial.numMat());
    if (indexMateriel >= 0)
        ui->comboMateriel->setCurrentIndex(indexMateriel);
}

// ---------------------------------------------------------------------------
// Choix courants
// ---------------------------------------------------------------------------

const Client *NouveauAchatDialog::clientChoisi() const
{
    if (ui->comboClient->currentIndex() < 0)
        return nullptr;

    const QString numero = ui->comboClient->currentData().toString();
    for (const Client &client : m_clients) {
        if (client.numClient() == numero)
            return &client;
    }
    return nullptr;
}

const Materiel *NouveauAchatDialog::materielChoisi() const
{
    if (ui->comboMateriel->currentIndex() < 0)
        return nullptr;

    const QString numero = ui->comboMateriel->currentData().toString();
    for (const Materiel &materiel : m_materiels) {
        if (materiel.numMat() == numero)
            return &materiel;
    }
    return nullptr;
}

int NouveauAchatDialog::quantiteDejaPrise() const
{
    // En modification, la quantité de l'achat d'origine a DÉJÀ été retirée du stock.
    // Si on garde le même matériel, on la « rend » avant de vérifier la nouvelle quantité.
    const Materiel *materiel = materielChoisi();
    if (m_modeEdition && materiel && materiel->numMat() == m_achatInitial.numMat())
        return m_achatInitial.qte();
    return 0;
}

// ---------------------------------------------------------------------------
// Résumé (stock + montant) et validation
// ---------------------------------------------------------------------------

void NouveauAchatDialog::mettreAJourResume()
{
    ui->labelErreur->hide();

    const Materiel *materiel = materielChoisi();
    if (!materiel) {
        ui->labelStock->setText(QStringLiteral("Stock actuel : —"));
        ui->labelStockInfo->setText(QStringLiteral("Choisissez un matériel"));
        ui->labelMontantValeur->setText(AchatsUi::formatMontant(0));
        return;
    }

    const int quantite = ui->spinQte->value();
    const int stockApres = materiel->stockActuel() + quantiteDejaPrise() - quantite;

    ui->labelStock->setText(QStringLiteral("Stock actuel : %1").arg(materiel->stockActuel()));
    if (stockApres >= 0) {
        ui->labelStockInfo->setText(QStringLiteral("Le stock passera de %1 à %2")
                                        .arg(materiel->stockActuel())
                                        .arg(stockApres));
    } else {
        ui->labelStockInfo->setText(QStringLiteral("Stock insuffisant"));
    }
    ui->labelMontantValeur->setText(AchatsUi::formatMontant(materiel->pu() * quantite));
}

QString NouveauAchatDialog::messageErreur() const
{
    if (!clientChoisi()) {
        return m_clients.isEmpty() ? QStringLiteral("Aucun client enregistré : ajoutez d'abord un client.")
                                   : QStringLiteral("Veuillez choisir un client.");
    }

    const Materiel *materiel = materielChoisi();
    if (!materiel) {
        return m_materiels.isEmpty() ? QStringLiteral("Aucun matériel enregistré : ajoutez d'abord un matériel.")
                                     : QStringLiteral("Veuillez choisir un matériel.");
    }

    const int disponible = materiel->stockActuel() + quantiteDejaPrise();
    if (ui->spinQte->value() > disponible) {
        return QStringLiteral("Stock insuffisant : %1 disponible(s) pour ce matériel.").arg(disponible);
    }
    return QString();   // aucune erreur
}

void NouveauAchatDialog::onEnregistrer()
{
    const QString erreur = messageErreur();
    if (!erreur.isEmpty()) {
        ui->labelErreur->setText(erreur);
        ui->labelErreur->show();
        return;                  // on reste dans la fenêtre
    }
    accept();                    // ferme la fenêtre avec le résultat « Accepted »
}

Achat NouveauAchatDialog::getAchat() const
{
    // On part de l'achat d'origine : en modification, cela garde son numéro (idAchat).
    Achat achat = m_achatInitial;

    const Client *client = clientChoisi();
    const Materiel *materiel = materielChoisi();
    if (!client || !materiel)
        return achat;            // ne devrait pas arriver : onEnregistrer() a déjà vérifié

    // Si le client a changé, l'ancien numéro de téléphone ne lui appartient plus.
    if (achat.numClient() != client->numClient())
        achat.setTelephoneClient(QString());

    achat.setNumClient(client->numClient());
    achat.setNomClient(client->nom());
    achat.setNumMat(materiel->numMat());
    achat.setDesignationMat(materiel->design());
    achat.setPrixUnitaire(materiel->pu());
    achat.setQte(ui->spinQte->value());
    achat.setDateAchat(ui->dateEdit->date());
    return achat;
}
