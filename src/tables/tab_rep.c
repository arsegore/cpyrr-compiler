#include "../../inc/tables/tab_rep.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * Implantation de la table de description des types et des en-têtes de
 * sous-programme
 *
 * Auteur: Adam HADDADI
 */
int tab_desc[1000];
int premiere_ligne_libre_desc = 0;

void init_tab_rep() {
    int i;

    for (i = 0; i < TAILLE_TAB_DESC; i++) {
        tab_desc[i] = -1;
    }
}

void afficher_tab_rep(int depart, int arrivee) {
    int i, j;

    if (depart == -1) {
        i = 0;
    } else {
        i = depart;
    }

    if (arrivee == -1) {
        j = TAILLE_TAB_DESC - 1;
    } else {
        j = arrivee;
    }

    printf("-----Table Desc-----\n");
    printf("| %4s | %10s | \n", "Id", "Valeur");
    printf("--------------------\n");
    for (; i <= j; i++) {
        printf("| %4d | %10d | \n",
            i,
            tab_desc[i]);
    }
    printf("\n");

}

/**
 * Diverses fonctions auxiliaires, mais seule l'interface
 * inserer_tab_desc() est publique (pour uniformiser l'écriture des
 * actions sémantiques
 */

void inserer_tab_rep(int val) {
    tab_rep[indice_pv++] = val;
}
