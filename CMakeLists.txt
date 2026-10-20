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
    achats/achatwindow.h
    achats/achatwindow.cpp
    achats/achat.h
    achats/achat.cpp

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
