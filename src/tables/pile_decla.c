#include <stdio.h>
#include <stdlib.h>
#include "tables/pile_decla.h"

int pile_decla[256];

int nb_decla_pile = 0;

void init_pile_decla() {
    int i;

    for (i = 0; i < TAILLE_PILE_DECLA; i++) {
        pile_decla[i] = -1;
    }
}

int sommet_pile_decla(){
    return pile_decla[nb_decla_pile];
}

void empiler_pile_decla(int num_region) {
    pile_decla[nb_decla_pile++] = num_region;
}

void depiler_pile_decla() {
    nb_decla_pile--;
}

void afficher_pile_decla() {
    int i;
    for (i = 0; i < TAILLE_PILE_DECLA; i++) printf("| %3d ", pile_decla[i]);
    printf("\n");
}