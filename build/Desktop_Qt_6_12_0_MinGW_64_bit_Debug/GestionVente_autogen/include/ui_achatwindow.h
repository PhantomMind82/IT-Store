/********************************************************************************
** Form generated from reading UI file 'achatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACHATWINDOW_H
#define UI_ACHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
#include "achats/logowidget.h"

QT_BEGIN_NAMESPACE

class Ui_AchatWindow
{
public:
    QVBoxLayout *layoutPrincipal;
    QFrame *entete;
    QHBoxLayout *layoutEntete;
    LogoWidget *logo;
    QLabel *titreMarque;
    QSpacerItem *spacerEntete;
    QLabel *slogan;
    QWidget *corps;
    QVBoxLayout *layoutCorps;
    QHBoxLayout *layoutBarre;
    QPushButton *btnAccueil;
    QHBoxLayout *layoutTitre;
    QLabel *iconeTitre;
    QVBoxLayout *layoutTextesTitre;
    QLabel *titrePage;
    QLabel *sousTitre;
    QSpacerItem *spacerBarre;
    QFrame *boiteRecherche;
    QHBoxLayout *layoutRecherche;
    QLabel *iconeRecherche;
    QLineEdit *champRecherche;
    QHBoxLayout *layoutActions;
    QPushButton *btnNouveau;
    QPushButton *btnModifier;
    QPushButton *btnFacture;
    QPushButton *btnSupprimer;
    QFrame *carte;
    QVBoxLayout *layoutCarte;
    QTableWidget *tableAchats;
    QHBoxLayout *layoutPied;
    QLabel *labelAide;
    QSpacerItem *spacerPied;
    QLabel *labelTotalTexte;
    QLabel *labelTotalValeur;

    void setupUi(QDialog *AchatWindow)
    {
        if (AchatWindow->objectName().isEmpty())
            AchatWindow->setObjectName("AchatWindow");
        AchatWindow->resize(1262, 860);
        AchatWindow->setMinimumSize(QSize(1000, 680));
        layoutPrincipal = new QVBoxLayout(AchatWindow);
        layoutPrincipal->setSpacing(0);
        layoutPrincipal->setObjectName("layoutPrincipal");
        layoutPrincipal->setContentsMargins(0, 0, 0, 0);
        entete = new QFrame(AchatWindow);
        entete->setObjectName("entete");
        layoutEntete = new QHBoxLayout(entete);
        layoutEntete->setSpacing(18);
        layoutEntete->setObjectName("layoutEntete");
        layoutEntete->setContentsMargins(56, 18, 56, 18);
        logo = new LogoWidget(entete);
        logo->setObjectName("logo");

        layoutEntete->addWidget(logo);

        titreMarque = new QLabel(entete);
        titreMarque->setObjectName("titreMarque");

        layoutEntete->addWidget(titreMarque);

        spacerEntete = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutEntete->addItem(spacerEntete);

        slogan = new QLabel(entete);
        slogan->setObjectName("slogan");

        layoutEntete->addWidget(slogan);


        layoutPrincipal->addWidget(entete);

        corps = new QWidget(AchatWindow);
        corps->setObjectName("corps");
        layoutCorps = new QVBoxLayout(corps);
        layoutCorps->setSpacing(24);
        layoutCorps->setObjectName("layoutCorps");
        layoutCorps->setContentsMargins(56, 32, 56, 32);
        layoutBarre = new QHBoxLayout();
        layoutBarre->setSpacing(20);
        layoutBarre->setObjectName("layoutBarre");
        btnAccueil = new QPushButton(corps);
        btnAccueil->setObjectName("btnAccueil");
        btnAccueil->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnAccueil->setAutoDefault(false);

        layoutBarre->addWidget(btnAccueil);

        layoutTitre = new QHBoxLayout();
        layoutTitre->setSpacing(14);
        layoutTitre->setObjectName("layoutTitre");
        iconeTitre = new QLabel(corps);
        iconeTitre->setObjectName("iconeTitre");

        layoutTitre->addWidget(iconeTitre);

        layoutTextesTitre = new QVBoxLayout();
        layoutTextesTitre->setSpacing(2);
        layoutTextesTitre->setObjectName("layoutTextesTitre");
        titrePage = new QLabel(corps);
        titrePage->setObjectName("titrePage");

        layoutTextesTitre->addWidget(titrePage);

        sousTitre = new QLabel(corps);
        sousTitre->setObjectName("sousTitre");

        layoutTextesTitre->addWidget(sousTitre);


        layoutTitre->addLayout(layoutTextesTitre);


        layoutBarre->addLayout(layoutTitre);

        spacerBarre = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutBarre->addItem(spacerBarre);

        boiteRecherche = new QFrame(corps);
        boiteRecherche->setObjectName("boiteRecherche");
        layoutRecherche = new QHBoxLayout(boiteRecherche);
        layoutRecherche->setSpacing(8);
        layoutRecherche->setObjectName("layoutRecherche");
        layoutRecherche->setContentsMargins(16, 0, 16, 0);
        iconeRecherche = new QLabel(boiteRecherche);
        iconeRecherche->setObjectName("iconeRecherche");

        layoutRecherche->addWidget(iconeRecherche);

        champRecherche = new QLineEdit(boiteRecherche);
        champRecherche->setObjectName("champRecherche");
        champRecherche->setClearButtonEnabled(true);

        layoutRecherche->addWidget(champRecherche);


        layoutBarre->addWidget(boiteRecherche);


        layoutCorps->addLayout(layoutBarre);

        layoutActions = new QHBoxLayout();
        layoutActions->setSpacing(16);
        layoutActions->setObjectName("layoutActions");
        btnNouveau = new QPushButton(corps);
        btnNouveau->setObjectName("btnNouveau");
        btnNouveau->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnNouveau->setAutoDefault(false);

        layoutActions->addWidget(btnNouveau);

        btnModifier = new QPushButton(corps);
        btnModifier->setObjectName("btnModifier");
        btnModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnModifier->setAutoDefault(false);

        layoutActions->addWidget(btnModifier);

        btnFacture = new QPushButton(corps);
        btnFacture->setObjectName("btnFacture");
        btnFacture->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnFacture->setAutoDefault(false);

        layoutActions->addWidget(btnFacture);

        btnSupprimer = new QPushButton(corps);
        btnSupprimer->setObjectName("btnSupprimer");
        btnSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnSupprimer->setAutoDefault(false);

        layoutActions->addWidget(btnSupprimer);

        layoutActions->setStretch(0, 1);
        layoutActions->setStretch(1, 1);
        layoutActions->setStretch(2, 1);
        layoutActions->setStretch(3, 1);

        layoutCorps->addLayout(layoutActions);

        carte = new QFrame(corps);
        carte->setObjectName("carte");
        layoutCarte = new QVBoxLayout(carte);
        layoutCarte->setSpacing(0);
        layoutCarte->setObjectName("layoutCarte");
        layoutCarte->setContentsMargins(0, 0, 0, 0);
        tableAchats = new QTableWidget(carte);
        if (tableAchats->columnCount() < 6)
            tableAchats->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableAchats->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableAchats->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableAchats->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableAchats->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableAchats->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableAchats->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableAchats->setObjectName("tableAchats");
        tableAchats->setFrameShape(QFrame::NoFrame);
        tableAchats->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableAchats->setSelectionMode(QAbstractItemView::SingleSelection);
        tableAchats->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableAchats->setShowGrid(false);
        tableAchats->setColumnCount(6);
        tableAchats->verticalHeader()->setVisible(false);

        layoutCarte->addWidget(tableAchats);


        layoutCorps->addWidget(carte);

        layoutPied = new QHBoxLayout();
        layoutPied->setSpacing(8);
        layoutPied->setObjectName("layoutPied");
        labelAide = new QLabel(corps);
        labelAide->setObjectName("labelAide");

        layoutPied->addWidget(labelAide);

        spacerPied = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutPied->addItem(spacerPied);

        labelTotalTexte = new QLabel(corps);
        labelTotalTexte->setObjectName("labelTotalTexte");

        layoutPied->addWidget(labelTotalTexte);

        labelTotalValeur = new QLabel(corps);
        labelTotalValeur->setObjectName("labelTotalValeur");

        layoutPied->addWidget(labelTotalValeur);


        layoutCorps->addLayout(layoutPied);

        layoutCorps->setStretch(2, 1);

        layoutPrincipal->addWidget(corps);


        retranslateUi(AchatWindow);

        QMetaObject::connectSlotsByName(AchatWindow);
    } // setupUi

    void retranslateUi(QDialog *AchatWindow)
    {
        AchatWindow->setWindowTitle(QCoreApplication::translate("AchatWindow", "IT Store - Achats", nullptr));
        titreMarque->setText(QCoreApplication::translate("AchatWindow", "IT Store", nullptr));
        slogan->setText(QCoreApplication::translate("AchatWindow", "Votre partenaire en mat\303\251riel informatique", nullptr));
        btnAccueil->setText(QCoreApplication::translate("AchatWindow", "\342\206\220 Accueil", nullptr));
        iconeTitre->setText(QString());
        titrePage->setText(QCoreApplication::translate("AchatWindow", "Achats", nullptr));
        sousTitre->setText(QCoreApplication::translate("AchatWindow", "Les achats de vos clients", nullptr));
        iconeRecherche->setText(QString());
        champRecherche->setPlaceholderText(QCoreApplication::translate("AchatWindow", "Client : num\303\251ro ou nom", nullptr));
        btnNouveau->setText(QCoreApplication::translate("AchatWindow", "Nouvel achat", nullptr));
        btnModifier->setText(QCoreApplication::translate("AchatWindow", "Modifier", nullptr));
        btnFacture->setText(QCoreApplication::translate("AchatWindow", "Facture PDF", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("AchatWindow", "Supprimer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableAchats->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AchatWindow", "N\302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableAchats->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AchatWindow", "CLIENT", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableAchats->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AchatWindow", "MAT\303\211RIEL", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableAchats->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AchatWindow", "QT\303\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableAchats->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AchatWindow", "DATE", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableAchats->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("AchatWindow", "MONTANT", nullptr));
        labelAide->setText(QCoreApplication::translate("AchatWindow", "S\303\251lectionnez un achat pour le modifier, le supprimer ou \303\251diter sa facture.", nullptr));
        labelTotalTexte->setText(QCoreApplication::translate("AchatWindow", "Total", nullptr));
        labelTotalValeur->setText(QCoreApplication::translate("AchatWindow", "0 Ar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AchatWindow: public Ui_AchatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACHATWINDOW_H
