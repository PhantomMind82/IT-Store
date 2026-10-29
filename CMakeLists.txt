<<<<<<< HEAD
cmake_minimum_required(VERSION 3.19)
project(GestionVente LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)

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
    achats/nouveau/nouveauachatdialog.h
    achats/nouveau/nouveauachatdialog.cpp
    achats/nouveau/nouveauachatdialog.ui
    achats/suppression/supprimerachatdialog.h
    achats/suppression/supprimerachatdialog.cpp
    achats/suppression/supprimerachatdialog.ui
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
    commun/style.h
)

# Permet d'écrire #include "clients/client.h" depuis n'importe quel dossier
target_include_directories(GestionVente PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GestionVente
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

install(TARGETS GestionVente
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET GestionVente
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
=======
cmake_minimum_required(VERSION 3.19)
project(GestionVente VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql Svg)

qt_standard_project_setup()

qt_add_executable(GestionVente
    WIN32 MACOSX_BUNDLE
    main.cpp

    ui/mainwindow.h
    ui/mainwindow.cpp
    ui/mainwindow.ui

    clients/clientwindow.h
    clients/clientwindow.cpp
    clients/client.h
    clients/client.cpp

    materiels/materielwindow.h
    materiels/materielwindow.cpp
    materiels/materiel.h
    materiels/materiel.cpp

    achats/achats.qrc
    achats/achatwindow.h
    achats/achatwindow.cpp
    achats/achatwindow.ui
    achats/nouveau/nouveauachat.h
    achats/nouveau/nouveauachat.cpp
    achats/nouveau/nouveauachat.ui
    achats/suppression/supprimerachat.h
    achats/suppression/supprimerachat.cpp
    achats/suppression/supprimerachat.ui
    achats/facture/facture.h
    achats/facture/facture.cpp
    achats/facture/facture.ui

    ventes/ventes.h
    ventes/ventes.cpp
    ventes/ventewindow.h
    ventes/ventewindow.cpp

    commun/database.h
    commun/database.cpp
    commun/database.qrc
    commun/factures/factures.qrc
    commun/style.h
)

set_target_properties(GestionVente PROPERTIES AUTORCC ON)

target_include_directories(GestionVente PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GestionVente
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
        Qt6::Svg
)

install(TARGETS GestionVente
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET GestionVente
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
>>>>>>> 8c2295e (Crafting)
