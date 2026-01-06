#include <stdio.h>
#include <stdlib.h>

#include "association_noms/association_noms.h"
#include "tables/tab_decla.h"
#include "tables/tab_lexico.h"

/**
 * Auteur: Paul RODRIGUES
 */

// NOTE : il faut aussi se servir de la pile des régions, voir notes tp
#include "tables/pile_regions.h"

/*
Probleme : si on imagine 2 variable x déclaree comme des INT, on recuperera toujours la premiere alors qu'on voulait peut-etre la 2eme
Solution? : parem en + pour différencier?
Est-ce vraiment un probleme?
*/

int association_noms(int num_lex, int nature) {
    int i,              /* pour parcourir la table des decla */
        j = 1,          /* pour simuler le depilement */
        asso_ok = 0,    /* indicateur de succès */
        s;              /* le sommet de pile courant */

    while (asso_ok == 0 && j <= nb_regions_pile) {
        
        s = pile_regions[nb_regions_pile - j];
        i = num_lex;

        while (i != -1) {
            if (tab_decla[i][REGION] == s) {

                if (nature == N_VAR) {
                    if (tab_decla[i][NATURE] == N_VAR || tab_decla[i][NATURE] == N_PARAM) {
                        asso_ok = 1;
                        break;
                    }
                } else if (tab_decla[i][NATURE] == nature) {
                    asso_ok = 1;
                    break;
                }
                
                if (tab_decla[i][NATURE] == nature) {
                    asso_ok = 1;
                    break; 
                }

                if (nature == TYPE && (tab_decla[i][NATURE] == N_STRUCT || tab_decla[i][NATURE] == N_TAB)) {
                    asso_ok = 1;
                    break;
                }
            }
            
            i = tab_decla[i][SUIVANT];
        }

        if (!asso_ok) {
            j++;
        }
    }

    if (asso_ok) return i;
    return -1;
}