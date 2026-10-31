#pragma once

#include <QDialog>
#include <QString>

class QFrame;
class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
class QDateEdit;
class QTableWidget;

class VenteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VenteWindow(QWidget *parent = nullptr);

private:
    void rechercherClient();
    void chargerVentes(const QString &numClient);
    void mettreAJourRecapitulatif(const QString &nomClient);
    void viderAffichage();
    QString conditionDateSql() const;

    QFrame *header;
    QLabel *titreLabel;
    QLabel *descriptionLabel;

    QPushButton *btnRechercheNumero;
    QPushButton *btnRechercheNom;
    QLineEdit *rechercheClient;
    QPushButton *btnRechercher;

    QLabel *clientNom;
    QLabel *clientNumero;

    QComboBox *periodeCombo;
    QDateEdit *dateDebut;
    QDateEdit *dateFin;

    QTableWidget *tableVentes;

    QLabel *recapClient;
    QLabel *recapArticles;
    QLabel *recapMontant;

    QLabel *totalGeneral;
    QPushButton *btnActualiser;
    QPushButton *btnImprimer;

    QString numClientActuel;
    QString nomClientActuel;
};