#include <stdio.h>
#include <stdlib.h>
#include "tables/tab_regions.h"
#include "tables/pile_regions.h"

tab_region_t tab_region;

int nb_regions_total = 0;

void init_tab_regions() {
    int i;

    for (i = 0; i < TAILLE_TAB_REGIONS; i++) {
        tab_region[i].taille_exec = -1;
        tab_region[i].nis = -1;
        tab_region[i].arbre_region = NULL;
    }
    inserer_region();
}


int inserer_region() {
    int num_region = nb_regions_total++;
    empiler_pile_regions(num_region);

    tab_region[num_region].nis = nb_regions_englobantes();

    return num_region;
}

void afficher_tab_regions(int depart, int arrivee) {
    int i, j;

    if (depart == -1) {
        i = 0;
    } else {
        i = depart;
    }

    if (arrivee == -1) {
        j = TAILLE_TAB_REGIONS - 1;
    } else {
        j = arrivee;
    }

    printf("------------Table des régions------------\n");
    printf("| %-4s | %-8s | %-8s | %-8s |\n", "ID", "execution",
               "NIS", "arbre");
    printf("----------------------------------------\n");
    for (i = depart; i < j; i++) {
        printf("| %-4d | %-8d | %-8d | %-8p |\n", i, tab_region[i].taille_exec,
               tab_region[i].nis, tab_region[i].arbre_region);
        printf("----------------------------------------\n");
    }
}

void modifier_taille_exec(int num_region, int exec) {
    tab_region[num_region].taille_exec = exec;
}

void modifier_arbre_region(int num_region, arbre *a) {
    tab_region[num_region].arbre_region = a;
}



