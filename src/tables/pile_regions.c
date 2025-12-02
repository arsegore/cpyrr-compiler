#include <stdio.h>
#include <stdlib.h>
#include "tables/pile_regions.h"

int pile_regions[150];

int nb_regions_pile = 0;

int num_region_courante;

void init_pile_regions() {
    int i;

    for (i = 0; i < TAILLE_PILE_REGIONS; i++) {
        pile_regions[i] = -1;
    }
}

int sommet_pile_region() {
    return pile_regions[nb_regions_pile - 1];
}

void empiler_pile_regions(int num_region) {
    pile_regions[nb_regions_pile++] = num_region;
    maj_region_courante();
}

void depiler_pile_regions() {
    nb_regions_pile--;
    maj_region_courante();
}

int nb_regions_englobantes() {
    return nb_regions_pile - 1;
}

void maj_region_courante() {
    num_region_courante = sommet_pile_region();
}

void afficher_pile_regions(int n) {
    int i;
    for (i = 0; i < n; i++) printf("| %3d ", pile_regions[i]);
    printf("\n");
}