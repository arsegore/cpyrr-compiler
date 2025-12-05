#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/arbre/pile_exec.h"

cellule pile_exec[5000];

int base_courante;

int taille_pile_exec = 0;

void init_pile_exec() {
    int i;
    cellule c;
    for (i = 0 ; i < TAILLE_PILE_EXEC ; i++) {
        pile_exec[i].chainage = -1;
        pile_exec[i].variable.lexeme = "";
        pile_exec[i].variable.a_valeur = -1;
    }
}

cellule sommet_pile_exec() {
    return pile_exec[taille_pile_exec - 1];
}

// Ancienne version en une seule fonction, à voir si c'était mieux au final
/*
void empiler_pile_exec(int chainage, var variable) {
    if (chainage != -1) {
        pile_exec[taille_pile_exec++].chainage = chainage;
    } else {
        pile_exec[taille_pile_exec++].variable = variable;
    }
}
*/

void empiler_pile_exec_chainage(int chainage) {
    pile_exec[taille_pile_exec++].chainage = chainage;
}

void empiler_pile_exec_variable(var variable) {
    pile_exec[taille_pile_exec++].variable = variable;
}

void maj_base_courante() {
    base_courante = taille_pile_exec;
}

void afficher_pile_exec() {
    int i;
    for (i = 0; i < TAILLE_PILE_EXEC; i++) {
        if (pile_exec[i].chainage != -1) {
            // chainage
            printf("| %20d |\n", pile_exec[i].chainage);
        } else {
            printf("| %15s ", pile_exec[i].variable.lexeme);
            switch (pile_exec[i].variable.a_valeur) {
                case 0: // entier
                    printf("%5d |\n", pile_exec[i].variable.valeur.entier);
                    break;
                case 1: // reel
                    printf("%5f |\n", pile_exec[i].variable.valeur.reel);
                    break;
                case 2: // booleen
                    printf("%5d |\n", pile_exec[i].variable.valeur.booleen);
                    break;
                case 3: // caractere
                    printf("%5c |\n", pile_exec[i].variable.valeur.caractere);
                    break;
                default:
                    printf("     |\n");
                    break;
            }
        }
    }
    printf("\n");
}