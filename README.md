# IT Store

Application de bureau de gestion des clients, du materiel, des achats et des factures. Le projet utilise C++17, Qt 6, CMake et SQLite.

## Prerequis

- CMake 3.19 ou plus recent.
- Qt 6.5 ou plus recent avec les modules Core, Gui, Widgets, Sql et Svg.
- Un compilateur C++17 (MinGW, MSVC, GCC ou Clang).

## Cloner et compiler

Cloner le depot, puis ouvrir `CMakeLists.txt` dans Qt Creator. Choisir un kit Qt 6 correspondant au compilateur installe, configurer le projet, puis compiler et lancer `GestionVente`.

En ligne de commande, apres avoir configure le chemin vers l'installation Qt :

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH=/chemin/vers/Qt/6.x/kit
cmake --build build
```

Chaque ordinateur doit avoir Qt et un compilateur compatibles. Les fichiers sources, interfaces `.ui` et ressources `.qrc` sont dans Git; les dossiers de build ne le sont pas.

## Base de donnees

Au premier lancement, SQLite cree le fichier de base dans le dossier de donnees utilisateur de Qt et l'application y initialise le schema. Le chemin est determine par Qt selon le systeme; il ne depend donc pas du dossier ou le depot a ete clone.

La base de travail de chaque personne est privee a son ordinateur et n'est pas synchronisee par Git. `commun/itstore.db` est utilisee en developpement si elle existe et ignoree par Git pour eviter de publier des donnees reelles ou personnelles. Pour repartir d'une base vide, fermer l'application puis supprimer uniquement la copie `itstore.db` du dossier de donnees utilisateur de l'application.

## Dossiers

- `ui/` : fenetre d'accueil.
- `clients/` : gestion des clients.
- `materiels/` : gestion du materiel et du stock.
- `achats/` : achats, formulaires, suppression et factures.
- `ventes/` : vues liees aux ventes.
- `commun/` : connexion SQLite, base modele, styles et ressources communes.

Ne poussez jamais de base utilisateur, sauvegarde ou donnees personnelles. Pour partager des donnees entre plusieurs installations, il faudra un service de base de donnees distant; la base SQLite locale n'est pas un mecanisme de synchronisation.
