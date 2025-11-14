#include <stdio.h>
#include <stdlib.h>
#include "../../inc/arbre/arbre.h"

/**
 * Auteur : Damien 
 */

/*
struct noeud {
    int nature;
    int valeur;
    struct noeud *fils_gauche;
    struct noeud *frere_droit;
};
typedef struct noeud *arbre;*/

arbre concat_pere_fils(arbre pere, arbre fils) {
    pere->fils_gauche = fils;
    return pere;
}

arbre concat_pere_frere(arbre pere, arbre frere) {
    pere->frere_droit = frere;
    return pere;
}

arbre creer_noeud(int nature, int valeur) {
    arbre a = NULL;
    if ((a = (arbre) malloc(sizeof(noeud))) == NULL) {
        printf("Erreur d'allocation.\n");
        exit(EXIT_FAILURE);
    }
    a->nature = nature;
    a->valeur = valeur;
    a->fils_gauche = NULL;
    a->frere_droit = NULL;
    return a;
}

void afficher_arbre_rec(arbre a, const char *prefix, int is_last) {
    if (a == NULL)
        return;

    // Affiche le préfixe et la branche
    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");

    // Affiche le contenu du nœud
    switch (a->nature) {
        case A_IDF: printf("IDF (%d)\n", a->valeur); break;
        case A_CSTE_ENTIERE: printf("CSTE_ENTIERE (%d)\n", a->valeur); break;
        case A_AFFECT: printf("AFFECT\n"); break;
        case A_PLUS: printf("PLUS\n"); break;
        case A_MOINS: printf("MOINS\n"); break;
        case A_MULT: printf("MULT\n"); break;
        case A_DIV: printf("DIV\n"); break;
        default: printf("INCONNU (%d)\n", a->valeur); break;
    }

    // Nouveau préfixe pour les fils
    char new_prefix[1024];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    // Parcourt les fils (le premier, puis ses frères)
    arbre fils = a->fils_gauche;
    while (fils) {
        afficher_arbre_rec(fils, new_prefix, fils->frere_droit == NULL);
        fils = fils->frere_droit;
    }
}

void afficher_arbre(arbre a) {
    if (a == NULL) {
        printf("(arbre vide)\n");
        return;
    }

    // Racine de l'arbre
    printf("└── ");
    switch (a->nature) {
        case A_IDF: printf("IDF (%d)\n", a->valeur); break;
        case A_CSTE_ENTIERE: printf("CSTE_ENTIERE (%d)\n", a->valeur); break;
        case A_AFFECT: printf("AFFECT\n"); break;
        case A_PLUS: printf("PLUS\n"); break;
        case A_MOINS: printf("MOINS\n"); break;
        case A_MULT: printf("MULT\n"); break;
        case A_DIV: printf("DIV\n"); break;
        default: printf("INCONNU (%d)\n", a->valeur); break;
    }

    // On appelle la récursion pour tous les fils de la racine avec le bon préfixe
    arbre fils = a->fils_gauche;
    while (fils) {
        afficher_arbre_rec(fils, "    ", fils->frere_droit == NULL);
        fils = fils->frere_droit;
    }
}

void execute_arbre(arbre a) {
    int i, v;
    switch (a->nature) {
        case A_OPAFF:
            i = recuperer_case_variable(a->fils_gauche); // fct à faire
            v = evalue_arbre_int(a->fils_gauche->frere_droit);
            stocker_pile_donnees(i, v); // fct à faire
            break;
        case A_APPEL_PROC:
            // gerer pile (mise en place de "pointeurs")
            execute_arbre(a);
            // gerer pile
            break;
        case A_APPEL_FCT:
            // gerer pile
            v = execute_arbre_fct(a);
            // gerer pile
            break;
        case A_LISTE_I:
            execute_arbre(a->fils_gauche);
            execute_arbre(a->fils_gauche->frere_droit);
            break;
        case A_IDF:
        case A_CSTE_ENTIERE:
        case A_AFFECT:
        case A_PLUS:
        case A_MOINS:
        case A_MULT:
        case A_DIV:
    }
}

int evalue_arbre_int(arbre a) {
    int i;
    switch (a->nature) {
        case A_IDF:
            i = recuperer_case_variable(a); // fct à faire
            return (valeur_pile(i)); // fct à faire
            break;
        case A_CSTE_ENTIERE:
            return a->valeur;
            break;
        case A_PLUS:
            evalue_arbre_int(a->fils_gauche) + evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
        case A_MOINS:
            evalue_arbre_int(a->fils_gauche) - evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
        case A_MULT:
            evalue_arbre_int(a->fils_gauche) * evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
        case A_DIV:
            evalue_arbre_int(a->fils_gauche) / evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
    }
}