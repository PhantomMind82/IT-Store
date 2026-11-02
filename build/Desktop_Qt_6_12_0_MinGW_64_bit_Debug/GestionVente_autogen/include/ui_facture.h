/********************************************************************************
** Form generated from reading UI file 'facture.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACTURE_H
#define UI_FACTURE_H

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

class Ui_Facture
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

    void setupUi(QDialog *Facture)
    {
        if (Facture->objectName().isEmpty())
            Facture->setObjectName("Facture");
        Facture->resize(720, 820);
        Facture->setMinimumSize(QSize(640, 700));
        Facture->setStyleSheet(QString::fromUtf8("\n"
"QWidget { font-family: \"Segoe UI\", \"Ubuntu\", \"Noto Sans\", \"DejaVu Sans\", sans-serif; font-size: 15px; color: #2B1608; }\n"
"QLabel { background: transparent; }\n"
"QPushButton { outline: none; }\n"
"QDialog#Facture { background: #FAF3EC; }\n"
"QFrame#feuille { background: #FFFFFF; border-radius: 16px; }\n"
"QLabel#labelFactureTitre { font-size: 28px; font-weight: 700; }\n"
"QLabel#labelStore { font-family: Georgia, \"Times New Roman\", serif; font-size: 22px; font-weight: 700; color: #B84A05; }\n"
"QLabel#labelNumClient, QLabel#labelDate, QLabel#labelNom, QLabel#labelTelephone { color: #7A5C45; }\n"
"\n"
"QTableWidget#tableFacture { background: transparent; border: 0; outline: 0; }\n"
"QTableWidget#tableFacture::item { padding: 8px 12px; border-top: 1px solid #F0E1D2; }\n"
"QTableWidget#tableFacture QHeaderView { background: transparent; }\n"
"QTableWidget#tableFacture QHeaderView::section { background-color: #FFF1E2; border: 0; border-bottom: 2px solid #E8CFB8; color: #70421F; font-size: 12px; fo"
                        "nt-weight: 700; padding: 10px 12px; }\n"
"\n"
"QFrame#widgetTotalFacture { background: #2B1608; border-radius: 12px; }\n"
"QLabel#labelTotalText { color: #E9D3BC; }\n"
"QLabel#labelTotalVal { color: #FFB066; font-size: 24px; font-weight: 700; }\n"
"QLabel#labelArretee { color: #7A5C45; }\n"
"QPushButton#btnFermerFacture { min-height: 52px; padding: 0 20px; border: 0; border-radius: 12px; font-size: 17px; font-weight: 700; background: #F1E3D3; color: #2B1608; }\n"
"QPushButton#btnFermerFacture:hover { background: #E8D5C0; }\n"
"QPushButton#btnGenererPdf { min-height: 52px; padding: 0 20px; border: 0; border-radius: 12px; font-size: 17px; font-weight: 700; color: #FFFFFF; background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #EA7210, stop:1 #D95F08); }\n"
"QPushButton#btnGenererPdf:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #F5801E, stop:1 #E56A10); }\n"
""));
        layoutPrincipal = new QVBoxLayout(Facture);
        layoutPrincipal->setSpacing(20);
        layoutPrincipal->setObjectName("layoutPrincipal");
        layoutPrincipal->setContentsMargins(32, 32, 32, 32);
        feuille = new QFrame(Facture);
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
        labelNumClient->setTextFormat(Qt::RichText);

        layoutInfos->addWidget(labelNumClient, 0, 0, 1, 1);

        labelDate = new QLabel(feuille);
        labelDate->setObjectName("labelDate");
        labelDate->setTextFormat(Qt::RichText);

        layoutInfos->addWidget(labelDate, 0, 1, 1, 1);

        labelNom = new QLabel(feuille);
        labelNom->setObjectName("labelNom");
        labelNom->setTextFormat(Qt::RichText);

        layoutInfos->addWidget(labelNom, 1, 0, 1, 1);

        labelTelephone = new QLabel(feuille);
        labelTelephone->setObjectName("labelTelephone");
        labelTelephone->setTextFormat(Qt::RichText);

        layoutInfos->addWidget(labelTelephone, 1, 1, 1, 1);


        layoutFeuille->addLayout(layoutInfos);

        tableFacture = new QTableWidget(feuille);
        if (tableFacture->columnCount() < 4)
            tableFacture->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableFacture->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableFacture->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableFacture->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tableFacture->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableFacture->setObjectName("tableFacture");
        tableFacture->setFrameShape(QFrame::NoFrame);
        tableFacture->setFocusPolicy(Qt::NoFocus);
        tableFacture->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableFacture->setSelectionMode(QAbstractItemView::NoSelection);
        tableFacture->setShowGrid(false);
        tableFacture->setColumnCount(4);
        tableFacture->horizontalHeader()->setMinimumSectionSize(90);
        tableFacture->verticalHeader()->setVisible(false);
        tableFacture->verticalHeader()->setDefaultSectionSize(44);

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
        labelArretee->setTextFormat(Qt::RichText);

        layoutFeuille->addWidget(labelArretee);

        layoutFeuille->setStretch(2, 1);

        layoutPrincipal->addWidget(feuille);

        layoutBoutons = new QHBoxLayout();
        layoutBoutons->setSpacing(12);
        layoutBoutons->setObjectName("layoutBoutons");
        btnFermerFacture = new QPushButton(Facture);
        btnFermerFacture->setObjectName("btnFermerFacture");
        btnFermerFacture->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnFermerFacture->setAutoDefault(false);

        layoutBoutons->addWidget(btnFermerFacture);

        btnGenererPdf = new QPushButton(Facture);
        btnGenererPdf->setObjectName("btnGenererPdf");
        btnGenererPdf->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnGenererPdf->setAutoDefault(false);

        layoutBoutons->addWidget(btnGenererPdf);

        layoutBoutons->setStretch(0, 1);
        layoutBoutons->setStretch(1, 2);

        layoutPrincipal->addLayout(layoutBoutons);

        layoutPrincipal->setStretch(0, 1);

        retranslateUi(Facture);

        QMetaObject::connectSlotsByName(Facture);
    } // setupUi

    void retranslateUi(QDialog *Facture)
    {
        Facture->setWindowTitle(QCoreApplication::translate("Facture", "Facture", nullptr));
        labelFactureTitre->setText(QCoreApplication::translate("Facture", "Facture N\302\260 0001", nullptr));
        labelStore->setText(QCoreApplication::translate("Facture", "IT Store", nullptr));
        labelNumClient->setText(QCoreApplication::translate("Facture", "N\302\260 client :", nullptr));
        labelDate->setText(QCoreApplication::translate("Facture", "Date :", nullptr));
        labelNom->setText(QCoreApplication::translate("Facture", "Nom :", nullptr));
        labelTelephone->setText(QCoreApplication::translate("Facture", "T\303\251l\303\251phone :", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableFacture->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Facture", "D\303\211SIGNATION", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableFacture->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Facture", "PU", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableFacture->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Facture", "QT\303\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableFacture->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Facture", "MONTANT", nullptr));
        labelTotalText->setText(QCoreApplication::translate("Facture", "Total", nullptr));
        labelTotalVal->setText(QCoreApplication::translate("Facture", "0 Ar", nullptr));
        labelArretee->setText(QString());
        btnFermerFacture->setText(QCoreApplication::translate("Facture", "Fermer", nullptr));
        btnGenererPdf->setText(QCoreApplication::translate("Facture", "G\303\251n\303\251rer le PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Facture: public Ui_Facture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTURE_H
