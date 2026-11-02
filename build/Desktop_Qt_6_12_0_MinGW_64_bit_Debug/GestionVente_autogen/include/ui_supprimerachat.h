/********************************************************************************
** Form generated from reading UI file 'supprimerachat.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPPRIMERACHAT_H
#define UI_SUPPRIMERACHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SupprimerAchat
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

    void setupUi(QDialog *SupprimerAchat)
    {
        if (SupprimerAchat->objectName().isEmpty())
            SupprimerAchat->setObjectName("SupprimerAchat");
        SupprimerAchat->resize(440, 300);
        SupprimerAchat->setMinimumSize(QSize(440, 300));
        SupprimerAchat->setStyleSheet(QString::fromUtf8("\n"
"QWidget { font-family: \"Segoe UI\", \"Ubuntu\", \"Noto Sans\", \"DejaVu Sans\", sans-serif; font-size: 15px; color: #2B1608; }\n"
"QLabel { background: transparent; }\n"
"QPushButton { outline: none; }\n"
"QDialog#SupprimerAchat { background: #FFFFFF; }\n"
"QLabel#labelSupprimerTitre { font-size: 22px; font-weight: 700; }\n"
"QLabel#labelSupprimerDesc { color: #7A5C45; }\n"
"QPushButton#btnAnnulerSup { min-height: 48px; padding: 0 20px; border: 0; border-radius: 12px; font-size: 16px; font-weight: 700; background: #F1E3D3; color: #2B1608; }\n"
"QPushButton#btnAnnulerSup:hover { background: #E8D5C0; }\n"
"QPushButton#btnConfirmerSup { min-height: 48px; padding: 0 20px; border: 0; border-radius: 12px; font-size: 16px; font-weight: 700; background: #C23030; color: #FFFFFF; }\n"
"QPushButton#btnConfirmerSup:hover { background: #A82626; }\n"
""));
        layoutPrincipal = new QVBoxLayout(SupprimerAchat);
        layoutPrincipal->setSpacing(14);
        layoutPrincipal->setObjectName("layoutPrincipal");
        layoutPrincipal->setContentsMargins(32, 32, 32, 32);
        iconeCorbeille = new QLabel(SupprimerAchat);
        iconeCorbeille->setObjectName("iconeCorbeille");
        iconeCorbeille->setPixmap(QPixmap(QString::fromUtf8(":/achats/assets/corbeille-rouge.svg")));
        iconeCorbeille->setMinimumSize(QSize(48, 48));
        iconeCorbeille->setMaximumSize(QSize(48, 48));

        layoutPrincipal->addWidget(iconeCorbeille);

        labelSupprimerTitre = new QLabel(SupprimerAchat);
        labelSupprimerTitre->setObjectName("labelSupprimerTitre");

        layoutPrincipal->addWidget(labelSupprimerTitre);

        labelSupprimerDesc = new QLabel(SupprimerAchat);
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

        btnAnnulerSup = new QPushButton(SupprimerAchat);
        btnAnnulerSup->setObjectName("btnAnnulerSup");
        btnAnnulerSup->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        layoutBoutons->addWidget(btnAnnulerSup);

        btnConfirmerSup = new QPushButton(SupprimerAchat);
        btnConfirmerSup->setObjectName("btnConfirmerSup");
        btnConfirmerSup->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnConfirmerSup->setAutoDefault(false);

        layoutBoutons->addWidget(btnConfirmerSup);


        layoutPrincipal->addLayout(layoutBoutons);


        retranslateUi(SupprimerAchat);

        btnAnnulerSup->setDefault(true);


        QMetaObject::connectSlotsByName(SupprimerAchat);
    } // setupUi

    void retranslateUi(QDialog *SupprimerAchat)
    {
        SupprimerAchat->setWindowTitle(QCoreApplication::translate("SupprimerAchat", "Supprimer un achat", nullptr));
        iconeCorbeille->setText(QString());
        labelSupprimerTitre->setText(QCoreApplication::translate("SupprimerAchat", "Supprimer cet achat ?", nullptr));
        labelSupprimerDesc->setText(QString());
        btnAnnulerSup->setText(QCoreApplication::translate("SupprimerAchat", "Annuler", nullptr));
        btnConfirmerSup->setText(QCoreApplication::translate("SupprimerAchat", "Supprimer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SupprimerAchat: public Ui_SupprimerAchat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPPRIMERACHAT_H
