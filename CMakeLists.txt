cmake_minimum_required(VERSION 3.19)
project(GestionVente LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets Sql Svg)

qt_standard_project_setup()

qt_add_executable(GestionVente
    WIN32 MACOSX_BUNDLE
    main.cpp

    # --- ui : accueil ---
    ui/mainwindow.h
    ui/mainwindow.cpp
    ui/mainwindow.ui

    # --- clients ---
    clients/clientwindow.h
    clients/clientwindow.cpp
    clients/client.h
    clients/client.cpp

    # --- materiels ---
    materiels/materielwindow.h
    materiels/materielwindow.cpp
    materiels/materiel.h
    materiels/materiel.cpp

    # --- achats ---
    achats/achat.h
    achats/achat.cpp
    achats/achatstyle.h
    achats/achatsui.h
    achats/achatsui.cpp
    achats/logowidget.h
    achats/logowidget.cpp
    achats/achatwindow.h
    achats/achatwindow.cpp
    achats/achatwindow.ui
    achats/nouveau/nouveauachat.h
    achats/nouveau/nouveauachat.cpp
    achats/nouveau/nouveauachat.ui
    achats/nouveau/nouveauachatdialog.h
    achats/nouveau/nouveauachatdialog.cpp
    achats/nouveau/nouveauachatdialog.ui
    achats/suppression/supprimerachat.h
    achats/suppression/supprimerachat.cpp
    achats/suppression/supprimerachat.ui
    achats/suppression/supprimerachatdialog.h
    achats/suppression/supprimerachatdialog.cpp
    achats/suppression/supprimerachatdialog.ui
    achats/facture/facture.h
    achats/facture/facture.cpp
    achats/facture/facture.ui
    achats/facture/facturedialog.h
    achats/facture/facturedialog.cpp
    achats/facture/facturedialog.ui
    achats/facture/nombreenlettres.h

    # --- ventes (listage) ---
    ventes/ventes.h
    ventes/ventes.cpp
    ventes/ventewindow.h
    ventes/ventewindow.cpp

    # --- commun ---
    commun/modeles.h
    commun/database.h
    commun/database.cpp
    commun/factures/factures.qrc
    commun/style.h
    achats/achats.qrc
)

set_target_properties(GestionVente PROPERTIES AUTORCC ON)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/commun/itstore.db"
    AND NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/commun/itstore.db")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/commun")
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/commun/itstore.db"
        "${CMAKE_CURRENT_BINARY_DIR}/commun/itstore.db"
        COPYONLY
    )
endif()

# HEADER_FILE_ONLY : visibles dans l'arborescence, mais jamais compilés
set_source_files_properties(${FICHIERS_DONNEES} PROPERTIES HEADER_FILE_ONLY TRUE)
target_sources(GestionVente PRIVATE ${FICHIERS_DONNEES})

# Permet d'écrire #include "clients/client.h" depuis n'importe quel dossier
target_include_directories(GestionVente PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(GestionVente PRIVATE
    # Dossier styles du projet (utilisé en secours dans chargerStyle())
    STYLES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/styles"

    # Base SQLite du projet : un seul fichier, quel que soit le dossier de build
    # (Debug, Release...). Lu en priorité par Database::ouvrir().
    DB_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/itstore.db"
)

target_link_libraries(GestionVente
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        Qt::Svg
)

# Copie le dossier styles à côté de l'exécutable.
# Cible personnalisée "ALL" : elle s'exécute à CHAQUE compilation,
# même si seul le fichier .qss a changé (contrairement à POST_BUILD,
# qui ne se déclenche que si l'exécutable est recompilé/relié).
add_custom_target(copy_styles ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/styles
            $<TARGET_FILE_DIR:GestionVente>/styles
    COMMENT "Copie du dossier styles"
)
add_dependencies(GestionVente copy_styles)

# NOTE : la base data/itstore.db n'est volontairement PAS copiée dans le dossier
# de build : on travaille directement sur le fichier du projet (DB_PATH), pour
# ne jamais écraser des données par une copie plus ancienne.

install(TARGETS GestionVente
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Installe aussi les styles avec l'application
install(DIRECTORY styles DESTINATION ${CMAKE_INSTALL_BINDIR})

# Installe la base à côté de l'exécutable (dossier data/), là où
# Database::ouvrir() la cherche une fois l'application déployée
install(FILES data/itstore.db DESTINATION ${CMAKE_INSTALL_BINDIR}/data)

qt_generate_deploy_app_script(
    TARGET GestionVente
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})