#pragma once

#include <QString>

/** Table Client (numClient : String, nom : String) */
class Client
{
public:
    Client() = default;
    Client(const QString &numClient, const QString &nom);

    QString numClient() const;
    QString nom() const;

    void setNumClient(const QString &numClient);
    void setNom(const QString &nom);

private:
    QString m_numClient;
    QString m_nom;
};
