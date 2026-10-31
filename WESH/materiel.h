#pragma once
#include <QString>

class Materiel
{
public:
    QString num;
    QString design;
    double pu = 0;
    int stockInit = 0;
    int stockActuel = 0;

    // Retourne false en cas d'échec ; "erreur" contient le message
    bool ajouter(QString &erreur) const;
    bool modifier(QString &erreur) const;
    static bool supprimer(const QString &num, QString &erreur);

    static bool existe(const QString &design);
    static QString prochainNumero();
    // critereNom = true : recherche par nom, sinon par numéro
    static bool chercher(const QString &texte, bool critereNom, Materiel &resultat);
};