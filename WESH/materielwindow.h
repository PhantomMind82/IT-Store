#pragma once
#include <QDialog>

class QLineEdit;
class QDoubleSpinBox;
class QSpinBox;
class QTableWidget;
class QStackedWidget;

class MaterielWindow : public QDialog
{
    Q_OBJECT
public:
    explicit MaterielWindow(QWidget *parent = nullptr);

private slots:
    void ajouter();
    void reinitAjout();
    void charger();
    void exporterPdf();

private:
    void editerLigne(int ligne);
    void supprimerLigne(const QString &num);

    // Ajout
    QLineEdit *editNom;
    QDoubleSpinBox *spinPu;
    QSpinBox *spinStock;

    // Situation
    QLineEdit *editRecherche;
    QTableWidget *table;
    QStackedWidget *pile;
};