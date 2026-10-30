#include "database.h"

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QStringList>
#include <QMessageBox>


// DB Commune : Ouverture + Création des Tables de chaque Module (MATéRIEL, CLIENT, ACHAT)
bool Database::ouvrir()
{
    const QString dossier =
    QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dossier);

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    db.setDatabaseName(dossier + QStringLiteral("/itstore.db"));

    // Vérification Chemin
    qDebug() << "Base SQLite utilisée :" << db.databaseName();

    if (!db.open()) {
        qWarning() << "Ouverture de la base impossible :" << db.lastError().text();
        return false;
    }

    // ====================================================== //
    // ====================================================== //

    QSqlQuery diagnostic(db);

    QString resultat;
    const QStringList tables = {
        "client",
        "materiel",
        "achat"
    };

    for (const QString &table : tables) {
        if (!diagnostic.exec(
                "SELECT COUNT(*) FROM " + table)) {
            resultat += table + " : erreur SQL\n";
            continue;
        }

        if (diagnostic.next()) {
            resultat += table + " : "
                        + diagnostic.value(0).toString()
                        + " enregistrement(s)\n";
        }
    }

    QMessageBox::information(
        nullptr,
        "État de la base SQLite",
        resultat
        );

    // ====================================================== //
    // ====================================================== //
    QSqlQuery verification(db);

    if (verification.exec("PRAGMA table_info(client)")) {
        while (verification.next()) {
            qDebug() << "Colonne client :"
                     << verification.value("name").toString();
        }
    }

    QSqlQuery verificationAchat(db);

    if (verificationAchat.exec("PRAGMA table_info(achat)")) {
        while (verificationAchat.next()) {
            qDebug() << "Colonne achat :"
                     << verificationAchat.value("name").toString();
        }
    }

    QSqlQuery verificationMateriel(db);

    if (verificationMateriel.exec("PRAGMA table_info(materiel)")) {
        while (verificationMateriel.next()) {
            qDebug() << "Colonne materiel :"
                     << verificationMateriel.value("name").toString();
        }
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
