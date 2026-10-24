#pragma once

#include <QDialog>

/**
 * Fenêtre VENTE (ouverte depuis l'accueil avec exec()).
 * TODO : à développer par le responsable du module.
 */
class VenteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VenteWindow(QWidget *parent = nullptr);
};
