#pragma once

#include <QDialog>

#include "commun/modeles.h"   // Achat

namespace Ui {
class SupprimerAchatDialog;
}

/**
 * @brief Boîte de confirmation « Supprimer cet achat ? » (maquette : écran de suppression).
 *
 * Elle affiche un résumé de l'achat et deux boutons. exec() renvoie
 * QDialog::Accepted si l'utilisateur confirme, QDialog::Rejected sinon.
 * C'est AchatWindow qui effectue ensuite la suppression.
 */
class SupprimerAchatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupprimerAchatDialog(const Achat &achat, QWidget *parent = nullptr);
    ~SupprimerAchatDialog() override;

private:
    Ui::SupprimerAchatDialog *ui;
};
