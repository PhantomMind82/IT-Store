<<<<<<< HEAD
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
=======
#include "ui/mainwindow.h"
#include "commun/database.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("IT Store");
    a.setOrganizationName("IT Store");
    a.setStyleSheet(QStringLiteral(
        "QMessageBox { background: #FFFFFF; }"
        "QMessageBox QLabel { color: #2B1608; min-width: 300px; font-size: 14px; }"
        "QMessageBox QPushButton { min-width: 92px; min-height: 38px; padding: 0 14px;"
        " border: 0; border-radius: 7px; background: #E96F10; color: #FFFFFF; font-weight: 700; }"
        "QMessageBox QPushButton:hover { background: #D85E08; }"));

    if (!Database::ouvrir()) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'ouvrir la base de données.");
        return 1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
>>>>>>> 8c2295e (Crafting)
