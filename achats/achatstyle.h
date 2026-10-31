#pragma once

#include <QString>

/**
 * @file achatstyle.h
 * @brief Les feuilles de style (QSS) du module achats, d'après la maquette orange.
 *
 * Le QSS ressemble au CSS des pages web. Chaque règle vise un widget par son
 * nom d'objet (objectName), par exemple  QPushButton#btnNouveau { ... }
 * vise le bouton dont le nom, dans le fichier .ui, est « btnNouveau ».
 *
 * Palette de la maquette :
 *   fond de page  #FAF3EC      texte        #2B1608     texte discret #7A5C45
 *   orange        #EA7210 -> #D95F08         bandeau      #D4590A -> #B84A05
 *   marron        #5B3A22 -> #3F2614         or           #A8620B -> #8C4F07
 *   rouge         #D64545 -> #B62F2F         bordures     #E6CFB8
 */
namespace AchatStyle {

// Règles communes à toutes les fenêtres : police, couleur du texte, étiquettes transparentes.
inline QString commun()
{
    return QStringLiteral(R"qss(
QWidget { font-family: "Segoe UI", "Ubuntu", "Noto Sans", "DejaVu Sans", sans-serif; font-size: 15px; color: #2B1608; }
QLabel { background: transparent; }
QPushButton { outline: none; }
)qss");
}

// Un bouton gris clair (Annuler, Fermer...). %1 = nom du bouton.
inline QString boutonGris(const QString &nom, int hauteur, int police)
{
    return QStringLiteral(
               "QPushButton#%1 { min-height: %2px; padding: 0 20px; border: 0; border-radius: 12px;"
               " font-size: %3px; font-weight: 700; background: #F1E3D3; color: #2B1608; }"
               "QPushButton#%1:hover { background: #E8D5C0; }")
        .arg(nom)
        .arg(hauteur)
        .arg(police);
}

// Un bouton avec dégradé (couleur c1 -> c2, et h1 -> h2 quand la souris est dessus).
inline QString boutonDegrade(const QString &nom, const QString &c1, const QString &c2,
                             const QString &h1, const QString &h2, int hauteur, int police)
{
    return QStringLiteral(
               "QPushButton#%1 { min-height: %2px; padding: 0 20px; border: 0; border-radius: 12px;"
               " font-size: %3px; font-weight: 700; color: #FFFFFF;"
               " background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 %4, stop:1 %5); }"
               "QPushButton#%1:hover {"
               " background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 %6, stop:1 %7); }")
        .arg(nom)
        .arg(hauteur)
        .arg(police)
        .arg(c1, c2, h1, h2);
}

// ---------------------------------------------------------------------------
// Fenêtre principale des achats (achatwindow.ui)
// ---------------------------------------------------------------------------
inline QString fenetreAchats()
{
    return commun() + QStringLiteral(R"qss(
QDialog#AchatWindow { background: #FAF3EC; }

/* Bandeau orange en haut : logo, nom, slogan */
QFrame#entete { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #D4590A, stop:1 #B84A05); }
QLabel#titreMarque { color: #FFFFFF; font-family: Georgia, "Times New Roman", serif; font-size: 38px; font-weight: 700; }
QLabel#slogan { color: #FFFFFF; }

/* Ligne du haut : retour, titre, recherche */
QPushButton#btnAccueil { min-height: 44px; padding: 0 18px; border: 0; border-radius: 12px; background: #FFFFFF; color: #2B1608; font-weight: 700; }
QPushButton#btnAccueil:hover { background: #FFF1E2; }
QLabel#titrePage { font-size: 32px; font-weight: 700; }
QLabel#sousTitre { color: #7A5C45; }
QFrame#boiteRecherche { min-height: 48px; background: #FFFFFF; border: 1px solid #E6CFB8; border-radius: 12px; }
QLineEdit#champRecherche { min-width: 260px; border: 0; background: transparent; color: #2B1608; selection-background-color: #FFEBD6; selection-color: #2B1608; }

/* Les 4 gros boutons d'action */
QPushButton#btnNouveau, QPushButton#btnModifier, QPushButton#btnFacture, QPushButton#btnSupprimer {
    min-height: 88px; padding: 0 22px; border: 0; border-radius: 14px;
    color: #FFFFFF; font-size: 22px; font-weight: 700; text-align: left; }
QPushButton#btnNouveau   { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #EA7210, stop:1 #D95F08); }
QPushButton#btnNouveau:hover   { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #F5801E, stop:1 #E56A10); }
QPushButton#btnModifier  { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #5B3A22, stop:1 #3F2614); }
QPushButton#btnModifier:hover  { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #6B462A, stop:1 #4D301B); }
QPushButton#btnFacture   { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #A8620B, stop:1 #8C4F07); }
QPushButton#btnFacture:hover   { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #B87216, stop:1 #9C5A0D); }
QPushButton#btnSupprimer { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #D64545, stop:1 #B62F2F); }
QPushButton#btnSupprimer:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #E25757, stop:1 #C73B3B); }

/* La carte blanche qui contient le tableau */
QFrame#carte { background: #FFFFFF; border-radius: 16px; }
QTableWidget#tableAchats { background: transparent; border: 0; outline: 0; selection-background-color: #FFEBD6; selection-color: #2B1608; }
QTableWidget#tableAchats::item { padding: 0 20px; border-top: 1px solid #F0E1D2; }
QTableWidget#tableAchats::item:hover { background: #FFF8F1; }
QTableWidget#tableAchats::item:selected { background: #FFEBD6; color: #2B1608; font-weight: 700; }
QTableWidget#tableAchats::item:selected:!active { background: #FFEBD6; color: #2B1608; }
QTableWidget#tableAchats QHeaderView { background: transparent; }
QTableWidget#tableAchats QHeaderView::section { background: #FFF8F1; color: #7A5C45; border: 0; padding: 0 20px; font-size: 12px; font-weight: 700; }
QTableWidget#tableAchats QHeaderView::section:first { border-top-left-radius: 16px; }
QTableWidget#tableAchats QHeaderView::section:last { border-top-right-radius: 16px; }

/* Ligne du bas : aide et total */
QLabel#labelAide, QLabel#labelTotalTexte { color: #7A5C45; }
QLabel#labelTotalValeur { font-size: 22px; font-weight: 700; color: #2B1608; }
)qss");
}

// ---------------------------------------------------------------------------
// Fenêtre « Nouvel achat / Modifier l'achat » (nouveauachatdialog.ui)
// ---------------------------------------------------------------------------
inline QString saisieAchat()
{
    return commun()
        + QStringLiteral(R"qss(
QDialog#NouveauAchatDialog { background: #FFFFFF; }
QFrame#headerWidget { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #EA7210, stop:1 #D95F08); }
QLabel#titleLabel { color: #FFFFFF; font-size: 28px; font-weight: 700; }

QLabel#labelClient, QLabel#labelMateriel, QLabel#labelQuantite, QLabel#labelDate { font-size: 13px; font-weight: 700; }
QLabel#labelStock { font-size: 13px; font-weight: 600; color: #7A5C45; }

QComboBox, QSpinBox, QDateEdit { min-height: 48px; padding: 0 14px; border: 1px solid #E6CFB8; border-radius: 10px; background: #FFF8F1; color: #2B1608; font-weight: 500; }
QComboBox:focus, QSpinBox:focus, QDateEdit:focus { border: 1px solid #EA7210; }
QComboBox QAbstractItemView { background: #FFFFFF; border: 1px solid #E6CFB8; selection-background-color: #FFEBD6; selection-color: #2B1608; outline: 0; }

QFrame#widgetTotal { background: #2B1608; border-radius: 12px; }
QLabel#labelMontantTitre { color: #E9D3BC; }
QLabel#labelStockInfo { color: #E9D3BC; font-size: 13px; }
QLabel#labelMontantValeur { color: #FFB066; font-size: 26px; font-weight: 700; }
QLabel#labelErreur { color: #B62F2F; font-weight: 600; }
)qss")
        + boutonGris(QStringLiteral("btnAnnuler"), 52, 17)
        + boutonDegrade(QStringLiteral("btnEnregistrer"), QStringLiteral("#EA7210"), QStringLiteral("#D95F08"),
                        QStringLiteral("#F5801E"), QStringLiteral("#E56A10"), 52, 17);
}

// ---------------------------------------------------------------------------
// Fenêtre « Supprimer cet achat ? » (supprimerachatdialog.ui)
// ---------------------------------------------------------------------------
inline QString suppressionAchat()
{
    return commun()
        + QStringLiteral(R"qss(
QDialog#SupprimerAchatDialog { background: #FFFFFF; }
QLabel#labelSupprimerTitre { font-size: 22px; font-weight: 700; }
QLabel#labelSupprimerDesc { color: #7A5C45; }
)qss")
        + boutonGris(QStringLiteral("btnAnnulerSup"), 48, 16)
        + QStringLiteral(
              "QPushButton#btnConfirmerSup { min-height: 48px; padding: 0 20px; border: 0; border-radius: 12px;"
              " font-size: 16px; font-weight: 700; background: #C23030; color: #FFFFFF; }"
              "QPushButton#btnConfirmerSup:hover { background: #A82626; }");
}

// ---------------------------------------------------------------------------
// Fenêtre « Facture » (facturedialog.ui)
// ---------------------------------------------------------------------------
inline QString facture()
{
    return commun()
        + QStringLiteral(R"qss(
QDialog#FactureDialog { background: #FAF3EC; }
QFrame#feuille { background: #FFFFFF; border-radius: 16px; }
QLabel#labelFactureTitre { font-size: 28px; font-weight: 700; }
QLabel#labelStore { font-family: Georgia, "Times New Roman", serif; font-size: 22px; font-weight: 700; color: #B84A05; }
QLabel#labelNumClient, QLabel#labelDate, QLabel#labelNom, QLabel#labelTelephone { color: #7A5C45; }

QTableWidget#tableFacture { background: transparent; border: 0; outline: 0; }
QTableWidget#tableFacture::item { padding: 0; border-top: 1px solid #F0E1D2; }
QTableWidget#tableFacture QHeaderView { background: transparent; }
QTableWidget#tableFacture QHeaderView::section { background: transparent; border: 0; color: #7A5C45; font-size: 12px; font-weight: 700; padding: 0; }

QFrame#widgetTotalFacture { background: #2B1608; border-radius: 12px; }
QLabel#labelTotalText { color: #E9D3BC; }
QLabel#labelTotalVal { color: #FFB066; font-size: 24px; font-weight: 700; }
QLabel#labelArretee { color: #7A5C45; }
)qss")
        + boutonGris(QStringLiteral("btnFermerFacture"), 52, 17)
        + boutonDegrade(QStringLiteral("btnGenererPdf"), QStringLiteral("#EA7210"), QStringLiteral("#D95F08"),
                        QStringLiteral("#F5801E"), QStringLiteral("#E56A10"), 52, 17);
}

} // namespace AchatStyle
