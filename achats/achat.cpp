#include "achat.h"

Achat::Achat(const QString &numClient, const QString &numMat, int qte,
             const QDate &dateAchat)
    : m_numClient(numClient), m_numMat(numMat), m_qte(qte), m_dateAchat(dateAchat)
{
}

QString Achat::numClient() const { return m_numClient; }
QString Achat::numMat() const    { return m_numMat; }
int     Achat::qte() const       { return m_qte; }
QDate   Achat::dateAchat() const { return m_dateAchat; }

void Achat::setNumClient(const QString &numClient) { m_numClient = numClient; }
void Achat::setNumMat(const QString &numMat)       { m_numMat = numMat; }
void Achat::setQte(int qte)                        { m_qte = qte; }
void Achat::setDateAchat(const QDate &dateAchat)   { m_dateAchat = dateAchat; }
