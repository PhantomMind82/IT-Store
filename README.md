# IT-Store — Vente de matériels informatiques

Application Qt 6 (C++ / CMake) de gestion des clients, matériels et achats.

## Compiler

Prérequis : Qt 6.5+ (avec le module **Sql**), CMake ≥ 3.19, MinGW ou autre compilateur C++17.

Dans **Qt Creator** : *Fichier → Ouvrir un fichier ou un projet* → choisir `CMakeLists.txt`,
puis **Ctrl+R**.

## Structure

| Dossier      | Contenu                                                         |
|--------------|-----------------------------------------------------------------|
| `ui/`        | Page d'accueil (`MainWindow`) : 3 cartes Matériel / Client / Achat |
| `clients/`   | `ClientWindow` (fenêtre) + classe `Client`                      |
| `materiels/` | `MaterielWindow` (fenêtre) + classe `Materiel`                  |
| `achats/`    | `AchatWindow` (fenêtre) + classe `Achat`                        |
| `commun/`    | `Database` (SQLite), `Style` (couleurs), `modeles.h`            |

## Où coder ?

Chaque carte de l'accueil ouvre déjà la fenêtre de son module (`exec()`).
Chaque fenêtre affiche pour l'instant « EN COURS DE DÉVELOPPEMENT ».

Pour développer votre module : ouvrez **uniquement votre dossier** et remplacez le contenu du
**constructeur** de votre fenêtre (`clientwindow.cpp`, `materielwindow.cpp` ou `achatwindow.cpp`).
Vous n'avez pas besoin de toucher à `ui/mainwindow.cpp`.

La base de données est ouverte au démarrage (`Database::ouvrir()` dans `main.cpp`).
Pour l'utiliser dans votre code : `#include <QSqlQuery>` puis `QSqlQuery q; q.exec("SELECT ...");`

Tables : `Client(numClient, nom)`, `Materiel(numMat, design, pu, stockActuel, stockInit)`,
`Achat(id, numClient, numMat, qte, date_achat)`.

## Règles de travail en équipe

- Chacun travaille uniquement dans **son dossier**.
- Une branche par module : `feature/clients`, `feature/materiels`, `feature/achats`.
- Les modifications de `commun/` et `ui/` passent par le responsable de l'intégration.
- Avant de pousser : `git pull --rebase origin main`.

## Règle de stock (énoncé)

- Vente : `StockActuel = StockActuel - Sortie`
- Suppression d'une vente : `StockActuel = StockActuel + Sortie`
