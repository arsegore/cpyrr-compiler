#include <stdio.h>
#include <stdlib.h>
#include "../../inc/arbre/arbre.h"

/**
 * Auteur : GRANJON Damien
 */

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

void afficher_arbre_rec(arbre a, const char *prefixe, int is_last) {
    char nouveau_prefixe[1024];
    arbre fils = a->fils_gauche;

    if (a == NULL) {
        return;
    }

    // Affiche le préfixe et la branche
    printf("%s", prefixe);
    printf("%s", is_last ? "└── " : "├── ");

    // Affiche le contenu du noeud
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
    snprintf(nouveau_prefixe, sizeof(nouveau_prefixe), "%s%s", prefixe, is_last ? "    " : "│   ");

    // Parcourt les fils
    while (fils) {
        afficher_arbre_rec(fils, nouveau_prefixe, fils->frere_droit == NULL);
        fils = fils->frere_droit;
    }
}

void afficher_arbre(arbre a) {
    arbre fils = a->fils_gauche;
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
            v = execute_arbre_fct(a); // fct à faire
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
        case A_MOD:
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
        case A_MOD:
            evalue_arbre_int(a->fils_gauche) % evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
    }
}