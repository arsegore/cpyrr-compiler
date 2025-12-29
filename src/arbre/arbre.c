#include <stdio.h>
#include <stdlib.h>
#include "arbre/arbre.h"
#include "tables/tab_lexico.h"
#include "tables/tab_decla.h"
#include "association_noms/association_noms.h"
#include "verif_sem/verif_sem.h"

// Macros pour les couleurs de texte
#define RESET   "\x1B[0m"
#define ROUGE   "\x1B[31m"
#define VERT    "\x1B[32m"
#define JAUNE   "\x1B[33m"
#define BLEU    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define BLANC   "\x1B[37m"

// Macros pour mettre en gras
#define GRAS    "\x1B[1m"


/**
 * Auteurs : TAD : Damien 
 *           Génération : Adam 
 */

arbre concat_pere_fils(arbre pere, arbre fils) {
    pere->fils_gauche = fils;
    return pere;
}

arbre concat_pere_frere(arbre pere, arbre frere) {
    pere->frere_droit = frere;
    return pere;
}

arbre creer_noeud(int nature, int valeur, int decla) {
    arbre a = NULL;
    if ((a = (arbre) malloc(sizeof(noeud))) == NULL) {
        printf("Erreur d'allocation.\n");
        exit(EXIT_FAILURE);
    }
    a->nature = nature;
    a->valeur = valeur;
    a->decla = decla;
    a->fils_gauche = NULL;
    a->frere_droit = NULL;
    return a;
}

// void afficher_arbre_rec(arbre a, const char *prefixe, int is_last) {
//     char nouveau_prefixe[1024];
//     arbre fils = a->fils_gauche;

//     if (a == NULL) {
//         return;
//     }

//     // Affiche le préfixe et la branche
//     printf("%s", prefixe);
//     printf("%s", is_last ? "└── " : "├── ");

//     // Affiche le contenu du noeud
//     switch (a->nature) {
//         case A_IDF:             printf("IDF (%d)\n", a->valeur); break;
//         case A_CSTE_ENTIERE:    printf("CSTE_ENTIERE (%d)\n", a->valeur); break;
//         case A_AFFECT:          printf("AFFECT\n"); break;
//         case A_PLUS:            printf("PLUS\n"); break;
//         case A_MOINS:           printf("MOINS\n"); break;
//         case A_MULT:            printf("MULT\n"); break;
//         case A_DIV:             printf("DIV\n"); break;
//         case A_MOD:             printf("MOD\n"); break;
//         default:                printf("INCONNU (%d)\n", a->valeur); break;
//     }

//     // Nouveau préfixe pour les fils
//     snprintf(nouveau_prefixe, sizeof(nouveau_prefixe), "%s%s", prefixe, is_last ? "    " : "│   ");

//     // Parcourt les fils
//     while (fils) {
//         afficher_arbre_rec(fils, nouveau_prefixe, fils->frere_droit == NULL);
//         fils = fils->frere_droit;
//     }
// }

// void afficher_arbre(arbre a) {
//     arbre fils = a->fils_gauche;
//     if (a == NULL) {
//         printf("(arbre vide)\n");
//         return;
//     }

//     // Racine de l'arbre
//     printf("└── ");
//     switch (a->nature) {
//         case A_IDF:             printf("IDF (%d)\n", a->valeur); break;
//         case A_CSTE_ENTIERE:    printf("CSTE_ENTIERE (%d)\n", a->valeur); break;
//         case A_AFFECT:          printf("AFFECT\n"); break;
//         case A_PLUS:            printf("PLUS\n"); break;
//         case A_MOINS:           printf("MOINS\n"); break;
//         case A_MULT:            printf("MULT\n"); break;
//         case A_DIV:             printf("DIV\n"); break;
//         case A_MOD:             printf("MOD\n"); break;
//         default:                printf("INCONNU (%d)\n", a->valeur); break;
//     }

//     // On appelle la récursion pour tous les fils de la racine avec le bon préfixe
//     while (fils) {
//         afficher_arbre_rec(fils, "    ", fils->frere_droit == NULL);
//         fils = fils->frere_droit;
//     }
// }

void afficher_nat_noeud(arbre a){
    printf("(" CYAN GRAS);
    switch (a->nature) {
        case A_IDF:             printf("A_IDF"); break;
        case A_CSTE_ENTIERE:    printf("A_CSTE_ENTIERE"); break;
        case A_CSTE_REELLE:     printf("A_CSTE_REELLE"); break;
        case A_CSTE_BOOL:       printf("A_CSTE_BOOL"); break;
        case A_AFFECT:          printf("A_AFFECT"); break;
        case A_ACCES_TAB:       printf("A_ACCES_TAB"); break;
        case A_ACCES_STRUCT:    printf("A_ACCES_STRUCT"); break;
        case A_PLUS:            printf("A_PLUS"); break;
        case A_MOINS:           printf("A_MOINS"); break;
        case A_MULT:            printf("A_MULT"); break;
        case A_DIV:             printf("A_DIV"); break;
        case A_MOD:             printf("A_MOD"); break;
        case A_ET:              printf("A_ET"); break;
        case A_OU:              printf("A_OU"); break;
        case A_SUP:             printf("A_SUP"); break;
        case A_SUPEGAL:         printf("A_SUPEGAL"); break;
        case A_INF:             printf("A_INF"); break;
        case A_INFEGAL:         printf("A_INFEGAL"); break;
        case A_DIFF:            printf("A_DIFF"); break;
        case A_EGAL:            printf("A_EGAL"); break;
        case A_SI_ALORS:        printf("A_SI_ALORS"); break;
        case A_SI_ALORS_SINON:  printf("A_SI_ALORS_SINON"); break;
        case A_LISTE_I:         printf("A_LISTE_I"); break;
        case A_LISTE_DIM:       printf("A_LISTE_ACCES_DIM"); break;
        case A_LISTE_ARG:       printf("A_LISTE_ARG"); break;
        case A_APPEL_PROC:      printf("A_APPEL_PROC"); break;
        case A_APPEL_FCT:       printf("A_APPEL_FCT"); break;
        case A_RET:             printf("A_RET"); break;
        default:                printf("A_INCONNU"); break;
    }
    printf(RESET ")[" MAGENTA"%d" RESET "][" VERT"%d" RESET"]\n", a->valeur, a->decla);
}

void afficher_arbre_aux(arbre a, int dec){
    int i;
    if (a == NULL){
        return;
    }

    for (i = 0; i < dec; i++){
        printf(" |   ");
    }
    
    afficher_nat_noeud(a);

    afficher_arbre_aux(a->fils_gauche, dec + 1);
    afficher_arbre_aux(a->frere_droit, dec);
}

void afficher_arbre(arbre a){
    afficher_arbre_aux(a, 0);
}

void execute_arbre(arbre a) {
    int i, v;
    switch (a->nature) {
        
        case A_IDF:
            break;
        case A_CSTE_ENTIERE:
            break;
        case A_CSTE_BOOL:
            break;
        case A_CSTE_CHAINE:
            break;
        case A_CSTE_CHAR:
            break;
        case A_CSTE_REELLE:
            break;

        case A_AFFECT:
            //i = recuperer_case_variable(a->fils_gauche); // fct à faire
            v = evalue_arbre_int(a->fils_gauche->frere_droit);
            //stocker_pile_donnees(i, v); // fct à faire
            break;
        case A_PLUS:
            break;
        case A_MOINS:
            break;
        case A_MULT:
            break;
        case A_DIV:
            break;
        case A_MOD:
            break;

        case A_RIEN:
            break;

        case A_APPEL_PROC:
            // gerer pile (mise en place de "pointeurs")
            execute_arbre(a);
            // gerer pile
            break;
        case A_APPEL_FCT:
            // gerer pile
            //v = execute_arbre_fct(a); // fct à faire
            // gerer pile
            break;
        // normalement on aura pas ça :
        /* case A_RET:
            break;*/
        // vu qu'on est pas dans une fonction

        case A_LISTE_I:
            execute_arbre(a->fils_gauche);
            execute_arbre(a->fils_gauche->frere_droit);
            break;

        case A_TANT_QUE:
            break;
        case A_SI_ALORS_SINON:
            break;

        case A_ET:
            break;
        case A_OU:
            break;
        case A_NON:
            break;
        case A_EGAL:
            break;
        case A_DIFF:
            break;
        case A_INF:
            break;
        case A_SUP:
            break;
        case A_INFEGAL:
            break;
        case A_SUPEGAL:
            break;

    }
}

int evalue_arbre_int(arbre a) {
    int i;
    switch (a->nature) {

        case A_IDF:
            //i = recuperer_case_variable(a); // fct à faire
            //return (valeur_pile(i)); // fct à faire
            break;

        case A_CSTE_ENTIERE:
            return a->valeur;
            break;

        case A_PLUS:
            return evalue_arbre_int(a->fils_gauche) + evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
        case A_MOINS:
            return evalue_arbre_int(a->fils_gauche) - evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
        case A_MULT:
            return evalue_arbre_int(a->fils_gauche) * evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
        case A_DIV:
            return evalue_arbre_int(a->fils_gauche) / evalue_arbre_int(a->fils_gauche->frere_droit);
            break;
        case A_MOD:
            return evalue_arbre_int(a->fils_gauche) % evalue_arbre_int(a->fils_gauche->frere_droit);
            break;

        case A_EGAL:
            if (evalue_arbre_int(a->fils_gauche) == evalue_arbre_int(a->fils_gauche->frere_droit)) {
                return 1;
            }
            return 0;
            break;
        case A_DIFF:
            if (evalue_arbre_int(a->fils_gauche) != evalue_arbre_int(a->fils_gauche->frere_droit)) {
                return 1;
            }
            return 0;
            break;
        case A_INF:
            if (evalue_arbre_int(a->fils_gauche) < evalue_arbre_int(a->fils_gauche->frere_droit)) {
                return 1;
            }
            return 0;
            break;
        case A_SUP:
            if (evalue_arbre_int(a->fils_gauche) > evalue_arbre_int(a->fils_gauche->frere_droit)) {
                return 1;
            }
            return 0;
            break;
        case A_INFEGAL:
            if (evalue_arbre_int(a->fils_gauche) <= evalue_arbre_int(a->fils_gauche->frere_droit)) {
                return 1;
            }
            return 0;
            break;
        case A_SUPEGAL:
            if (evalue_arbre_int(a->fils_gauche) >= evalue_arbre_int(a->fils_gauche->frere_droit)) {
                return 1;
            }
            return 0;
            break;
    }
    return 0; // pr enlever un warning, à revoir
}

// CONSTANTES
arbre a_cr_a_idf(int num_lex, int num_dec){
    return creer_noeud(A_IDF, num_lex, num_dec);
}

arbre a_cr_cste_entiere(int valeur){
    return creer_noeud(A_CSTE_ENTIERE, valeur, -1);
}

arbre a_cr_cste_bool(int valeur){
    return creer_noeud(A_CSTE_BOOL, valeur, -1);
}

arbre a_cr_cste_chaine(int valeur){
    return creer_noeud(A_CSTE_CHAINE, valeur, -1);
}

arbre a_cr_cste_char(int valeur){
    return creer_noeud(A_CSTE_CHAR, valeur, -1);
}

arbre a_cr_cste_reelle(int valeur){
    return creer_noeud(A_CSTE_REELLE, valeur, -1);
}



// EXPRESSIONS
int verif_calcul(arbre gauche, arbre droit) {
    if (gauche->nature != A_CSTE_REELLE && gauche->nature != A_CSTE_ENTIERE) {
        // faire erreur qui dit pas bon type
        erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                        tab_decla[gauche->decla][FIN_DECLA],
                                        E_TYPE_CALCUL));
        return 1;
    } else {
        if (gauche->nature != droit->nature) {
            erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                             tab_decla[gauche->decla][FIN_DECLA],
                                             E_TYPE_CALCUL));
            return 1;
        }
    }
    return 0;
}

arbre a_cr_plus(arbre gauche, arbre droit){
    if (verif_calcul(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_PLUS, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_moins(arbre gauche, arbre droit){
    if (verif_calcul(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_MOINS, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_mult(arbre gauche, arbre droit){
    if (verif_calcul(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_MULT, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_div(arbre gauche, arbre droit){
    if (verif_calcul(gauche, droit) == 1) {
        return NULL;
    }
    if (droit->valeur == 0) {
        // faire erreur qui dit pas diviser par 0
        erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                         tab_decla[gauche->decla][FIN_DECLA],
                                         E_TYPE_CALCUL));
    }
    return concat_pere_fils(creer_noeud(A_DIV, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_mod(arbre gauche, arbre droit){
    if (verif_calcul(gauche, droit) == 1) {
        return NULL;
    }
    if (droit->valeur == 0) {
        // faire erreur qui dit pas diviser par 0
        erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                         tab_decla[gauche->decla][FIN_DECLA],
                                         E_TYPE_CALCUL));
    }
    return concat_pere_fils(creer_noeud(A_MOD, -1, -1),
                            concat_pere_frere(gauche, droit));
}



// AFFECTATIONS
int verif_affectation(arbre gauche, arbre droit) {
    if (gauche->nature != droit->nature) {
        erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                         tab_decla[gauche->decla][FIN_DECLA],
                                         E_TYPE_AFF));
        return 1;
    }
    return 0;
}

arbre a_cr_affect(arbre gauche, arbre droit){
    if (verif_affect(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_AFFECT, -1, -1),
                            concat_pere_frere(gauche, droit));
}



// VARIABLES
arbre a_cr_idf(int valeur, int num_dec){
    return creer_noeud(A_IDF, valeur, num_dec);
}

arbre a_cr_acces_tab(int idf, arbre liste_acces_dim, int num_dec){
    return concat_pere_fils(creer_noeud(A_ACCES_TAB, -1, -1), 
                            concat_pere_frere(a_cr_idf(idf, num_dec), liste_acces_dim));
}

arbre a_cr_acces_struct(int idf, arbre champ, int num_dec){
    return concat_pere_fils(creer_noeud(A_ACCES_STRUCT, -1, -1),
                            concat_pere_frere(a_cr_idf(idf, num_dec), champ));
}



// EXPRESSIONS BOOLEENNES
int verif_comparaison(arbre gauche, arbre droit) {
    if (gauche->nature != droit->nature) {
        erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                         tab_decla[gauche->decla][FIN_DECLA],
                                         E_TYPE_CONDITION));
        return 1;
    }
    return 0;
}

int verif_bool(int bool, arbre droit) {
    if (bool != 0 && bool != 1 && droit->nature != A_CSTE_BOOL) {
        // faire erreur qui dit pas bon type
        erreur_semantique(generer_erreur(tab_decla[droit->decla][DEBUT_DECLA],
                                        tab_decla[droit->decla][FIN_DECLA],
                                        E_TYPE_CONDITION));
        return 1;
    }
    return 0;
}


arbre a_cr_sup(arbre gauche, arbre droit){
    if (verif_comparaison(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_SUP, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_inf(arbre gauche, arbre droit){
    if (verif_comparaison(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_INF, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_supegal(arbre gauche, arbre droit){
    if (verif_comparaison(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_SUPEGAL, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_infegal(arbre gauche, arbre droit){
    if (verif_comparaison(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_INFEGAL, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_egal_arith(arbre gauche, arbre droit){
    if (verif_comparaison(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_EGAL, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_diff_arith(arbre gauche, arbre droit){
    if (verif_comparaison(gauche, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_DIFF, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_egal_bool(int bool, arbre droit){
    if (verif_bool(bool, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_EGAL, -1, -1),
                            concat_pere_frere(a_cr_cste_bool(bool), droit));
}

arbre a_cr_diff_bool(int bool, arbre droit){
    if (verif_bool(bool, droit) == 1) {
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_DIFF, -1, -1),
                            concat_pere_frere(a_cr_cste_bool(bool), droit));
}

arbre a_cr_non(arbre arbre){
    if (arbre->nature != A_CSTE_BOOL) {
        // erreur pour le '!'
        erreur_semantique(generer_erreur(tab_decla[arbre->decla][DEBUT_DECLA],
                                        tab_decla[arbre->decla][FIN_DECLA],
                                        E_TYPE_CONDITION));
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_NON, -1, -1), arbre);
}

arbre a_cr_et(arbre gauche, arbre droit){
    if (gauche->nature != A_CSTE_BOOL || droit->nature != A_CSTE_BOOL) {
        erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                        tab_decla[droit->decla][FIN_DECLA],
                                        E_TYPE_CONDITION));
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_ET, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_ou(arbre gauche, arbre droit){
    if (gauche->nature != A_CSTE_BOOL || droit->nature != A_CSTE_BOOL) {
        erreur_semantique(generer_erreur(tab_decla[gauche->decla][DEBUT_DECLA],
                                        tab_decla[droit->decla][FIN_DECLA],
                                        E_TYPE_CONDITION));
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_OU, -1, -1),
                            concat_pere_frere(gauche, droit));
}



// CONDITIONNELLES
arbre a_cr_si_alors(arbre si, arbre alors){
    if (si->nature != A_CSTE_BOOL) {
        erreur_semantique(generer_erreur(tab_decla[si->decla][DEBUT_DECLA],
                                         tab_decla[si->decla][FIN_DECLA],
                                         E_TYPE_CONDITION));
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_SI_ALORS, -1, -1),
                            concat_pere_frere(si, alors));  
}

arbre a_cr_si_alors_sinon(arbre si, arbre alors, arbre sinon){ // (cond)--(liste_i)--(liste_i)
    if (si->nature != A_CSTE_BOOL) {
        erreur_semantique(generer_erreur(tab_decla[si->decla][DEBUT_DECLA],
                                         tab_decla[si->decla][FIN_DECLA],
                                         E_TYPE_CONDITION));
        return NULL;
    }
    if (sinon->nature != A_CSTE_BOOL) {
        erreur_semantique(generer_erreur(tab_decla[sinon->decla][DEBUT_DECLA],
                                         tab_decla[sinon->decla][FIN_DECLA],
                                         E_TYPE_CONDITION));
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_SI_ALORS_SINON, -1, -1),
                            concat_pere_frere(si, concat_pere_frere(alors, sinon)));  
}



// LISTE INSTRUCTIONS
arbre a_cr_liste_i(arbre instruction, arbre liste_inst_suivantes){
    return concat_pere_fils(creer_noeud(A_LISTE_I, -1, -1),
                            concat_pere_frere(instruction, liste_inst_suivantes));
}

arbre a_cr_inst(arbre instruction){
    return concat_pere_fils(creer_noeud(A_LISTE_I, -1, -1),
                            instruction);
}



// LISTE PARAM ( A TRANSFORMER EN LISTE ARGUMENTS !!!! PARAM C POUR LES DECLA )
arbre a_cr_liste_arg_fin(arbre un_arg){
    return concat_pere_fils(creer_noeud(A_LISTE_ARG, -1, -1),
                            un_arg);
}

arbre a_cr_liste_arg_suiv(arbre un_arg, arbre liste_suivants) {
    return concat_pere_fils(creer_noeud(A_LISTE_ARG, -1, -1),
                            concat_pere_frere(un_arg, liste_suivants));
}



// APPEL DE FCT/PROC
arbre a_cr_appel(int idf, arbre liste_args) {
    int num_dec;
    printf("Je passe dans a_cr_appel, idf %d\n", idf);
    if ((num_dec = association_noms(idf, N_FCT)) != -1) {
        printf("bonjour je suis le num_dec (dans fct) %d\n", num_dec);
        return a_cr_appel_fct(idf, liste_args, num_dec);

    } else if ((num_dec = association_noms(idf, N_PROC)) != -1) {
        printf("bonjour je suis le num_dec (dans proc) %d\n", num_dec);
        return a_cr_appel_proc(idf, liste_args, num_dec);

    } else {
        printf("euuuuuh erreur dans a_cr_appel\n");
        // je le mets ici mais un appel de proc crée un nouveau champ dans table lexico, pas cool
        // donc ça fait un segfault, pour enlever erreur décommenter en-dessous (mais c'est pas juste)
        //return a_cr_appel_proc(idf, liste_args, num_dec);
        // erreur ?????????
        return NULL;
    }
}

arbre a_cr_appel_fct(int idf, arbre liste_args, int num_dec){
    return concat_pere_fils(creer_noeud(A_APPEL_FCT, -1, -1),
                            concat_pere_frere(a_cr_a_idf(idf, num_dec), liste_args));
}

arbre a_cr_appel_proc(int idf, arbre liste_args, int num_dec){
    return concat_pere_fils(creer_noeud(A_APPEL_PROC, -1, -1),
                            concat_pere_frere(a_cr_a_idf(idf, num_dec), liste_args));
}



// RETOUR DE FCT
arbre a_cr_ret(arbre valeur){
    return concat_pere_fils(creer_noeud(A_RET, -1, -1), valeur);
}



// TANT QUE 
arbre a_cr_tant_que(arbre condition, arbre liste_inst){
    if (condition->nature != A_CSTE_BOOL) {
        erreur_semantique(generer_erreur(tab_decla[condition->decla][DEBUT_DECLA],
                                         tab_decla[condition->decla][FIN_DECLA],
                                         E_TYPE_CONDITION));
        return NULL;
    }
    return concat_pere_fils(creer_noeud(A_TANT_QUE, -1, -1),
                            concat_pere_frere(condition, liste_inst));
}



// LISTE ACCES DIM 
arbre a_cr_feuille_dim(int val){
    return a_cr_cste_entiere(val);
}

arbre a_cr_liste_dim_fin(arbre une_dim){
    return concat_pere_fils(creer_noeud(A_LISTE_DIM, -1, -1),
                            une_dim);
}

arbre a_cr_liste_dim_suiv(arbre une_dim, arbre liste_suivante) {
    return concat_pere_fils(creer_noeud(A_LISTE_DIM, -1, -1),
                            concat_pere_frere(une_dim, liste_suivante));
}








