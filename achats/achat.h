#pragma once

#include <QDate>
#include <QString>

/** Table Achat (numClient, numMat, qte, date_achat) */
class Achat
{
public:
    Achat() = default;
    Achat(const QString &numClient, const QString &numMat, int qte,
          const QDate &dateAchat);

    QString numClient() const;
    QString numMat() const;
    int     qte() const;
    QDate   dateAchat() const;

    void setNumClient(const QString &numClient);
    void setNumMat(const QString &numMat);
    void setQte(int qte);
    void setDateAchat(const QDate &dateAchat);

private:
    QString m_numClient;
    QString m_numMat;
    int     m_qte = 0;
    QDate   m_dateAchat;
};
