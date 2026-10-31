#include "achat.h"

Achat::Achat(int idAchat, const QString &numClient, const QString &nomClient,
             const QString &numMat, const QString &designationMat,
             int qte, double prixUnitaire, const QDate &dateAchat,
             const QString &telephoneClient)
    : m_idAchat(idAchat),
      m_numClient(numClient),
      m_nomClient(nomClient),
      m_telephoneClient(telephoneClient),
      m_numMat(numMat),
      m_designationMat(designationMat),
      m_qte(qte),
      m_prixUnitaire(prixUnitaire),
      m_dateAchat(dateAchat)
{
}

int     Achat::idAchat() const         { return m_idAchat; }
QString Achat::numClient() const       { return m_numClient; }
QString Achat::nomClient() const       { return m_nomClient; }
QString Achat::telephoneClient() const { return m_telephoneClient; }
QString Achat::numMat() const          { return m_numMat; }
QString Achat::designationMat() const  { return m_designationMat; }
int     Achat::qte() const             { return m_qte; }
double  Achat::prixUnitaire() const    { return m_prixUnitaire; }
double  Achat::montantTotal() const    { return m_qte * m_prixUnitaire; }
QDate   Achat::dateAchat() const       { return m_dateAchat; }

void Achat::setIdAchat(int id)                          { m_idAchat = id; }
void Achat::setNumClient(const QString &numClient)      { m_numClient = numClient; }
void Achat::setNomClient(const QString &nomClient)      { m_nomClient = nomClient; }
void Achat::setTelephoneClient(const QString &telephone){ m_telephoneClient = telephone; }
void Achat::setNumMat(const QString &numMat)            { m_numMat = numMat; }
void Achat::setDesignationMat(const QString &designation){ m_designationMat = designation; }
void Achat::setQte(int qte)                             { m_qte = qte; }
void Achat::setPrixUnitaire(double prix)                { m_prixUnitaire = prix; }
void Achat::setDateAchat(const QDate &date)             { m_dateAchat = date; }
