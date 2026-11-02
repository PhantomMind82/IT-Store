/********************************************************************************
** Form generated from reading UI file 'nouveauachat.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOUVEAUACHAT_H
#define UI_NOUVEAUACHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NouveauAchat
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
    QHBoxLayout *layoutQuantite;
    QLineEdit *champQuantite;
    QVBoxLayout *layoutBoutonsQuantite;
    QPushButton *btnAugmenterQuantite;
    QPushButton *btnReduireQuantite;
    QVBoxLayout *layoutChampDate;
    QLabel *labelDate;
    QDateEdit *dateEdit;
    QHBoxLayout *layoutActionsArticles;
    QPushButton *btnAjouterArticle;
    QSpacerItem *spacerActionsArticles;
    QPushButton *btnRetirerArticle;
    QTableWidget *tableArticlesCommande;
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

    void setupUi(QDialog *NouveauAchat)
    {
        if (NouveauAchat->objectName().isEmpty())
            NouveauAchat->setObjectName("NouveauAchat");
        NouveauAchat->resize(600, 760);
        NouveauAchat->setMinimumSize(QSize(520, 680));
        NouveauAchat->setStyleSheet(QString::fromUtf8("\n"
"QWidget { font-family: \"Segoe UI\", \"Ubuntu\", \"Noto Sans\", \"DejaVu Sans\", sans-serif; font-size: 15px; color: #2B1608; }\n"
"QLabel { background: transparent; }\n"
"QPushButton { outline: none; }\n"
"QDialog#NouveauAchat { background: #FFFFFF; }\n"
"QFrame#headerWidget { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #EA7210, stop:1 #D95F08); }\n"
"QLabel#titleLabel { color: #FFFFFF; font-size: 28px; font-weight: 700; }\n"
"\n"
"QLabel#labelClient, QLabel#labelMateriel, QLabel#labelQuantite, QLabel#labelDate { font-size: 13px; font-weight: 700; }\n"
"QLabel#labelStock { font-size: 13px; font-weight: 600; color: #7A5C45; }\n"
"\n"
"QComboBox, QDateEdit { min-height: 48px; padding: 0 14px; border: 1px solid #E6CFB8; border-radius: 10px; background: #FFF8F1; color: #2B1608; font-weight: 500; }\n"
"QLineEdit#champQuantite { min-width: 128px; min-height: 48px; padding: 0 12px; border: 1px solid #E6CFB8; border-radius: 10px; background: #FFF8F1; color: #2B1608; font-size: 15px; font-weight: 5"
                        "00; selection-background-color: #E8D5C0; selection-color: #2B1608; }\n"
"QPushButton#btnAugmenterQuantite, QPushButton#btnReduireQuantite { border: 1px solid #D7B99B; border-radius: 6px; background: #F1E3D3; color: #3A2414; font-size: 18px; font-weight: 800; }\n"
"QPushButton#btnAugmenterQuantite:hover, QPushButton#btnReduireQuantite:hover { background: #E8D5C0; border-color: #EA7210; }\n"
"QPushButton#btnAugmenterQuantite:pressed, QPushButton#btnReduireQuantite:pressed { background: #DDBF9F; }\n"
"QPushButton#btnAjouterArticle { min-height: 42px; padding: 0 16px; border: 0; border-radius: 8px; background: #315B47; color: white; font-weight: 700; }\n"
"QPushButton#btnAjouterArticle:hover { background: #264A39; }\n"
"QPushButton#btnRetirerArticle { min-height: 38px; padding: 0 14px; border: 1px solid #D9B8A0; border-radius: 8px; background: #FFF4EA; color: #8A3B24; font-weight: 700; }\n"
"QPushButton#btnRetirerArticle:hover { background: #F7E3D4; }\n"
"QLabel#labelArticlesCommande { font-size: 15px; font-weight"
                        ": 700; }\n"
"QTableWidget#tableArticlesCommande { min-height: 140px; background: white; border: 1px solid #E6CFB8; gridline-color: #F0E1D2; selection-background-color: #FFEBD6; selection-color: #2B1608; }\n"
"QTableWidget#tableArticlesCommande::item { padding: 6px 10px; }\n"
"QComboBox:focus, QLineEdit#champQuantite:focus, QDateEdit:focus { border: 1px solid #EA7210; }\n"
"QComboBox QAbstractItemView { background: #FFFFFF; border: 1px solid #E6CFB8; selection-background-color: #FFEBD6; selection-color: #2B1608; outline: 0; }\n"
"\n"
"QFrame#widgetTotal { background: #2B1608; border-radius: 12px; }\n"
"QLabel#labelMontantTitre { color: #E9D3BC; }\n"
"QLabel#labelStockInfo { color: #E9D3BC; font-size: 13px; }\n"
"QLabel#labelMontantValeur { color: #FFB066; font-size: 26px; font-weight: 700; }\n"
"QLabel#labelErreur { color: #B62F2F; font-weight: 600; }\n"
"QPushButton#btnAnnuler { min-height: 52px; padding: 0 20px; border: 0; border-radius: 12px; font-size: 17px; font-weight: 700; background: #F1E3D3; color: #2B"
                        "1608; }\n"
"QPushButton#btnAnnuler:hover { background: #E8D5C0; }\n"
"QPushButton#btnEnregistrer { min-height: 52px; padding: 0 20px; border: 0; border-radius: 12px; font-size: 17px; font-weight: 700; color: #FFFFFF; background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #EA7210, stop:1 #D95F08); }\n"
"QPushButton#btnEnregistrer:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #F5801E, stop:1 #E56A10); }\n"
""));
        layoutPrincipal = new QVBoxLayout(NouveauAchat);
        layoutPrincipal->setSpacing(0);
        layoutPrincipal->setObjectName("layoutPrincipal");
        layoutPrincipal->setContentsMargins(0, 0, 0, 0);
        headerWidget = new QFrame(NouveauAchat);
        headerWidget->setObjectName("headerWidget");
        layoutHeader = new QHBoxLayout(headerWidget);
        layoutHeader->setObjectName("layoutHeader");
        layoutHeader->setContentsMargins(32, 24, 32, 24);
        titleLabel = new QLabel(headerWidget);
        titleLabel->setObjectName("titleLabel");

        layoutHeader->addWidget(titleLabel);


        layoutPrincipal->addWidget(headerWidget);

        corps = new QWidget(NouveauAchat);
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

        layoutQuantite = new QHBoxLayout();
        layoutQuantite->setSpacing(8);
        layoutQuantite->setObjectName("layoutQuantite");
        champQuantite = new QLineEdit(corps);
        champQuantite->setObjectName("champQuantite");
        champQuantite->setAlignment(Qt::AlignmentFlag::AlignCenter);
        champQuantite->setMaxLength(7);

        layoutQuantite->addWidget(champQuantite);

        layoutBoutonsQuantite = new QVBoxLayout();
        layoutBoutonsQuantite->setSpacing(3);
        layoutBoutonsQuantite->setObjectName("layoutBoutonsQuantite");
        btnAugmenterQuantite = new QPushButton(corps);
        btnAugmenterQuantite->setObjectName("btnAugmenterQuantite");
        btnAugmenterQuantite->setMinimumSize(QSize(42, 22));
        btnAugmenterQuantite->setMaximumSize(QSize(42, 22));
        btnAugmenterQuantite->setAutoDefault(false);

        layoutBoutonsQuantite->addWidget(btnAugmenterQuantite);

        btnReduireQuantite = new QPushButton(corps);
        btnReduireQuantite->setObjectName("btnReduireQuantite");
        btnReduireQuantite->setMinimumSize(QSize(42, 22));
        btnReduireQuantite->setMaximumSize(QSize(42, 22));
        btnReduireQuantite->setAutoDefault(false);

        layoutBoutonsQuantite->addWidget(btnReduireQuantite);


        layoutQuantite->addLayout(layoutBoutonsQuantite);


        layoutChampQte->addLayout(layoutQuantite);


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

        layoutActionsArticles = new QHBoxLayout();
        layoutActionsArticles->setObjectName("layoutActionsArticles");
        btnAjouterArticle = new QPushButton(corps);
        btnAjouterArticle->setObjectName("btnAjouterArticle");
        btnAjouterArticle->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnAjouterArticle->setAutoDefault(false);

        layoutActionsArticles->addWidget(btnAjouterArticle);

        spacerActionsArticles = new QSpacerItem(24, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutActionsArticles->addItem(spacerActionsArticles);

        btnRetirerArticle = new QPushButton(corps);
        btnRetirerArticle->setObjectName("btnRetirerArticle");
        btnRetirerArticle->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnRetirerArticle->setAutoDefault(false);

        layoutActionsArticles->addWidget(btnRetirerArticle);


        layoutCorps->addLayout(layoutActionsArticles);

        tableArticlesCommande = new QTableWidget(corps);
        if (tableArticlesCommande->columnCount() < 3)
            tableArticlesCommande->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableArticlesCommande->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableArticlesCommande->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableArticlesCommande->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableArticlesCommande->setObjectName("tableArticlesCommande");
        tableArticlesCommande->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableArticlesCommande->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableArticlesCommande->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableArticlesCommande->setShowGrid(false);
        tableArticlesCommande->setColumnCount(3);
        tableArticlesCommande->verticalHeader()->setVisible(false);
        tableArticlesCommande->verticalHeader()->setDefaultSectionSize(42);

        layoutCorps->addWidget(tableArticlesCommande);

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


        retranslateUi(NouveauAchat);

        btnEnregistrer->setDefault(true);


        QMetaObject::connectSlotsByName(NouveauAchat);
    } // setupUi

    void retranslateUi(QDialog *NouveauAchat)
    {
        NouveauAchat->setWindowTitle(QCoreApplication::translate("NouveauAchat", "Achat", nullptr));
        titleLabel->setText(QCoreApplication::translate("NouveauAchat", "Nouvel achat", nullptr));
        labelClient->setText(QCoreApplication::translate("NouveauAchat", "Client", nullptr));
        labelMateriel->setText(QCoreApplication::translate("NouveauAchat", "Mat\303\251riel", nullptr));
        labelStock->setText(QCoreApplication::translate("NouveauAchat", "Stock actuel : \342\200\224", nullptr));
        labelQuantite->setText(QCoreApplication::translate("NouveauAchat", "Quantit\303\251", nullptr));
        champQuantite->setText(QCoreApplication::translate("NouveauAchat", "1", nullptr));
        btnAugmenterQuantite->setText(QCoreApplication::translate("NouveauAchat", "+", nullptr));
        btnReduireQuantite->setText(QCoreApplication::translate("NouveauAchat", "\342\210\222", nullptr));
        labelDate->setText(QCoreApplication::translate("NouveauAchat", "Date d\342\200\231achat", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("NouveauAchat", "dd/MM/yyyy", nullptr));
        btnAjouterArticle->setText(QCoreApplication::translate("NouveauAchat", "Ajouter cet article \303\240 la commande", nullptr));
        btnRetirerArticle->setText(QCoreApplication::translate("NouveauAchat", "Retirer la ligne", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableArticlesCommande->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("NouveauAchat", "ARTICLE", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableArticlesCommande->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("NouveauAchat", "QUANTIT\303\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableArticlesCommande->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("NouveauAchat", "MONTANT", nullptr));
        labelMontantTitre->setText(QCoreApplication::translate("NouveauAchat", "Montant", nullptr));
        labelStockInfo->setText(QCoreApplication::translate("NouveauAchat", "Choisissez un mat\303\251riel", nullptr));
        labelMontantValeur->setText(QCoreApplication::translate("NouveauAchat", "0 Ar", nullptr));
        labelErreur->setText(QString());
        btnAnnuler->setText(QCoreApplication::translate("NouveauAchat", "Annuler", nullptr));
        btnEnregistrer->setText(QCoreApplication::translate("NouveauAchat", "Enregistrer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NouveauAchat: public Ui_NouveauAchat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOUVEAUACHAT_H
