<<<<<<< HEAD
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
=======
# IT Store

Application de bureau de gestion des clients, du matériel, des achats et des factures, écrite en C++ avec Qt 6 et CMake.

## Prérequis

- Qt 6.5 ou version plus récente, avec les modules Core, Gui, Widgets, Sql et Svg.
- CMake 3.19 ou plus récent.
- Un compilateur C++17 : GCC ou Clang sous Linux, Visual Studio ou MinGW sous Windows.
- Ninja ou Make est recommandé.

## Compilation sous Linux

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH=/chemin/vers/Qt/6.x/gcc_64
cmake --build build
./build/GestionVente
```

Avec les paquets Qt de la distribution, `CMAKE_PREFIX_PATH` peut être omis si CMake trouve Qt automatiquement.

## Compilation sous Windows

Ouvrir le `CMakeLists.txt` de ce dépôt dans Qt Creator, choisir un kit Qt 6 correspondant au compilateur installé, puis configurer un nouveau dossier de build. Dans un terminal Developer PowerShell, la compilation peut aussi se faire ainsi :

```powershell
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64"
cmake --build build --config Debug
```

Remplacer le chemin Qt et le nom du kit par ceux installés sur l’ordinateur. Ne pas partager les dossiers `build/` ou les fichiers `CMakeCache.txt` : ils contiennent les chemins propres à chaque machine. Si le projet est déplacé, créer un nouveau dossier de build et reconfigurer CMake.

## Base de données

`commun/itstore.db` est la base modèle du projet et est embarquée dans l’exécutable via `commun/database.qrc`. Au premier lancement, l’application en fait une copie dans le dossier de données utilisateur fourni par Qt. La base de travail reste donc propre à chaque ordinateur et n’est pas synchronisée par Git.

Pour repartir du jeu de données modèle, fermer l’application puis supprimer uniquement le fichier `itstore.db` dans le dossier de données utilisateur de l’application. Au prochain lancement, une nouvelle copie de la base modèle sera créée. Sauvegarder la base utilisateur avant toute réinitialisation.

Chaque personne développe et teste avec sa propre base locale. Pour partager les données en direct entre plusieurs ordinateurs, il faudra plus tard ajouter un serveur de base de données; ne pas mettre les bases de travail ni leurs sauvegardes contenant des données personnelles sur GitHub.

## Équipe et GitHub

- Cloner ce dépôt puis ouvrir son `CMakeLists.txt` dans Qt Creator.
- Chaque membre utilise son propre dossier de build, ignoré par Git.
- Faire une branche par fonctionnalité et intégrer les changements par pull request.
- `commun/itstore.db` est uniquement un jeu de données modèle commun. Les bases utilisateur, sauvegardes et données réelles ne doivent pas être poussées.

## Dossiers du code

- `ui/` : fenêtre d’accueil.
- `clients/` : écrans et modèle client.
- `materiels/` : écrans et modèle matériel.
- `achats/` : liste, formulaire de commande, suppression et factures PDF.
- `commun/` : accès SQLite, base modèle et styles communs.
- `ventes/` : écrans de vente.

La structure des données est mise à niveau automatiquement au démarrage. `numero_commande` regroupe les lignes achetées ensemble; `prix_unitaire_achat` garde le prix payé au moment de la commande.
>>>>>>> 8c2295e (Crafting)
