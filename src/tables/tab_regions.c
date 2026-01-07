#include <stdio.h>
#include <stdlib.h>
#include "tables/tab_regions.h"
#include "tables/pile_regions.h"
#include "tables/tab_decla.h"

/**
 * tab_regions.c
 *
 * Implantation de la table des régions et de ses fonctions
 *
 * Auteur : HADDADI Adam, GRANJON Damien, MOULIN Baptiste
 */

tab_region_t tab_region;

int nb_regions_total = 0;

void init_tab_regions() {
    int i;

    for (i = 0; i < TAILLE_TAB_REGIONS; i++) {
        tab_region[i].taille = -1;
        tab_region[i].nis = -1;
        tab_region[i].arbre_region = NULL;
    }
}


void inserer_region(int taille) {
    int num_region = nb_regions_total++;

    empiler_pile_regions(num_region);
    tab_region[num_region].nis = nb_regions_englobantes();
    modifier_taille(num_region, taille+ tab_region[num_region].nis);
}

void afficher_tab_regions() {
    int i = 0;


    printf("--------------Table des régions--------------\n");
    printf("| %-4s | %-8s | %-8s | %-12s |\n", "ID", "taille",
               "NIS", "arbre");
    printf("--------------------------------------------\n");
    while (tab_region[i].taille > -1) {
        printf("| %-4d | %-8d | %-8d | %-12p |\n", i, tab_region[i].taille,
               tab_region[i].nis, tab_region[i].arbre_region);
        printf("--------------------------------------------\n");
        i++;
    }
}

void modifier_taille(int num_region, int taille) {
    tab_region[num_region].taille = taille;
}

void mettre_a_jour_taille_region(int num_region, int deplacement_final) {
    if (tab_region[num_region].nis == 0) {
        modifier_taille(num_region, deplacement_final);
    } else {
        modifier_taille(num_region, tab_region[num_region].nis + 1 + deplacement_final);
    }
}

void evaluer_taille_programme(){
    int i;
    int taille = 0;
    for (i = 0; i < HAUTEUR; i++){
        if (tab_decla[i][NATURE] == N_VAR && tab_decla[i][REGION] == 0){
            taille += taille_type(tab_decla[i][DESCRIPTION]);
        }
    }
    mettre_a_jour_taille_region(0, taille);
}

void modifier_arbre_region(int num_region, arbre a) {
    tab_region[num_region].arbre_region = a;
}



