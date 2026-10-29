#include "client.h"

Client::Client(const QString &numClient, const QString &nom)
    : m_numClient(numClient), m_nom(nom)
{
}

QString Client::numClient() const { return m_numClient; }
QString Client::nom() const       { return m_nom; }

void Client::setNumClient(const QString &numClient) { m_numClient = numClient; }
void Client::setNom(const QString &nom)             { m_nom = nom; }
