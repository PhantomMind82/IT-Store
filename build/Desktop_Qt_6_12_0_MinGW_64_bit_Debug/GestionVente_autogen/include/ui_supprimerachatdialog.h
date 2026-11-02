/********************************************************************************
** Form generated from reading UI file 'supprimerachatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPPRIMERACHATDIALOG_H
#define UI_SUPPRIMERACHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SupprimerAchatDialog
{
public:
    QVBoxLayout *layoutPrincipal;
    QLabel *iconeCorbeille;
    QLabel *labelSupprimerTitre;
    QLabel *labelSupprimerDesc;
    QSpacerItem *spacerBas;
    QHBoxLayout *layoutBoutons;
    QSpacerItem *spacerBoutons;
    QPushButton *btnAnnulerSup;
    QPushButton *btnConfirmerSup;

    void setupUi(QDialog *SupprimerAchatDialog)
    {
        if (SupprimerAchatDialog->objectName().isEmpty())
            SupprimerAchatDialog->setObjectName("SupprimerAchatDialog");
        SupprimerAchatDialog->resize(440, 300);
        SupprimerAchatDialog->setMinimumSize(QSize(440, 300));
        layoutPrincipal = new QVBoxLayout(SupprimerAchatDialog);
        layoutPrincipal->setSpacing(14);
        layoutPrincipal->setObjectName("layoutPrincipal");
        layoutPrincipal->setContentsMargins(32, 32, 32, 32);
        iconeCorbeille = new QLabel(SupprimerAchatDialog);
        iconeCorbeille->setObjectName("iconeCorbeille");

        layoutPrincipal->addWidget(iconeCorbeille);

        labelSupprimerTitre = new QLabel(SupprimerAchatDialog);
        labelSupprimerTitre->setObjectName("labelSupprimerTitre");

        layoutPrincipal->addWidget(labelSupprimerTitre);

        labelSupprimerDesc = new QLabel(SupprimerAchatDialog);
        labelSupprimerDesc->setObjectName("labelSupprimerDesc");
        labelSupprimerDesc->setWordWrap(true);
        labelSupprimerDesc->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        layoutPrincipal->addWidget(labelSupprimerDesc);

        spacerBas = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutPrincipal->addItem(spacerBas);

        layoutBoutons = new QHBoxLayout();
        layoutBoutons->setSpacing(12);
        layoutBoutons->setObjectName("layoutBoutons");
        spacerBoutons = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutBoutons->addItem(spacerBoutons);

        btnAnnulerSup = new QPushButton(SupprimerAchatDialog);
        btnAnnulerSup->setObjectName("btnAnnulerSup");
        btnAnnulerSup->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        layoutBoutons->addWidget(btnAnnulerSup);

        btnConfirmerSup = new QPushButton(SupprimerAchatDialog);
        btnConfirmerSup->setObjectName("btnConfirmerSup");
        btnConfirmerSup->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnConfirmerSup->setAutoDefault(false);

        layoutBoutons->addWidget(btnConfirmerSup);


        layoutPrincipal->addLayout(layoutBoutons);


        retranslateUi(SupprimerAchatDialog);

        btnAnnulerSup->setDefault(true);


        QMetaObject::connectSlotsByName(SupprimerAchatDialog);
    } // setupUi

    void retranslateUi(QDialog *SupprimerAchatDialog)
    {
        SupprimerAchatDialog->setWindowTitle(QCoreApplication::translate("SupprimerAchatDialog", "Supprimer un achat", nullptr));
        iconeCorbeille->setText(QString());
        labelSupprimerTitre->setText(QCoreApplication::translate("SupprimerAchatDialog", "Supprimer cet achat ?", nullptr));
        labelSupprimerDesc->setText(QString());
        btnAnnulerSup->setText(QCoreApplication::translate("SupprimerAchatDialog", "Annuler", nullptr));
        btnConfirmerSup->setText(QCoreApplication::translate("SupprimerAchatDialog", "Supprimer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SupprimerAchatDialog: public Ui_SupprimerAchatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPPRIMERACHATDIALOG_H
