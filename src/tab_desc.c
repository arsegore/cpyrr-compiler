#include "../inc/tab_desc.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * Implantation de la table de description des types et des en-têtes de
 * sous-programme
 *
 * Auteur: Adam 
 */
int tab_desc[1000];
int premiere_ligne_libre_desc = 0;

void init_tab_desc() {
    int i;

    for (i = 0; i < TAILLE_TAB_DESC; i++) {
        tab_desc[i] = -1;
    }
}

void afficher_tab_desc(int depart, int arrivee) {
    int i, j;

    if (depart == -1) {
        i = 0;
    } else {
        i = depart;
    }

    if (arrivee == -1) {
        j = TAILLE_TAB_DESC - 1;
    } else {
        j = arrivee;
    }

    printf("-----Table Desc-----\n");
    printf("| %4s | %10s | \n", "Id", "Valeur");
    printf("--------------------\n");
    for (; i <= j; i++) {
        printf("| %4d | %10d | \n",
            i,
            tab_desc[i]);
    }
    printf("\n");

}

/**
 * Diverses fonctions auxiliaires, mais seule l'interface
 * inserer_tab_desc() est publique (pour uniformiser l'écriture des
 * actions sémantiques
 */

int inserer_desc_fct(int type_ret, int nb_param, va_list parametres) {
    int depart = premiere_ligne_libre_desc;
    int courant = depart;
    int i;

    // TYPE RETOUR + NB_PARAM + 2 CASES PAR PARAM
    premiere_ligne_libre_desc += (1 + 1 + 2 * nb_param);
    tab_desc[courant++] = type_ret;
    tab_desc[courant++] = nb_param;
    for (i = 0; i < 2 * nb_param; i++) {
        tab_desc[courant++] = va_arg(parametres, int);
    }

    return depart;
}

int inserer_desc_proc(int nb_param, va_list parametres) {
    int depart = premiere_ligne_libre_desc;
    int courant = depart;
    int i;

    // NB_PARAM + 2 CASES PAR PARAM
    premiere_ligne_libre_desc += (1 + 2 * nb_param);
    tab_desc[courant++] = nb_param;
    for (i = 0; i < 2 * nb_param; i++) {
        tab_desc[courant++] = va_arg(parametres, int);
    }

    return depart;
}

int inserer_desc_tab(int type, int nb_dim, va_list bornes) {
    int depart = premiere_ligne_libre_desc;
    int courant = depart;
    int i;

    // TYPE + NB_DIM + 2 CASES PAR DIM (borne sup et borne inf)
    premiere_ligne_libre_desc += (1 + 2 * nb_dim);
    tab_desc[courant++] = type;
    tab_desc[courant++] = nb_dim;
    for (i = 0; i < 2 * nb_dim; i++) {
        tab_desc[courant++] = va_arg(bornes, int);
    }

    return depart;
}

int inserer_desc_struct(int nb_champs, va_list champs) {
    int depart = premiere_ligne_libre_desc;
    int courant = depart;
    int i;

    // TYPE + NB_DIM + 3 CASES PAR CHAMP (num_lex, type, exec)
    premiere_ligne_libre_desc += (1 + 3 * nb_champs);
    tab_desc[courant++] = nb_champs;
    for (i = 0; i < 3 * nb_champs; i++) {
        tab_desc[courant++] = va_arg(champs, int);
    }

    return depart;
}

int inserer_description(int type_desc, int nb, ...) {
    va_list args;
    va_start(args, nb);
    int num_desc = -1;
    int t;

    switch (type_desc) {
        case D_FCT:
            t = va_arg(args, int);
            num_desc = inserer_desc_fct(t, nb, args);
            break;
        case D_PROC:
            num_desc = inserer_desc_proc(nb, args);
            break;
        case D_STRUCT:
            num_desc = inserer_desc_struct(nb, args);
            break;
        case D_TAB:
            t = va_arg(args ,int);
            num_desc = inserer_desc_tab(t, nb, args);
        default:
            break;
    }

    return num_desc;
}
