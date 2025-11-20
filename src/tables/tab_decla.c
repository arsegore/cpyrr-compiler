#include <stdio.h>
#include <stdlib.h>

#include "tables/tab_lexico.h"
#include "tables/tab_decla.h"
#include "tables/tab_rep.h"
#include "tables/pile_regions.h"

/* a faire
   - chainage
   - champ execution, il faut la table des region, doit utiliser le NIS
*/

int premiere_ligne_libre_decla = DEBORDEMENT;
int tab_decla[HAUTEUR][LARGEUR];
int decla_courante = -1;

void init_types_base() {
    determiner_ligne_decla(inserer_lexeme("int", 3));
    remplir_nature(decla_courante, N_TYPE_B);
    remplir_desc(decla_courante, -1);
    remplir_region(decla_courante, 0);
    

    determiner_ligne_decla(inserer_lexeme("float", 3));
    remplir_nature(decla_courante, N_TYPE_B);
    remplir_desc(decla_courante, -1);
    remplir_region(decla_courante, 0);

    determiner_ligne_decla(inserer_lexeme("bool", 3));
    remplir_nature(decla_courante, N_TYPE_B);
    remplir_desc(decla_courante, -1);
    remplir_region(decla_courante, 0);

    determiner_ligne_decla(inserer_lexeme("char", 3));
    remplir_nature(decla_courante, N_TYPE_B);
    remplir_desc(decla_courante, -1);
    remplir_region(decla_courante, 0);

    for(int i = 0; i < 4; i++){
        tab_decla[i][EXECUTION] = 1;
    }
    
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
    while (i < DEBORDEMENT && (tab_decla[i][NATURE] != -1)) {
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

void determiner_ligne_decla(int num_lexico){
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

    decla_courante = indice;
}

void remplir_nature(int num_decla, int nature){
    tab_decla[num_decla][NATURE] = nature;
}

void remplir_region(int num_decla, int region){
    tab_decla[num_decla][REGION] = region;
}

void remplir_desc(int num_decla, int desc){
    tab_decla[num_decla][DESCRIPTION] = desc;
}

void remplir_exec(int num_decla){
    int nature = tab_decla[num_decla][NATURE];
    switch(nature){
    case 1:
    case 2:
        tab_decla[num_decla][EXECUTION] = taille_type(num_decla);
        break;
    case 3:
    case 4:
        tab_decla[num_decla][EXECUTION] = deplacement;
        break;
    case 5:
    case 6:
        tab_decla[num_decla][EXECUTION] = num_region_courante;
        break;
    }
}

int taille_type(int num_type){
    int nature = tab_decla[num_type][NATURE];
    int acc = 0, i,
        commencement = tab_decla[num_type][DESCRIPTION],
        nb_champs = tab_rep[commencement];
    if(nature == N_TYPE_B){
        return 1;
    }

    switch(nature){
    case N_STRUCT:
        for(i = commencement+2; i < commencement+(nb_champs * 3); i +=3){
            acc += tab_decla[tab_rep[i]][EXECUTION];
        }
        break;

    case N_TAB:
        nb_champs = tab_rep[commencement+1];
        acc = tab_decla[tab_rep[commencement+1]][EXECUTION];
        for(i = commencement+3; i <= commencement+3+(nb_champs); i+=2){
            printf("on passe %d fois\n",i);
            acc*= tab_rep[i];
        }
        break;

    case N_VAR:
        acc = tab_decla[tab_rep[commencement]][EXECUTION];
        break;

    case N_PARAM:
         printf("on passe la ?4\n");
        acc = tab_decla[tab_rep[commencement]][EXECUTION];
        break;
    }
    return acc;

}