#pragma once

#include <QDialog>
#include <QVector>

namespace Ui {
class NouveauAchat;
}

class NouveauAchat : public QDialog
{
    Q_OBJECT

public:
    explicit NouveauAchat(int idAchat = 0, QWidget *parent = nullptr);
    ~NouveauAchat() override;

private slots:
    void mettreAJourResume();
    void ajouterArticle();
    void retirerArticle();
    void onEnregistrer();

private:
    struct ArticleCommande {
        int idMateriel;
        QString designation;
        double prixUnitaire;
        int quantite;
    };

    int quantiteInitialePourMateriel() const;
    int quantiteChoisie() const;
    void definirQuantite(int quantite);
    QString obtenirMessageErreur() const;
    void afficherArticlesCommande();

    Ui::NouveauAchat *ui;
    int m_idAchat;
    QString m_idMaterielInitial;
    int m_quantiteInitiale = 0;
    bool m_commandeAvecPlusieursArticles = false;
    double m_prixUnitaireInitial = 0;
    double m_prixUnitaire = 0;
    int m_stockActuel = 0;
    QVector<ArticleCommande> m_articlesCommande;
};
