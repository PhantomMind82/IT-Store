#pragma once

/**
 * Point d'entrée unique des classes de données.
 * Les autres modules font simplement : #include "commun/modeles.h"
 */

#include <QList>

#include "clients/client.h"
#include "materiels/materiel.h"
#include "achats/achat.h"


using ListeClients   = QList<Client>;
using ListeMateriels = QList<Materiel>;
using ListeAchats    = QList<Achat>;

