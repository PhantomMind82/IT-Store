#include "logowidget.h"

#include <QPainter>
#include <QPainterPath>

LogoWidget::LogoWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(48, 48);
}

QSize LogoWidget::sizeHint() const
{
    return QSize(48, 48);
}

void LogoWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    // On dessine dans un repère de 48 x 48 et on l'adapte à la taille réelle du widget.
    const qreal echelle = qMin(width(), height()) / 48.0;
    p.translate((width() - 48 * echelle) / 2, (height() - 48 * echelle) / 2);
    p.scale(echelle, echelle);

    // Étiquette jaune : M6 26 L26 6 H40 V20 L20 40 Z
    QPainterPath etiquette;
    etiquette.moveTo(6, 26);
    etiquette.lineTo(26, 6);
    etiquette.lineTo(40, 6);
    etiquette.lineTo(40, 20);
    etiquette.lineTo(20, 40);
    etiquette.closeSubpath();

    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#FFD23F"));
    p.drawPath(etiquette);

    // Point rouge de l'étiquette : centre (32, 14), rayon 3,2
    p.setBrush(QColor("#DC3C3C"));
    p.drawEllipse(QPointF(32, 14), 3.2, 3.2);
}
