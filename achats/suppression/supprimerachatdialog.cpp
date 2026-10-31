#include "supprimerachatdialog.h"
#include "ui_supprimerachatdialog.h"

#include "achats/achatsui.h"
#include "achats/achatstyle.h"

SupprimerAchatDialog::SupprimerAchatDialog(const Achat &achat, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SupprimerAchatDialog)
{
    ui->setupUi(this);
    setStyleSheet(AchatStyle::suppressionAchat());

    // Le rond rose avec la corbeille rouge.
    ui->iconeCorbeille->setFixedSize(48, 48);
    ui->iconeCorbeille->setPixmap(AchatsUi::pastille(AchatsUi::Icone::Corbeille, 48,
                                                     QColor("#FBE0E0"), QColor("#FBE0E0"), QColor("#B62F2F")));

    // %1, %2... sont remplacés par les valeurs données à arg(), dans l'ordre.
    // %2 apparaît deux fois : arg() remplace toutes ses occurrences d'un coup.
    ui->labelSupprimerDesc->setText(
        QStringLiteral("L'achat n° %1 (%2 %3 par %4) sera supprimé et le stock du matériel augmentera de %2.")
            .arg(achat.idAchat())
            .arg(achat.qte())
            .arg(achat.designationMat())
            .arg(achat.nomClient()));

    connect(ui->btnAnnulerSup, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btnConfirmerSup, &QPushButton::clicked, this, &QDialog::accept);
}

SupprimerAchatDialog::~SupprimerAchatDialog()
{
    delete ui;
}
