#pragma once

#include <QDialog>

/**
 * Fenêtre MATÉRIELS (ouverte depuis l'accueil avec exec()).
 * TODO : à développer par le responsable du module.
 */
class MaterielWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MaterielWindow(QWidget *parent = nullptr);
};
