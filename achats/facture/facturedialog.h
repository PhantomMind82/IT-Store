#pragma once

#include <QDialog>

#include "commun/modeles.h"   // Achat, ListeAchats

namespace Ui {
class FactureDialog;
}

/**
 * @brief Fenêtre « Facture d'un client » (maquette : écran de facture).
 *
 * On lui donne la liste des achats d'UN client ; elle affiche la facture
 * (en-tête, tableau, total, montant en lettres) et peut l'enregistrer en PDF.
 *
 * Le PDF est produit avec QPdfWriter (module Qt Gui, déjà présent) :
 * on fabrique une page HTML, QTextDocument la met en page, puis
 * QTextDocument::print() l'écrit dans le fichier PDF.
 */
class FactureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FactureDialog(const ListeAchats &achatsDuClient, QWidget *parent = nullptr);
    ~FactureDialog() override;

private slots:
    void genererPdf();

private:
    QString numeroFacture() const;     // « 0001 » : numéro du client sur 4 chiffres
    QDate dateFacture() const;         // date du dernier achat de la liste
    double totalGeneral() const;       // somme des montants
    QString htmlPourPdf() const;       // la page HTML qui sera transformée en PDF

    Ui::FactureDialog *ui;
    ListeAchats m_achats;
};
