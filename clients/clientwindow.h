#pragma once

#include <QDialog>

/**
 * Fenêtre CLIENTS (ouverte depuis l'accueil avec exec()).
 * TODO : à développer par le responsable du module.
 */
class ClientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
};
