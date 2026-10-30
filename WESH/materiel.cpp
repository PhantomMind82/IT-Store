#include "materiel.h"

#include <QSqlError>
#include <QSqlQuery>

bool Materiel::ajouter(QString &erreur) const
{
    QSqlQuery q;
    q.prepare("INSERT INTO materiel (numMat, design, pu, stockInit, stockActuel) "
              "VALUES (:n, :d, :p, :s, :s)");
    q.bindValue(":n", num);
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
    q.prepare("UPDATE materiel SET design = :d, pu = :p, "
              "stockInit = stockInit + (:s - stockActuel), "
              "stockActuel = :s WHERE numMat = :n");
    q.bindValue(":d", design);
    q.bindValue(":p", pu);
    q.bindValue(":s", stockActuel);
    q.bindValue(":n", num);
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
    q.prepare("DELETE FROM materiel WHERE numMat = :n");
    q.bindValue(":n", num);
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
    q.prepare("SELECT 1 FROM materiel WHERE design = :d COLLATE NOCASE");
    q.bindValue(":d", design);
    q.exec();
    return q.next();
}

QString Materiel::prochainNumero()
{
    QSqlQuery q("SELECT MAX(CAST(SUBSTR(numMat, 4) AS INTEGER)) FROM materiel "
                "WHERE numMat LIKE 'MAT%'");
    int n = 0;
    if (q.next())
        n = q.value(0).toInt();
    return QString("MAT%1").arg(n + 1, 3, 10, QChar('0'));
}

bool Materiel::chercher(const QString &texte, bool critereNom, Materiel &r)
{
    QSqlQuery q;
    if (critereNom)
        q.prepare("SELECT numMat, design, pu, stockInit, stockActuel FROM materiel "
                  "WHERE design LIKE :t ORDER BY design LIMIT 1");
    else
        q.prepare("SELECT numMat, design, pu, stockInit, stockActuel FROM materiel "
                  "WHERE numMat LIKE :t ORDER BY numMat LIMIT 1");
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