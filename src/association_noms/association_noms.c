#include <stdio.h>
#include <stdlib.h>

#include "association_noms/association_noms.h"
#include "tables/tab_decla.h"
#include "tables/tab_lexico.h"

/**
 * Auteur: Paul 
 */

// NOTE : il faut aussi se servir de la pile des régions, voir notes tp
#include "tables/pile_regions.h"

/*
Probleme : si on imagine 2 variable x déclaree comme des INT, on recuperera toujours la premiere alors qu'on voulait peut-etre la 2eme
Solution? : parem en + pour différencier?
Est-ce vraiment un probleme?
*/

int association_noms(int num_lex, int nature){
    int i = num_lex,    /* pour parcourir la table des decla */
        j = 1,          /* servira a simuler le depilement */
        asso_ok = 0,    /* pour savoir si j'ai bien trouve l'association */
        s;              /* le sommet de pile */


    while (asso_ok == 0 && j <= nb_regions_pile){

        /* je regarde le sommet de pile, j permet de simuler le depilement */
        s = pile_regions[nb_regions_pile - j++];
        printf("Sommet de pile = %d\n", s);

        /* une fois le sommet identifie je parcours la table des declarations en utilisant le num lexico jusqu'a trouver la bonne declaration */
        while (tab_decla[i][REGION] != s && tab_decla[i][SUIVANT] != -1){
            printf("   val region pour i = %d : %d\n", i, tab_decla[i][REGION]);
            i = tab_decla[i][SUIVANT];
            printf("   suivant =  %d\n", tab_decla[i][SUIVANT]);
        }

        /* je verifie que la nature de la decla correspond a la nature recherchee */

        // Cas geneal
        if (tab_decla[i][NATURE] == nature){
            asso_ok = 1;
        }

        // Cas Tab ou Struct (Appel avec TYPE)
        if (nature == TYPE
            && (tab_decla[i][NATURE] == N_STRUCT
                || tab_decla[i][NATURE] == N_TAB)){

            asso_ok = 1;
        }
    }

    if (asso_ok) return i;
    return -1;
}