#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>
#include <QString>

class QLineEdit;
class QComboBox;
class QPushButton;
class QTableWidget;

class ClientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);

private:
    // Données d'un client
    struct Client {
        int     id  = -1;
        QString nom;
        QString tel;
    };

    // --- Interface ---
    void creerUI();
    void chargerStyle();
    QWidget *creerCarteAjout();
    QWidget *creerCarteModification();
    QWidget *creerCarteSuppression();
    QWidget *creerCarteListe();

    // --- Base de données ---
    void chargerClients();                        // (re)remplit le tableau
    bool rechercherClient(const QString &critere, const QString &texte,
                          Client &resultat, int &total);

    // --- Actions ---
    void ajouterClient();
    void rechercherPourModification();
    void modifierClient();
    void rechercherPourSuppression();
    void supprimerClient();

    void reinitialiserAjout();
    void reinitialiserModification();
    void reinitialiserSuppression();

    // --- Utilitaires ---
    static QString formaterId(int id);             // 1 -> "001"
    static QString formaterTel(const QString &t);  // 0341234567 -> "034 12 345 67"
    static QString nettoyerTel(const QString &t);  // enlève espaces, points, tirets
    static bool    telValide(const QString &t);

    // 1. Ajouter
    QLineEdit *m_ajoutNom = nullptr;
    QLineEdit *m_ajoutTel = nullptr;

    // 2. Modifier
    QComboBox *m_modCritere = nullptr;
    QLineEdit *m_modRecherche = nullptr;
    QLineEdit *m_modNum = nullptr;
    QLineEdit *m_modNom = nullptr;
    QLineEdit *m_modTel = nullptr;
    int        m_modId = -1;

    // 3. Supprimer
    QComboBox *m_supCritere = nullptr;
    QLineEdit *m_supRecherche = nullptr;
    QLineEdit *m_supNum = nullptr;
    QLineEdit *m_supNom = nullptr;
    QLineEdit *m_supTel = nullptr;
    int        m_supId = -1;

    // 4. Liste
    QTableWidget *m_table = nullptr;
};

#endif // CLIENTWINDOW_H