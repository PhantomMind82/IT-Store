#include "ventewindow.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QFont>
#include <QDate>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
#include <QLocale>


VenteWindow::VenteWindow(QWidget *parent)
    : QDialog(parent) // Se base sur le plan de la maison standard (qui est parent)
{
    // ============================================================
    // 1. CONFIGURATION DE LA FENÊTRE
    // ============================================================

    setWindowTitle("VENTE");

    resize(1200, 720);
    setMinimumSize(1050, 650);

    setStyleSheet(R"(
        QDialog {
            background-color: #FAF9F6;
            color: #542C82;
        }

        QLabel {
            color: #183B43;
        }

        QLineEdit,
        QComboBox,
        QDateEdit {
            background-color: #FFFFFF;
            border: 1px solid #D9E1DF;
            border-radius: 7px;
            padding: 9px 12px;
            color: #183B43;
            font-size: 13px;
        }

        QLineEdit:focus,
        QComboBox:focus,
        QDateEdit:focus {
            border: 1px solid #2F5961;
        }

        QPushButton {
            background-color: #FFFFFF;
            border: 1px solid #D9E1DF;
            border-radius: 7px;
            padding: 9px 16px;
            color: #183B43;
            font-size: 13px;
        }

        QPushButton:hover {
            background-color: #F1F5F3;
        }

        QTableWidget {
            background-color: #FFFFFF;
            border: none;
            gridline-color: #E6ECEA;
            border-radius: 8px;
            color: #183B43;
            font-size: 13px;
        }

        QTableWidget::item {
            padding: 8px;
            border-bottom: 1px solid #E6ECEA;
        }

        QHeaderView::section {
            background-color: #F0E8F8;
            border: none;
            padding: 11px;
            color: #183B43;
            font-weight: bold;
            font-size: 12px;
        }

        /* ======================================================== */
        /* CORRECTION DES FLÈCHES ET DES ZONES DE CLIC INTERNES     */
        /* ======================================================== */

        /* 1. On réserve une place nette de 30px à droite pour les flèches */
        QComboBox, QDateEdit {
            padding-right: 30px;
        }

        /* 2. On positionne la zone cliquable du bouton tout à droite */
        QComboBox::drop-down, QDateEdit::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 30px;
            border: none;
        }


    )");




    // ============================================================
    // 2. TITRE ET DESCRIPTION
    // ============================================================

    header = new QFrame();

    header->setStyleSheet(R"(
        QFrame {
            background-color: #6F3FAF;
            border-radius: 10px;
        }
    )");

    titreLabel = new QLabel("Matériels vendus à un client");

    QFont titreFont;
    titreFont.setPointSize(23);
    titreFont.setBold(true);

    titreLabel->setFont(titreFont);

    titreLabel->setStyleSheet(
        "color: white;"
    );

    descriptionLabel = new QLabel(
        "Liste des matériels qu'un client a acheté, "
        "avec les détails de chaque vente."
    );

    descriptionLabel->setStyleSheet(
        "color: #EDE4F7; font-size: 13px;"
    );

    QVBoxLayout *headerLayout = new QVBoxLayout(header);

    headerLayout->setContentsMargins(22, 16, 22, 16);
    headerLayout->setSpacing(4);
    headerLayout->addWidget(titreLabel);
    headerLayout->addWidget(descriptionLabel);

    // ============================================================
    // 3. RECHERCHE CLIENT
    // ============================================================

    QLabel *titreRecherche = new QLabel("Rechercher un client");

    QFont sousTitreFont;
    sousTitreFont.setPointSize(14);
    sousTitreFont.setBold(true);

    titreRecherche->setFont(sousTitreFont);


    btnRechercheNumero = new QPushButton("Par numéro");
    btnRechercheNom = new QPushButton("Par nom");

    btnRechercheNumero->setCheckable(true);
    btnRechercheNom->setCheckable(true);

    btnRechercheNumero->setChecked(true); // Option recherche par défaut

    btnRechercheNumero->setStyleSheet(R"(
        QPushButton {
            background-color: #F66D5B;
            color: white;
            border: none;
            border-radius: 7px;
            padding: 9px 25px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #E85F4E;
        }
    )");

    btnRechercheNom->setStyleSheet(R"(
        QPushButton {
            background-color: #FFFFFF;
            color: #183B43;
            border: 1px solid #D9E1DF;
            border-radius: 7px;
            padding: 9px 25px;
        }

        QPushButton:hover {
            background-color: #F1F5F3;
        }
    )");


    rechercheClient = new QLineEdit();

    rechercheClient->setPlaceholderText(
        "Ex : 2 ou Rabe "
    );

    rechercheClient->setMinimumHeight(40);


    btnRechercher = new QPushButton("🔍  Rechercher");

    btnRechercher->setMinimumHeight(40);

    btnRechercher->setStyleSheet(R"(
        QPushButton {
            background-color: #542C82;
            color: white;
            border: none;
            border-radius: 7px;
            padding: 9px 20px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #633695;
        }


    )");


    // ============================================================
    // 4. INFORMATIONS CLIENT
    // ============================================================

    QFrame *clientFrame = new QFrame();

    clientFrame->setStyleSheet(R"(
        QFrame {
            background-color: #F0E8F8;
            border-radius: 7px;
        }
    )");


    QLabel *clientTitre = new QLabel("👤  Client");

    clientTitre->setFont(sousTitreFont);


    QLabel *labelNumero = new QLabel("N° Client");
    QLabel *labelNom = new QLabel("Nom");

    clientNumero = new QLabel(" ");
    clientNom = new QLabel(" ");

    clientNumero->setStyleSheet("font-weight: bold;");
    clientNom->setStyleSheet("font-weight: bold;");



    QGridLayout *clientLayout = new QGridLayout(clientFrame);

    clientLayout->setContentsMargins(18, 14, 18, 14);

    clientLayout->addWidget(clientTitre, 0, 0, 1, 2);

    clientLayout->addWidget(labelNumero, 1, 0);
    clientLayout->addWidget(clientNumero, 1, 1);

    clientLayout->addWidget(labelNom, 2, 0);
    clientLayout->addWidget(clientNom, 2, 1);

    // Élargir les colonnes et répartir l'espace disponible
    clientLayout->setColumnStretch(0, 1);
    clientLayout->setColumnStretch(1, 2);

    // Donner une hauteur minimale aux deux lignes
    labelNumero->setMinimumHeight(38);
    clientNumero->setMinimumHeight(38);

    labelNom->setMinimumHeight(38);
    clientNom->setMinimumHeight(38);

    // Style des valeurs
    clientNumero->setStyleSheet(
        "font-weight: bold; padding: 6px 10px;"
        );

    clientNom->setStyleSheet(
        "font-weight: bold; padding: 6px 10px;"
        );

    // ============================================================
    // 5. FILTRE PÉRIODE
    // ============================================================

    QFrame *periodeFrame = new QFrame();

    QLabel *periodeTitre = new QLabel("📅  Période");

    periodeTitre->setFont(sousTitreFont);

    periodeCombo = new QComboBox();

    periodeCombo->addItem("Entre 2 dates");
    periodeCombo->addItem("Un mois");
    periodeCombo->addItem("Une année");

    periodeCombo->setCurrentIndex(0);

    QLabel *labelDu = new QLabel("Du");
    QLabel *labelAu = new QLabel("Au");


    dateDebut = new QDateEdit();
    dateFin = new QDateEdit();

    dateDebut->setCalendarPopup(true);
    dateFin->setCalendarPopup(true);

    dateDebut->setDisplayFormat("dd/MM/yyyy");
    dateFin->setDisplayFormat("dd/MM/yyyy");

    dateDebut->setDate(QDate::currentDate());
    dateFin->setDate(QDate::currentDate());

    dateDebut->setMaximumDate(QDate::currentDate());
    dateFin->setMaximumDate(QDate::currentDate());

    dateDebut->setToolTip("Choisir la date de début");
    dateFin->setToolTip("Choisir la date de fin");

    dateDebut->setDateRange(
        QDate(2000, 1, 1),
        QDate::currentDate()
    );

    dateFin->setDateRange(
        QDate(2000, 1, 1),
        QDate::currentDate()
    );


    QGridLayout *periodeLayout = new QGridLayout(periodeFrame);

    periodeLayout->setContentsMargins(10, 10, 10, 10);

    periodeLayout->addWidget(periodeTitre, 0, 0, 1, 2);

    periodeLayout->addWidget(periodeCombo, 1, 0, 1, 2);

    periodeLayout->addWidget(labelDu, 2, 0);
    periodeLayout->addWidget(labelAu, 2, 1);

    periodeLayout->addWidget(dateDebut, 3, 0);
    periodeLayout->addWidget(dateFin, 3, 1);


    // ============================================================
    // 6. CONTENEUR DE LA ZONE DU HAUT
    // ============================================================

    QFrame *topFrame = new QFrame();

    topFrame->setStyleSheet(R"(
        QFrame {
            background-color: #FFFFFF;
            border: 1px solid #E2D8EA;
            border-radius: 8px;
        }
    )");


    QHBoxLayout *topLayout = new QHBoxLayout(topFrame);

    topLayout->setContentsMargins(14, 14, 14, 14);
    topLayout->setSpacing(18);


    // ----- Bloc recherche -----

    QVBoxLayout *rechercheLayout = new QVBoxLayout();

    rechercheLayout->addWidget(titreRecherche);


    QHBoxLayout *typeRechercheLayout = new QHBoxLayout();

    typeRechercheLayout->addWidget(btnRechercheNumero);
    typeRechercheLayout->addWidget(btnRechercheNom);

    rechercheLayout->addLayout(typeRechercheLayout);


    QHBoxLayout *inputRechercheLayout = new QHBoxLayout();

    inputRechercheLayout->addWidget(rechercheClient);
    inputRechercheLayout->addWidget(btnRechercher);

    rechercheLayout->addLayout(inputRechercheLayout);


    // ----- Ajout des trois blocs -----

    topLayout->addLayout(rechercheLayout, 2);
    topLayout->addWidget(clientFrame, 2);
    topLayout->addWidget(periodeFrame, 2);


    // ============================================================
    // 7. TITRE DU TABLEAU
    // ============================================================

    QLabel *titreTableau = new QLabel("🛒  Liste des matériels vendus");

    titreTableau->setFont(sousTitreFont);


    // ============================================================
    // 8. TABLEAU
    // ============================================================

    tableVentes = new QTableWidget();

    tableVentes->setColumnCount(6);

    tableVentes->setHorizontalHeaderLabels({
        "#",
        "Désignation",
        "PU (Ar)",
        "Quantité",
        "Montant (Ar)",
        "Date d'achat"
    });

    tableVentes->setRowCount(0);


    // ----------------------------
    // Configuration tableau
    // ----------------------------

    tableVentes->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVentes->setSelectionMode(QAbstractItemView::SingleSelection);

    tableVentes->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableVentes->verticalHeader()->setVisible(false);

    tableVentes->setAlternatingRowColors(false);

    tableVentes->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
    );

    tableVentes->horizontalHeader()->setSectionResizeMode(
        0,
        QHeaderView::ResizeToContents
    );


    // ============================================================
    // 9. TOTAL GÉNÉRAL
    // ============================================================

    QFrame *totalFrame = new QFrame();

    totalFrame->setStyleSheet(R"(
        QFrame {
            background-color: #F3ECF8;
            border-radius: 7px;
        }
    )");


    QLabel *labelTotal = new QLabel("Total général :");

    labelTotal->setFont(sousTitreFont);


    totalGeneral = new QLabel("O Ar"); // TODO : à modifier

    totalGeneral->setAlignment(Qt::AlignCenter);

    totalGeneral->setMinimumWidth(145);

    totalGeneral->setStyleSheet(R"(
        QLabel {
            background-color: #F66D5B;
            color: white;
            border-radius: 6px;
            padding: 10px 15px;
            font-size: 15px;
            font-weight: bold;
        }
    )");


    QHBoxLayout *totalLayout = new QHBoxLayout(totalFrame);

    totalLayout->setContentsMargins(12, 8, 12, 8);

    totalLayout->addStretch();
    totalLayout->addWidget(labelTotal);
    totalLayout->addWidget(totalGeneral);


    // ============================================================
    // 10. BOUTONS DU BAS
    // ============================================================



    btnActualiser = new QPushButton("⟳  Actualiser");

    btnImprimer = new QPushButton("▣  Imprimer / Exporter");


    btnImprimer->setStyleSheet(R"(
        QPushButton {
            background-color: #542C82;
            color: white;
            border: none;
            border-radius: 7px;
            padding: 10px 17px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #633695;
        }
    )");


    QHBoxLayout *bottomLayout = new QHBoxLayout();


    bottomLayout->addStretch();

    bottomLayout->addWidget(btnActualiser);
    bottomLayout->addWidget(btnImprimer);


    // ============================================================
    // 11. BLOC PRINCIPAL : TABLEAU
    // ============================================================

    QFrame *tableFrame = new QFrame();

    tableFrame->setStyleSheet(R"(
        QFrame {
            background-color: #FFFFFF;
            border: 1px solid #E2D8EA;
            border-radius: 8px;
        }
    )");


    QVBoxLayout *tableLayout = new QVBoxLayout(tableFrame);

    tableLayout->setContentsMargins(14, 14, 14, 14);

    tableLayout->addWidget(titreTableau);
    tableLayout->addWidget(tableVentes, 1);
    tableLayout->addWidget(totalFrame);
    tableLayout->addLayout(bottomLayout);


    // ============================================================
    // 12. BLOC RÉCAPITULATIF
    // ============================================================
    QFrame *recapFrame = new QFrame();
    recapFrame->setStyleSheet(R"(
    QFrame {
        background-color: #FFFFFF;
        border: 1px solid #E2D8EA;
        border-radius: 8px;
    }
)");

    QLabel *recapTitre = new QLabel("☷ Récapitulatif");
    recapTitre->setFont(sousTitreFont);
    recapTitre->setStyleSheet(R"(
    QLabel {
        background-color: #FFF0EC;
        border-radius: 6px;
        padding: 12px;
        color: #183B43;
    }
)");

    // Style pour les étiquettes de gauche
    QString labelStyle = "font-size: 13px; color: #555555;";

    QLabel *recapLabelClient = new QLabel("Client");
    QLabel *recapLabelArticles = new QLabel("Nombre d'articles");
    QLabel *recapLabelMontant = new QLabel("Montant total");

    recapLabelClient->setStyleSheet(labelStyle);
    recapLabelArticles->setStyleSheet(labelStyle);
    recapLabelMontant->setStyleSheet(labelStyle);

    // Style pour les valeurs de droite (avec fond blanc, bordure grise et padding pour simuler des champs propres)
    QString valeurStyle = R"(
    QLabel {
        font-weight: bold;
        font-size: 14px;
        border: 1px solid #E2D8EA;
        border-radius: 6px;
        padding: 6px 12px;
        background-color: #FFFFFF;
    }
)";

    recapClient = new QLabel(" ");
    recapArticles = new QLabel(" ");
    recapMontant = new QLabel(" ");

    recapClient->setStyleSheet(valeurStyle);
    recapArticles->setStyleSheet(valeurStyle);
    recapMontant->setStyleSheet(valeurStyle);

    // Alignement vertical au centre pour que le texte soit bien aligné avec les boîtes de droite
    recapLabelClient->setAlignment(Qt::AlignVCenter);
    recapLabelArticles->setAlignment(Qt::AlignVCenter);
    recapLabelMontant->setAlignment(Qt::AlignVCenter);

    QGridLayout *recapInfos = new QGridLayout();
    recapInfos->setHorizontalSpacing(12);
    recapInfos->setVerticalSpacing(14);
    recapInfos->setContentsMargins(0, 0, 0, 0);

    recapInfos->addWidget(recapLabelClient, 0, 0);
    recapInfos->addWidget(recapClient, 0, 1);
    recapInfos->addWidget(recapLabelArticles, 1, 0);
    recapInfos->addWidget(recapArticles, 1, 1);
    recapInfos->addWidget(recapLabelMontant, 2, 0);
    recapInfos->addWidget(recapMontant, 2, 1);

    // Permet aux colonnes de s'étendre proportionnellement
    recapInfos->setColumnStretch(0, 1);
    recapInfos->setColumnStretch(1, 1);

    QVBoxLayout *recapLayout = new QVBoxLayout(recapFrame);
    recapLayout->setContentsMargins(16, 16, 16, 16);
    recapLayout->addWidget(recapTitre);
    recapLayout->addSpacing(12); // Plus d'espace sous le titre
    recapLayout->addLayout(recapInfos);

    // Remplacer addStretch() par un espacement fixe ou proportionnel pour éviter de tout tasser vers le haut
    recapLayout->addStretch();



    // ============================================================
    // 13. PARTIE CENTRALE
    // ============================================================

    QHBoxLayout *mainContentLayout = new QHBoxLayout();

    mainContentLayout->setSpacing(18);

    mainContentLayout->addWidget(tableFrame, 4);
    mainContentLayout->addWidget(recapFrame, 1);

    mainContentLayout->setStretch(0, 4);
    mainContentLayout->setStretch(1, 1);

    // ============================================================
    // 14. LAYOUT PRINCIPAL DE LA FENÊTRE
    // ============================================================

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(20, 18, 20, 20);

    mainLayout->setSpacing(14);


    // En-tête
    mainLayout->addWidget(header);

    // Zone recherche / client / période
    mainLayout->addWidget(topFrame);


    // Zone tableau + récapitulatif
    mainLayout->addLayout(mainContentLayout, 1); // Non-compression du tableau


    setLayout(mainLayout);


    // ============================================================
    // 15. INTERACTIONS & BASE DE DONNéES
    // ============================================================

    // Bouton "Par numéro"
    connect(btnRechercheNumero, &QPushButton::clicked,
            this, [this]()
            {
                btnRechercheNumero->setChecked(true);
                btnRechercheNom->setChecked(false);

                btnRechercheNumero->setStyleSheet(R"(
                    QPushButton {
                        background-color: #F66D5B;
                        color: white;
                        border: none;
                        border-radius: 7px;
                        padding: 9px 25px;
                        font-weight: bold;
                    }
                )");

                btnRechercheNom->setStyleSheet(R"(
                    QPushButton {
                        background-color: #FFFFFF;
                        color: #183B43;
                        border: 1px solid #D9E1DF;
                        border-radius: 7px;
                        padding: 9px 25px;
                    }
                )");

                rechercheClient->setPlaceholderText(
                    "Ex. : 2"
                    );
    });


    // Bouton "Par nom"
    connect(btnRechercheNom, &QPushButton::clicked,
            this, [this]()
            {
                btnRechercheNom->setChecked(true);
                btnRechercheNumero->setChecked(false);

                btnRechercheNom->setStyleSheet(R"(
            QPushButton {
                background-color: #F66D5B;
                color: white;
                border: none;
                border-radius: 7px;
                padding: 9px 25px;
                font-weight: bold;
            }
        )");

                btnRechercheNumero->setStyleSheet(R"(
            QPushButton {
                background-color: #FFFFFF;
                color: #183B43;
                border: 1px solid #D9E1DF;
                border-radius: 7px;
                padding: 9px 25px;
            }
        )");

                rechercheClient->setPlaceholderText(
                    "Ex. : Rabe"
                    );
    });


    // Bouton rechercher
    connect(btnRechercher, &QPushButton::clicked,
            this, [this]()
            {
        /*
         * Pour le moment, aucune recherche SQLite.
         *
         * Plus tard :
         * 1. récupérer le texte de recherche
         * 2. chercher le client dans SQLite
         * 3. récupérer ses ventes
         * 4. remplir le tableau
         * 5. mettre à jour le récapitulatif
        */

        // 1. Récupérer le texte saisi
        const QString recherche = rechercheClient->text().trimmed();

        if (recherche.isEmpty()) {
            QMessageBox::warning(
                this,
                "Recherche",
                "Veuillez saisir un numéro ou un nom de client."
            );
            return;
        }

        // 2. Vérifier la connexion SQLite
        QSqlDatabase db = QSqlDatabase::database();

        if (!db.isOpen()) {
            QMessageBox::critical(
                this,
                "Base de données",
                "La connexion SQlite n'est pas ouverte."
            );
            return;
        }

        // DIAGNOSTIC : vérifier les clients présents dans la base utilisée
        // ---------------------------------------------------------------------------------------------- //
        // ---------------------------------------------------------------------------------------------- //
        QSqlQuery diagnostic(db);

        if (diagnostic.exec("SELECT numClient, nom FROM client")) {
            QString listeClients;

            while (diagnostic.next()) {
                listeClients +=
                    diagnostic.value("numClient").toString()
                    + " - "
                    + diagnostic.value("nom").toString()
                    + "\n";
            }

            QMessageBox::information(
                this,
                "Diagnostic SQLite",
                listeClients.isEmpty()
                    ? "La table client est vide."
                    : "Clients présents dans la base :\n\n" + listeClients
                );
        } else {
            QMessageBox::critical(
                this,
                "Diagnostic SQLite",
                diagnostic.lastError().text()
                );
        }

        // ---------------------------------------------------------------------------------------------- //
        // ---------------------------------------------------------------------------------------------- //

        // 3. Rechercher le client par numéro ou par nom
        QSqlQuery clientQuery(db);
        QString sqlClient;

        if (btnRechercheNumero->isChecked()) {
            sqlClient =
                "SELECT numClient, nom "
                "FROM client "
                "WHERE numClient = ?";
        }
        else
        {
            sqlClient =
                "SELECT numClient, nom "
                "FROM client "
                "WHERE nom LIKE ? COLLATE NOCASE "
                "ORDER BY nom";
        }

        if (!clientQuery.prepare(sqlClient)) {
            QMessageBox::critical(
                this,
                "Erreur SQL",
                "Préparation de la requête impossible :\n"
                    + clientQuery.lastError().text()
                );
            return;
        }



        // Un seul paramètre ? dans chaque requête
        if (btnRechercheNumero->isChecked()) {
            clientQuery.addBindValue(recherche);
        } else {
            clientQuery.addBindValue("%" + recherche + "%");
        }

        if (!clientQuery.exec()) {
            QMessageBox::critical(
                this,
                "Erreur SQL",
                clientQuery.lastError().text()
                );
            return;
        }

        // 4. Vérifier que le client existe
        if (!clientQuery.next()) {
            tableVentes->setRowCount(0);
            clientNumero->setText("-");
            clientNom->setText("Client introuvable");
            recapClient->setText("-");
            recapArticles->setText("0");
            recapMontant->setText("0 Ar");
            totalGeneral->setText("0 Ar");

            QMessageBox::information(
                this,
                "Recherche",
                "Aucun client correspondant."
            );

            return;
        }

        const QString idClient = clientQuery.value("numClient").toString();
        const QString nomClient = clientQuery.value("nom").toString();


        clientNumero->setText(idClient);
        clientNom->setText(nomClient);

        // -------------------------------------------------------------------- //
        // 5. Récupérer les achats de ce client
        QSqlQuery ventesQuery(db);

        const QString sqlVentes = R"(
            SELECT
                m.design,
                m.pu,
                a.qte,
                m.pu * a.qte AS montant,
                a.date_achat
            FROM achat AS a
            JOIN materiel AS m
                ON m.numMat = a.numMat
            WHERE a.numClient = ?
            ORDER BY a.date_achat DESC
        )";

        if (!ventesQuery.prepare(sqlVentes)) {
            QMessageBox::critical(
                this,
                "Erreur SQL",
                "Préparation de la requête des ventes impossible :\n"
                    + ventesQuery.lastError().text()
                );
            return;
        }

        ventesQuery.addBindValue(idClient);

        if (!ventesQuery.exec()) {
            QMessageBox::critical(
                this,
                "Erreur SQL - Execution des Ventes",
                ventesQuery.lastError().text()
            );
            return;
        }


        // 6. Vider les tableaux avnt d'ajouter les vrais résultats
        tableVentes->setRowCount(0);

        double montantTotal = 0.0;
        int nombreLignes = 0;

        const QLocale locale(QLocale::French, QLocale::France);

        // 7. Ajouter chaque achat dans le tableau
        while (ventesQuery.next()) {
            const int ligne = tableVentes->rowCount();
            tableVentes->insertRow(ligne);

            const QString designation = ventesQuery.value("design").toString();

            const double prixUnitaire = ventesQuery.value("pu").toDouble();

            const int quantite = ventesQuery.value("qte").toInt();

            const double montant = ventesQuery.value("montant").toDouble();

            const QString dateAchat = ventesQuery.value("date_achat").toString();

            QDate date = QDate::fromString(dateAchat, "yyyy-MM-dd");

            QString dateAffichee = date.isValid()
                ? date.toString("dd/MM/yyyy")
                : dateAchat;

            montantTotal += montant;
            nombreLignes++;

            tableVentes->setItem(
                ligne, 0,
                new QTableWidgetItem(QString::number(ligne + 1))
            );

            tableVentes->setItem(
                ligne, 1,
                new QTableWidgetItem(designation)
            );

            tableVentes->setItem(
                ligne, 2,
                new QTableWidgetItem(locale.toString(prixUnitaire, 'f', 0))
            );

            tableVentes->setItem(
                ligne, 3,
                new QTableWidgetItem(QString::number(quantite))
            );

            tableVentes->setItem(
                ligne, 4,
                new QTableWidgetItem(locale.toString(montant, 'f', 0))
            );

            tableVentes->setItem(
                ligne, 5,
                new QTableWidgetItem(dateAffichee)
            );
        }

        // 8. Actualiser le récap
        recapClient->setText(nomClient);
        recapArticles->setText(QString::number(nombreLignes));

        const QString totalFormate = locale.toString(montantTotal, 'f', 0) + " Ar";

        recapMontant->setText(totalFormate);
        totalGeneral->setText(totalFormate);


        if (nombreLignes == 0) {
            QMessageBox::information(
                this,
                "Résultat",
                "Le Client existe, mais aucun achat n'est enregistré pour lui."
            );
        }
    });


    // Bouton actualiser
    connect(btnActualiser, &QPushButton::clicked,
            this, [this]()
            {
                /*
         * Plus tard :
         * recharger les ventes depuis SQLite.
         */
            });


    // Bouton imprimer
    connect(btnImprimer, &QPushButton::clicked,
            this, [this]()
            {
                /*
         * Fonction d'impression/export à développer
         * plus tard.
         */
            });


    // Changement de période
    connect(periodeCombo,
            &QComboBox::currentTextChanged,
            this,
            [this](const QString &texte)
            {
                bool entreDeuxDates = (texte == "Entre 2 dates");

                dateDebut->setEnabled(entreDeuxDates);
                dateFin->setEnabled(entreDeuxDates);
            });

   // Logique : Date de fin > Date de début
    connect(dateDebut, &QDateEdit::dateChanged,
            this, [this](const QDate &date)
            {
                dateFin->setMinimumDate(date);
            });

    connect(dateFin, &QDateEdit::dateChanged,
            this, [this](const QDate &date)
            {
                dateDebut->setMaximumDate(date);
            });

    // Désactivées par défaut car "Toutes les dates"
    dateDebut->setEnabled(true);
    dateFin->setEnabled(true);
}

void VenteWindow::rechercherClientParNumero()
{
    QString numero = rechercheClient->text().trimmed();

    // Vérifier que l'utilisateur a saisi quelque chose
    if (numero.isEmpty()) {
        QMessageBox::warning(
            this,
            "Recherche",
            "Veuillez saisir le numéro du client."
            );
        return;
    }

    QSqlQuery query;

    query.prepare(R"(
        SELECT numClient, nom
        FROM Client
        WHERE numClient = ?
    )");

    query.addBindValue(numero);

    if (!query.exec()) {
        QMessageBox::critical(
            this,
            "Erreur SQL",
            "Erreur lors de la recherche du client :\n" +
            query.lastError().text()
            );
        return;
    }

    // Le client n'existe pas
    if (!query.next()) {
        QMessageBox::information(
            this,
            "Client introuvable",
            "Aucun client trouvé avec le numéro : " + numero
        );
        return;
    }

    // Récupération des informations du client
    QString numClient = query.value("numClient").toString();
    QString nomClient = query.value("nom").toString();

    // Mise à jour de l'affichage du client
    clientNumero->setText(numClient);
    clientNom->setText(nomClient);

    // Charger les matériels achetés par ce client
    chargerVentes(numClient);

    // Mettre à jour le récapitulatif
    mettreAJourRecapitulatif(nomClient);
}

void VenteWindow::mettreAJourRecapitulatif(const QString &nomClient)
{
    recapClient->setText(nomClient);

    int nombre = tableVentes->rowCount();

    double total = 0;

    for (int i = 0; i < nombre; ++i) {

        QTableWidgetItem *item =
            tableVentes->item(i, 4);

        if (item != nullptr) {
            total += item->text().toDouble();
        }
    }

    recapArticles->setText(
        QString::number(nombre)
    );

    recapMontant->setText(
        QString::number(total, 'f', 0) + " Ar"
    );

    totalGeneral->setText(
        QString::number(total, 'f', 0) + " Ar"
    );
}


void VenteWindow::chargerVentes(const QString &numClient){
    // TODO
}



