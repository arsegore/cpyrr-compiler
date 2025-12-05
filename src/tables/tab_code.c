#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables/tab_code.h"

/**
 * Auteur : Adam HADDADI
 */

const char *tab_code[NB_LIGNES_MAX_PROG];
int nb_lignes = 0;

void init_tab_code(){
    int i;
    for (i = 0; i < NB_LIGNES_MAX_PROG; i++){
        tab_code[i] = NULL;
    }
    nb_lignes = 0;
}

void afficher_tab_code(){
    int i;
    printf("Code source du programme : \n");
    for (i = 0; i < nb_lignes; i++){
        printf("%3d| %s\n", i + 1, tab_code[i]);
    }
}

void ajouter_ligne_code(const char *ligne) {
    if (nb_lignes >= NB_LIGNES_MAX_PROG) {
        fprintf(stderr, "Trop de lignes dans le programme (max: %d)\n", 
                NB_LIGNES_MAX_PROG);
        exit(EXIT_FAILURE);
    }
    
    tab_code[nb_lignes] = strdup(ligne);
    nb_lignes++;
}