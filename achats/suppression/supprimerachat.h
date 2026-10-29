#pragma once

#include <QDialog>

namespace Ui {
class SupprimerAchat;
}

class SupprimerAchat : public QDialog
{
    Q_OBJECT

public:
    explicit SupprimerAchat(int idAchat, QWidget *parent = nullptr);
    ~SupprimerAchat() override;

private slots:
    void onConfirmer();

private:
    Ui::SupprimerAchat *ui;
    int m_idAchat;
    int m_quantite = 0;
    int m_idMateriel = 0;
    QString m_numeroCommande;
};
