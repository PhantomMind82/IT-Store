#include "ventewindow.h"

VenteWindow::VenteWindow(QWidget *parent)
    : QDialog(parent)
{
    // C'est ici que vous construirez l'interface de votre fenêtre de vente plus tard
    setWindowTitle("Gestion des Ventes");
    resize(400, 300);
}
