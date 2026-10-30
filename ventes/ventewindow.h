#pragma once

#include <QDialog>

// TODO : Module à réaliser correspondant au VENTE

class VenteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VenteWindow(QWidget *parent = nullptr);

private:

    // =========================
    // Fonctions du module VENTE
    // =========================

    // Recherche un client à partir du numéro saisi
    void rechercherClientParNumero();

    // Charge les ventes d'un client et remplit le tableau
    void chargerVentes(const QString &numClient);

    // Met à jour le récapitulatif après le chargement des ventes
    void mettreAJourRecapitulatif(const QString &nomClient);


    // =========================
    // En-tête
    // =========================
    class QFrame *header;
    class QLabel *titreLabel;
    class QLabel *descriptionLabel;


    // =========================
    // Recherche client
    // =========================
    class QPushButton *btnRechercheNumero;
    class QPushButton *btnRechercheNom;
    class QLineEdit *rechercheClient;
    class QPushButton *btnRechercher;


    // =========================
    // Informations client
    // =========================
    class QLabel *clientNom;
    class QLabel *clientNumero;


    // =========================
    // Filtre période
    // =========================
    class QComboBox *periodeCombo;
    class QDateEdit *dateDebut;
    class QDateEdit *dateFin;


    // =========================
    // Tableau des ventes
    // =========================
    class QTableWidget *tableVentes;


    // =========================
    // Récapitulatif
    // =========================
    class QLabel *recapClient;
    class QLabel *recapArticles;
    class QLabel *recapMontant;


    // =========================
    // Bas de page
    // =========================
    class QLabel *nombreArticles;
    class QLabel *totalGeneral;
    class QPushButton *btnActualiser;
    class QPushButton *btnImprimer;
};