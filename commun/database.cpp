#include "database.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QVector>

namespace {

bool executer(QSqlDatabase &db, const QString &sql)
{
    QSqlQuery query(db);
    if (query.exec(sql))
        return true;

    qWarning() << "Erreur SQL :" << query.lastError().text() << "\n" << sql;
    return false;
}

bool creerSchema(QSqlDatabase &db)
{
    return executer(db, QStringLiteral(
        "CREATE TABLE IF NOT EXISTS client ("
        "id_client INTEGER PRIMARY KEY AUTOINCREMENT, nom TEXT NOT NULL, telephone TEXT)"))
        && executer(db, QStringLiteral(
            "CREATE TABLE IF NOT EXISTS materiel ("
            "id_materiel INTEGER PRIMARY KEY AUTOINCREMENT, designation TEXT NOT NULL,"
            "prix_unitaire REAL CHECK (prix_unitaire > 0),"
            "stock_actuel INTEGER NOT NULL DEFAULT 0 CHECK (stock_actuel >= 0),"
            "stock_initial INTEGER NOT NULL DEFAULT 0 CHECK (stock_initial >= 0))"))
        && executer(db, QStringLiteral(
            "CREATE TABLE IF NOT EXISTS achat ("
            "id_achat INTEGER PRIMARY KEY AUTOINCREMENT,"
            "id_client INTEGER REFERENCES client(id_client),"
            "id_materiel INTEGER REFERENCES materiel(id_materiel),"
            "qte INTEGER NOT NULL DEFAULT 1, date_achat TEXT DEFAULT CURRENT_TIMESTAMP,"
            "numero_commande TEXT, prix_unitaire_achat REAL NOT NULL DEFAULT 0)"))
        && executer(db, QStringLiteral(
            "CREATE INDEX IF NOT EXISTS idx_achat_numero_commande ON achat(numero_commande)"));
}

bool migrerAncienneBase(QSqlDatabase &db)
{
    QSqlQuery colonnes(db);
    if (!colonnes.exec(QStringLiteral("PRAGMA table_info(client)")))
        return false;

    bool ancienSchema = false;
    while (colonnes.next())
        ancienSchema |= colonnes.value(1).toString() == QStringLiteral("numClient");
    if (!ancienSchema)
        return creerSchema(db);

    struct AncienClient { QString id; QString nom; };
    struct AncienMateriel { QString id; QString designation; double prix; int stock; int stockInitial; };
    struct AncienAchat { int id; QString client; QString materiel; int quantite; QString date; };
    QVector<AncienClient> clients;
    QVector<AncienMateriel> materiels;
    QVector<AncienAchat> achats;

    QSqlQuery lireClients(db);
    if (!lireClients.exec(QStringLiteral("SELECT numClient, nom FROM client")))
        return false;
    while (lireClients.next())
        clients.append({lireClients.value(0).toString(), lireClients.value(1).toString()});

    QSqlQuery lireMateriels(db);
    if (!lireMateriels.exec(QStringLiteral(
            "SELECT numMat, design, pu, stockActuel, stockInit FROM materiel")))
        return false;
    while (lireMateriels.next())
        materiels.append({lireMateriels.value(0).toString(), lireMateriels.value(1).toString(),
                          lireMateriels.value(2).toDouble(), lireMateriels.value(3).toInt(),
                          lireMateriels.value(4).toInt()});

    QSqlQuery lireAchats(db);
    if (!lireAchats.exec(QStringLiteral(
            "SELECT id, numClient, numMat, qte, date_achat FROM achat")))
        return false;
    while (lireAchats.next())
        achats.append({lireAchats.value(0).toInt(), lireAchats.value(1).toString(),
                       lireAchats.value(2).toString(), lireAchats.value(3).toInt(),
                       lireAchats.value(4).toString()});

    if (!db.transaction())
        return false;
    const auto rollback = [&db]() { db.rollback(); return false; };
    if (!executer(db, QStringLiteral("ALTER TABLE client RENAME TO client_legacy"))
        || !executer(db, QStringLiteral("ALTER TABLE materiel RENAME TO materiel_legacy"))
        || !executer(db, QStringLiteral("ALTER TABLE achat RENAME TO achat_legacy"))
        || !creerSchema(db))
        return rollback();

    QHash<QString, int> nouveauxClients;
    QSqlQuery insererClient(db);
    insererClient.prepare(QStringLiteral("INSERT INTO client (nom) VALUES (?)"));
    for (const AncienClient &client : clients) {
        insererClient.bindValue(0, client.nom);
        if (!insererClient.exec())
            return rollback();
        nouveauxClients.insert(client.id, insererClient.lastInsertId().toInt());
    }

    struct MaterielConverti { int id; double prix; };
    QHash<QString, MaterielConverti> nouveauxMateriels;
    QSqlQuery insererMateriel(db);
    insererMateriel.prepare(QStringLiteral(
        "INSERT INTO materiel (designation, prix_unitaire, stock_actuel, stock_initial) "
        "VALUES (?, ?, ?, ?)"));
    for (const AncienMateriel &materiel : materiels) {
        insererMateriel.bindValue(0, materiel.designation);
        insererMateriel.bindValue(1, materiel.prix);
        insererMateriel.bindValue(2, materiel.stock);
        insererMateriel.bindValue(3, materiel.stockInitial);
        if (!insererMateriel.exec())
            return rollback();
        nouveauxMateriels.insert(materiel.id,
                                 {insererMateriel.lastInsertId().toInt(), materiel.prix});
    }

    QSqlQuery insererAchat(db);
    insererAchat.prepare(QStringLiteral(
        "INSERT INTO achat (id_achat, id_client, id_materiel, qte, date_achat, "
        "numero_commande, prix_unitaire_achat) VALUES (?, ?, ?, ?, ?, ?, ?)"));
    for (const AncienAchat &achat : achats) {
        if (!nouveauxClients.contains(achat.client) || !nouveauxMateriels.contains(achat.materiel)) {
            qWarning() << "Migration SQLite interrompue : une reference d'achat est absente.";
            return rollback();
        }
        insererAchat.bindValue(0, achat.id);
        insererAchat.bindValue(1, nouveauxClients.value(achat.client));
        insererAchat.bindValue(2, nouveauxMateriels.value(achat.materiel).id);
        insererAchat.bindValue(3, achat.quantite);
        insererAchat.bindValue(4, achat.date);
        insererAchat.bindValue(5, QStringLiteral("CMD-%1").arg(achat.id, 6, 10, QLatin1Char('0')));
        insererAchat.bindValue(6, nouveauxMateriels.value(achat.materiel).prix);
        if (!insererAchat.exec())
            return rollback();
    }

    if (!executer(db, QStringLiteral("DROP TABLE achat_legacy"))
        || !executer(db, QStringLiteral("DROP TABLE materiel_legacy"))
        || !executer(db, QStringLiteral("DROP TABLE client_legacy"))
        || !db.commit())
        return rollback();
    return true;
}

}

bool Database::ouvrir()
{
    QString cheminBaseProjet;
    QDir dossierProjet(QCoreApplication::applicationDirPath());
    for (int niveau = 0; niveau < 5; ++niveau) {
        const QString candidat = dossierProjet.filePath(QStringLiteral("commun/itstore.db"));
        if (QFileInfo::exists(candidat)) {
            cheminBaseProjet = QFileInfo(candidat).absoluteFilePath();
            break;
        }
        if (!dossierProjet.cdUp())
            break;
    }

    QString cheminBase = cheminBaseProjet;
    if (cheminBase.isEmpty()) {
        const QString dossier = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        if (dossier.isEmpty() || !QDir().mkpath(dossier)) {
            qWarning() << "Impossible de créer le dossier de données :" << dossier;
            return false;
        }

        cheminBase = QDir(dossier).filePath(QStringLiteral("itstore.db"));
    }

    QSqlDatabase db = QSqlDatabase::contains()
        ? QSqlDatabase::database()
        : QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    if (db.isOpen())
        return db.databaseName() == cheminBase;

    db.setDatabaseName(cheminBase);

    if (!db.open()) {
        qWarning() << "Ouverture de la base impossible :" << db.lastError().text();
        return false;
    }

    return migrerAncienneBase(db)
        && executer(db, QStringLiteral("PRAGMA foreign_keys = ON"));
}