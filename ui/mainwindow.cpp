#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clients/clientwindow.h"
#include "materiels/materielwindow.h"
#include "achats/achatwindow.h"
#include "ventes/ventewindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("IT Store");
    resize(940, 620);

    QWidget *central = new QWidget;
    central->setObjectName("central");
    central->setStyleSheet("#central { background-color: rgb(240, 242, 245); }");
    setCentralWidget(central);

    QVBoxLayout *principal = new QVBoxLayout(central);
    principal->setContentsMargins(0, 0, 0, 0);
    principal->setSpacing(0);

    // ---------- Bandeau bleu ----------
    QWidget *entete = new QWidget;
    entete->setObjectName("entete");
    entete->setFixedHeight(85);
    entete->setStyleSheet("#entete { background: qlineargradient("
                          "x1:0, y1:0, x2:1, y2:0, stop:0 #2a66b8, stop:1 #1e4f9c); }");

    QLabel *logo = new QLabel("🏷️  IT Store");
    logo->setStyleSheet("color: white; font-size: 36px; font-weight: bold; background: transparent; font-family: Georgia, 'Times New Roman', Times, serif");

    QLabel *slogan = new QLabel("Votre partenaire en matériel informatique");
    slogan->setStyleSheet("color: white; font-size: 10px; background: transparent; font-family: Verdana, Geneva, Tahoma, sans-serif");

    QHBoxLayout *layEntete = new QHBoxLayout(entete);
    layEntete->setContentsMargins(40, 0, 40, 0);
    layEntete->addWidget(logo);
    layEntete->addStretch();
    layEntete->addWidget(slogan);

    principal->addWidget(entete);

    // ---------- Titre ----------
    QLabel *titre = new QLabel("Bienvenue sur IT Store");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("color: #0f2350; font-size: 38px; font-weight: bold;");

    QLabel *sousTitre = new QLabel("Choisissez une section pour commencer");
    sousTitre->setAlignment(Qt::AlignCenter);
    sousTitre->setStyleSheet("color: #5a6785; font-size: 18px;");

    // ---------- Cartes ----------
    QPushButton *carteMat = creerCarte("💻", "Materiel", "#2bb58a", "#1a9370");
    QPushButton *carteCli = creerCarte("👥", "Client",   "#2f78e0", "#1f5cc0");
    QPushButton *carteAch = creerCarte("🛒", "Achat",    "#ff9420", "#f07a10");
    QPushButton *carteVen = creerCarte("💰", "Vente",    "#a855f7", "#7e22ce");


    QHBoxLayout *layCartes = new QHBoxLayout;
    layCartes->setSpacing(40);
    layCartes->setContentsMargins(50, 0, 50, 0);
    layCartes->addStretch();
    layCartes->addWidget(carteMat);
    layCartes->addWidget(carteCli);
    layCartes->addWidget(carteAch);
    layCartes->addWidget(carteVen);
    layCartes->addStretch();

    principal->addStretch(1);
    principal->addWidget(titre);
    principal->addWidget(sousTitre);
    principal->addSpacing(35);
    principal->addLayout(layCartes);
    principal->addStretch(2);

    // ---------- Actions ----------
    connect(carteCli, &QPushButton::clicked, this, [this]() {
        ClientWindow fenetre(this);
        fenetre.exec();
    });

    connect(carteMat, &QPushButton::clicked, this, [this]() {
        MaterielWindow fenetre(this);
        fenetre.exec();
    });

    connect(carteAch, &QPushButton::clicked, this, [this]() {
        AchatWindow fenetre(this);
        fenetre.exec();
    });

    connect(carteVen, &QPushButton::clicked, this, [this]() {
        VenteWindow fenetre(this);
        fenetre.exec();
    });
}

QPushButton *MainWindow::creerCarte(const QString &icone, const QString &titre,
                                    const QString &couleur1, const QString &couleur2)
{
    QPushButton *carte = new QPushButton;
    carte->setFixedSize(200, 180);
    carte->setCursor(Qt::PointingHandCursor);
    carte->setStyleSheet(QString(
                             "QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                             " stop:0 %1, stop:1 %2); border: none; border-radius: 12px; }"
                             "QPushButton:hover { border: 3px solid rgba(255,255,255,150); }")
                             .arg(couleur1, couleur2));

    QLabel *cercle = new QLabel(icone);
    cercle->setFixedSize(100, 100);
    cercle->setAlignment(Qt::AlignCenter);
    cercle->setStyleSheet("background: rgba(255,255,255,60); border-radius: 50px;"
                          " font-size: 44px; color: white;");
    cercle->setAttribute(Qt::WA_TransparentForMouseEvents);

    QLabel *nom = new QLabel(titre);
    nom->setAlignment(Qt::AlignCenter);
    nom->setStyleSheet("background: transparent; color: white;"
                       " font-size: 26px; font-weight: bold;");
    nom->setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout *lay = new QVBoxLayout(carte);
    lay->setAlignment(Qt::AlignCenter);
    lay->setSpacing(12);
    lay->addWidget(cercle, 0, Qt::AlignHCenter);
    lay->addWidget(nom);

    return carte;
}

MainWindow::~MainWindow()
{
    delete ui;
}