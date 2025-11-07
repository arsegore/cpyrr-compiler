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
int idx_premier_libre = 0;
int nbparam = 0;
int nbchamps = 0;
int deplacement = 0;
int nbdimension = 0;


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
    tab_rep[idx_premier_libre++] = val;
}

void inserer_tab_rep_premier(int val){
    tab_rep[idx_nb_element] = val;
}_

void debut_proc(){
    idx_nb_element = idx_premier_libre;
    nbparam = 0;
    idx_premier_libre++;
}

/* exactement la même que proc, faut il vraiment refaire uen fct ? */
void debut_struct(){
    idx_nb_element = idx_premier_libre;
    nbchamps = 0;
    idx_premier_libre++;
}

/**
 * Permet de commencer le debut d'une fonction
 * @param valeur de retour de type inserer a la deuxième case libre
 */
void debut_fct(int val){
    idx_nb_element = idx_premier_libre++;
    tab_rep[idx_premier_libre++] = val;
    nbparam = 0;
}

void debut_tab(){
    idx_nb_element = idx_premier_libre++;
    idx_type_element = idx_premier_libre++;
    nbdimension = 0;
}

void inserer_tab_type(int val){
    tab_rep[idx_type_element] = val;
}