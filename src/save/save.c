#include <stdio.h>
#include <stdlib.h>
#include "save/save.h"

/**
 * save.c
 *
 * Implantation des fonctions de sauvegarde en mémoire des tables
 *
 * Auteur : Baptiste MOULIN
 */

void save_tab_lex() {
    int i;
    FILE* f_save_tab_lex;

    if ((f_save_tab_lex = fopen(NOM_FIC_SAVE_TAB_LEX, "w+")) == NULL) {
        printf("Erreur ouverture/création du fichier de sauvegarde de la tab lexico\n");
        return;
    }
    
    for (i=0; i<TAILLE_TAB_HASH_CODE; i++) {
        if (tab_hash_code[i] != -1) {
            fprintf(f_save_tab_lex, "%d ", tab_hash_code[i]);
        }
    }

    fprintf(f_save_tab_lex, "\n\n");

    for (i=0; i<TAILLE_TAB_LEXICO; i++) {
        if (tab_lexico[i].longueur != -1) {
            fprintf(f_save_tab_lex, "%d %s %d\n", tab_lexico[i].longueur, tab_lexico[i].lexeme, tab_lexico[i].suivant);
        }
    }

    fclose(f_save_tab_lex);
}