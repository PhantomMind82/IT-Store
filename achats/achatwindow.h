#pragma once

#include <QDialog>

/**
 * Fenêtre ACHATS (ouverte depuis l'accueil avec exec()).
 * TODO : à développer par le responsable du module.
 */
class AchatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AchatWindow(QWidget *parent = nullptr);
};
