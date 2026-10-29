#include "nouveauachat.h"
#include "ui_nouveauachat.h"

#include <QDate>
#include <QFrame>
#include <QIntValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QLocale>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QScrollArea>
#include <QVariantList>

static QString enAriary(double valeur)
{
    return QLocale::c().toString(valeur, 'f', 0).replace(',', QChar(0x00A0)) + QChar(0x00A0) + "Ar";
}

static bool executer(const QString &sql, const QVariantList &valeurs)
{
    QSqlQuery q;
    q.prepare(sql);
    for (const QVariant &valeur : valeurs)
        q.addBindValue(valeur);
    return q.exec() && q.numRowsAffected() == 1;
}

NouveauAchat::NouveauAchat(int idAchat, QWidget *parent)
    : QDialog(parent), ui(new Ui::NouveauAchat), m_idAchat(idAchat)
{
    ui->setupUi(this);
    ui->champQuantite->setValidator(new QIntValidator(1, 1000000, ui->champQuantite));
    ui->champQuantite->setText(QStringLiteral("1"));

    auto *zoneDefilable = new QScrollArea(this);
    zoneDefilable->setObjectName("zoneDefilable");
    zoneDefilable->setWidgetResizable(true);
    zoneDefilable->setFrameShape(QFrame::NoFrame);
    zoneDefilable->setMinimumHeight(300);
    zoneDefilable->setStyleSheet("QScrollArea#zoneDefilable { background: #FFFFFF; border: 0; }"
                                 "QScrollArea#zoneDefilable QWidget#qt_scrollarea_viewport { background: #FFFFFF; }");
    ui->layoutPrincipal->replaceWidget(ui->corps, zoneDefilable);
    zoneDefilable->setWidget(ui->corps);
    ui->corps->setAttribute(Qt::WA_StyledBackground, true);
    ui->corps->setStyleSheet("QWidget#corps { background-color: #FFFFFF; }");

    QSqlQuery requete("SELECT id_client, nom FROM client ORDER BY nom");
    while (requete.next())
        ui->comboClient->addItem(requete.value(0).toString() + " – " + requete.value(1).toString(), requete.value(0));

    requete.exec("SELECT id_materiel, designation, prix_unitaire FROM materiel ORDER BY designation");
    while (requete.next())
        ui->comboMateriel->addItem(requete.value(1).toString() + " – " + enAriary(requete.value(2).toDouble()), requete.value(0));

    ui->comboClient->setPlaceholderText("Choisir un client");
    ui->comboMateriel->setPlaceholderText("Choisir un matériel");
    ui->comboClient->setCurrentIndex(-1);
    ui->comboMateriel->setCurrentIndex(-1);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->labelErreur->hide();
    ui->tableArticlesCommande->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableArticlesCommande->verticalHeader()->setDefaultSectionSize(42);
    ui->tableArticlesCommande->setColumnWidth(1, 100);
    ui->tableArticlesCommande->horizontalHeader()->setStyleSheet(
        "QHeaderView::section { background: #FFF1E2; color: #70421F; border: 0; "
        "border-bottom: 2px solid #E8CFB8; padding: 8px; font-weight: 700; }");

    if (m_idAchat > 0) {
        requete.prepare("SELECT id_client, id_materiel, qte, date_achat, prix_unitaire_achat FROM achat WHERE id_achat = ?");
        requete.addBindValue(m_idAchat);
        requete.exec();
        if (requete.next()) {
            m_idMaterielInitial = requete.value(1).toString();
            m_quantiteInitiale = requete.value(2).toInt();
            m_prixUnitaireInitial = requete.value(4).toDouble();
            ui->comboClient->setCurrentIndex(ui->comboClient->findData(requete.value(0)));
            ui->comboMateriel->setCurrentIndex(ui->comboMateriel->findData(requete.value(1)));
            definirQuantite(m_quantiteInitiale);
            ui->dateEdit->setDate(QDate::fromString(requete.value(3).toString(), "yyyy-MM-dd"));
        }
        QSqlQuery nombreArticles;
        nombreArticles.prepare("SELECT COUNT(*) FROM achat WHERE numero_commande = "
                               "(SELECT numero_commande FROM achat WHERE id_achat = ?)");
        nombreArticles.addBindValue(m_idAchat);
        if (nombreArticles.exec() && nombreArticles.next())
            m_commandeAvecPlusieursArticles = nombreArticles.value(0).toInt() > 1;

        ui->titleLabel->setText("Modifier l'achat");
        setWindowTitle("Modifier un achat");
        ui->btnAjouterArticle->hide();
        ui->btnRetirerArticle->hide();
        ui->tableArticlesCommande->hide();
        ui->btnEnregistrer->setText("Enregistrer les modifications");
        if (m_commandeAvecPlusieursArticles) {
            ui->comboClient->setEnabled(false);
            ui->dateEdit->setEnabled(false);
        }
    } else {
        ui->titleLabel->setText("Nouvelle commande");
        setWindowTitle("Nouvelle commande");
        ui->btnEnregistrer->setText("Enregistrer la commande");
    }

    connect(ui->comboMateriel, &QComboBox::currentIndexChanged, this, &NouveauAchat::mettreAJourResume);
    connect(ui->comboClient, &QComboBox::currentIndexChanged, this, &NouveauAchat::mettreAJourResume);
    connect(ui->champQuantite, &QLineEdit::textChanged, this, &NouveauAchat::mettreAJourResume);
    connect(ui->champQuantite, &QLineEdit::editingFinished, this, [this]() {
        definirQuantite(quantiteChoisie());
        mettreAJourResume();
    });
    connect(ui->btnAugmenterQuantite, &QPushButton::clicked, this, [this]() {
        definirQuantite(quantiteChoisie() + 1);
    });
    connect(ui->btnReduireQuantite, &QPushButton::clicked, this, [this]() {
        definirQuantite(quantiteChoisie() - 1);
    });
    connect(ui->btnAjouterArticle, &QPushButton::clicked, this, &NouveauAchat::ajouterArticle);
    connect(ui->btnRetirerArticle, &QPushButton::clicked, this, &NouveauAchat::retirerArticle);
    connect(ui->tableArticlesCommande, &QTableWidget::itemSelectionChanged, this, [this]() {
        ui->btnRetirerArticle->setEnabled(!ui->tableArticlesCommande->selectedItems().isEmpty());
    });
    connect(ui->btnAnnuler, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btnEnregistrer, &QPushButton::clicked, this, &NouveauAchat::onEnregistrer);

    mettreAJourResume();
}

NouveauAchat::~NouveauAchat()
{
    delete ui;
}

int NouveauAchat::quantiteInitialePourMateriel() const
{
    const bool memeMateriel = ui->comboMateriel->currentData().toString() == m_idMaterielInitial;
    return (m_idAchat > 0 && memeMateriel) ? m_quantiteInitiale : 0;
}

int NouveauAchat::quantiteChoisie() const
{
    bool valide = false;
    const int quantite = ui->champQuantite->text().toInt(&valide);
    return valide ? qBound(1, quantite, 1000000) : 1;
}

void NouveauAchat::definirQuantite(int quantite)
{
    ui->champQuantite->setText(QString::number(qBound(1, quantite, 1000000)));
}

void NouveauAchat::afficherArticlesCommande()
{
    ui->tableArticlesCommande->setRowCount(0);
    double montantTotal = 0;

    for (const ArticleCommande &article : m_articlesCommande) {
        const int ligne = ui->tableArticlesCommande->rowCount();
        ui->tableArticlesCommande->insertRow(ligne);
        const QStringList valeurs = {
            article.designation,
            QString::number(article.quantite),
            enAriary(article.prixUnitaire * article.quantite)
        };
        for (int colonne = 0; colonne < valeurs.size(); ++colonne) {
            auto *cellule = new QTableWidgetItem(valeurs[colonne]);
            if (colonne > 0)
                cellule->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->tableArticlesCommande->setItem(ligne, colonne, cellule);
        }
        montantTotal += article.prixUnitaire * article.quantite;
    }

    ui->labelMontantValeur->setText(enAriary(montantTotal));
    ui->btnRetirerArticle->setEnabled(!ui->tableArticlesCommande->selectedItems().isEmpty());
    if (m_idAchat == 0)
        ui->btnEnregistrer->setEnabled(!m_articlesCommande.isEmpty() && ui->comboClient->currentIndex() >= 0);
}

void NouveauAchat::ajouterArticle()
{
    const QString erreur = obtenirMessageErreur();
    if (!erreur.isEmpty()) {
        ui->labelErreur->setText(erreur);
        ui->labelErreur->show();
        return;
    }

    const int idMateriel = ui->comboMateriel->currentData().toInt();
    const QString designation = ui->comboMateriel->currentText().section(" – ", 0, 0);
    const int quantite = quantiteChoisie();
    bool articleTrouve = false;

    for (ArticleCommande &article : m_articlesCommande) {
        if (article.idMateriel == idMateriel) {
            article.quantite += quantite;
            articleTrouve = true;
            break;
        }
    }
    if (!articleTrouve)
        m_articlesCommande.append({idMateriel, designation, m_prixUnitaire, quantite});

    ui->labelErreur->hide();
    ui->comboMateriel->setCurrentIndex(-1);
    definirQuantite(1);
    afficherArticlesCommande();
    mettreAJourResume();
}

void NouveauAchat::retirerArticle()
{
    const int ligne = ui->tableArticlesCommande->currentRow();
    if (ligne < 0 || ligne >= m_articlesCommande.size())
        return;

    m_articlesCommande.removeAt(ligne);
    afficherArticlesCommande();
    mettreAJourResume();
}

void NouveauAchat::mettreAJourResume()
{
    ui->labelErreur->hide();

    m_prixUnitaire = 0;
    m_stockActuel = 0;
    QSqlQuery requete;
    requete.prepare("SELECT prix_unitaire, stock_actuel FROM materiel WHERE id_materiel = ?");
    requete.addBindValue(ui->comboMateriel->currentData());
    requete.exec();

    if (!requete.next()) {
        ui->labelStock->setText("Stock actuel : —");
        ui->labelStockInfo->setText("Choisissez un matériel");
        ui->btnAjouterArticle->setEnabled(false);
        if (m_idAchat == 0) {
            double montantCommande = 0;
            for (const ArticleCommande &article : m_articlesCommande)
                montantCommande += article.prixUnitaire * article.quantite;
            ui->labelMontantValeur->setText(enAriary(montantCommande));
            ui->btnEnregistrer->setEnabled(!m_articlesCommande.isEmpty()
                                           && ui->comboClient->currentIndex() >= 0);
        } else {
            ui->btnEnregistrer->setEnabled(false);
        }
        return;
    }
    const bool memeMaterielInitial = ui->comboMateriel->currentData().toString() == m_idMaterielInitial;
    m_prixUnitaire = m_idAchat > 0 && memeMaterielInitial
        ? m_prixUnitaireInitial
        : requete.value(0).toDouble();
    m_stockActuel = requete.value(1).toInt();

    const int quantite = quantiteChoisie();
    int quantiteDansCommande = 0;
    for (const ArticleCommande &article : m_articlesCommande) {
        if (article.idMateriel == ui->comboMateriel->currentData().toInt())
            quantiteDansCommande = article.quantite;
    }
    const int stockApres = m_stockActuel + quantiteInitialePourMateriel() - quantiteDansCommande - quantite;

    ui->labelStock->setText(QString("Stock actuel : %1").arg(m_stockActuel));
    if (stockApres >= 0)
        ui->labelStockInfo->setText(QString("Le stock passera de %1 à %2").arg(m_stockActuel).arg(stockApres));
    else
        ui->labelStockInfo->setText("Stock insuffisant");
    if (m_idAchat == 0) {
        double montantCommande = m_prixUnitaire * quantite;
        for (const ArticleCommande &article : m_articlesCommande)
            montantCommande += article.prixUnitaire * article.quantite;
        ui->labelMontantValeur->setText(enAriary(montantCommande));
        ui->btnAjouterArticle->setEnabled(obtenirMessageErreur().isEmpty());
    } else {
        ui->labelMontantValeur->setText(enAriary(m_prixUnitaire * quantite));
        ui->btnEnregistrer->setEnabled(obtenirMessageErreur().isEmpty());
    }
}

QString NouveauAchat::obtenirMessageErreur() const
{
    if (ui->comboClient->currentIndex() < 0) {
        return ui->comboClient->count() == 0 ? "Aucun client enregistré : ajoutez d'abord un client."
                                             : "Veuillez choisir un client.";
    }
    if (ui->comboMateriel->currentIndex() < 0) {
        return ui->comboMateriel->count() == 0 ? "Aucun matériel enregistré : ajoutez d'abord un matériel."
                                               : "Veuillez choisir un matériel.";
    }

    const int disponible = m_stockActuel + quantiteInitialePourMateriel();
    int quantiteDejaAjoutee = 0;
    if (m_idAchat == 0) {
        for (const ArticleCommande &article : m_articlesCommande) {
            if (article.idMateriel == ui->comboMateriel->currentData().toInt())
                quantiteDejaAjoutee = article.quantite;
        }
    }
    if (quantiteChoisie() + quantiteDejaAjoutee > disponible)
        return QString("Stock insuffisant : %1 disponible(s) pour ce matériel.").arg(disponible);
    return QString();
}

void NouveauAchat::onEnregistrer()
{
    if (m_idAchat == 0) {
        if (ui->comboClient->currentIndex() < 0) {
            ui->labelErreur->setText("Veuillez choisir un client pour cette commande.");
            ui->labelErreur->show();
            return;
        }
        if (m_articlesCommande.isEmpty()) {
            ui->labelErreur->setText("Ajoutez au moins un article à la commande.");
            ui->labelErreur->show();
            return;
        }

        const QVariant idClient = ui->comboClient->currentData();
        const QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
        QSqlDatabase::database().transaction();
        QSqlQuery prochaineReference;
        const bool referencePrete = prochaineReference.exec(
            "SELECT COALESCE((SELECT seq + 1 FROM sqlite_sequence WHERE name = 'achat'), "
            "(SELECT COALESCE(MAX(id_achat), 0) + 1 FROM achat))")
            && prochaineReference.next();
        const QString numeroCommande = referencePrete
            ? QString("CMD-%1").arg(prochaineReference.value(0).toInt(), 6, 10, QChar('0'))
            : QString();
        bool commandeEnregistree = referencePrete;

        for (const ArticleCommande &article : m_articlesCommande) {
            commandeEnregistree = executer(
                "UPDATE materiel SET stock_actuel = stock_actuel - ? WHERE id_materiel = ? AND stock_actuel >= ?",
                {article.quantite, article.idMateriel, article.quantite});
            if (!commandeEnregistree)
                break;

            commandeEnregistree = executer(
                "INSERT INTO achat (id_client, id_materiel, qte, date_achat, numero_commande, prix_unitaire_achat) "
                "VALUES (?, ?, ?, ?, ?, ?)",
                {idClient, article.idMateriel, article.quantite, date, numeroCommande, article.prixUnitaire});
            if (!commandeEnregistree)
                break;
        }

        if (!commandeEnregistree || !QSqlDatabase::database().commit()) {
            QSqlDatabase::database().rollback();
            ui->labelErreur->setText("Stock insuffisant ou erreur : la commande n'a pas été enregistrée.");
            ui->labelErreur->show();
            return;
        }
        accept();
        return;
    }

    const QString erreur = obtenirMessageErreur();
    if (!erreur.isEmpty()) {
        ui->labelErreur->setText(erreur);
        ui->labelErreur->show();
        return;
    }

    const QVariant client = ui->comboClient->currentData();
    const QVariant materiel = ui->comboMateriel->currentData();
    const int quantite = quantiteChoisie();
    const QString date = ui->dateEdit->date().toString("yyyy-MM-dd");

    QSqlDatabase::database().transaction();
    bool ok;
    if (m_idAchat > 0) {
        ok = executer("UPDATE materiel SET stock_actuel = stock_actuel + ? WHERE id_materiel = ?", {m_quantiteInitiale, m_idMaterielInitial})
             && executer("UPDATE materiel SET stock_actuel = stock_actuel - ? WHERE id_materiel = ? AND stock_actuel >= ?",
                         {quantite, materiel, quantite})
             && executer("UPDATE achat SET id_client = ?, id_materiel = ?, qte = ?, date_achat = ?, prix_unitaire_achat = ? WHERE id_achat = ?",
                         {client, materiel, quantite, date, m_prixUnitaire, m_idAchat});
    } else {
        ok = executer("UPDATE materiel SET stock_actuel = stock_actuel - ? WHERE id_materiel = ? AND stock_actuel >= ?",
                      {quantite, materiel, quantite})
             && executer("INSERT INTO achat (id_client, id_materiel, qte, date_achat) VALUES (?, ?, ?, ?)",
                         {client, materiel, quantite, date});
    }

    if (!ok) {
        QSqlDatabase::database().rollback();
        ui->labelErreur->setText("Stock insuffisant ou erreur : l'achat n'a pas pu être enregistré.");
        ui->labelErreur->show();
        return;
    }
    QSqlDatabase::database().commit();
    accept();
}
