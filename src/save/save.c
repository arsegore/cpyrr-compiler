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
 * Auteur : Baptiste 
 */

void save_tab_lex() {
    int i;
    FILE* f_save_tab_lex;

    if (mkdir(NOM_DOSSIER_SAVES, 0755) != 0 && errno != EEXIST) {
        printf("Erreur création du dossier pour les sauvegardes\n");
        return;
    }

    if ((f_save_tab_lex = fopen(NOM_FIC_SAVE_TAB_LEX, "w+")) == NULL) {
        printf("Erreur ouverture/création du fichier de sauvegarde de la table lexicographique\n");
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
        printf("Erreur ouverture/création du fichier de sauvegarde de la table des déclarations\n");
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

void save_tab_regions() {
    int i;
    FILE* f_save_tab_regions;

    if (mkdir(NOM_DOSSIER_SAVES, 0755) != 0 && errno != EEXIST) {
        printf("Erreur création du dossier pour les sauvegardes\n");
        return;
    }

    if ((f_save_tab_regions = fopen(NOM_FIC_SAVE_TAB_REGIONS, "w+")) == NULL) {
        printf("Erreur ouverture/création du fichier de sauvegarde de la table des régions\n");
        return;
    }

    for (i=0; i<TAILLE_TAB_REGIONS; i++) {
        if (tab_region[i].taille != -1) {
            fprintf(f_save_tab_regions, "%d %d %p\n", tab_region[i].taille, tab_region[i].nis, tab_region[i].arbre_region);
        }
    }

    fclose(f_save_tab_regions);
}

void save_tab_rep() {
    int i;
    FILE* f_save_tab_rep;

    if (mkdir(NOM_DOSSIER_SAVES, 0755) != 0 && errno != EEXIST) {
        printf("Erreur création du dossier pour les sauvegardes\n");
        return;
    }

    if ((f_save_tab_rep = fopen(NOM_FIC_SAVE_TAB_REP, "w+")) == NULL) {
        printf("Erreur ouverture/création du fichier de sauvegarde de la table de représentation des types et entêtes de sous programmes\n");
        return;
    }

    for (i=0; i<TAILLE_TAB_REP; i++) {
        if (tab_rep[i] != -1) {
            fprintf(f_save_tab_rep, "%d ", tab_rep[i]);
        }
    }

    fclose(f_save_tab_rep);
}