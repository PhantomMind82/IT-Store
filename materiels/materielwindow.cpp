<<<<<<< HEAD
#include "materielwindow.h"
#include "commun/style.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MaterielWindow::MaterielWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("MATÉRIELS"));
    resize(760, 480);
    setStyleSheet(QStringLiteral("QDialog { background: %1; }").arg(Style::FOND_VIOLET));

    auto *module = new QLabel(tr("MATÉRIELS"), this);
    module->setAlignment(Qt::AlignCenter);
    module->setStyleSheet(QStringLiteral(
        "font-size: 24px; font-weight: bold; letter-spacing: 6px; color: %1;")
        .arg(Style::VERT));

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
#include "materielwindow.h"
#include "commun/style.h"

#include <QDialog>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>

MaterielWindow::MaterielWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Gestion du matériel"));
    resize(960, 580);
    setStyleSheet(QStringLiteral("QDialog { background: %1; }").arg(Style::FOND_VIOLET));

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(16);

    auto *titre = new QLabel(tr("Matériel"), this);
    titre->setStyleSheet(QStringLiteral("font-size: 28px; font-weight: bold; color: %1;").arg(Style::BLEU_FONCE));
    layout->addWidget(titre);

    auto *barre = new QHBoxLayout;
    auto *recherche = new QLineEdit(this);
    recherche->setPlaceholderText(tr("Rechercher par référence ou désignation"));
    recherche->setClearButtonEnabled(true);
    barre->addWidget(recherche, 1);
    auto *ajouter = new QPushButton(tr("+  Nouveau matériel"), this);
    ajouter->setCursor(Qt::PointingHandCursor);
    barre->addWidget(ajouter);
    layout->addLayout(barre);

    auto *table = new QTableWidget(0, 5, this);
    table->setHorizontalHeaderLabels({tr("Référence"), tr("Désignation"), tr("Prix unitaire"),
                                      tr("Stock actuel"), tr("Stock initial")});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setMinimumHeight(280);
    layout->addWidget(table, 1);

    auto *etat = new QLabel(tr("Le catalogue sera chargé lorsque le backend sera raccordé."), this);
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
        formulaire.setMinimumWidth(440);
        auto *contenu = new QVBoxLayout(&formulaire);
        auto *champs = new QFormLayout;
        auto *reference = new QLineEdit(&formulaire);
        auto *designation = new QLineEdit(&formulaire);
        auto *prix = new QDoubleSpinBox(&formulaire);
        auto *stock = new QSpinBox(&formulaire);
        auto *stockInitial = new QSpinBox(&formulaire);
        reference->setPlaceholderText(tr("Référence interne"));
        designation->setPlaceholderText(tr("Nom du matériel"));
        prix->setRange(0, 999999999);
        prix->setDecimals(2);
        stock->setRange(0, 10000000);
        stockInitial->setRange(0, 10000000);
        champs->addRow(tr("Référence"), reference);
        champs->addRow(tr("Désignation"), designation);
        champs->addRow(tr("Prix unitaire"), prix);
        champs->addRow(tr("Stock actuel"), stock);
        champs->addRow(tr("Stock initial"), stockInitial);
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
        ouvrirFormulaire(tr("Nouveau matériel"));
    });
    connect(modifier, &QPushButton::clicked, this, [this, table, ouvrirFormulaire]() {
        if (table->currentRow() < 0) {
            QMessageBox::information(this, tr("Modifier un matériel"), tr("Sélectionnez un matériel dans la liste."));
            return;
        }
        ouvrirFormulaire(tr("Modifier le matériel"));
    });
    connect(supprimer, &QPushButton::clicked, this, [this, table]() {
        if (table->currentRow() < 0) {
            QMessageBox::information(this, tr("Supprimer un matériel"), tr("Sélectionnez un matériel dans la liste."));
            return;
        }
        QMessageBox::information(this, tr("Backend requis"),
                                 tr("La suppression sera activée avec le backend."));
    });
    connect(recherche, &QLineEdit::textChanged, table, [table, etat](const QString &texte) {
        bool resultat = false;
        for (int ligne = 0; ligne < table->rowCount(); ++ligne) {
            bool correspond = false;
            for (int colonne = 0; colonne < table->columnCount(); ++colonne) {
                const auto *cellule = table->item(ligne, colonne);
                correspond = correspond || (cellule && cellule->text().contains(texte, Qt::CaseInsensitive));
            }
            table->setRowHidden(ligne, !correspond);
            resultat = resultat || correspond;
        }
        etat->setText(texte.isEmpty()
            ? QObject::tr("Le catalogue sera chargé lorsque le backend sera raccordé.")
            : (resultat ? QObject::tr("Résultats filtrés.") : QObject::tr("Aucun résultat dans la liste actuelle.")));
    });
    connect(fermer, &QPushButton::clicked, this, &QDialog::accept);

}
>>>>>>> 8c2295e (Crafting)
