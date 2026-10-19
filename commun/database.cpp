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
