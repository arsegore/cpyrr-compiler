#include <stdio.h>
#include <stdlib.h>

#include "association_noms/association_noms.h"
#include "tables/tab_decla.h"
#include "tables/tab_lexico.h"
#include "tables/pile_regions.h"

/**
 * Auteur: Paul RODRIGUES
 */

int association_noms(int num_lex, int nature){
    int i = num_lex,    /* pour parcourir la table des decla */
        j = 1,          /* servira a simuler le depilement */
        asso_ok = 0,    /* pour savoir si j'ai bien trouve l'association */
        s;              /* le sommet de pile */


    while (asso_ok == 0 && j <= nb_regions_pile){

        /* je regarde le sommet de pile, j permet de simuler le depilement */
        s = pile_regions[nb_regions_pile - j++];

        /* une fois le sommet identifie je parcours la table des declarations en utilisant le num lexico jusqu'a trouver la bonne declaration */
        while (tab_decla[i][REGION] != s && tab_decla[i][SUIVANT] != -1){
            i = tab_decla[i][SUIVANT];
        }

        /* je verifie que la nature de la decla correspond a la nature recherchee */
        if (tab_decla[i][NATURE] == nature){
            asso_ok = 1;
        }
    }

    return i;
}