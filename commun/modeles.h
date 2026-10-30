#pragma once

/**
 * Point d'entrée unique des classes de données.
 * Les autres modules font simplement : #include "commun/modeles.h"
 */

#include <QList>

#include "clients/client.h"
#include "materiels/materiel.h"
#include "achats/achat.h"
#include "ventes/ventes.h"

using ListeClients   = QList<Client>;
using ListeMateriels = QList<Materiel>;
using ListeAchats    = QList<Achat>;
using ListeVentes    = QList<Vente>;
