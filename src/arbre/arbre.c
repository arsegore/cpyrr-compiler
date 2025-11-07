#include <stdio.h>
#include <stdlib.h>
#include "../../inc/arbre/arbre.h"

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

    // Racine de l’arbre
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

    // On appelle la récursion pour tous les fils de la racine
    arbre fils = a->fils_gauche;
    while (fils) {
        afficher_arbre_rec(fils, "", fils->frere_droit == NULL);
        fils = fils->frere_droit;
    }
}


int main() {
    arbre a1 = creer_noeud(A_AFFECT, 0);
    arbre a2 = creer_noeud(A_IDF, 1);
    arbre a3 = creer_noeud(A_PLUS, 0);
    arbre a4 = creer_noeud(A_CSTE_ENTIERE, 2);
    arbre a5 = creer_noeud(A_CSTE_ENTIERE, 3);

    // Construction de l’arbre :
    concat_pere_fils(a1, a2);          // a1 -> a2
    concat_pere_frere(a2, a3);         // a2 -> a3
    concat_pere_fils(a3, a4);          // a3 -> a4
    concat_pere_frere(a4, a5);         // a4 -> a5

    printf("a1->fils_gauche = %p\n", (void*)a1->fils_gauche);
    printf("a2->frere_droit = %p\n", (void*)a2->frere_droit);
    printf("a3->fils_gauche = %p\n", (void*)a3->fils_gauche);
    printf("a4->frere_droit = %p\n", (void*)a4->frere_droit);
    return 0;
}