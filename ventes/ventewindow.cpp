#include "ventewindow.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QFont>
#include <QDate>
#include <QLocale>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>


VenteWindow::VenteWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("VENTE");
    resize(1200, 720);
    setMinimumSize(1050, 650);

    setStyleSheet(R"(
        QDialog { background-color: #FAF9F6; color: #542C82; }
        QLabel { color: #183B43; }
        QLineEdit, QComboBox, QDateEdit {
            background-color: #FFFFFF; border: 1px solid #D9E1DF;
            border-radius: 7px; padding: 9px 12px; color: #183B43;
            font-size: 13px;
        }
        QLineEdit:focus, QComboBox:focus, QDateEdit:focus {
            border: 1px solid #6F3FAF;
        }
        QPushButton {
            background-color: #FFFFFF; border: 1px solid #D9E1DF;
            border-radius: 7px; padding: 9px 16px; color: #183B43;
            font-size: 13px;
        }
        QPushButton:hover { background-color: #F1F5F3; }
        QTableWidget {
            background-color: #FFFFFF; border: none;
            gridline-color: #E6ECEA; border-radius: 8px;
            color: #183B43; font-size: 13px;
        }
        QTableWidget::item { padding: 8px; border-bottom: 1px solid #E6ECEA; }
        QHeaderView::section {
            background-color: #F0E8F8; border: none; padding: 11px;
            color: #183B43; font-weight: bold; font-size: 12px;
        }
        QComboBox, QDateEdit { padding-right: 30px; }
        QComboBox::drop-down, QDateEdit::drop-down {
            subcontrol-origin: padding; subcontrol-position: top right;
            width: 30px; border: none;
        }
    )");

    QFont sousTitreFont;
    sousTitreFont.setPointSize(14);
    sousTitreFont.setBold(true);

    // 1. En-tête
    header = new QFrame(this);
    header->setStyleSheet("QFrame { background-color: #6F3FAF; border-radius: 10px; }");

    titreLabel = new QLabel("Matériels vendus à un client");
    QFont titreFont;
    titreFont.setPointSize(23);
    titreFont.setBold(true);
    titreLabel->setFont(titreFont);
    titreLabel->setStyleSheet("color: white;");

    descriptionLabel = new QLabel(
        "Liste des matériels qu'un client a acheté, avec les détails de chaque vente.");
    descriptionLabel->setStyleSheet("color: #EDE4F7; font-size: 13px;");

    QVBoxLayout *headerLayout = new QVBoxLayout(header);
    headerLayout->setContentsMargins(22, 16, 22, 16);
    headerLayout->setSpacing(4);
    headerLayout->addWidget(titreLabel);
    headerLayout->addWidget(descriptionLabel);

    // 2. Recherche du client
    QLabel *titreRecherche = new QLabel("Rechercher un client");
    titreRecherche->setFont(sousTitreFont);

    btnRechercheNumero = new QPushButton("Par numéro");
    btnRechercheNom = new QPushButton("Par nom");
    btnRechercheNumero->setCheckable(true);
    btnRechercheNom->setCheckable(true);
    btnRechercheNumero->setChecked(true);

    auto appliquerStyleRecherche = [this]() {
        const QString styleActif = R"(
            QPushButton { background-color: #F66D5B; color: white;
                border: none; border-radius: 7px; padding: 9px 25px; font-weight: bold; }
            QPushButton:hover { background-color: #E85F4E; }
        )";
        const QString styleInactif = R"(
            QPushButton { background-color: white; color: #183B43;
                border: 1px solid #D9E1DF; border-radius: 7px; padding: 9px 25px; }
            QPushButton:hover { background-color: #F1F5F3; }
        )";
        btnRechercheNumero->setStyleSheet(btnRechercheNumero->isChecked() ? styleActif : styleInactif);
        btnRechercheNom->setStyleSheet(btnRechercheNom->isChecked() ? styleActif : styleInactif);
    };
    appliquerStyleRecherche();

    rechercheClient = new QLineEdit;
    rechercheClient->setPlaceholderText("Ex : CL001");
    rechercheClient->setMinimumHeight(40);

    btnRechercher = new QPushButton("🔍  Rechercher");
    btnRechercher->setMinimumHeight(40);
    btnRechercher->setStyleSheet(R"(
        QPushButton { background-color: #542C82; color: white; border: none;
            border-radius: 7px; padding: 9px 20px; font-weight: bold; }
        QPushButton:hover { background-color: #633695; }
    )");

    QHBoxLayout *choixRecherche = new QHBoxLayout;
    choixRecherche->addWidget(btnRechercheNumero);
    choixRecherche->addWidget(btnRechercheNom);

    QHBoxLayout *inputRechercheLayout = new QHBoxLayout;
    inputRechercheLayout->addWidget(rechercheClient, 1);
    inputRechercheLayout->addWidget(btnRechercher);

    QVBoxLayout *rechercheLayout = new QVBoxLayout;
    rechercheLayout->setSpacing(9);
    rechercheLayout->addWidget(titreRecherche);
    rechercheLayout->addLayout(choixRecherche);
    rechercheLayout->addLayout(inputRechercheLayout);

    // 3. Carte client
    QFrame *clientFrame = new QFrame;
    clientFrame->setStyleSheet(
        "QFrame { background-color: #FFFFFF; border: 1px solid #E2D8EA; border-radius: 8px; }");
    QLabel *clientTitre = new QLabel("Client sélectionné");
    clientTitre->setFont(sousTitreFont);

    clientNumero = new QLabel("—");
    clientNom = new QLabel("—");
    clientNumero->setStyleSheet("font-size: 14px; font-weight: bold;");
    clientNom->setStyleSheet("font-size: 14px; font-weight: bold;");

    QGridLayout *clientLayout = new QGridLayout(clientFrame);
    clientLayout->setContentsMargins(14, 12, 14, 12);
    clientLayout->addWidget(clientTitre, 0, 0, 1, 2);
    clientLayout->addWidget(new QLabel("N° Client :"), 1, 0);
    clientLayout->addWidget(clientNumero, 1, 1);
    clientLayout->addWidget(new QLabel("Nom :"), 2, 0);
    clientLayout->addWidget(clientNom, 2, 1);

    // 4. Filtre de période
    QFrame *periodeFrame = new QFrame;
    periodeFrame->setStyleSheet(
        "QFrame { background-color: #FFFFFF; border: 1px solid #E2D8EA; border-radius: 8px; }");
    QLabel *periodeTitre = new QLabel("Filtrer par période");
    periodeTitre->setFont(sousTitreFont);

    periodeCombo = new QComboBox;
    periodeCombo->addItems({"Entre 2 dates", "Un mois", "Une année"});
    periodeCombo->setCurrentIndex(0);

    dateDebut = new QDateEdit(QDate::currentDate());
    dateFin = new QDateEdit(QDate::currentDate());
    for (QDateEdit *dateEdit : {dateDebut, dateFin}) {
        dateEdit->setCalendarPopup(true);
        dateEdit->setDisplayFormat("dd/MM/yyyy");
        dateEdit->setMaximumDate(QDate::currentDate());
        dateEdit->setMinimumDate(QDate(2000, 1, 1));
        dateEdit->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
    }
    dateDebut->setToolTip("Date de début");
    dateFin->setToolTip("Date de fin");

    QGridLayout *periodeLayout = new QGridLayout(periodeFrame);
    periodeLayout->setContentsMargins(14, 12, 14, 12);
    periodeLayout->addWidget(periodeTitre, 0, 0, 1, 2);
    periodeLayout->addWidget(periodeCombo, 1, 0, 1, 2);
    periodeLayout->addWidget(new QLabel("Du :"), 2, 0);
    periodeLayout->addWidget(new QLabel("Au :"), 2, 1);
    periodeLayout->addWidget(dateDebut, 3, 0);
    periodeLayout->addWidget(dateFin, 3, 1);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setSpacing(18);
    topLayout->addLayout(rechercheLayout, 3);
    topLayout->addWidget(clientFrame, 2);
    topLayout->addWidget(periodeFrame, 2);

    // 5. Tableau des ventes
    QLabel *titreTableau = new QLabel("🛒  Liste des matériels vendus");
    titreTableau->setFont(sousTitreFont);

    tableVentes = new QTableWidget;
    tableVentes->setColumnCount(6);
    tableVentes->setHorizontalHeaderLabels(
        {"#", "Désignation", "PU (Ar)", "Quantité", "Montant (Ar)", "Date d'achat"});
    tableVentes->setRowCount(0);
    tableVentes->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVentes->setSelectionMode(QAbstractItemView::SingleSelection);
    tableVentes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableVentes->verticalHeader()->setVisible(false);
    tableVentes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableVentes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    QFrame *totalFrame = new QFrame;
    totalFrame->setStyleSheet("QFrame { background-color: #F3ECF8; border-radius: 7px; }");
    QLabel *labelTotal = new QLabel("Total général :");
    labelTotal->setFont(sousTitreFont);
    totalGeneral = new QLabel("0 Ar");
    totalGeneral->setAlignment(Qt::AlignCenter);
    totalGeneral->setMinimumWidth(145);
    totalGeneral->setStyleSheet(R"(
        QLabel { background-color: #F66D5B; color: white; border-radius: 6px;
            padding: 10px 15px; font-size: 15px; font-weight: bold; }
    )");
    QHBoxLayout *totalLayout = new QHBoxLayout(totalFrame);
    totalLayout->setContentsMargins(12, 8, 12, 8);
    totalLayout->addStretch();
    totalLayout->addWidget(labelTotal);
    totalLayout->addWidget(totalGeneral);

    btnActualiser = new QPushButton("⟳  Actualiser");
    btnImprimer = new QPushButton("▣  Imprimer / Exporter");
    btnImprimer->setStyleSheet(R"(
        QPushButton { background-color: #542C82; color: white; border: none;
            border-radius: 7px; padding: 10px 17px; font-weight: bold; }
        QPushButton:hover { background-color: #633695; }
    )");
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnActualiser);
    bottomLayout->addWidget(btnImprimer);

    QFrame *tableFrame = new QFrame;
    tableFrame->setStyleSheet(
        "QFrame { background-color: #FFFFFF; border: 1px solid #E2D8EA; border-radius: 8px; }");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableFrame);
    tableLayout->setContentsMargins(14, 14, 14, 14);
    tableLayout->addWidget(titreTableau);
    tableLayout->addWidget(tableVentes, 1);
    tableLayout->addWidget(totalFrame);
    tableLayout->addLayout(bottomLayout);

    // 6. Récapitulatif
    QFrame *recapFrame = new QFrame;
    recapFrame->setStyleSheet(
        "QFrame { background-color: #FFFFFF; border: 1px solid #E2D8EA; border-radius: 8px; }");
    QLabel *recapTitre = new QLabel("☷ Récapitulatif");
    recapTitre->setFont(sousTitreFont);
    recapTitre->setStyleSheet(
        "QLabel { background-color: #FFF0EC; border-radius: 6px; padding: 12px; color: #183B43; }");

    QLabel *labelClient = new QLabel("Client");
    QLabel *labelArticles = new QLabel("Nombre d'articles");
    QLabel *labelMontant = new QLabel("Montant total");
    QString labelStyle = "font-size: 13px; color: #555555;";
    labelClient->setStyleSheet(labelStyle);
    labelArticles->setStyleSheet(labelStyle);
    labelMontant->setStyleSheet(labelStyle);

    QString valeurStyle = R"(
        QLabel { font-weight: bold; font-size: 14px; border: 1px solid #E2D8EA;
            border-radius: 6px; padding: 6px 12px; background-color: #FFFFFF; }
    )";
    recapClient = new QLabel("—");
    recapArticles = new QLabel("0");
    recapMontant = new QLabel("0 Ar");
    for (QLabel *label : {recapClient, recapArticles, recapMontant})
        label->setStyleSheet(valeurStyle);

    QGridLayout *recapInfos = new QGridLayout;
    recapInfos->setHorizontalSpacing(12);
    recapInfos->setVerticalSpacing(14);
    recapInfos->addWidget(labelClient, 0, 0);
    recapInfos->addWidget(recapClient, 0, 1);
    recapInfos->addWidget(labelArticles, 1, 0);
    recapInfos->addWidget(recapArticles, 1, 1);
    recapInfos->addWidget(labelMontant, 2, 0);
    recapInfos->addWidget(recapMontant, 2, 1);

    QVBoxLayout *recapLayout = new QVBoxLayout(recapFrame);
    recapLayout->setContentsMargins(16, 16, 16, 16);
    recapLayout->addWidget(recapTitre);
    recapLayout->addSpacing(12);
    recapLayout->addLayout(recapInfos);
    recapLayout->addStretch();

    QHBoxLayout *mainContentLayout = new QHBoxLayout;
    mainContentLayout->setSpacing(18);
    mainContentLayout->addWidget(tableFrame, 4);
    mainContentLayout->addWidget(recapFrame, 1);

    // 7. Mise en page générale
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(18);
    mainLayout->addWidget(header);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(mainContentLayout, 1);

    // 8. Connexions des boutons
    connect(btnRechercheNumero, &QPushButton::clicked, this, [this, appliquerStyleRecherche]() {
        btnRechercheNumero->setChecked(true);
        btnRechercheNom->setChecked(false);
        rechercheClient->setPlaceholderText("Ex : CL001");
        appliquerStyleRecherche();
    });
    connect(btnRechercheNom, &QPushButton::clicked, this, [this, appliquerStyleRecherche]() {
        btnRechercheNom->setChecked(true);
        btnRechercheNumero->setChecked(false);
        rechercheClient->setPlaceholderText("Ex : Rakoto");
        appliquerStyleRecherche();
    });

    connect(btnRechercher, &QPushButton::clicked, this, &VenteWindow::rechercherClient);

    connect(rechercheClient, &QLineEdit::returnPressed, this, &VenteWindow::rechercherClient);

    connect(periodeCombo, &QComboBox::currentTextChanged,
            this, [this](const QString &periode)
            {
                bool entreDeuxDates = (periode == "Entre 2 dates");

                dateDebut->setEnabled(true);
                dateFin->setEnabled(entreDeuxDates);

                if (periode == "Entre 2 dates") {
                    dateDebut->setDisplayFormat("dd/MM/yyyy");
                    dateFin->setDisplayFormat("dd/MM/yyyy");
                }
                else if (periode == "Un mois") {
                    dateDebut->setDisplayFormat("MMMM yyyy");
                }
                else if (periode == "Une année") {
                    dateDebut->setDisplayFormat("yyyy");
                }

                if (!numClientActuel.isEmpty())
                    chargerVentes(numClientActuel);
    });

    connect(dateDebut, &QDateEdit::dateChanged, this, [this](const QDate &date) {
        dateFin->setMinimumDate(date);
        if (!numClientActuel.isEmpty())
            chargerVentes(numClientActuel);
    });
    connect(dateFin, &QDateEdit::dateChanged, this, [this](const QDate &date) {
        dateDebut->setMaximumDate(date);
        if (!numClientActuel.isEmpty())
            chargerVentes(numClientActuel);
    });

    connect(btnActualiser, &QPushButton::clicked, this, [this]() {
        if (numClientActuel.isEmpty()) {
            QMessageBox::information(this, "Actualiser", "Recherchez d'abord un client.");
            return;
        }
        chargerVentes(numClientActuel);
    });

    connect(btnImprimer, &QPushButton::clicked, this, [this]() {
        if (tableVentes->rowCount() == 0) {
            QMessageBox::information(this, "Imprimer", "Aucune vente à imprimer ou exporter.");
            return;
        }

        QString html = "<h2>Matériels vendus à un client</h2>";
        html += "<p><b>Client :</b> " + nomClientActuel.toHtmlEscaped()
                + " (" + numClientActuel.toHtmlEscaped() + ")</p>";
        html += "<table border='1' cellspacing='0' cellpadding='5' width='100%'>";
        html += "<tr><th>#</th><th>Désignation</th><th>PU (Ar)</th><th>Quantité</th>"
                "<th>Montant (Ar)</th><th>Date d'achat</th></tr>";

        for (int row = 0; row < tableVentes->rowCount(); ++row) {
            html += "<tr>";
            for (int col = 0; col < tableVentes->columnCount(); ++col) {
                QTableWidgetItem *item = tableVentes->item(row, col);
                html += "<td>" + (item ? item->text().toHtmlEscaped() : QString()) + "</td>";
            }
            html += "</tr>";
        }
        html += "</table><p><b>" + totalGeneral->text().toHtmlEscaped() + "</b></p>";

        QString chemin = QFileDialog::getSaveFileName(
            this, "Exporter les ventes", "ventes_" + numClientActuel + ".csv",
            "Fichier CSV (*.csv);;Fichier HTML (*.html);;Tous les fichiers (*)");
        if (chemin.isEmpty())
            return;

        if (chemin.endsWith(".html", Qt::CaseInsensitive)) {
            QFile fichier(chemin);
            if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier.");
                return;
            }
            QTextStream sortie(&fichier);
            sortie << html;
            QMessageBox::information(this, "Export terminé", "Le fichier HTML a été créé.");
        } else {
            if (!chemin.endsWith(".csv", Qt::CaseInsensitive))
                chemin += ".csv";
            QFile fichier(chemin);
            if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier.");
                return;
            }
            QTextStream sortie(&fichier);
            sortie << "sep=;\n#;Désignation;PU (Ar);Quantité;Montant (Ar);Date d'achat\n";
            for (int row = 0; row < tableVentes->rowCount(); ++row) {
                for (int col = 0; col < tableVentes->columnCount(); ++col) {
                    if (col) sortie << ';';
                    QTableWidgetItem *item = tableVentes->item(row, col);
                    QString valeur = item ? item->text() : QString();
                    valeur.replace('"', "\"\"");
                    sortie << '"' << valeur << '"';
                }
                sortie << '\n';
            }
            QMessageBox::information(this, "Export terminé", "Le fichier CSV a été créé.");
        }
    });
}

QString VenteWindow::conditionDateSql() const
{
    const QString periode = periodeCombo->currentText();

    if (periode == "Entre 2 dates") {
        return " AND date(a.date_achat) BETWEEN date(:dateDebut) "
               "AND date(:dateFin)";
    }

    if (periode == "Un mois") {
        return " AND strftime('%Y-%m', a.date_achat) = :mois";
    }

    if (periode == "Une année") {
        return " AND strftime('%Y', a.date_achat) = :annee";
    }

    return QString();
}

void VenteWindow::rechercherClient()
{
    const QString saisie = rechercheClient->text().trimmed();
    if (saisie.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez saisir le numéro ou le nom du client.");
        rechercheClient->setFocus();
        return;
    }

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Base de données", "La connexion SQLite n'est pas ouverte.");
        return;
    }

    QSqlQuery query;
    if (btnRechercheNumero->isChecked()) {
        query.prepare("SELECT numClient, nom FROM Client WHERE numClient = :valeur");
        query.bindValue(":valeur", saisie);
    } else {
        query.prepare("SELECT numClient, nom FROM Client WHERE nom LIKE :valeur COLLATE NOCASE "
                      "ORDER BY nom LIMIT 1");
        query.bindValue(":valeur", "%" + saisie + "%");
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL",
                              "Erreur lors de la recherche du client :\n" + query.lastError().text());
        return;
    }

    if (!query.next()) {
        viderAffichage();
        QMessageBox::information(this, "Client introuvable",
                                 "Aucun client correspondant à cette recherche.");
        return;
    }

    numClientActuel = query.value("numClient").toString();
    nomClientActuel = query.value("nom").toString();
    clientNumero->setText(numClientActuel);
    clientNom->setText(nomClientActuel);
    chargerVentes(numClientActuel);
}

void VenteWindow::chargerVentes(const QString &numClient)
{
    tableVentes->setRowCount(0);

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Base de données", "La connexion SQLite n'est pas ouverte.");
        return;
    }

    QString sql = R"(
        SELECT m.design, m.pu, a.qte,
               (m.pu * a.qte) AS montant,
               a.date_achat
        FROM Achat AS a
        INNER JOIN Materiel AS m ON m.numMat = a.numMat
        WHERE a.numClient = :numClient
    )";
    sql += conditionDateSql();
    sql += " ORDER BY date(a.date_achat) DESC, a.id DESC";

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":numClient", numClient);

    const QString periode = periodeCombo->currentText();

    if (periode == "Entre 2 dates") {

        query.bindValue(":dateDebut",
                        dateDebut->date().toString("yyyy-MM-dd"));

        query.bindValue(":dateFin",
                        dateFin->date().toString("yyyy-MM-dd"));
    }
    else if (periode == "Un mois") {

        query.bindValue(":mois",
                        dateDebut->date().toString("yyyy-MM"));
    }
    else if (periode == "Une année") {

        query.bindValue(":annee",
                        dateDebut->date().toString("yyyy"));
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL",
                              "Erreur lors du chargement des ventes :\n" + query.lastError().text());
        return;
    }

    const QLocale locale(QLocale::French, QLocale::France);
    double total = 0.0;
    int numeroLigne = 0;

    while (query.next()) {
        const QString designation = query.value("design").toString();
        const double prixUnitaire = query.value("pu").toDouble();
        const int quantite = query.value("qte").toInt();
        const double montant = query.value("montant").toDouble();
        const QString dateSql = query.value("date_achat").toString();

        const QDate date = QDate::fromString(dateSql, "yyyy-MM-dd");
        const QString dateAffichee = date.isValid() ? date.toString("dd/MM/yyyy") : dateSql;

        const int row = tableVentes->rowCount();
        tableVentes->insertRow(row);

        auto ajouterCellule = [this, row](int colonne, const QString &texte, double valeur = 0.0) {
            QTableWidgetItem *item = new QTableWidgetItem(texte);
            item->setTextAlignment(Qt::AlignCenter);
            item->setData(Qt::UserRole, valeur);
            tableVentes->setItem(row, colonne, item);
        };

        ++numeroLigne;
        ajouterCellule(0, QString::number(numeroLigne));
        ajouterCellule(1, designation);
        ajouterCellule(2, locale.toString(prixUnitaire, 'f', 0), prixUnitaire);
        ajouterCellule(3, QString::number(quantite), quantite);
        ajouterCellule(4, locale.toString(montant, 'f', 0), montant);
        ajouterCellule(5, dateAffichee);

        total += montant;
    }

    mettreAJourRecapitulatif(nomClientActuel);
    totalGeneral->setText(locale.toString(total, 'f', 0) + " Ar");

    if (numeroLigne == 0) {
        // Le client existe, mais aucune vente ne correspond à la période choisie.
        recapArticles->setText("0");
        recapMontant->setText("0 Ar");
        totalGeneral->setText("0 Ar");
    }
}

void VenteWindow::mettreAJourRecapitulatif(const QString &nomClient)
{
    const QLocale locale(QLocale::French, QLocale::France);
    double total = 0.0;

    for (int row = 0; row < tableVentes->rowCount(); ++row) {
        QTableWidgetItem *item = tableVentes->item(row, 4);
        if (item)
            total += item->data(Qt::UserRole).toDouble();
    }

    recapClient->setText(nomClient.isEmpty() ? "—" : nomClient);
    recapArticles->setText(QString::number(tableVentes->rowCount()));
    recapMontant->setText(locale.toString(total, 'f', 0) + " Ar");
    totalGeneral->setText(locale.toString(total, 'f', 0) + " Ar");
}

void VenteWindow::viderAffichage()
{
    numClientActuel.clear();
    nomClientActuel.clear();
    clientNumero->setText("—");
    clientNom->setText("—");
    tableVentes->setRowCount(0);
    mettreAJourRecapitulatif(QString());
}