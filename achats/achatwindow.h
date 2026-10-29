#pragma once

#include <QDialog>

<<<<<<< HEAD
#include "commun/modeles.h"   // Achat, Client, Materiel et les listes ListeAchats, ListeClients, ListeMateriels

=======
>>>>>>> 8c2295e (Crafting)
namespace Ui {
class AchatWindow;
}

<<<<<<< HEAD
/**
 * @brief Fenêtre principale de la section « Achats » (maquette : écran « Achats »).
 *
 * Elle affiche la liste des achats dans un tableau et propose :
 *  - Nouvel achat  -> ouvre NouveauAchatDialog
 *  - Modifier      -> ouvre NouveauAchatDialog avec l'achat sélectionné
 *  - Facture PDF   -> ouvre FactureDialog pour le client de l'achat sélectionné
 *  - Supprimer     -> ouvre SupprimerAchatDialog
 *  - Recherche     -> filtre le tableau par nom ou numéro de téléphone du client
 *
 * Pour l'instant les listes sont VIDES : le tableau reste vide.
 * Quand la base de données sera branchée, il suffira de remplir
 * m_achats / m_clients / m_materiels dans chargerDonnees().
 */
=======
>>>>>>> 8c2295e (Crafting)
class AchatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AchatWindow(QWidget *parent = nullptr);
    ~AchatWindow() override;

<<<<<<< HEAD
    // Permettent à un autre module (ou à la base de données) de fournir les données.
    void setAchats(const ListeAchats &achats);
    void setClients(const ListeClients &clients);
    void setMateriels(const ListeMateriels &materiels);

private slots:
=======
private slots:
    void chargerTable();
>>>>>>> 8c2295e (Crafting)
    void onNouveau();
    void onModifier();
    void onFacture();
    void onSupprimer();
<<<<<<< HEAD
    void rafraichir();          // redessine le tableau (tient compte de la recherche)

private:
    void configurerTable();     // largeurs de colonnes, hauteur des lignes...
    void ajouterIcones();       // icônes des boutons, du titre et de la recherche
    void chargerDonnees();      // point d'entrée pour la future lecture de la base

    int idSelectionne() const;              // numéro de l'achat sélectionné, -1 si aucun
    int indexParId(int idAchat) const;      // position de l'achat dans m_achats, -1 si absent
    int prochainId() const;                 // plus grand numéro existant + 1
    static bool correspond(const Achat &achat, const QString &recherche);

    Ui::AchatWindow *ui;
    ListeAchats m_achats;
    ListeClients m_clients;
    ListeMateriels m_materiels;
=======

private:
    int idSelectionne() const;
    int idChoisi(const QString &titre);

    Ui::AchatWindow *ui;
>>>>>>> 8c2295e (Crafting)
};
