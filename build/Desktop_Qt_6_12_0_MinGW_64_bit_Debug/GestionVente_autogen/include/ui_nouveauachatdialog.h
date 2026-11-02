/********************************************************************************
** Form generated from reading UI file 'nouveauachatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOUVEAUACHATDIALOG_H
#define UI_NOUVEAUACHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NouveauAchatDialog
{
public:
    QVBoxLayout *layoutPrincipal;
    QFrame *headerWidget;
    QHBoxLayout *layoutHeader;
    QLabel *titleLabel;
    QWidget *corps;
    QVBoxLayout *layoutCorps;
    QVBoxLayout *layoutChampClient;
    QLabel *labelClient;
    QComboBox *comboClient;
    QVBoxLayout *layoutChampMateriel;
    QLabel *labelMateriel;
    QComboBox *comboMateriel;
    QLabel *labelStock;
    QHBoxLayout *layoutQteDate;
    QVBoxLayout *layoutChampQte;
    QLabel *labelQuantite;
    QSpinBox *spinQte;
    QVBoxLayout *layoutChampDate;
    QLabel *labelDate;
    QDateEdit *dateEdit;
    QFrame *widgetTotal;
    QHBoxLayout *layoutTotal;
    QVBoxLayout *layoutTextesTotal;
    QLabel *labelMontantTitre;
    QLabel *labelStockInfo;
    QSpacerItem *spacerTotal;
    QLabel *labelMontantValeur;
    QLabel *labelErreur;
    QSpacerItem *spacerBas;
    QHBoxLayout *layoutBoutons;
    QPushButton *btnAnnuler;
    QPushButton *btnEnregistrer;

    void setupUi(QDialog *NouveauAchatDialog)
    {
        if (NouveauAchatDialog->objectName().isEmpty())
            NouveauAchatDialog->setObjectName("NouveauAchatDialog");
        NouveauAchatDialog->resize(600, 700);
        NouveauAchatDialog->setMinimumSize(QSize(520, 640));
        layoutPrincipal = new QVBoxLayout(NouveauAchatDialog);
        layoutPrincipal->setSpacing(0);
        layoutPrincipal->setObjectName("layoutPrincipal");
        layoutPrincipal->setContentsMargins(0, 0, 0, 0);
        headerWidget = new QFrame(NouveauAchatDialog);
        headerWidget->setObjectName("headerWidget");
        layoutHeader = new QHBoxLayout(headerWidget);
        layoutHeader->setObjectName("layoutHeader");
        layoutHeader->setContentsMargins(32, 24, 32, 24);
        titleLabel = new QLabel(headerWidget);
        titleLabel->setObjectName("titleLabel");

        layoutHeader->addWidget(titleLabel);


        layoutPrincipal->addWidget(headerWidget);

        corps = new QWidget(NouveauAchatDialog);
        corps->setObjectName("corps");
        layoutCorps = new QVBoxLayout(corps);
        layoutCorps->setSpacing(18);
        layoutCorps->setObjectName("layoutCorps");
        layoutCorps->setContentsMargins(32, 28, 32, 28);
        layoutChampClient = new QVBoxLayout();
        layoutChampClient->setSpacing(6);
        layoutChampClient->setObjectName("layoutChampClient");
        labelClient = new QLabel(corps);
        labelClient->setObjectName("labelClient");

        layoutChampClient->addWidget(labelClient);

        comboClient = new QComboBox(corps);
        comboClient->setObjectName("comboClient");

        layoutChampClient->addWidget(comboClient);


        layoutCorps->addLayout(layoutChampClient);

        layoutChampMateriel = new QVBoxLayout();
        layoutChampMateriel->setSpacing(6);
        layoutChampMateriel->setObjectName("layoutChampMateriel");
        labelMateriel = new QLabel(corps);
        labelMateriel->setObjectName("labelMateriel");

        layoutChampMateriel->addWidget(labelMateriel);

        comboMateriel = new QComboBox(corps);
        comboMateriel->setObjectName("comboMateriel");

        layoutChampMateriel->addWidget(comboMateriel);

        labelStock = new QLabel(corps);
        labelStock->setObjectName("labelStock");

        layoutChampMateriel->addWidget(labelStock);


        layoutCorps->addLayout(layoutChampMateriel);

        layoutQteDate = new QHBoxLayout();
        layoutQteDate->setSpacing(16);
        layoutQteDate->setObjectName("layoutQteDate");
        layoutChampQte = new QVBoxLayout();
        layoutChampQte->setSpacing(6);
        layoutChampQte->setObjectName("layoutChampQte");
        labelQuantite = new QLabel(corps);
        labelQuantite->setObjectName("labelQuantite");

        layoutChampQte->addWidget(labelQuantite);

        spinQte = new QSpinBox(corps);
        spinQte->setObjectName("spinQte");
        spinQte->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinQte->setMinimum(1);
        spinQte->setMaximum(1000000);
        spinQte->setValue(1);

        layoutChampQte->addWidget(spinQte);


        layoutQteDate->addLayout(layoutChampQte);

        layoutChampDate = new QVBoxLayout();
        layoutChampDate->setSpacing(6);
        layoutChampDate->setObjectName("layoutChampDate");
        labelDate = new QLabel(corps);
        labelDate->setObjectName("labelDate");

        layoutChampDate->addWidget(labelDate);

        dateEdit = new QDateEdit(corps);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setCalendarPopup(true);

        layoutChampDate->addWidget(dateEdit);


        layoutQteDate->addLayout(layoutChampDate);


        layoutCorps->addLayout(layoutQteDate);

        widgetTotal = new QFrame(corps);
        widgetTotal->setObjectName("widgetTotal");
        layoutTotal = new QHBoxLayout(widgetTotal);
        layoutTotal->setObjectName("layoutTotal");
        layoutTotal->setContentsMargins(22, 18, 22, 18);
        layoutTextesTotal = new QVBoxLayout();
        layoutTextesTotal->setSpacing(2);
        layoutTextesTotal->setObjectName("layoutTextesTotal");
        labelMontantTitre = new QLabel(widgetTotal);
        labelMontantTitre->setObjectName("labelMontantTitre");

        layoutTextesTotal->addWidget(labelMontantTitre);

        labelStockInfo = new QLabel(widgetTotal);
        labelStockInfo->setObjectName("labelStockInfo");

        layoutTextesTotal->addWidget(labelStockInfo);


        layoutTotal->addLayout(layoutTextesTotal);

        spacerTotal = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutTotal->addItem(spacerTotal);

        labelMontantValeur = new QLabel(widgetTotal);
        labelMontantValeur->setObjectName("labelMontantValeur");

        layoutTotal->addWidget(labelMontantValeur);


        layoutCorps->addWidget(widgetTotal);

        labelErreur = new QLabel(corps);
        labelErreur->setObjectName("labelErreur");
        labelErreur->setWordWrap(true);

        layoutCorps->addWidget(labelErreur);

        spacerBas = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutCorps->addItem(spacerBas);

        layoutBoutons = new QHBoxLayout();
        layoutBoutons->setSpacing(12);
        layoutBoutons->setObjectName("layoutBoutons");
        btnAnnuler = new QPushButton(corps);
        btnAnnuler->setObjectName("btnAnnuler");
        btnAnnuler->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnAnnuler->setAutoDefault(false);

        layoutBoutons->addWidget(btnAnnuler);

        btnEnregistrer = new QPushButton(corps);
        btnEnregistrer->setObjectName("btnEnregistrer");
        btnEnregistrer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        layoutBoutons->addWidget(btnEnregistrer);

        layoutBoutons->setStretch(0, 1);
        layoutBoutons->setStretch(1, 2);

        layoutCorps->addLayout(layoutBoutons);


        layoutPrincipal->addWidget(corps);


        retranslateUi(NouveauAchatDialog);

        btnEnregistrer->setDefault(true);


        QMetaObject::connectSlotsByName(NouveauAchatDialog);
    } // setupUi

    void retranslateUi(QDialog *NouveauAchatDialog)
    {
        NouveauAchatDialog->setWindowTitle(QCoreApplication::translate("NouveauAchatDialog", "Achat", nullptr));
        titleLabel->setText(QCoreApplication::translate("NouveauAchatDialog", "Nouvel achat", nullptr));
        labelClient->setText(QCoreApplication::translate("NouveauAchatDialog", "Client", nullptr));
        labelMateriel->setText(QCoreApplication::translate("NouveauAchatDialog", "Mat\303\251riel", nullptr));
        labelStock->setText(QCoreApplication::translate("NouveauAchatDialog", "Stock actuel : \342\200\224", nullptr));
        labelQuantite->setText(QCoreApplication::translate("NouveauAchatDialog", "Quantit\303\251", nullptr));
        labelDate->setText(QCoreApplication::translate("NouveauAchatDialog", "Date d\342\200\231achat", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("NouveauAchatDialog", "dd/MM/yyyy", nullptr));
        labelMontantTitre->setText(QCoreApplication::translate("NouveauAchatDialog", "Montant", nullptr));
        labelStockInfo->setText(QCoreApplication::translate("NouveauAchatDialog", "Choisissez un mat\303\251riel", nullptr));
        labelMontantValeur->setText(QCoreApplication::translate("NouveauAchatDialog", "0 Ar", nullptr));
        labelErreur->setText(QString());
        btnAnnuler->setText(QCoreApplication::translate("NouveauAchatDialog", "Annuler", nullptr));
        btnEnregistrer->setText(QCoreApplication::translate("NouveauAchatDialog", "Enregistrer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NouveauAchatDialog: public Ui_NouveauAchatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOUVEAUACHATDIALOG_H
