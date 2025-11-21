#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
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

    if (mkdir(NOM_DOSSIER_SAVES, 0755) != 0 && errno != EEXIST) {
        printf("Erreur création du dossier pour les sauvegardes\n");
        return;
    }

    if ((f_save_tab_lex = fopen(NOM_FIC_SAVE_TAB_LEX, "w+")) == NULL) {
        printf("Erreur ouverture/création du fichier de sauvegarde de la tab lexico\n");
        return;
    }
    
    for (i=0; i<TAILLE_TAB_HASH_CODE; i++) {
        if (i != TAILLE_TAB_HASH_CODE-1) {
            fprintf(f_save_tab_lex, "%d ", tab_hash_code[i]);
        }
        else {
            fprintf(f_save_tab_lex, "%d", tab_hash_code[i]);
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

void save_tab_decla() {
    int i, j;
    FILE* f_save_tab_decla;

    if (mkdir(NOM_DOSSIER_SAVES, 0755) != 0 && errno != EEXIST) {
        printf("Erreur création du dossier pour les sauvegardes\n");
        return;
    }

    if ((f_save_tab_decla = fopen(NOM_FIC_SAVE_TAB_DECLA, "w+")) == NULL) {
        printf("Erreur ouverture/création du fichier de sauvegarde de la tab des déclarations\n");
        return;
    }

    for (i=0; i<HAUTEUR; i++) {
        if (tab_decla[i][0] != -1) {
            for (j=0; j<LARGEUR; j++) {
                if (j != LARGEUR-1) {
                    fprintf(f_save_tab_decla, "%d ", tab_decla[i][j]);
                }
                else {
                    fprintf(f_save_tab_decla, "%d", tab_decla[i][j]);
                }
            }
            
            fprintf(f_save_tab_decla, "\n");
        }
    }

    fclose(f_save_tab_decla);
}