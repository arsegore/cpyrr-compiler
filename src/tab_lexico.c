#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/tab_lexico.h"

/**
 * tab_lexico.c 
 *
 * Implantation des fonctions de manipulation de la table Lexicographique
 *
 * Auteur : Adam HADDADI
 */

t_tab_lexico tab_lexico;
int tab_hash_code[TAILLE_TAB_HASH_CODE];
int premiere_ligne_libre = 0;

/**
 * Initialise la table lexico, notamment en mettant le champ longueur à -1
 */
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

/**
 * Affiche la table lexico de depart à arrivee, ou entierement si les 
 * deux valeurs sont égales à -1
 *
 * @param depart : L'indice d'où l'affichage commence
 * @param arrivee : L'indice de fin de l'affichage
 */
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

    printf("--- Table Lexicographique ---\n");
    printf("|  Id| Lgr|     Léxème| Sui|\n");
    for (; i <= j; i++) {
        printf("| %3d| %3d| %10s| %3d|\n", 
                i,
                tab_lexico[i].longueur,
                tab_lexico[i].lexeme,
                tab_lexico[i].suivant);
    }
}

/**
 * Renvoie le hash-code d'un léxème, permettant de définir 
 * dans quelle zone de la table lexico il sera doit être inséré
 *
 * @param lexeme : Un léxème 
 * @return : Le hash-code du léxème
 */
int calculer_hash_code(char *lexeme) {
    int i;
    int somme = 0;
    for (i = 0; lexeme[i] != '\0'; i++) {
        somme += (int) lexeme[i];
    }
    return somme % 32;
}

/**
 * Renvoie le léxème correspondant à un numéro lexicograpghique 
 * donné 
 *
 * @param num_lexico : Le numéro lexico du léxème recherché
 * @return : Le léxème correspondant dans la table
 */
char *recuperer_lexeme(int num_lexico) {
    return tab_lexico[num_lexico].lexeme;
}

/** 
 * Insère un léxème dans la table lexico.
 *
 * @param lexeme : Le léxème à insérer dans la table lexico 
 * @return : Le numéro lexico du léxème inséré (si le léxème était déjà présent dans 
 * la table, retourne quand même son numéro lexico)
 */
int inserer_lexeme(char *lexeme) {
    int hash, ligne_courante, num_lexico;

    hash = calculer_hash_code(lexeme);

    if (tab_hash_code[hash] == -1) {
        num_lexico = premiere_ligne_libre++;
        tab_lexico[num_lexico].longueur = strlen(lexeme);
        tab_lexico[num_lexico].lexeme = lexeme;
        tab_hash_code[hash] = num_lexico;
    } else {
        ligne_courante = tab_hash_code[hash];
        while (tab_lexico[ligne_courante].suivant != -1) {
            // si léxèmes de même longueur, on compare
            if (strlen(lexeme) == tab_lexico[ligne_courante].longueur
                && (strcmp(lexeme, tab_lexico[ligne_courante].lexeme) == 0)) {
                num_lexico = ligne_courante;
                return num_lexico;
            }
            ligne_courante = tab_lexico[ligne_courante].suivant;
        }
        num_lexico = premiere_ligne_libre++;
        tab_lexico[ligne_courante].suivant = num_lexico;
        tab_lexico[num_lexico].longueur = strlen(lexeme);
        tab_lexico[num_lexico].lexeme = lexeme;
    }
    
    return num_lexico;
}

/* Main temporaire pour les tests...*/
/*
int main(int argc, char **argv) {
    init_tab_lexico();
    printf("Hash-code de 'feur' = %d\n", 
            calculer_hash_code("feur"));
    inserer_lexeme("feur");
    inserer_lexeme("reuf");
    inserer_lexeme("uerf");
    inserer_lexeme("bonjour");
    inserer_lexeme("caramba");
    inserer_lexeme("pausecafe");
    inserer_lexeme("nobruoj");
    printf("Numéro lexico de 'bonjour' : %d\n",
    inserer_lexeme("bonjour"));
    afficher_tab_lexico(0, 20);
    exit(EXIT_SUCCESS);
}
*/

