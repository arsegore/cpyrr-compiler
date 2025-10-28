#include <stdlib.h>
#include <stdio.h>
#include "../inc/tab_decla.h"

/* a faire
   - chainage
   - champ execution, il faut la table des region, doit utiliser le NIS
   - gestion des suivants, pour l'instant je ne sais pas comment faire,
   ça demande d'avoir les noms/ lexeme mais je les ai po
   
*/

// mise a -1 /!\ attention penser si des valeurs negatives peuvent exister
// tout definir a -1 ou juste juqu'a n ? 
void initialiser(table_decl table, int n){
    int i, j;

    for(i = 0; i < n; i++){
        for(j = 0; j < 5; j++){   
            table[i][j] = -1;
        }
    }
}

// affiche tous les champs d'une ligne passé en parametre
void modifier_champ(table_decl table, int ligne, int colonne, int val){
    table[ligne][colonne] = val;
}

void afficher_element(table_decl table, int ligne){
    int i;
    // En-tête du tableau
    printf("%-3s | %-8s | %-8s | %-8s | %-12s | %-10s |\n",
           "ID", "nature", "suivant", "region", "description", "execution");
    printf("------------------------------------------------------------------\n");

    printf("%-3d | ",ligne);
    for(i = 0; i < 3; i++){
        printf("%-8d | ",table[ligne][i]);
    }
    printf("%-12d | ",table[ligne][3]);
    printf("%-10d | ",table[ligne][4]);
    printf("\n");
}
    
void affichage(table_decl table, int n){
    int i,j;

    // En-tête du tableau
    printf("%-3s | %-8s | %-8s | %-8s | %-12s | %-10s |\n",
           "ID", "nature", "suivant", "region", "description", "execution");
    printf("------------------------------------------------------------------\n");

    
    for(i = 0; i < n; i++){
        printf("%-3d | ", i);
        for(j = 0; j < 3; j++){
            printf("%-8d | ",table[i][j]);
        }
        printf("%-12d | ",table[i][3]);
        printf("%-10d | ",table[i][4]);
        printf("\n");
    }
}

// prends la nature en entrée, le numero de region
void ajouter_element(table_decl table, int nature, int region){
    int i;

    // on cherche l'incide juste après le dernier ajouter
    while(table[i][0] != -1){
        i++;
    }
    // on met la nature dans le champ 0
    table[i][0] = nature;
    table[i][1] = -1; // avoir une fct chainage ? si il est le premier laisser -1 ?
    table[i][2] = region;
    table[i][3] = -1; // avoir les index des declaration de type, entete machin chouettea
    table[i][4] = -1; // ppir l'instant aucune idee de lexec
    
}

    
