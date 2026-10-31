#pragma once

#include <QWidget>

/**
 * @brief Le logo « IT Store » (étiquette jaune avec un point rouge), dessiné en code.
 *
 * Pas besoin de fichier image : paintEvent() trace directement les formes
 * avec QPainter. Le dessin est celui de la maquette (viewBox 48 x 48).
 * Il est utilisé dans le bandeau orange de la fenêtre des achats
 * (widget « promu » dans achatwindow.ui).
 */
class LogoWidget : public QWidget
{
public:
    explicit LogoWidget(QWidget *parent = nullptr);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
