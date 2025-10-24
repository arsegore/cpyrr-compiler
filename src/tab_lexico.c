#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tab_lexico.h"

/**
 * tab_lexico.c 
 *
 * Implantation des fonctions de manipulation de la table Lexicographique
 *
 * Auteur : Adam HADDADI
 */

t_tab_lexico tab_lexico;
int premiere_ligne_libre = 32;

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
 * Renvoie le hach-code d'un léxème, permettant de définir 
 * dans quelle zone de la table lexico il sera doit être inséré
 *
 * @param lexeme : Un léxème 
 * @return : Le hach-code du léxème
 */
int calculer_hach_code(char *lexeme) {
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
 * De 0 à 31 : Les premiers léxèmes du hach-code correspondant à l'indice
 * de 32 à 500 : Les léxèmes de même hach-code qu'un léxème déjà rencontré 
 *
 * @param lexeme : Le léxème à insérer dans la table lexico 
 * @return : Le numéro lexico du léxème inséré
 */
int inserer_lexeme(char *lexeme) {
    int hach_code, ligne_courante, num_lexico;

    hach_code = calculer_hach_code(lexeme);

    if (tab_lexico[hach_code].longueur == -1) {
       tab_lexico[hach_code].longueur = strlen(lexeme);
       tab_lexico[hach_code].lexeme = lexeme;
       num_lexico = hach_code;
    } else {
        ligne_courante = hach_code;
        while (tab_lexico[ligne_courante].suivant != -1) {
            ligne_courante = tab_lexico[ligne_courante].suivant;
        }
        tab_lexico[premiere_ligne_libre].longueur = strlen(lexeme);
        tab_lexico[premiere_ligne_libre].lexeme = lexeme;
        tab_lexico[ligne_courante].suivant = premiere_ligne_libre;
        num_lexico = premiere_ligne_libre;
        premiere_ligne_libre++;
    }
    return num_lexico;
}

/* Main temporaire pour les tests...*/
/*
int main(int argc, char **argv) {
    init_tab_lexico();
    printf("Hach-code de 'feur' = %d\n", 
            calculer_hach_code("feur"));
    inserer_lexeme("feur");
    inserer_lexeme("reuf");
    inserer_lexeme("uerf");
    inserer_lexeme("bonjour");
    inserer_lexeme("caramba");
    inserer_lexeme("pausecafe");
    afficher_tab_lexico(0, 60);
    exit(EXIT_SUCCESS);
}
*/

