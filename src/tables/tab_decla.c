#include <stdio.h>
#include <stdlib.h>

#include "tables/tab_lexico.h"
#include "tables/tab_decla.h"


/* a faire
   - chainage
   - champ execution, il faut la table des region, doit utiliser le NIS
*/

int premiere_ligne_libre_decla = DEBORDEMENT;
int tab_decla[HAUTEUR][LARGEUR];

void init_types_base() {
    inserer_declaration(inserer_lexeme("int", 3),
                        N_TYPE_B,
                        0,
                        -1);
    inserer_declaration(inserer_lexeme("float", 5),
                        N_TYPE_B,
                        0,
                        -1);
    inserer_declaration(inserer_lexeme("bool", 4),
                        N_TYPE_B,
                        0,
                        -1);
    inserer_declaration(inserer_lexeme("char", 4),
                        N_TYPE_B,
                        0,
                        -1);
}

void init_tab_decla() {
    int i, j;

    for (i = 0; i < HAUTEUR; i++) {
        for (j = 0; j < LARGEUR; j++) {
            tab_decla[i][j] = -1;
        }
    }
    init_types_base();
}

/**
 * Ne sert qu'à avoir un meilleur affichage
 *
 * @param nature
 * @return La chaîne correspondante à la nature
 */
const char* string_nature(int nature) {
    switch (nature) {
        case N_TYPE_B:    return "N_TYPE_B";
        case N_STRUCT:    return "N_STRUCT";
        case N_TAB:       return "N_TAB";
        case N_VAR:       return "N_VAR";
        case N_PARAM:     return "N_PARAM";
        case N_PROC:      return "N_PROC";
        case N_FCT:      return "N_FONC";
        case N_CH_STRUCT: return "N_CH_STRUCT";
        case N_ARG:     return "N_ARG";
        default:          return "N_INCONNU";
    }
}

void afficher_ligne(int num, int entete) {
    int i;
    // En-tête du tableau
    if (entete) {
        printf("| %4s | %13s | %8s | %8s | %12s | %10s |\n", "ID", "nature",
               "suivant", "region", "description", "execution");
        printf(
            "-----------------------------------------------------------------------"
            "\n");
    }
    printf("| %4d | %12s | %8d | %8d | %12d | %10d |\n", num,
           string_nature(tab_decla[num][NATURE]), tab_decla[num][SUIVANT],
           tab_decla[num][REGION], tab_decla[num][DESCRIPTION],
           tab_decla[num][EXECUTION]);
}

void afficher_tab_decla() {
    int i = 0, j;
    printf(
        "---------------------------Table des déclarations-----------------------\n");
    printf("| %4s | %12s | %8s | %8s | %12s | %10s |\n", "ID", "nature",
           "suivant", "region", "description", "execution");
    printf(
        "------------------------------------------------------------------------\n");
    while ((tab_decla[i][NATURE] != -1) && i < DEBORDEMENT) {
        afficher_ligne(i++, 0);
    }
    printf(
        "----------------------------Zone de debordement-------------------------\n");
    i = DEBORDEMENT;
    while (tab_decla[i][NATURE] != -1) {
        afficher_ligne(i, 0);
        i++;
    }
    printf("\n");
}

void inserer_declaration(int num_lexico, int nature, int region, int description) {
    int i, indice, exec;

    if (tab_decla[num_lexico][NATURE] != -1) {
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
    tab_decla[indice][DESCRIPTION] = description;
    
    switch (nature){

        // exec = taille à l'exécution d'une valeur de ce type (en tenant compte qu'il s'agit d'une machine C, cf ci-dessous).
        // fonction taille_type?
    case N_STRUCT : exec = -1; break;
    case N_TAB    : exec = -1; break;

        // exec = déplacement à l'exécution, de l'emplacement associé à la variable ou du paramètre dans la zone de données correspondante.
        // variable deplacement?
    case N_VAR    : exec = -1; break;
    case N_PARAM  : exec = -1; break;
        
        // exec = num de region
    case N_PROC   : exec = region; break;
    case N_FCT    : exec = region; break;
    }
    
    tab_decla[indice][EXECUTION] = exec;
    // TODO : insérer le reste
}
