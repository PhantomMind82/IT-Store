#include "achatsui.h"

#include <QLinearGradient>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

#include <initializer_list>

namespace {

// On dessine à 2x puis on indique à Qt que c'est une image « haute densité » :
// l'icône reste nette sur les écrans HiDPI.
constexpr qreal RATIO = 2.0;

// Construit un tracé à partir d'une liste de points reliés par des lignes droites.
QPainterPath polyligne(std::initializer_list<QPointF> points, bool fermer = false)
{
    QPainterPath chemin;
    bool premier = true;
    for (const QPointF &pt : points) {
        if (premier) {
            chemin.moveTo(pt);
            premier = false;
        } else {
            chemin.lineTo(pt);
        }
    }
    if (fermer)
        chemin.closeSubpath();
    return chemin;
}

// Trace une icône dans le rectangle `zone`. Les coordonnées ci-dessous sont celles
// de la maquette : un repère de 24 x 24, trait de 1,9, bouts et angles arrondis.
void tracer(QPainter &p, AchatsUi::Icone type, const QRectF &zone, const QColor &trait)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);
    p.translate(zone.topLeft());
    p.scale(zone.width() / 24.0, zone.height() / 24.0);
    p.setPen(QPen(trait, 1.9, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.setBrush(Qt::NoBrush);

    switch (type) {
    case AchatsUi::Icone::Plus:
        p.drawPath(polyligne({{12, 5}, {12, 19}}));
        p.drawPath(polyligne({{5, 12}, {19, 12}}));
        break;
    case AchatsUi::Icone::Crayon:
        p.drawPath(polyligne({{4, 20}, {8, 20}, {19, 9}, {15, 5}, {4, 16}}, true));
        break;
    case AchatsUi::Icone::Document:
        p.drawPath(polyligne({{6, 3}, {14, 3}, {18, 7}, {18, 21}, {6, 21}}, true));
        p.drawPath(polyligne({{9, 13}, {15, 13}}));
        p.drawPath(polyligne({{9, 17}, {15, 17}}));
        break;
    case AchatsUi::Icone::Corbeille:
        p.drawPath(polyligne({{4, 7}, {20, 7}}));
        p.drawPath(polyligne({{9, 7}, {9, 4}, {15, 4}, {15, 7}}));
        p.drawPath(polyligne({{6, 7}, {7, 20}, {17, 20}, {18, 7}}));
        break;
    case AchatsUi::Icone::Panier:
        p.drawEllipse(QPointF(9, 20), 1.5, 1.5);
        p.drawEllipse(QPointF(18, 20), 1.5, 1.5);
        p.drawPath(polyligne({{2, 3}, {5, 3}, {7.5, 15}, {18.5, 15}, {21, 7}, {6, 7}}));
        break;
    case AchatsUi::Icone::Loupe:
        p.drawEllipse(QPointF(11, 11), 7, 7);
        p.drawPath(polyligne({{20, 20}, {16.5, 16.5}}));
        break;
    }
    p.restore();
}

QPixmap pixmapVide(int largeur, int hauteur)
{
    QPixmap pix(QSize(largeur, hauteur) * RATIO);
    pix.setDevicePixelRatio(RATIO);
    pix.fill(Qt::transparent);
    return pix;
}

} // namespace

QString AchatsUi::formatNombre(double valeur)
{
    const qint64 entier = qRound64(valeur);
    const QString chiffres = QString::number(qAbs(entier));

    QString resultat;
    for (int i = 0; i < chiffres.size(); ++i) {
        // Une séparation tous les 3 chiffres en partant de la droite.
        if (i > 0 && (chiffres.size() - i) % 3 == 0)
            resultat += QChar(0x00A0);
        resultat += chiffres.at(i);
    }
    return entier < 0 ? QChar('-') + resultat : resultat;
}

QString AchatsUi::formatMontant(double valeur)
{
    return formatNombre(valeur) + QChar(0x00A0) + QStringLiteral("Ar");
}

QPixmap AchatsUi::icone(Icone type, int taille, const QColor &trait)
{
    QPixmap pix = pixmapVide(taille, taille);
    QPainter p(&pix);
    tracer(p, type, QRectF(0, 0, taille, taille), trait);
    return pix;
}

QPixmap AchatsUi::pastille(Icone type, int diametre, const QColor &fond1, const QColor &fond2,
                           const QColor &trait, int margeDroite)
{
    QPixmap pix = pixmapVide(diametre + margeDroite, diametre);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient degrade(0, 0, diametre, diametre);
    degrade.setColorAt(0, fond1);
    degrade.setColorAt(1, fond2);
    p.setPen(Qt::NoPen);
    p.setBrush(degrade);
    p.drawEllipse(QRectF(0, 0, diametre, diametre));

    // L'icône occupe la moitié du rond, centrée.
    const qreal cote = diametre * 0.5;
    tracer(p, type, QRectF((diametre - cote) / 2, (diametre - cote) / 2, cote, cote), trait);
    return pix;
}
