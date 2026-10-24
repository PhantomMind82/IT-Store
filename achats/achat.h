#pragma once

#include <QDate>
#include <QString>

/**
 * @brief Un achat : un client achète une quantité d'un matériel à une date donnée.
 *
 * C'est une simple classe de données (pas d'interface graphique ici).
 * Les attributs sont privés (préfixe m_) et on y accède par des méthodes :
 *  - les "getters" (ex. qte()) lisent la valeur ;
 *  - les "setters" (ex. setQte()) la modifient.
 */
class Achat
{
public:
    Achat() = default;
    Achat(int idAchat, const QString &numClient, const QString &nomClient,
          const QString &numMat, const QString &designationMat,
          int qte, double prixUnitaire, const QDate &dateAchat,
          const QString &telephoneClient = QString());

    // --- Lecture ---
    int     idAchat() const;
    QString numClient() const;
    QString nomClient() const;
    QString telephoneClient() const;
    QString numMat() const;
    QString designationMat() const;
    int     qte() const;
    double  prixUnitaire() const;
    double  montantTotal() const;      // qte x prix unitaire (calculé, pas stocké)
    QDate   dateAchat() const;

    // --- Modification ---
    void setIdAchat(int id);
    void setNumClient(const QString &numClient);
    void setNomClient(const QString &nomClient);
    void setTelephoneClient(const QString &telephone);
    void setNumMat(const QString &numMat);
    void setDesignationMat(const QString &designation);
    void setQte(int qte);
    void setPrixUnitaire(double prix);
    void setDateAchat(const QDate &date);

private:
    int     m_idAchat = 0;
    QString m_numClient;
    QString m_nomClient;
    QString m_telephoneClient;
    QString m_numMat;
    QString m_designationMat;
    int     m_qte = 0;
    double  m_prixUnitaire = 0.0;
    QDate   m_dateAchat;
};
