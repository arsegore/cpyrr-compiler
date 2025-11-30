#include "tables/tab_rep.h"
#include "tables/tab_decla.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * Implantation de la table de description des types et des en-têtes de
 * sous-programme
 *
 * Auteur: Louis , Adam , Baptiste Moulin
 */
int tab_rep[1000];
int id_rep_courante;
int idx_premier_libre = 0;
int idx_nb_element = 0;
int idx_type_element = 0;
int nbparam = 0;
int nbchamps;
int deplacement;
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
}

void debut_proc(){
    id_rep_courante = idx_premier_libre++;
    idx_nb_element = id_rep_courante;
    nbparam = 0;
}

void debut_depl(){
    deplacement = 0;
}

/* exactement la même que proc, faut il vraiment refaire uen fct ? */
void debut_struct(){
    id_rep_courante = idx_premier_libre++;
    idx_nb_element = id_rep_courante;
    nbchamps = 0;
    deplacement = 0;
}

void debut_fct(int type){
    id_rep_courante = idx_premier_libre++;
    idx_nb_element = id_rep_courante;
    tab_rep[idx_premier_libre++] = type;
    nbparam = 0;
}

void debut_tab(){
    id_rep_courante = idx_premier_libre++;
    idx_type_element = id_rep_courante;
    idx_nb_element = idx_premier_libre++;
    nbdimension = 0;
}

void incr_nb_dim() {
    nbdimension++;
}

void incr_nb_champ() {
    nbchamps++;
}

void incr_depl(int num_lexico) {
    deplacement+=taille_type(num_lexico);
}

void incr_param() {
    nbparam++;
}


