#include "ui/mainwindow.h"
#include "commun/database.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!Database::ouvrir()) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'ouvrir la base de données.");
        return 1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
