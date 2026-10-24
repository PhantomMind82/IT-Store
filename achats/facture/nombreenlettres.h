#pragma once

#include <string>

/**
 * @file nombreenlettres.h
 * @brief Écrit un nombre entier en toutes lettres, en français.
 *
 * Exemple : NombreEnLettres::enLettres(980000) -> "neuf cent quatre-vingt mille"
 *
 * Ce fichier n'utilise PAS Qt : c'est du C++ standard (std::string), donc
 * on peut le tester tout seul. Dans facturedialog.cpp on convertit le
 * résultat en QString avec QString::fromStdString().
 *
 * Règles de l'orthographe traditionnelle appliquées :
 *  - "et" pour 21, 31, 41, 51, 61 et 71 (vingt et un, soixante et onze)
 *  - "quatre-vingts" et "deux cents" prennent un "s" seulement s'ils terminent le nombre
 *    (quatre-vingts, mais quatre-vingt mille ; deux cents, mais deux cent mille)
 *  - "mille" ne s'écrit jamais "un mille" et ne prend jamais de "s"
 */
namespace NombreEnLettres {

namespace detail {

// Les mots de 0 à 19 (indice = valeur du nombre).
inline const char *const UNITES[20] = {
    "zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf",
    "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize",
    "dix-sept", "dix-huit", "dix-neuf"
};

// Les dizaines (indice = chiffre des dizaines). 7 et 9 sont construits à partir de 6 et 8.
inline const char *const DIZAINES[10] = {
    "", "", "vingt", "trente", "quarante", "cinquante", "soixante",
    "soixante", "quatre-vingt", "quatre-vingt"
};

// n est compris entre 0 et 99. finDuNombre = true si ce mot termine tout le nombre
// (sert uniquement à écrire "quatre-vingts" avec un s).
inline std::string moinsDeCent(int n, bool finDuNombre)
{
    if (n < 20)
        return UNITES[n];

    const int d = n / 10;   // chiffre des dizaines
    const int u = n % 10;   // chiffre des unités

    if (d == 7 || d == 9) {                       // 70-79 et 90-99
        if (d == 7 && u == 1)
            return "soixante et onze";
        return std::string(DIZAINES[d]) + "-" + UNITES[10 + u];
    }
    if (u == 0) {                                 // 20, 30, ... 80
        if (d == 8)
            return finDuNombre ? "quatre-vingts" : "quatre-vingt";
        return DIZAINES[d];
    }
    if (u == 1 && d != 8)                         // 21, 31, 41, 51, 61
        return std::string(DIZAINES[d]) + " et un";
    return std::string(DIZAINES[d]) + "-" + UNITES[u];   // 22, 83, ...
}

// n est compris entre 1 et 999.
inline std::string moinsDeMille(int n, bool finDuNombre)
{
    const int c = n / 100;   // chiffre des centaines
    const int reste = n % 100;
    std::string texte;

    if (c > 0) {
        if (c == 1) {
            texte = "cent";
        } else {
            texte = std::string(UNITES[c]) + " cent";
            if (reste == 0 && finDuNombre)
                texte += "s";                     // deux cents
        }
        if (reste == 0)
            return texte;
        texte += " ";
    }
    texte += moinsDeCent(reste, finDuNombre);
    return texte;
}

} // namespace detail

/** Écrit n en lettres. Gère les nombres jusqu'à 999 milliards. */
inline std::string enLettres(long long n)
{
    if (n == 0)
        return "zéro";
    if (n >= 1000000000000LL || n <= -1000000000000LL)
        return std::to_string(n);                 // trop grand : on garde les chiffres

    std::string signe;
    if (n < 0) {
        signe = "moins ";
        n = -n;
    }

    const int milliards = static_cast<int>(n / 1000000000LL);
    const int millions  = static_cast<int>((n / 1000000LL) % 1000);
    const int milliers  = static_cast<int>((n / 1000LL) % 1000);
    const int unites    = static_cast<int>(n % 1000);

    std::string resultat;
    auto ajouter = [&resultat](const std::string &mots) {
        if (!resultat.empty())
            resultat += " ";
        resultat += mots;
    };

    if (milliards > 0)
        ajouter(detail::moinsDeMille(milliards, true) + (milliards > 1 ? " milliards" : " milliard"));
    if (millions > 0)
        ajouter(detail::moinsDeMille(millions, true) + (millions > 1 ? " millions" : " million"));
    if (milliers > 0) {
        if (milliers == 1)
            ajouter("mille");
        else
            ajouter(detail::moinsDeMille(milliers, false) + " mille");
    }
    if (unites > 0)
        ajouter(detail::moinsDeMille(unites, true));

    return signe + resultat;
}

} // namespace NombreEnLettres
