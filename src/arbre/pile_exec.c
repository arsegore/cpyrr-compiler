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
    printf("\n--- PILE À L'EXECUTION (BC: %d, TAILLE: %d) ---\n", base_courante, taille_pile_exec);
    for (int i = 0; i < taille_pile_exec; i++) {
        printf("[%3d] ", i);
        if (pile_exec[i].type == CHAINAGE) {
            printf("| CHAINAGE -> %d |\n", pile_exec[i].contenu.chainage);
        } else {
            var *v = &pile_exec[i].contenu.donnees;
            printf("| VAR %-10s | Type: %-7s | Val: ", v->lexeme, recup_nom_type(v->type_var));
            if (v->type_var == 0) printf("%d", v->valeur.entier);
            else if (v->type_var == 1) printf("%f", v->valeur.reel);
            else if (v->type_var == 2) printf("%s", v->valeur.bool ? "true" : "false");
            else if (v->type_var == 3) printf("%c", v->valeur.caractere);
            printf(" |\n");
        }
    }
}

void allouer_taille(int taille){
    var v = {NULL, -1, {0}};
    int i;

    for (int i = 0; i < taille; i++){
        empiler_pile_exec_variable(v);
    }
}