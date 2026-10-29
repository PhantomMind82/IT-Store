<<<<<<< HEAD
#include "clientwindow.h"
#include "commun/style.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ClientWindow::ClientWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("CLIENTS"));
    resize(760, 480);
    setStyleSheet(QStringLiteral("QDialog { background: %1; }").arg(Style::FOND_VIOLET));

    auto *module = new QLabel(tr("CLIENTS"), this);
    module->setAlignment(Qt::AlignCenter);
    module->setStyleSheet(QStringLiteral(
        "font-size: 24px; font-weight: bold; letter-spacing: 6px; color: %1;")
        .arg(Style::BLEU));

    auto *message = new QLabel(tr("EN COURS DE DÉVELOPPEMENT"), this);
    message->setAlignment(Qt::AlignCenter);
    message->setWordWrap(true);
    message->setStyleSheet(QStringLiteral(
        "font-size: 40px; font-weight: bold; color: %1;").arg(Style::BLEU_FONCE));

    auto *fermer = new QPushButton(tr("Fermer"), this);
    fermer->setCursor(Qt::PointingHandCursor);
    connect(fermer, &QPushButton::clicked, this, &QDialog::accept);

    auto *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(module);
    layout->addWidget(message);
    layout->addStretch();
    layout->addWidget(fermer, 0, Qt::AlignRight);

    // TODO : remplacer ce contenu par l'interface réelle du module
}
=======
#include "clientwindow.h"
#include "commun/style.h"

#include <QDialog>
#include <QFormLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

ClientWindow::ClientWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Gestion des clients"));
    resize(900, 560);
    setStyleSheet(QStringLiteral("QDialog { background: %1; }").arg(Style::FOND_VIOLET));

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(16);

    auto *titre = new QLabel(tr("Clients"), this);
    titre->setStyleSheet(QStringLiteral("font-size: 28px; font-weight: bold; color: %1;").arg(Style::BLEU_FONCE));
    auto *description = new QLabel(tr("Coordonnées et comptes clients"), this);
    description->setStyleSheet(QStringLiteral("color: %1;").arg(Style::BLEU));
    layout->addWidget(titre);
    layout->addWidget(description);

    auto *barre = new QHBoxLayout;
    auto *recherche = new QLineEdit(this);
    recherche->setPlaceholderText(tr("Rechercher par nom ou numéro client"));
    recherche->setClearButtonEnabled(true);
    barre->addWidget(recherche, 1);
    auto *ajouter = new QPushButton(tr("+  Nouveau client"), this);
    ajouter->setCursor(Qt::PointingHandCursor);
    barre->addWidget(ajouter);
    layout->addLayout(barre);

    auto *table = new QTableWidget(0, 2, this);
    table->setHorizontalHeaderLabels({tr("Numéro client"), tr("Nom")});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setMinimumHeight(260);
    layout->addWidget(table, 1);

    auto *etat = new QLabel(tr("La liste des clients sera chargée lorsque le backend sera raccordé."), this);
    etat->setStyleSheet(QStringLiteral("color: %1;").arg(Style::BLEU));
    layout->addWidget(etat);

    auto *actions = new QHBoxLayout;
    actions->addStretch();
    auto *modifier = new QPushButton(tr("Modifier"), this);
    auto *supprimer = new QPushButton(tr("Supprimer"), this);
    auto *fermer = new QPushButton(tr("Fermer"), this);
    modifier->setCursor(Qt::PointingHandCursor);
    supprimer->setCursor(Qt::PointingHandCursor);
    fermer->setCursor(Qt::PointingHandCursor);
    actions->addWidget(modifier);
    actions->addWidget(supprimer);
    actions->addWidget(fermer);
    layout->addLayout(actions);

    const auto ouvrirFormulaire = [this](const QString &titreFenetre) {
        QDialog formulaire(this);
        formulaire.setWindowTitle(titreFenetre);
        formulaire.setMinimumWidth(420);

        auto *contenu = new QVBoxLayout(&formulaire);
        auto *champs = new QFormLayout;
        auto *numero = new QLineEdit(&formulaire);
        auto *nom = new QLineEdit(&formulaire);
        numero->setPlaceholderText(tr("Ex. CL-001"));
        nom->setPlaceholderText(tr("Nom complet ou raison sociale"));
        champs->addRow(tr("Numéro client"), numero);
        champs->addRow(tr("Nom"), nom);
        contenu->addLayout(champs);

        auto *boutons = new QHBoxLayout;
        boutons->addStretch();
        auto *annuler = new QPushButton(tr("Annuler"), &formulaire);
        auto *enregistrer = new QPushButton(tr("Enregistrer"), &formulaire);
        boutons->addWidget(annuler);
        boutons->addWidget(enregistrer);
        contenu->addLayout(boutons);
        connect(annuler, &QPushButton::clicked, &formulaire, &QDialog::reject);
        connect(enregistrer, &QPushButton::clicked, &formulaire, [this]() {
            QMessageBox::information(this, tr("Backend requis"),
                                     tr("Le formulaire est prêt. L'enregistrement sera activé avec le backend."));
        });
        formulaire.exec();
    };

    connect(ajouter, &QPushButton::clicked, this, [ouvrirFormulaire]() {
        ouvrirFormulaire(tr("Nouveau client"));
    });
    connect(modifier, &QPushButton::clicked, this, [this, table, ouvrirFormulaire]() {
        if (!table->currentRow()) {
            QMessageBox::information(this, tr("Modifier un client"), tr("Sélectionnez un client dans la liste."));
            return;
        }
        ouvrirFormulaire(tr("Modifier le client"));
    });
    connect(supprimer, &QPushButton::clicked, this, [this, table]() {
        if (table->currentRow() < 0) {
            QMessageBox::information(this, tr("Supprimer un client"), tr("Sélectionnez un client dans la liste."));
            return;
        }
        QMessageBox::information(this, tr("Backend requis"),
                                 tr("La suppression sera activée avec le backend."));
    });
    connect(recherche, &QLineEdit::textChanged, table, [table, etat](const QString &texte) {
        for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
            const bool correspond = table->item(ligne, 0)->text().contains(texte, Qt::CaseInsensitive)
                || table->item(ligne, 1)->text().contains(texte, Qt::CaseInsensitive);
            table->setRowHidden(ligne, !correspond);
        }
        etat->setText(texte.isEmpty()
            ? QObject::tr("La liste des clients sera chargée lorsque le backend sera raccordé.")
            : QObject::tr("Aucun résultat dans la liste actuelle."));
    });
    connect(fermer, &QPushButton::clicked, this, &QDialog::accept);
}
>>>>>>> 8c2295e (Crafting)
