#include "../../inc/tables/tab_lexico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * tab_lexico.c
 *
 * Implantation des fonctions de manipulation de la table Lexicographique
 *
 * Auteur : Adam 
 */

t_tab_lexico tab_lexico;
int tab_hash_code[TAILLE_TAB_HASH_CODE];
int premiere_ligne_libre_lexico = 0;

void init_tab_lexico() {
    int i; 

    for (i = 0; i < TAILLE_TAB_LEXICO; i++) {
        tab_lexico[i].longueur = -1;
        tab_lexico[i].lexeme = NULL;
        tab_lexico[i].suivant = -1;
    }

    for (i = 0; i < TAILLE_TAB_HASH_CODE; i++) {
        tab_hash_code[i] = -1;
    }
}

void afficher_tab_lexico(int depart, int arrivee) {
    int i, j; 

    if (depart == -1) {
        i = 0;
    } else {
        i = depart;
    }

    if (arrivee == -1) {
        j = TAILLE_TAB_LEXICO - 1;
    } else {
        j = arrivee; 
    }

    printf("---Table Lexicographique---\n");
    printf("|  Id| Lgr|     Léxème| Sui|\n");
    printf("---------------------------\n");
    for (; i <= j; i++) {
        printf("| %3d| %3d| %10s| %3d|\n", 
                i,
                tab_lexico[i].longueur,
                tab_lexico[i].lexeme,
                tab_lexico[i].suivant);
    }
    printf("\n");
}

int calculer_hash_code(char *lexeme) {
    int i;
    int somme = 0;
    for (i = 0; lexeme[i] != '\0'; i++) {
        somme += (int) lexeme[i];
    }
    return somme % 32;
}

char *recuperer_lexeme(int num_lexico) {
    return tab_lexico[num_lexico].lexeme;
}


int inserer_lexeme(char *lexeme) {
    int hash, ligne_courante, num_lexico;

    hash = calculer_hash_code(lexeme);

    if (tab_hash_code[hash] == -1) {
        num_lexico = premiere_ligne_libre_lexico++;
        tab_lexico[num_lexico].longueur = strlen(lexeme);
        tab_lexico[num_lexico].lexeme = lexeme;
        tab_hash_code[hash] = num_lexico;
    } else {
        ligne_courante = tab_hash_code[hash];
        do {
            // si léxèmes de même longueur, on compare
            if (strlen(lexeme) == tab_lexico[ligne_courante].longueur
                && (strcmp(lexeme, tab_lexico[ligne_courante].lexeme) == 0)) {
                num_lexico = ligne_courante;
                return num_lexico;
            }
            ligne_courante = tab_lexico[ligne_courante].suivant;
        } while (tab_lexico[ligne_courante].suivant != -1);
        num_lexico = premiere_ligne_libre_lexico++;
        tab_lexico[ligne_courante].suivant = num_lexico;
        tab_lexico[num_lexico].longueur = strlen(lexeme);
        tab_lexico[num_lexico].lexeme = lexeme;
    }
    
    return num_lexico;
}



