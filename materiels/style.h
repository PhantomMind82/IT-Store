#pragma once
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

inline QString styleFenetre(const QString &couleur)
{
    return QString(
               "QDialog { background: #f3f6fb; }"
               "QLabel { color: #1b2540; font-size: 13px; }"
               "QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox, QDateEdit {"
               " padding: 6px; border: 1px solid #c5cde0; border-radius: 6px;"
               " background: white; color: #1b2540; }"
               "QComboBox QAbstractItemView { background: white; color: #1b2540;"
               " selection-background-color: %1; selection-color: white; border: 1px solid #c5cde0; }"
               "QTableView { background: aliceblue; color: #1b2540; "
               " alternate-background-color: #eef2fa; gridline-color: black-bleu;"
               " border: 2px solid #c5cde0; border-radius: 6px;"
               " selection-background-color: %1; selection-color: white; }"
               "QHeaderView::section { background: %1; color: white; padding: 8px;"
               " border: none; font-weight: bold; }"
               "QPushButton { background: %1; color: white; border: 2px solid transparent;"
               " border-radius: 6px; padding: 9px 18px; font-weight: bold; }"
               "QPushButton:hover { border: 2px solid rgba(0,0,0,70); }"
               "QPushButton#btnSupprimer { background: #e04545; }"
               "QPushButton#btnGris { background: #8a94a8; }"
               ).arg(couleur);
}



inline QWidget *creerEnteteClair(const QString &icone, const QString &titre,
                                 const QString &sousTitre, const QString &couleur)
{
    QWidget *w = new QWidget;
    w->setObjectName("enteteClair");
    w->setStyleSheet("#enteteClair { background: transparent; }");

    QLabel *ico = new QLabel(icone);
    ico->setStyleSheet(QString("font-size: 38px; color: %1; background: transparent;").arg(couleur));

    QLabel *t = new QLabel(titre);
    t->setStyleSheet("color: #0f2350; font-size: 35px; font-weight: bold; background: transparent;");

    QLabel *s = new QLabel(sousTitre);
    s->setStyleSheet("color: #5a6785; font-size: 13px; background: transparent;");

    QVBoxLayout *textes = new QVBoxLayout;
    textes->setSpacing(0);
    textes->addWidget(t);
    textes->addWidget(s);

    QHBoxLayout *l = new QHBoxLayout(w);
    l->setContentsMargins(4, 0, 4, 0);
    l->setSpacing(14);
    l->addWidget(ico);
    l->addLayout(textes);
    l->addStretch();
    return w;
}
