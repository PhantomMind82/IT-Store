#include "materielwindow.h"
#include "materiel.h"
#include "style.h"

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QLocale>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QSqlQuery>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QSqlError>

#include <QDate>
#include <QFileDialog>
#include <QPageSize>
#include <QPdfWriter>
#include <QTextDocument>

static const QString DEVISE = " Ar";

MaterielWindow::MaterielWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Gestion des matériels");
    resize(1100, 740);
    setStyleSheet(styleFenetre("#2f78e0") +
                  "QGroupBox { background: white; border: 1px solid #c5cde0; border-radius: 8px;"
                  " margin-top: 14px; font-weight: bold; color: #1f5cc0; padding: 8px; }"
                  "QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 6px; }"
                  "QGroupBox QLabel { font-weight: normal; color: #1b2540; }");

    // ---------- Page 0 : Ajouter ----------
    editNom = new QLineEdit;
    editNom->setPlaceholderText("Entrez le nom du matériel");
    spinPu = new QDoubleSpinBox;
    spinPu->setRange(0, 1000000000);
    spinPu->setDecimals(2);
    spinPu->setSuffix(DEVISE);
    spinStock = new QSpinBox;
    spinStock->setRange(0, 1000000);

    QPushButton *btnEnreg = new QPushButton("Enregistrer");
    QPushButton *btnReinit = new QPushButton("Réinitialiser");
    btnReinit->setObjectName("btnGris");

    btnEnreg->setAutoDefault(false);
    btnReinit->setAutoDefault(false);


    QGroupBox *boxAjout = new QGroupBox("Ajouter un matériel");
    QFormLayout *formA = new QFormLayout;
    formA->addRow("Nom :", editNom);
    formA->addRow("Prix unitaire :", spinPu);
    formA->addRow("Stock initial :", spinStock);
    QHBoxLayout *btnsA = new QHBoxLayout;
    btnsA->addWidget(btnEnreg);
    btnsA->addWidget(btnReinit);
    btnsA->addStretch();
    QVBoxLayout *layA = new QVBoxLayout(boxAjout);
    layA->addLayout(formA);
    layA->addLayout(btnsA);
    layA->addStretch();

    // ---------- Page 1 : Situation ----------
    editRecherche = new QLineEdit;
    editRecherche->setPlaceholderText("🔍 Rechercher par nom ou par numéro...");
    editRecherche->setClearButtonEnabled(true);
    
    
    
    QPushButton *btnPdf = new QPushButton("📄 Exporter l'état de stock (PDF)");
    btnPdf->setAutoDefault(false);
    
    
    
    table = new QTableWidget(0, 6);
    table->setHorizontalHeaderLabels({"N° Matériel", "Designation", "Prix unitaire", "Stock initial", "Stock actuel", "Actions"});
    table->setAlternatingRowColors(true);
    table->verticalHeader()->setVisible(false);
    table->verticalHeader()->setDefaultSectionSize(40);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    table->setColumnWidth(5, 150);

    table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    table->horizontalHeader()->setStretchLastSection(false);


    table->setStyleSheet(
        "QTableWidget { font-weight: 600; font-size: 13px;}"
        "QTableWidget::item { padding-left: 0px; }"

        "QTableWidget::item:selected { background: #cfe0ff; color: #1b2540; }"
        "QTableWidget::item:focus { background: #cfe0ff; color: #1b2540; }"

        "QHeaderView { background: #2f78e0; }"
        "QTableCornerButton::section { background: #2f78e0; border: none; }"

        "QScrollBar:vertical { background: #e6ebf5; width: 14px; margin: 0; }"
        "QScrollBar::handle:vertical { background: #B1ADAD; min-height: 30px;"
        " border-radius: 6px;  }"
        "QScrollBar::handle:vertical:hover { background: #B1ADAD; border-radius: 10px; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }");



    QGroupBox *boxSit = new QGroupBox("Situation des matériels");
    QHBoxLayout *layBarre = new QHBoxLayout;
    layBarre->addWidget(editRecherche, 1);
    layBarre->addWidget(btnPdf);
    QVBoxLayout *laySit = new QVBoxLayout(boxSit);
    laySit->addLayout(layBarre);
    laySit->addWidget(table);


    // ---------- Pile de pages ----------
    pile = new QStackedWidget;
    pile->addWidget(boxAjout);   // 0
    pile->addWidget(boxSit);     // 1
    pile->setCurrentIndex(0);

    // ---------- Cartes du haut ----------
    auto carte = [](const QString &icone, const QString &titre, const QString &sous,
                    const QString &c1, const QString &c2) {
        QPushButton *b = new QPushButton;
        b->setMinimumHeight(85);

        b->setAutoDefault(false);
        b->setDefault(false);


        b->setCursor(Qt::PointingHandCursor);
        b->setStyleSheet(QString(
                             "QPushButton { background: qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 %1, stop:1 %2);"
                             " border: none; border-radius: 10px; }"
                             "QPushButton:hover { border: 3px solid rgba(255,255,255,170); }").arg(c1, c2));

        QLabel *lTitre = new QLabel(icone + "  " + titre);
        lTitre->setAlignment(Qt::AlignCenter);
        lTitre->setStyleSheet("background: transparent; color: white;"
                              " font-size: 18px; font-weight: bold;");
        lTitre->setAttribute(Qt::WA_TransparentForMouseEvents);

        QLabel *lSous = new QLabel(sous);
        lSous->setAlignment(Qt::AlignCenter);
        lSous->setStyleSheet("background: transparent; color: rgba(255,255,255,210);"
                             " font-size: 12px; font-weight: normal;");
        lSous->setAttribute(Qt::WA_TransparentForMouseEvents);

        QVBoxLayout *lay = new QVBoxLayout(b);
        lay->setContentsMargins(8, 8, 8, 8);
        lay->setSpacing(2);
        lay->addStretch();
        lay->addWidget(lTitre);
        lay->addWidget(lSous);
        lay->addStretch();
        return b;
    };
    QPushButton *cAjout = carte("➕", "Ajouter un matériel", "Enregistrer un nouveau matériel",
                                "#5b6fe0", "#4455c8");
    QPushButton *cSit = carte("📋", "Situation des matériels",
                              "Consulter, modifier et supprimer", "#5b6fe0", "#4455c8");

    QHBoxLayout *layCartes = new QHBoxLayout;
    layCartes->setSpacing(12);
    layCartes->addWidget(cAjout);
    layCartes->addWidget(cSit);

    // ---------- Mise en page ----------
    QVBoxLayout *principal = new QVBoxLayout(this);
    principal->setContentsMargins(20, 20, 20, 20);
    principal->setSpacing(12);
    principal->addWidget(creerEnteteClair("💻", "Gestion de Matériel",
                                          "Ajouter, modifier, supprimer et consulter les matériels", "#2f78e0"));
    principal->addLayout(layCartes);
    principal->addWidget(pile, 1);

    // ---------- Connexions ----------
    connect(btnEnreg, &QPushButton::clicked, this, &MaterielWindow::ajouter);
    connect(btnReinit, &QPushButton::clicked, this, &MaterielWindow::reinitAjout);

    connect(btnPdf, &QPushButton::clicked, this, &MaterielWindow::exporterPdf);
        
        
        
    connect(editRecherche, &QLineEdit::textChanged, this, &MaterielWindow::charger);

    connect(cAjout, &QPushButton::clicked, this, [this]() {
        pile->setCurrentIndex(0);
        editNom->setFocus();
    });
    connect(cSit, &QPushButton::clicked, this, [this]() {
        pile->setCurrentIndex(1);
        charger();
    });

    charger();
}

// ---------------- Ajout ----------------
void MaterielWindow::ajouter()
{
    const QString nom = editNom->text().trimmed();
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Entre le nom du matériel.");
        return;
    }
    if (Materiel::existe(nom)) {
        QMessageBox::warning(this, "Attention", "Matériel déjà saisi.");
        return;
    }

    Materiel m;
    m.num = Materiel::prochainNumero();
    m.design = nom;
    m.pu = spinPu->value();
    m.stockInit = spinStock->value();

    QString erreur;
    if (!m.ajouter(erreur)) {
        QMessageBox::critical(this, "Erreur", erreur);
        return;
    }

    QMessageBox::information(this, "Succès", "Matériel enregistré sous le numéro " + m.num);
    reinitAjout();
    charger();
}

void MaterielWindow::reinitAjout()
{
    editNom->clear();
    spinPu->setValue(0);
    spinStock->setValue(0);
    editNom->setFocus();
}

// ---------------- Situation (liste + recherche) ----------------
void MaterielWindow::charger()
{
    const QString t = "%" + editRecherche->text().trimmed() + "%";

    QSqlQuery q;


    q.prepare("SELECT numMat, design, pu, stockInit, stockActuel FROM materiel "
              "WHERE design LIKE :t1 OR numMat LIKE :t2 ORDER BY numMat");


    q.bindValue(":t1", t);
    q.bindValue(":t2", t);
    q.exec();

    table->setRowCount(0);
    while (q.next()) {
        const QString num = q.value(0).toString();
        const QString nom = q.value(1).toString();
        const double pu = q.value(2).toDouble();
        const int init = q.value(3).toInt();
        const int actuel = q.value(4).toInt();


        const int r = table->rowCount();
        table->insertRow(r);

        auto *itPu = new QTableWidgetItem(QLocale().toString(pu, 'f', 0) + DEVISE);
        itPu->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        auto *itInit = new QTableWidgetItem(QString::number(init));
        itInit->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        auto *itActuel = new QTableWidgetItem(QString::number(actuel));
        itActuel->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        table->setItem(r, 4, new QTableWidgetItem);
        table->item(r, 4)->setFlags(Qt::NoItemFlags);

        table->setItem(r, 0, new QTableWidgetItem(num));
        table->setItem(r, 1, new QTableWidgetItem(nom));
        table->setItem(r, 2, itPu);
        table->setItem(r, 3, itInit);
        table->setItem(r, 4, itActuel);


        QPushButton *btnMod = new QPushButton("✏️");
        btnMod->setToolTip("Modifier");
        btnMod->setCursor(Qt::PointingHandCursor);

        btnMod->setAutoDefault(false);

        btnMod->setStyleSheet("QPushButton { background: #c5c9d1; border-radius: 6px;"
                              " padding: 4px 10px; font-size: 15px; }");

        QPushButton *btnSup = new QPushButton("❌");
        btnSup->setToolTip("Supprimer");
        btnSup->setCursor(Qt::PointingHandCursor);

        btnSup->setAutoDefault(false);

        btnSup->setStyleSheet("QPushButton { background: #c5c9d1; border-radius: 6px;"
                              " padding: 4px 10px; font-size: 15px; }");

        QWidget *actions = new QWidget;
        QHBoxLayout *lay = new QHBoxLayout(actions);
        lay->setContentsMargins(6, 4, 6, 4);
        lay->setSpacing(8);
        lay->addWidget(btnMod);
        lay->addWidget(btnSup);
        table->setCellWidget(r, 5, actions);

        connect(btnMod, &QPushButton::clicked, this, [this, r]() { editerLigne(r); });
        connect(btnSup, &QPushButton::clicked, this, [this, num]() { supprimerLigne(num); });
    }
}

// ---------------- Modification directement dans la ligne ----------------
void MaterielWindow::editerLigne(int ligne)
{
    const QString num = table->item(ligne, 0)->text();

    // Valeurs actuelles lues dans la base (pas dans le texte formaté)
    QSqlQuery q;
    q.prepare("SELECT design, pu, stockActuel FROM materiel WHERE numMat = :n");
    q.bindValue(":n", num);
    q.exec();
    if (!q.next())
        return;

    // Une seule ligne en édition à la fois
    editRecherche->setEnabled(false);
    for (int i = 0; i < table->rowCount(); ++i) {
        if (i == ligne) continue;
        if (QWidget *w = table->cellWidget(i, 5))
            w->setEnabled(false);
    }

    // Champs éditables dans les cellules
    QLineEdit *eNom = new QLineEdit(q.value(0).toString());
    QDoubleSpinBox *sPu = new QDoubleSpinBox;
    sPu->setRange(0, 1000000000);
    sPu->setDecimals(2);
    sPu->setSuffix(DEVISE);
    sPu->setValue(q.value(1).toDouble());
    QSpinBox *sStock = new QSpinBox;
    sStock->setRange(0, 1000000);
    sStock->setValue(q.value(2).toInt());

    table->setCellWidget(ligne, 1, eNom);
    table->setCellWidget(ligne, 2, sPu);
    table->setCellWidget(ligne, 4, sStock);

    // Boutons Valider / Annuler à la place de Modifier / Supprimer
    QPushButton *btnOk = new QPushButton("✔");
    btnOk->setToolTip("Valider");
    btnOk->setCursor(Qt::PointingHandCursor);

    btnOk->setAutoDefault(false);

    btnOk->setStyleSheet("QPushButton { background: #2bb58a; border-radius: 6px;"
                         " padding: 4px 10px; font-size: 15px; }");

    QPushButton *btnNon = new QPushButton("✖");
    btnNon->setToolTip("Annuler");
    btnNon->setCursor(Qt::PointingHandCursor);

    btnNon->setAutoDefault(false);

    btnNon->setStyleSheet("QPushButton { background: #8a94a8; border-radius: 6px;"
                          " padding: 4px 10px; font-size: 15px; }");

    QWidget *actions = new QWidget;
    QHBoxLayout *lay = new QHBoxLayout(actions);
    lay->setContentsMargins(6, 4, 6, 4);
    lay->setSpacing(8);
    lay->addWidget(btnOk);
    lay->addWidget(btnNon);
    table->setCellWidget(ligne, 5, actions);

    eNom->setFocus();

    connect(btnNon, &QPushButton::clicked, this, [this]() {
        editRecherche->setEnabled(true);
        QTimer::singleShot(0, this, &MaterielWindow::charger);
    });

    connect(btnOk, &QPushButton::clicked, this, [=]() {
        const QString nom = eNom->text().trimmed();
        if (nom.isEmpty()) {
            QMessageBox::warning(this, "Attention", "Le nom ne peut pas être vide.");
            return;
        }

        Materiel m;
        m.num = num;
        m.design = nom;
        m.pu = sPu->value();
        m.stockActuel = sStock->value();

        QString erreur;
        if (!m.modifier(erreur)) {
            QMessageBox::critical(this, "Erreur", erreur);
            return;
        }

        editRecherche->setEnabled(true);
        QTimer::singleShot(0, this, &MaterielWindow::charger);
    });
}

// ---------------- Suppression d'une ligne ----------------
void MaterielWindow::supprimerLigne(const QString &num)
{
    if (QMessageBox::question(this, "Confirmation",
                              "Supprimer le matériel " + num + " ?") != QMessageBox::Yes)
        return;

    QString erreur;
    if (!Materiel::supprimer(num, erreur)) {
        QMessageBox::critical(this, "Impossible de supprimer", erreur);
        return;
    }

    QTimer::singleShot(0, this, &MaterielWindow::charger);
}


// ---------------- État de stock en PDF ----------------
void MaterielWindow::exporterPdf()
{
    const QString fichier = QFileDialog::getSaveFileName(
        this, "Enregistrer l'état de stock", "etat_de_stock.pdf", "PDF (*.pdf)");
    if (fichier.isEmpty())
        return;

    QString html =
        "<h2 align='center'>ETAT DE STOCK</h2>"
        "<p align='center'>Édité le " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>"
                                                        "<table border='1' cellspacing='0' cellpadding='6' width='100%'>"
                                                        "<tr bgcolor='#dddddd'><th align='left'>DESIGNATION</th>"
                                                        "<th align='right'>STOCK</th></tr>";

    QSqlQuery q("SELECT design, stockActuel FROM materiel ORDER BY design");
    while (q.next()) {
        html += "<tr><td>" + q.value(0).toString().toHtmlEscaped() + "</td>"
                                                                     "<td align='right'>" + q.value(1).toString() + "</td></tr>";
    }
    html += "</table>";

    QTextDocument doc;
    doc.setHtml(html);

    QPdfWriter pdf(fichier);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    doc.print(&pdf);

    QMessageBox::information(this, "PDF", "État de stock enregistré.");
}