#pragma once

#include <QDialog>

#include "commun/modeles.h"   // Achat, Client, Materiel, ListeClients, ListeMateriels

namespace Ui {
class NouveauAchatDialog;
}

/**
 * @brief Boîte de dialogue « Nouvel achat » et « Modifier l'achat » (maquette : écran de saisie).
 *
 * Elle sert aux deux cas :
 *  - création : on l'ouvre, on remplit, on clique sur Enregistrer ;
 *  - modification : on appelle d'abord setAchat(), ce qui remplit les champs
 *    avec l'achat existant et change le titre en « Modifier l'achat ».
 *
 * Ordre d'utilisation :
 *   NouveauAchatDialog d(this);
 *   d.setClients(...);  d.setMateriels(...);   // les listes des menus déroulants
 *   d.setAchat(...);                           // seulement pour une modification
 *   if (d.exec() == QDialog::Accepted) { Achat a = d.getAchat(); ... }
 */
class NouveauAchatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NouveauAchatDialog(QWidget *parent = nullptr);
    ~NouveauAchatDialog() override;

    void setClients(const ListeClients &clients);
    void setMateriels(const ListeMateriels &materiels);
    void setAchat(const Achat &achat);     // passe en mode « modification »

    Achat getAchat() const;                // l'achat tel que saisi (à appeler après Accepted)

private slots:
    void mettreAJourResume();              // recalcule stock, montant et efface l'erreur
    void onEnregistrer();                  // vérifie la saisie puis ferme la fenêtre

private:
    QString messageErreur() const;         // texte de l'erreur, ou "" si tout est correct
    const Client *clientChoisi() const;
    const Materiel *materielChoisi() const;
    int quantiteDejaPrise() const;         // en modification : quantité de l'achat d'origine pour ce matériel

    void remplirClients();
    void remplirMateriels();
    void appliquerPreselection();          // en modification : sélectionne le client et le matériel de l'achat

    Ui::NouveauAchatDialog *ui;
    bool m_modeEdition = false;
    Achat m_achatInitial;                  // l'achat avant modification (vide pour une création)
    ListeClients m_clients;
    ListeMateriels m_materiels;
};
