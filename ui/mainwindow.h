<<<<<<< HEAD
#pragma once
#include <QMainWindow>

class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *creerCarte(const QString &icone, const QString &titre,
                            const QString &couleur1, const QString &couleur2);

    Ui::MainWindow *ui;
=======
#pragma once
#include <QMainWindow>

class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *creerCarte(const QString &icone, const QString &titre,
                            const QString &couleur1, const QString &couleur2);

    Ui::MainWindow *ui;
>>>>>>> 8c2295e (Crafting)
};