#include "tables/tab_rep.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * Implantation de la table de description des types et des en-têtes de
 * sous-programme
 *
 * Auteur: Louis PELOUX, Adam HADDADI
 */
int tab_rep[1000];
int idx_premier_libre = 0;
int idx_nb_element = 0;
int idx_type_element = 0;
int nbparam = 0;
int nbchamps = 0;
int deplacement = 0;
int nbdimension;


void init_tab_rep() {
    int i;

    for (i = 0; i < TAILLE_TAB_REP; i++) {
        tab_rep[i] = -1;
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
        j = TAILLE_TAB_REP - 1;
    } else {
        j = arrivee;
    }

    printf("----- Table Rep -----\n");
    printf("| %4s | %10s | \n", "Id", "Valeur");
    printf("--------------------\n");
    for (; i <= j; i++) {
        printf("| %4d | %10d | \n",
            i,
            tab_rep[i]);
    }
    printf("\n");

}

void inserer_tab_rep(int val) {
    tab_rep[idx_premier_libre++] = val;
}

void inserer_tab_rep_nb_elem(int val){
    tab_rep[idx_nb_element] = val;
}

void inserer_tab_rep_type(int type){
    tab_rep[idx_type_element] = type;
    printf("Type du tab dans [%d] == %d\n", idx_type_element, type);
}

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

void debut_fct(int type){
    idx_nb_element = idx_premier_libre++;
    tab_rep[idx_premier_libre++] = type;
    nbparam = 0;
}

void debut_tab(){
    idx_type_element = idx_premier_libre++;
    idx_nb_element = idx_premier_libre++;
    printf("indice du type du tab = %d\n", idx_type_element);
    printf("indice du nbdim du tab = %d\n", idx_nb_element);
    nbdimension = 0;
}
