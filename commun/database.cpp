<<<<<<< HEAD
#include "database.h"

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QStringList>

bool Database::ouvrir()
{
    const QString dossier =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dossier);

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    db.setDatabaseName(dossier + QStringLiteral("/itstore.db"));

    if (!db.open()) {
        qWarning() << "Ouverture de la base impossible :" << db.lastError().text();
        return false;
    }

    QStringList requetes;
    requetes << QStringLiteral("PRAGMA foreign_keys = ON");

    requetes << QStringLiteral(
        "CREATE TABLE IF NOT EXISTS Client ("
        " numClient TEXT PRIMARY KEY,"
        " nom       TEXT NOT NULL)");

    requetes << QStringLiteral(
        "CREATE TABLE IF NOT EXISTS Materiel ("
        " numMat      TEXT PRIMARY KEY,"
        " design      TEXT NOT NULL,"
        " pu          REAL NOT NULL DEFAULT 0,"
        " stockActuel INTEGER NOT NULL DEFAULT 0,"
        " stockInit   INTEGER NOT NULL DEFAULT 0)");

    requetes << QStringLiteral(
        "CREATE TABLE IF NOT EXISTS Achat ("
        " id          INTEGER PRIMARY KEY AUTOINCREMENT,"
        " numClient   TEXT NOT NULL REFERENCES Client(numClient),"
        " numMat      TEXT NOT NULL REFERENCES Materiel(numMat),"
        " qte         INTEGER NOT NULL,"
        " date_achat  TEXT NOT NULL)");   // format yyyy-MM-dd

    QSqlQuery q(db);
    for (const QString &sql : requetes) {
        if (!q.exec(sql)) {
            qWarning() << "Erreur SQL :" << q.lastError().text() << "\n" << sql;
            return false;
        }
    }
    return true;
}
=======
#include "database.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static void initialiserRessourcesBase()
{
    Q_INIT_RESOURCE(database);
}

static QString cheminBaseConventionnel()
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QStringList cheminsPossibles = {
        QDir(appDir).filePath("commun/itstore.db"),
        QDir(appDir).filePath("../commun/itstore.db"),
        QDir::cleanPath(QDir::currentPath() + "/commun/itstore.db"),
        QDir::cleanPath(QDir::currentPath() + "/../commun/itstore.db")
    };

    for (const QString &chemin : cheminsPossibles) {
        if (QFileInfo::exists(chemin))
            return chemin;
    }

    return QDir(appDir).filePath("commun/itstore.db");
}

bool Database::ouvrir()
{
    initialiserRessourcesBase();

    QString cheminBase = cheminBaseConventionnel();

    QString dossierBase = QFileInfo(cheminBase).absolutePath();
    if (!QDir().exists(dossierBase) && !QDir().mkpath(dossierBase)) {
        qDebug() << "Impossible de créer le dossier de la base de données :" << dossierBase;
        return false;
    }

    if (!QFile::exists(cheminBase)) {
        QFile baseIntegree(QStringLiteral(":/database/itstore.db"));
        QFile baseUtilisateur(cheminBase);
        if (!baseIntegree.open(QIODevice::ReadOnly) || !baseUtilisateur.open(QIODevice::WriteOnly)
            || baseUtilisateur.write(baseIntegree.readAll()) < 0) {
            qDebug() << "Impossible de préparer la base de données : " << cheminBase;
            return false;
        }
    }

    QSqlDatabase db = QSqlDatabase::contains()
        ? QSqlDatabase::database()
        : QSqlDatabase::addDatabase("QSQLITE");
    if (db.isOpen()) {
        return db.databaseName() == cheminBase;
    }

    db.setDatabaseName(cheminBase);

    if(!db.open()){
        qDebug() <<"Erreur d`ouverture d`itstore : "<< db.lastError().text();
        return false;
    }

    QSqlQuery colonnes("PRAGMA table_info(achat)");
    bool numeroCommandeExiste = false;
    bool prixAchatExiste = false;
    while (colonnes.next()) {
        const QString nomColonne = colonnes.value("name").toString();
        if (nomColonne == "numero_commande")
            numeroCommandeExiste = true;
        if (nomColonne == "prix_unitaire_achat")
            prixAchatExiste = true;
    }

    if (!numeroCommandeExiste || !prixAchatExiste) {
        if (!db.transaction())
            return false;

        bool colonnesAjoutees = true;
        if (!numeroCommandeExiste) {
            QSqlQuery ajouterNumeroCommande;
            colonnesAjoutees = ajouterNumeroCommande.exec("ALTER TABLE achat ADD COLUMN numero_commande TEXT");
        }
        if (colonnesAjoutees && !prixAchatExiste) {
            QSqlQuery ajouterPrixAchat;
            colonnesAjoutees = ajouterPrixAchat.exec("ALTER TABLE achat ADD COLUMN prix_unitaire_achat REAL NOT NULL DEFAULT 0");
        }

        QSqlQuery attribuerReferences;
        const bool referencesAttribuees = colonnesAjoutees
            && attribuerReferences.exec("UPDATE achat SET numero_commande = 'CMD-' || printf('%06d', id_achat) WHERE numero_commande IS NULL OR numero_commande = ''");
        QSqlQuery enregistrerPrix;
        const bool prixEnregistres = referencesAttribuees
            && enregistrerPrix.exec("UPDATE achat SET prix_unitaire_achat = COALESCE((SELECT prix_unitaire FROM materiel WHERE materiel.id_materiel = achat.id_materiel), 0) WHERE prix_unitaire_achat = 0");
        QSqlQuery indexCommande;
        const bool indexCree = prixEnregistres
            && indexCommande.exec("CREATE INDEX IF NOT EXISTS idx_achat_numero_commande ON achat(numero_commande)");

        if (!indexCree) {
            db.rollback();
            qDebug() << "Impossible de mettre à jour la structure des achats:" << db.lastError().text();
            return false;
        }
        if (!db.commit())
            return false;
    } else {
        QSqlQuery referencesManquantes;
        if (!referencesManquantes.exec("UPDATE achat SET numero_commande = 'CMD-' || printf('%06d', id_achat) WHERE numero_commande IS NULL OR numero_commande = ''"))
            return false;
        QSqlQuery indexCommande;
        if (!indexCommande.exec("CREATE INDEX IF NOT EXISTS idx_achat_numero_commande ON achat(numero_commande)"))
            return false;
    }

    qDebug()<<"Connexion successful!";

    return true;
}
>>>>>>> 8c2295e (Crafting)
