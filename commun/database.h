<<<<<<< HEAD
#pragma once

namespace Database {
    /**
     * Ouvre (ou crée) la base SQLite de l'application et crée les tables
     * Client, Materiel et Achat si elles n'existent pas encore.
     * Retourne false en cas d'échec.
     *
     * Ensuite, partout dans le code : QSqlQuery q; q.exec("SELECT ...");
     */
    bool ouvrir();
}
=======
#pragma once

namespace Database {
    bool ouvrir();
}
>>>>>>> 8c2295e (Crafting)
