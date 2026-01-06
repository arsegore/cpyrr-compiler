#include <stdio.h>
#include <stdlib.h>
#include "arbre/arbre.h"
#include "tables/tab_lexico.h"
#include "tables/tab_decla.h"
#include "tables/tab_rep.h"
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

void afficher_nat_noeud(arbre a){
    printf("(" CYAN GRAS);
    switch (a->nature) {
        case A_IDF:             printf("A_IDF"); break;
        case A_CSTE_ENTIERE:    printf("A_CSTE_ENTIERE"); break;
        case A_CSTE_REELLE:     printf("A_CSTE_REELLE"); break;
        case A_CSTE_BOOL:       printf("A_CSTE_BOOL"); break;
        case A_CSTE_CHAINE:     printf("A_CSTE_CHAINE"); break;
        case A_CSTE_CHAR:       printf("A_CSTE_CHAR"); break;
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
        case A_NON:             printf("A_NON"); break;
        case A_SUP:             printf("A_SUP"); break;
        case A_SUPEGAL:         printf("A_SUPEGAL"); break;
        case A_INF:             printf("A_INF"); break;
        case A_INFEGAL:         printf("A_INFEGAL"); break;
        case A_DIFF:            printf("A_DIFF"); break;
        case A_EGAL:            printf("A_EGAL"); break;
        case A_RIEN:            printf("A_RIEN"); break;
        case A_SI_ALORS:        printf("A_SI_ALORS"); break;
        case A_SI_ALORS_SINON:  printf("A_SI_ALORS_SINON"); break;
        case A_TANT_QUE:        printf("A_TANT_QUE"); break;
        case A_LISTE_I:         printf("A_LISTE_I"); break;
        case A_LISTE_DIM:       printf("A_LISTE_DIM"); break;
        case A_DIM:             printf("A_DIM"); break;
        case A_LISTE_CHAMPS:    printf("A_LISTE_CHAMPS"); break;
        case A_CHAMP:           printf("A_CHAMP"); break;
        case A_LISTE_ARG:       printf("A_LISTE_ARG"); break;
        case A_APPEL_PROC:      printf("A_APPEL_PROC"); break;
        case A_APPEL_FCT:       printf("A_APPEL_FCT"); break;
        case A_RET:             printf("A_RET"); break;
        default:                printf("A_INCONNU"); break;
    }

    if (a->nature == A_IDF || a->nature == A_CHAMP) {
        printf(RESET ")[" MAGENTA "%s" RESET "][" VERT "%d" RESET "]\n", recuperer_lexeme(a->valeur), a->decla);
    } else {
        printf(RESET ")[" MAGENTA "%d" RESET "][" VERT "%d" RESET "]\n", a->valeur, a->decla);
    }
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
arbre a_cr_plus(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_PLUS, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_moins(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_MOINS, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_mult(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_MULT, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_div(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_DIV, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_mod(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_MOD, -1, -1),
                            concat_pere_frere(gauche, droit));
}

// AFFECTATIONS
arbre a_cr_affect(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_AFFECT, -1, -1),
                            concat_pere_frere(gauche, droit));
}

// VARIABLES
arbre a_cr_idf(int valeur, int num_dec){
    return creer_noeud(A_IDF, valeur, num_dec);
}

// EXPRESSIONS BOOLEENNES
arbre a_cr_sup(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_SUP, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_inf(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_INF, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_supegal(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_SUPEGAL, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_infegal(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_INFEGAL, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_egal_arith(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_EGAL, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_diff_arith(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_DIFF, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_egal_bool(int bool, arbre droit){
    return concat_pere_fils(creer_noeud(A_EGAL, -1, -1),
                            concat_pere_frere(a_cr_cste_bool(bool), droit));
}

arbre a_cr_diff_bool(int bool, arbre droit){
    return concat_pere_fils(creer_noeud(A_DIFF, -1, -1),
                            concat_pere_frere(a_cr_cste_bool(bool), droit));
}

arbre a_cr_non(arbre arbre){
    return concat_pere_fils(creer_noeud(A_NON, -1, -1), arbre);
}

arbre a_cr_et(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_ET, -1, -1),
                            concat_pere_frere(gauche, droit));
}

arbre a_cr_ou(arbre gauche, arbre droit){
    return concat_pere_fils(creer_noeud(A_OU, -1, -1),
                            concat_pere_frere(gauche, droit));
}

// CONDITIONNELLES
arbre a_cr_si_alors(arbre si, arbre alors){
    return concat_pere_fils(creer_noeud(A_SI_ALORS, -1, -1),
                            concat_pere_frere(si, alors));  
}

arbre a_cr_si_alors_sinon(arbre si, arbre alors, arbre sinon){ // (cond)--(liste_i)--(liste_i)
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
arbre a_cr_appel(int idf, arbre liste_args, int decla) {
    if (decla != -1 && tab_decla[decla][NATURE] == N_PROC) {
        return a_cr_appel_proc(idf, liste_args, decla);
    }
    return a_cr_appel_fct(idf, liste_args, decla);
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
    return concat_pere_fils(creer_noeud(A_TANT_QUE, -1, -1),
                            concat_pere_frere(condition, liste_inst));
}

// ACCES TAB
arbre a_cr_dim(int val) {
    return creer_noeud(A_DIM, val, -1);
}

arbre a_cr_liste_dim_fin(arbre une_dim) {
    return concat_pere_fils(creer_noeud(A_LISTE_DIM, -1, -1), une_dim);
}

arbre a_cr_liste_dim_suiv(arbre une_dim, arbre suite) {
    return concat_pere_fils(creer_noeud(A_LISTE_DIM, -1, -1),
                            concat_pere_frere(une_dim, suite));
}


arbre a_cr_acces_tab(int idf, arbre liste, int num_dec) {
    return concat_pere_fils(a_cr_idf(idf, num_dec), liste);
}

arbre a_cr_champ(int num_lex, arbre liste_dim) {
    arbre c = creer_noeud(A_CHAMP, num_lex, -1);
    if (liste_dim != NULL) {
        concat_pere_fils(c, liste_dim);
    }
    return c;
}

arbre a_cr_liste_champs_fin(arbre noeud_champ) {
    return concat_pere_fils(creer_noeud(A_LISTE_CHAMPS, -1, -1),
                            noeud_champ);
}

arbre a_cr_liste_champs_suiv(arbre noeud_champ, arbre suite_liste) {
    return concat_pere_fils(creer_noeud(A_LISTE_CHAMPS, -1, -1),
                            concat_pere_frere(noeud_champ, suite_liste));
}

arbre a_cr_acces_struct(int idf, arbre liste, int num_dec) {
    return concat_pere_fils(a_cr_idf(idf, num_dec), liste);
}

int trouver_type_champ(int id_type_struct, int num_lex_champ) {
    int base_champ;
    int id_rep = tab_decla[id_type_struct][DESCRIPTION];
    int nb_champs = tab_rep[id_rep];

    printf("id type struct = %d\n", id_type_struct);

    if (id_type_struct == -1 || tab_decla[id_type_struct][NATURE] != N_STRUCT) {
        return -1; 
    }
    
    for (int i = 0; i < nb_champs; i++) {
        base_champ = id_rep + 1 + (i * 3);
        if (tab_rep[base_champ] == num_lex_champ) {
            return tab_rep[base_champ + 1];
        }
    }
    return -1;
}

int trouver_type_tab(int id_decla_tab) {
    int id_type = tab_decla[id_decla_tab][DESCRIPTION];
    return tab_rep[tab_decla[id_type][DESCRIPTION]];
}

int recuperer_type_noeud(arbre a) {
    if (a == NULL) return -1;

    switch (a->nature) {
        case A_CSTE_ENTIERE: return 0; // TREETYPE_ENTIER
        case A_CSTE_REELLE:  return 1; // TREETYPE_REEL
        case A_CSTE_BOOL:    return 2; // TREETYPE_BOOL
        case A_CSTE_CHAR:    return 3; // TREETYPE_CHAR

        case A_IDF:
            if (a->decla != -1) return tab_decla[a->decla][DESCRIPTION];
            break;

        case A_PLUS: case A_MOINS: case A_MULT: case A_DIV: case A_MOD:
            return recuperer_type_noeud(a->fils_gauche);

        case A_ET: case A_OU: case A_NON:
        case A_EGAL: case A_DIFF: case A_INF: case A_SUP: case A_INFEGAL: case A_SUPEGAL:
            return 2; // TREETYPE_BOOL

        case A_APPEL_FCT:
            if (a->decla != -1) return tab_rep[tab_decla[a->decla][DESCRIPTION]];
            break;
            
        case A_ACCES_STRUCT:
            return evaluer_type_acces_champ(a->decla, a->fils_gauche);

        default:
            break;
    }
    return -1;
}

int evaluer_type_corps(arbre a, int num_lex, int *type_corps, int decla, int ligne) {
    const char *lexeme = recuperer_lexeme(num_lex);
    arbre courant = a;
    int type_courant;

    if (a == NULL) return 0;

    if (a->nature == A_RET) {
        type_courant = recuperer_type_noeud(a->fils_gauche); // type de retour

        if (*type_corps == -1) {
            *type_corps = type_courant;
        } else if (*type_corps != type_courant) {
            erreur_semantique(generer_erreur(ligne, 0, E_RET_INCOHERENT, decla,
                              lexeme,
                              recup_nom_type(*type_corps), 
                              recup_nom_type(type_courant)));
            return 1;
        }
    }

    if (evaluer_type_corps(a->fils_gauche, num_lex, type_corps, decla, ligne)) return 1;
    if (evaluer_type_corps(a->frere_droit, num_lex, type_corps, decla, ligne)) return 1;

    return 0;
}








