/********************************************************************************
** Form generated from reading UI file 'facturedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACTUREDIALOG_H
#define UI_FACTUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FactureDialog
{
public:
    QVBoxLayout *layoutPrincipal;
    QFrame *feuille;
    QVBoxLayout *layoutFeuille;
    QHBoxLayout *layoutTitreFacture;
    QLabel *labelFactureTitre;
    QSpacerItem *spacerTitre;
    QLabel *labelStore;
    QGridLayout *layoutInfos;
    QLabel *labelNumClient;
    QLabel *labelDate;
    QLabel *labelNom;
    QLabel *labelTelephone;
    QTableWidget *tableFacture;
    QFrame *widgetTotalFacture;
    QHBoxLayout *layoutTotalFacture;
    QLabel *labelTotalText;
    QSpacerItem *spacerTotalFacture;
    QLabel *labelTotalVal;
    QLabel *labelArretee;
    QHBoxLayout *layoutBoutons;
    QPushButton *btnFermerFacture;
    QPushButton *btnGenererPdf;

    void setupUi(QDialog *FactureDialog)
    {
        if (FactureDialog->objectName().isEmpty())
            FactureDialog->setObjectName("FactureDialog");
        FactureDialog->resize(720, 820);
        FactureDialog->setMinimumSize(QSize(640, 700));
        layoutPrincipal = new QVBoxLayout(FactureDialog);
        layoutPrincipal->setSpacing(20);
        layoutPrincipal->setObjectName("layoutPrincipal");
        layoutPrincipal->setContentsMargins(32, 32, 32, 32);
        feuille = new QFrame(FactureDialog);
        feuille->setObjectName("feuille");
        layoutFeuille = new QVBoxLayout(feuille);
        layoutFeuille->setSpacing(22);
        layoutFeuille->setObjectName("layoutFeuille");
        layoutFeuille->setContentsMargins(32, 32, 32, 32);
        layoutTitreFacture = new QHBoxLayout();
        layoutTitreFacture->setObjectName("layoutTitreFacture");
        labelFactureTitre = new QLabel(feuille);
        labelFactureTitre->setObjectName("labelFactureTitre");

        layoutTitreFacture->addWidget(labelFactureTitre);

        spacerTitre = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutTitreFacture->addItem(spacerTitre);

        labelStore = new QLabel(feuille);
        labelStore->setObjectName("labelStore");

        layoutTitreFacture->addWidget(labelStore);


        layoutFeuille->addLayout(layoutTitreFacture);

        layoutInfos = new QGridLayout();
        layoutInfos->setObjectName("layoutInfos");
        layoutInfos->setHorizontalSpacing(16);
        layoutInfos->setVerticalSpacing(6);
        labelNumClient = new QLabel(feuille);
        labelNumClient->setObjectName("labelNumClient");

        layoutInfos->addWidget(labelNumClient, 0, 0, 1, 1);

        labelDate = new QLabel(feuille);
        labelDate->setObjectName("labelDate");

        layoutInfos->addWidget(labelDate, 0, 1, 1, 1);

        labelNom = new QLabel(feuille);
        labelNom->setObjectName("labelNom");

        layoutInfos->addWidget(labelNom, 1, 0, 1, 1);

        labelTelephone = new QLabel(feuille);
        labelTelephone->setObjectName("labelTelephone");

        layoutInfos->addWidget(labelTelephone, 1, 1, 1, 1);


        layoutFeuille->addLayout(layoutInfos);

        tableFacture = new QTableWidget(feuille);
        if (tableFacture->columnCount() < 4)
            tableFacture->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableFacture->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableFacture->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableFacture->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableFacture->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableFacture->setObjectName("tableFacture");
        tableFacture->setFrameShape(QFrame::NoFrame);
        tableFacture->setFocusPolicy(Qt::NoFocus);
        tableFacture->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableFacture->setSelectionMode(QAbstractItemView::NoSelection);
        tableFacture->setShowGrid(false);
        tableFacture->setColumnCount(4);
        tableFacture->verticalHeader()->setVisible(false);

        layoutFeuille->addWidget(tableFacture);

        widgetTotalFacture = new QFrame(feuille);
        widgetTotalFacture->setObjectName("widgetTotalFacture");
        layoutTotalFacture = new QHBoxLayout(widgetTotalFacture);
        layoutTotalFacture->setObjectName("layoutTotalFacture");
        layoutTotalFacture->setContentsMargins(22, 18, 22, 18);
        labelTotalText = new QLabel(widgetTotalFacture);
        labelTotalText->setObjectName("labelTotalText");

        layoutTotalFacture->addWidget(labelTotalText);

        spacerTotalFacture = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutTotalFacture->addItem(spacerTotalFacture);

        labelTotalVal = new QLabel(widgetTotalFacture);
        labelTotalVal->setObjectName("labelTotalVal");

        layoutTotalFacture->addWidget(labelTotalVal);


        layoutFeuille->addWidget(widgetTotalFacture);

        labelArretee = new QLabel(feuille);
        labelArretee->setObjectName("labelArretee");
        labelArretee->setWordWrap(true);

        layoutFeuille->addWidget(labelArretee);

        layoutFeuille->setStretch(2, 1);

        layoutPrincipal->addWidget(feuille);

        layoutBoutons = new QHBoxLayout();
        layoutBoutons->setSpacing(12);
        layoutBoutons->setObjectName("layoutBoutons");
        btnFermerFacture = new QPushButton(FactureDialog);
        btnFermerFacture->setObjectName("btnFermerFacture");
        btnFermerFacture->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnFermerFacture->setAutoDefault(false);

        layoutBoutons->addWidget(btnFermerFacture);

        btnGenererPdf = new QPushButton(FactureDialog);
        btnGenererPdf->setObjectName("btnGenererPdf");
        btnGenererPdf->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnGenererPdf->setAutoDefault(false);

        layoutBoutons->addWidget(btnGenererPdf);

        layoutBoutons->setStretch(0, 1);
        layoutBoutons->setStretch(1, 2);

        layoutPrincipal->addLayout(layoutBoutons);

        layoutPrincipal->setStretch(0, 1);

        retranslateUi(FactureDialog);

        QMetaObject::connectSlotsByName(FactureDialog);
    } // setupUi

    void retranslateUi(QDialog *FactureDialog)
    {
        FactureDialog->setWindowTitle(QCoreApplication::translate("FactureDialog", "Facture", nullptr));
        labelFactureTitre->setText(QCoreApplication::translate("FactureDialog", "Facture N\302\260 0001", nullptr));
        labelStore->setText(QCoreApplication::translate("FactureDialog", "IT Store", nullptr));
        labelNumClient->setText(QCoreApplication::translate("FactureDialog", "N\302\260 client :", nullptr));
        labelDate->setText(QCoreApplication::translate("FactureDialog", "Date :", nullptr));
        labelNom->setText(QCoreApplication::translate("FactureDialog", "Nom :", nullptr));
        labelTelephone->setText(QCoreApplication::translate("FactureDialog", "T\303\251l\303\251phone :", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableFacture->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("FactureDialog", "D\303\211SIGNATION", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableFacture->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("FactureDialog", "PU", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableFacture->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("FactureDialog", "QT\303\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableFacture->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("FactureDialog", "MONTANT", nullptr));
        labelTotalText->setText(QCoreApplication::translate("FactureDialog", "Total", nullptr));
        labelTotalVal->setText(QCoreApplication::translate("FactureDialog", "0 Ar", nullptr));
        labelArretee->setText(QString());
        btnFermerFacture->setText(QCoreApplication::translate("FactureDialog", "Fermer", nullptr));
        btnGenererPdf->setText(QCoreApplication::translate("FactureDialog", "G\303\251n\303\251rer le PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FactureDialog: public Ui_FactureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTUREDIALOG_H
