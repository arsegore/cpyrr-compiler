#include <stdlib.h>
#include <stdio.h>
#include "../inc/tab_decla.h"

/* a faire
   - chainage
   - champ execution, il faut la table des region, doit utiliser le NIS
   - gestion des suivants, pour l'instant je ne sais pas comment faire,
   ça demande d'avoir les noms/ lexeme mais je les ai po
   
*/

int premiere_ligne_libre_decla = DEBORDEMENT; // indice 1ere case LIBRE de la zone de debordementt
int tab_decla[HAUTEUR][LARGEUR]; 

void init_tab_decla(){
    int i, j;

    for(i = 0; i < HAUTEUR; i++){
        for(j = 0; j < LARGEUR; j++){   
            tab_decla[i][j] = -1;
        }
    }
}

void afficher_ligne(int num, int entete){
    int i;
    // En-tête du tableau
    if (entete) {
        printf("%-4s | %-8s | %-8s | %-8s | %-12s | %-10s |\n",
               "ID", "nature", "suivant", "region", "description", "execution");
        printf("------------------------------------------------------------------\n");
    }
    printf("%-4d | %-8d | %-8d | %-8d | %-12d | %-10d |\n",
            num,
            tab_decla[num][NATURE],
            tab_decla[num][SUIVANT],
            tab_decla[num][REGION],
            tab_decla[num][DESCRIPTION],
            tab_decla[num][EXECUTION]);
}
    
void afficher_tab_decla(){
    int i=0 ,j;

    printf("%-4s | %-8s | %-8s | %-8s | %-12s | %-10s |\n",
           "ID", "nature", "suivant", "region", "description", "execution");
    printf("------------------------------------------------------------------\n");
    while ((tab_decla[i][NATURE] != - 1) && i < DEBORDEMENT) { 
        afficher_ligne(i++, 0);
    }
    printf("-------------------------Zone de debordement----------------------\n");
    i = DEBORDEMENT;
    while (tab_decla[i][NATURE] != -1){
        afficher_ligne(i, 0);
        i++;
    }
}

void inserer_declaration(int num_lexico, int nature, int region){
    int i, indice;

    if (tab_decla[num_lexico][NATURE] != -1){
        i = num_lexico;
        while (tab_decla[i][SUIVANT] != -1) {
            i = tab_decla[i][SUIVANT];
        }
        
        indice = premiere_ligne_libre_decla++;
        tab_decla[i][SUIVANT] = indice; 
    } else {
        indice = num_lexico;
    }
   
    tab_decla[indice][NATURE] = nature;
    tab_decla[indice][REGION] = region;
    // TODO : insérer le reste
    
}
