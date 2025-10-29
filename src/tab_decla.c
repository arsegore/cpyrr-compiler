#include <stdlib.h>
#include <stdio.h>
#include "../inc/tab_decla.h"
#include "../inc/tab_lexico.h"

/* a faire
   - chainage
   - champ execution, il faut la table des region, doit utiliser le NIS
   - gestion des suivants, pour l'instant je ne sais pas comment faire,
   ça demande d'avoir les noms/ lexeme mais je les ai po
   
*/

int i_deb = DEBORDEMENT; // indice 1ere case LIBRE de la zone de debordement

// mise a -1 /!\ attention penser si des valeurs negatives peuvent exister
// tout definir a -1 ou juste juqu'a n ? 
void initialiser(table_decl table){
    int i, j;

    for(i = 0; i < HAUTEUR; i++){
        for(j = 0; j < LARGEUR; j++){   
            table[i][j] = -1;
        }
    }
}

// affiche tous les champs d'une ligne passé en parametre
void modifier_champ(table_decl table, int ligne, int colonne, int val){

    // Cas d'erreur
    if (ligne >= HAUTEUR || colonne >= LARGEUR){
        printf("Erreur, tentative de modifier un champ non defini\n");
        return;
    }
    
    table[ligne][colonne] = val;
}

void afficher_element(table_decl table, int ligne){
    int i;
    // En-tête du tableau
    printf("%-4s | %-8s | %-8s | %-8s | %-12s | %-10s |\n",
           "ID", "nature", "suivant", "region", "description", "execution");
    printf("------------------------------------------------------------------\n");

    printf("%-4d | ",ligne);
    for(i = 0; i < 3; i++){
        printf("%-8d | ",table[ligne][i]);
    }
    printf("%-12d | ",table[ligne][3]);
    printf("%-10d | ",table[ligne][4]);
    printf("\n");
}
    
void affichage(table_decl table){
    int i=0 ,j;

    // En-tête du tableau
    printf("%-4s | %-8s | %-8s | %-8s | %-12s | %-10s |\n",
           "ID", "nature", "suivant", "region", "description", "execution");
    printf("------------------------------------------------------------------\n");

    // Affichage table des déclarations
    while (table[i][0] != -1){
        printf("%-4d | ", i);
        for(j = 0; j < 3; j++){
            printf("%-8d | ",table[i][j]);
        }
        printf("%-12d | ",table[i][3]);
        printf("%-10d | ",table[i][4]);
        printf("\n");
        i++;
    }

    // Affichage zone de debordement
    printf("-------------------------Zone de debordement----------------------\n");
    i = DEBORDEMENT;
    while (table[i][0] != -1){
        printf("%-4d | ", i);
        for(j = 0; j < 3; j++){
            printf("%-8d | ",table[i][j]);
        }
        printf("%-12d | ",table[i][3]);
        printf("%-10d | ",table[i][4]);
        printf("\n");
        i++;
    }
}

// prends la nature en entrée, le numero de region
void ajouter_element(table_decl table, char *lexeme, int nature, int region){
    int i;

    // on verifie si c'est la 1ere declaration du lexeme
    i = recuperer_num_lexico(lexeme); // recup_num_lex() a definir

    // si 1ere declaration on declare dans la case correspondant au num lex sinon on déclare dans la 1ere case de la zone de debordement
    if (table[i][0] != -1){
        // on parcours la chaine des suivants jusqu'a trouver la derniere declaration
        while (table[i][1] != -1){
            i = table[i][1];
        }
        table[i][1] = i_deb; // le suivant du dernier element de la chaine devient l'indice de la nouvelle declaration
        i = i_deb;
    }
    
    // on cherche l'indice juste après le dernier ajoute
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
    
int main(){
    table_decl t;

    initialiser(t);
    init_tab_lexico();

    inserer_lexeme("a");
    inserer_lexeme("b");
    inserer_lexeme("c");
    
    ajouter_element(t, "a", N_TAB, 1);
    ajouter_element(t, "b", N_TAB, 2);
    ajouter_element(t, "c", N_TAB, 3);
    ajouter_element(t, "c", N_TAB, 4);
    ajouter_element(t, "a", N_TAB, 5);
    ajouter_element(t, "b", N_TAB, 6);
    ajouter_element(t, "c", N_TAB, 7);
    ajouter_element(t, "a", N_TAB, 8);

    affichage(t);

    

    
    
    
    return 1;
}