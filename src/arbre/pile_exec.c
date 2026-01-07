#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre/pile_exec.h"
#include "verif_sem/verif_sem.h"

cellule pile_exec[5000];

int base_courante;

int taille_pile_exec = 0;

void init_pile_exec() {
    int i;
    for (i = 0 ; i < TAILLE_PILE_EXEC ; i++) {
        pile_exec[i].type = VARIABLE;
        pile_exec[i].contenu.donnees.lexeme = "";
        pile_exec[i].contenu.donnees.type_var = -1; // type indéfini, on part sur ça pour dire que la case est vide
    }
}

void empiler_pile_exec_chainage(int base_courante) {
    pile_exec[taille_pile_exec].type = CHAINAGE;
    pile_exec[taille_pile_exec].contenu.chainage = base_courante;
    taille_pile_exec++;
}

void empiler_pile_exec_variable(var variable) {
    pile_exec[taille_pile_exec].type = VARIABLE;
    pile_exec[taille_pile_exec].contenu.donnees = variable;
    taille_pile_exec++;
}

void afficher_pile_exec() {
    int i;
    int t;
    char *nom_var;

    printf("\n----------- PILE A L'EXECUTION -----------\n");

    for (i = 0; i < taille_pile_exec; i++) {
        printf("[%03d] ", i);

        if (pile_exec[i].type == CHAINAGE) {
            printf("| Chaînage -> %5d", pile_exec[i].contenu.chainage);
            printf("                 |");
        } else {
            t = pile_exec[i].contenu.donnees.type_var;
            nom_var = pile_exec[i].contenu.donnees.lexeme;

            // Protection si le lexeme est NULL
            printf("| %-10s | Type:%d | Valeur: ", (nom_var ? nom_var : "cellule vide"), t);

            if (t == TREETYPE_ENTIER) printf("%d", pile_exec[i].contenu.donnees.valeur.entier);
            else if (t == TREETYPE_REEL) printf("%f", pile_exec[i].contenu.donnees.valeur.reel);
            else if (t == TREETYPE_BOOL) printf("%s", pile_exec[i].contenu.donnees.valeur.bool ? "T" : "F");
            else if (t == TREETYPE_CHAR) printf("'%c'", pile_exec[i].contenu.donnees.valeur.caractere);
            else printf("?");
            printf("|");

        }
        if (i == BC) printf(" <--[BC]");
        printf("\n");
        printf("-------------------------------------------\n");
    }
}

void allouer_taille(int taille){
    var v = {NULL, -1, {0}};
    int i;

    for (int i = 0; i < taille; i++){
        empiler_pile_exec_variable(v);
    }
}