#pragma once

#include <QColor>
#include <QPixmap>
#include <QString>

/**
 * @brief Petits outils d'affichage communs à tout le module achats :
 *        formatage des montants et icônes dessinées en code.
 */
namespace AchatsUi {

/** Les icônes de la maquette (traits arrondis, dessinées avec QPainter). */
enum class Icone { Plus, Crayon, Document, Corbeille, Panier, Loupe };

/** 950000 -> "950 000" (espace insécable entre les milliers). */
QString formatNombre(double valeur);

/** 950000 -> "950 000 Ar". */
QString formatMontant(double valeur);

/** Une icône seule (trait de couleur `trait`), de `taille` x `taille` pixels. */
QPixmap icone(Icone type, int taille, const QColor &trait);

/**
 * Une icône dans un rond coloré (dégradé de fond1 vers fond2).
 * margeDroite ajoute de la place transparente à droite (sert à écarter
 * l'icône du texte dans un bouton).
 */
QPixmap pastille(Icone type, int diametre, const QColor &fond1, const QColor &fond2,
                 const QColor &trait, int margeDroite = 0);

} // namespace AchatsUi
