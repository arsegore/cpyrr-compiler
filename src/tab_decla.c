#include "../inc/tab_decla.h"
#include <stdio.h>
#include <stdlib.h>

#include "../inc/tab_lexico.h"

/* a faire
   - chainage
   - champ execution, il faut la table des region, doit utiliser le NIS
*/

int premiere_ligne_libre_decla = DEBORDEMENT;
int tab_decla[HAUTEUR][LARGEUR];

void init_types_base() {
    inserer_declaration(inserer_lexeme("int"),
                        N_TYPE_B,
                        0);
    inserer_declaration(inserer_lexeme("float"),
                        N_TYPE_B,
                        0);
    inserer_declaration(inserer_lexeme("bool"),
                        N_TYPE_B,
                        0);
    inserer_declaration(inserer_lexeme("char"),
                        N_TYPE_B,
                        0);
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
        case N_FONC:      return "N_FONC";
        case N_CH_STRUCT: return "N_CH_STRUCT";

            // C'est une bonne pratique de gérer les cas inconnus
        default:          return "N_INCONNU";
    }
}

void afficher_ligne(int num, int entete) {
    int i;
    // En-tête du tableau
    if (entete) {
        printf("%-4s | %-13s | %-8s | %-8s | %-12s | %-10s |\n", "ID", "nature",
               "suivant", "region", "description", "execution");
        printf(
            "------------------------------------------------------------------"
            "\n");
    }
    printf("%-4d | %-12s | %-8d | %-8d | %-12d | %-10d |\n", num,
           string_nature(tab_decla[num][NATURE]), tab_decla[num][SUIVANT],
           tab_decla[num][REGION], tab_decla[num][DESCRIPTION],
           tab_decla[num][EXECUTION]);
}

void afficher_tab_decla() {
    int i = 0, j;

    printf("%-4s | %-12s | %-8s | %-8s | %-12s | %-10s |\n", "ID", "nature",
           "suivant", "region", "description", "execution");
    printf(
        "------------------------------------------------------------------\n");
    while ((tab_decla[i][NATURE] != -1) && i < DEBORDEMENT) {
        afficher_ligne(i++, 0);
    }
    printf(
        "-------------------------Zone de debordement----------------------\n");
    i = DEBORDEMENT;
    while (tab_decla[i][NATURE] != -1) {
        afficher_ligne(i, 0);
        i++;
    }
}

void inserer_declaration(int num_lexico, int nature, int region) {
    int i, indice;

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
    // TODO : insérer le reste
}
