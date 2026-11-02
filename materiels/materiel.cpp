#include "materiel.h"

#include <QSqlError>
#include <QSqlQuery>

Materiel::Materiel(const QString &numero, const QString &designation, double prix,
                                     int stockCourant, int stockInitial)
        : num(numero), design(designation), pu(prix),
            stockInit(stockInitial), stockActuel(stockCourant)
{
}

bool Materiel::ajouter(QString &erreur) const
{
    QSqlQuery q;
    q.prepare("INSERT INTO materiel (id_materiel, designation, prix_unitaire, stock_initial, stock_actuel) "
              "VALUES (:n, :d, :p, :s, :s)");
    q.bindValue(":n", num.toInt());
    q.bindValue(":d", design);
    q.bindValue(":p", pu);
    q.bindValue(":s", stockInit);
    if (!q.exec()) {
        erreur = q.lastError().text();
        return false;
    }
    return true;
}

bool Materiel::modifier(QString &erreur) const
{
    QSqlQuery q;
    q.prepare("UPDATE materiel SET designation = :d, prix_unitaire = :p, "
              "stock_initial = stock_initial + (:s - stock_actuel), "
              "stock_actuel = :s WHERE id_materiel = :n");
    q.bindValue(":d", design);
    q.bindValue(":p", pu);
    q.bindValue(":s", stockActuel);
    q.bindValue(":n", num.toInt());
    if (!q.exec()) {
        erreur = q.lastError().text();
        return false;
    }
    if (q.numRowsAffected() == 0) {
        erreur = "Matériel non trouvé.";
        return false;
    }
    return true;
}

bool Materiel::supprimer(const QString &num, QString &erreur)
{
    QSqlQuery q;
    q.prepare("DELETE FROM materiel WHERE id_materiel = :n");
    q.bindValue(":n", num.toInt());
    if (!q.exec()) {
        erreur = "Ce matériel a des achats enregistrés. Supprime d'abord ces achats.";
        return false;
    }
    if (q.numRowsAffected() == 0) {
        erreur = "Matériel non trouvé.";
        return false;
    }
    return true;
}

bool Materiel::existe(const QString &design)
{
    QSqlQuery q;
    q.prepare("SELECT 1 FROM materiel WHERE designation = :d COLLATE NOCASE");
    q.bindValue(":d", design);
    q.exec();
    return q.next();
}

QString Materiel::prochainNumero()
{
    QSqlQuery q("SELECT COALESCE(MAX(id_materiel), 0) + 1 FROM materiel");
    int n = 1;
    if (q.next())
        n = q.value(0).toInt();
    return QString::number(n);
}

bool Materiel::chercher(const QString &texte, bool critereNom, Materiel &r)
{
    QSqlQuery q;
    if (critereNom)
        q.prepare("SELECT id_materiel, designation, prix_unitaire, stock_initial, stock_actuel "
                  "FROM materiel WHERE designation LIKE :t ORDER BY designation LIMIT 1");
    else
        q.prepare("SELECT id_materiel, designation, prix_unitaire, stock_initial, stock_actuel "
                  "FROM materiel WHERE printf('MAT%03d', id_materiel) LIKE :t "
                  "ORDER BY id_materiel LIMIT 1");
    q.bindValue(":t", "%" + texte + "%");
    q.exec();

    if (!q.next())
        return false;

    r.num = q.value(0).toString();
    r.design = q.value(1).toString();
    r.pu = q.value(2).toDouble();
    r.stockInit = q.value(3).toInt();
    r.stockActuel = q.value(4).toInt();
    return true;
}