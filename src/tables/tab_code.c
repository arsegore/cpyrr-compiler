#include <stdio.h>
#include <stdlib.h>
#include "tables/tab_code.h"

const char *tab_code[NB_LIGNES_MAX_PROG];
int nb_lignes_code;

void init_tab_code(){
    int i;
    for (i = 0; i < NB_LIGNES_MAX_PROG; i++){
        tab_code[i] = NULL;
    }
    nb_lignes_code = 0;
}

void ajouter_ligne_code(const char *ligne) {
    
}