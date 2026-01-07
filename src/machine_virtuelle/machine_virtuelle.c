#include "machine_virtuelle/machine_virtuelle.h"
#include "arbre/pile_exec.h"
#include "tables/tab_decla.h"
#include "tables/tab_regions.h"
#include "tables/tab_reels.h"
#include "tables/pile_regions.h"
#include "tables/tab_lexico.h"
#include "tables/tab_rep.h"
#include <stdlib.h>
#include <stdio.h>


int retourne;
val valeur_retour;
int region_courante;

int recuperer_case_variable(arbre a) {
    int num_decla = a->decla;
    int region_decla = tab_decla[num_decla][REGION];
    int nis_decla = tab_region[region_decla].nis;
    int nis_util = tab_region[num_region_courante].nis;
    int decalage = tab_decla[num_decla][EXECUTION];
    int adresse, nb_dim, adresse_base;
    int type, taille_type;
    int indice, indice_borne_inf = 2, borne_inf, borne_sup;
    int num_lex_champ;
    arbre dim_courante, champ_courant;

    if (nis_util == 0) { // on est dans le main
        adresse = decalage;
    } else if (nis_util == nis_decla) {
        adresse = BC + nis_util + decalage + 1;
    } else {
        adresse =  pile_exec[BC + nis_decla - nis_util].contenu.chainage + decalage + 1;
    }

    // if (a->fils_gauche) {
    //     // Accès à un tab
    //     if (a->fils_gauche->nature == A_LISTE_DIM){ // accès tableau
    //         type = tab_decla[num_decla][DESCRIPTION];
    //         taille_type = tab_decla[tab_rep[tab_decla[type][DESCRIPTION]]][EXECUTION];
    //         dim_courante = a->fils_gauche;
    //         nb_dim = 1;

    //         while(dim_courante != NULL) {
    //             afficher_arbre(dim_courante);
    //             indice = evaluer_arbre_int(dim_courante->fils_gauche);
    //             borne_inf = tab_rep[tab_decla[type][DESCRIPTION] + indice_borne_inf];
    //             borne_sup = tab_rep[tab_decla[type][DESCRIPTION] + indice_borne_inf + 1];
    //             printf("DIM %d, borne inf %d, borne sup %d, indice %d\n", nb_dim, borne_inf, borne_sup, indice);

    //             adresse += (nb_dim - 1) * borne_sup + indice;
    //             indice_borne_inf += 2;
    //             dim_courante = dim_courante->fils_gauche->frere_droit;

    //             nb_dim++;
    //         }
    //     }

    //     // Accès à une struct (on cherche le champ correspondant)
    //     // else if (a->fils_gauche->nature == A_LISTE_CHAMPS) {
    //     // }
    // }

    return adresse;
}

void debut_region(int num_decla) {
    int region = tab_decla[num_decla][EXECUTION]; // le num de région de la fct/proc
    int n = tab_region[region_courante].nis;
    int p = tab_region[region].nis;
    int ancienne_bc = BC;
    int nouvelle_bc = taille_pile_exec;
    int i;

    // NIS croissant de n à n+1
    if (p == n+1){
        empiler_pile_exec_chainage(ancienne_bc); // copie du chainage dynamique
        for (i = 0; i < n; i++) {
            empiler_pile_exec_chainage(pile_exec[ancienne_bc + i].contenu.chainage); // copie des n chainages statiques de la région appelante
        }
    }

    // NIS stagne
    else if (p == n) {
        for (i = 0; i < n; i++) {
            empiler_pile_exec_chainage(pile_exec[ancienne_bc + i].contenu.chainage); // copie des n chainages statiques de la région appelante
        }
    }

    // NIS décroissant
    else if (p < n) {
        for (i = n - p; i < n; i++) {
            empiler_pile_exec_chainage(pile_exec[ancienne_bc + i].contenu.chainage); // copie des derniers chainages de la région appelante
        }
    }

    empiler_pile_exec_chainage(ancienne_bc); // chainage dynamique
    BC = nouvelle_bc;
    region_courante = region;
}

void execute_arbre(arbre a) {
    val valeur;
    int adresse;

    if (a == NULL || retourne) return;

    switch(a->nature){
        case A_LISTE_I:
            if (a->fils_gauche) {
                execute_arbre(a->fils_gauche);
            } else return;
            if (!retourne) {
                execute_arbre(a->fils_gauche->frere_droit);
            }
            break;
        case A_AFFECT:
            printf("Entrée dans un noeud A_AFFECT\n");
            // valeur = evaluer_expression(a->fils_gauche->frere_droit);
            // adresse = recuperer_case_variable(a->fils_gauche);
            // pile_exec[adresse].contenu.donnees.valeur = valeur;
            // pile_exec[adresse].contenu.donnees.type_var = recuperer_type_noeud(a->fils_gauche); //fg et fd sont du mm type (sémantique oblige)
            // pile_exec[adresse].contenu.donnees.lexeme = recuperer_lexeme(a->fils_gauche->valeur);
            printf("Sortie d'un noeud A_AFFECT\n");
            break;
        case A_SI_ALORS:
            printf("Entrée dans un noeud A_SI_ALORS\n");
            if (evaluer_arbre_bool(a->fils_gauche)) {
                execute_arbre(a->fils_gauche->frere_droit);
            }
            break;
            printf("Sortie d'un noeud A_SI_ALORS\n");
        case A_SI_ALORS_SINON:
            printf("Entrée dans un noeud A_SI_ALORS_SINON\n");
            if (evaluer_arbre_bool(a->fils_gauche)) {
                execute_arbre(a->fils_gauche->frere_droit);
            } else {
                execute_arbre(a->fils_gauche->frere_droit->frere_droit);
            }
            break;
            printf("Sortie d'un noeud A_SI_ALORS_SINON\n");

        case A_TANT_QUE:
            printf("Entrée dans un noeud A_TANT_QUE\n");
            while (evaluer_arbre_bool(a->fils_gauche) && !retourne) {
                execute_arbre(a->fils_gauche->frere_droit);
            }
            break;
            printf("Sortie d'un noeud A_TANT_QUE\n");
        case A_RET:
            printf("Entrée dans un noeud A_RET\n");
            valeur_retour = evaluer_expression(a->fils_gauche);
            retourne = 1;
            printf("Sortie d'un noeud A_RET\n");
            break;
        case A_APPEL_FCT: case A_APPEL_PROC:
            printf("Entrée dans un noeud A_APPEL (FCT OU PROC)\n");
            afficher_arbre(a->fils_gauche);
            appel_region(a);
            printf("Sortie d'un noeud A_APPEL (FCT OU PROC)\n");
            break;
        default:
            break;
    }
}

void appel_region(arbre a) {
    int decla;
    int region;
    int nb_args;
    int i;
    int bc_appelante;
    int region_appelante;
    int adresse_param;
    val args[50];
    int type[50];
    arbre arg_courant;
    arbre idf_noeud;

    nb_args = 0;
    idf_noeud = a->fils_gauche;
    decla = idf_noeud->decla;
    region = tab_decla[decla][EXECUTION];
    arg_courant = idf_noeud->frere_droit;

    while (arg_courant != NULL && arg_courant->nature == A_LISTE_ARG) {
        if (arg_courant->fils_gauche != NULL) {
            args[nb_args] = evaluer_expression(arg_courant->fils_gauche);
            type[nb_args] = recuperer_type_noeud(arg_courant->fils_gauche);
            nb_args++;
        }
        arg_courant = arg_courant->frere_droit;
    }
    
    bc_appelante = BC;
    region_appelante = region_courante;

    debut_region(decla);
    allouer_taille(tab_region[region].taille - (tab_region[region].nis + 1)); // les chainages sont déjà empilés

    for (i = 0; i < nb_args; i++) {
        adresse_param = BC + tab_region[region].nis + 1 + i;
        pile_exec[adresse_param].contenu.donnees.valeur = args[i];
        pile_exec[adresse_param].contenu.donnees.type_var = type[i];
    }

    afficher_pile_exec();

    execute_arbre(tab_region[region].arbre_region);

    retourne = 0;
    region_courante = region_appelante;
    taille_pile_exec = BC;
    BC = bc_appelante;
}

int evaluer_arbre_int(arbre a) {
    if (a == NULL) return 0;

    switch (a->nature) {
        // CONSTANTES
        case A_CSTE_ENTIERE:
        case A_DIM:
            return a->valeur;
        // OPERATIONS
        case A_PLUS: 
            return evaluer_arbre_int(a->fils_gauche) + evaluer_arbre_int(a->fils_gauche->frere_droit);
        case A_MULT:
            return evaluer_arbre_int(a->fils_gauche) * evaluer_arbre_int(a->fils_gauche->frere_droit);
        case A_MOINS:
            return evaluer_arbre_int(a->fils_gauche) - evaluer_arbre_int(a->fils_gauche->frere_droit);
        case A_MOD:
            return evaluer_arbre_int(a->fils_gauche) % evaluer_arbre_int(a->fils_gauche->frere_droit);
        case A_DIV:
            return evaluer_arbre_int(a->fils_gauche) / evaluer_arbre_int(a->fils_gauche->frere_droit);
        // VARIABLE 
        case A_IDF:    
        return pile_exec[recuperer_case_variable(a)].contenu.donnees.valeur.entier;
        // ERREUR
        default:
            return 0;
    }
}

int evaluer_arbre_bool(arbre a) {
    if (a == NULL) return 0;

    switch (a->nature) {
        case A_CSTE_BOOL:
            return a->valeur; // 0 pour FALSE, 1 pour TRUE
        case A_ET:
            return evaluer_arbre_bool(a->fils_gauche) && evaluer_arbre_bool(a->fils_gauche->frere_droit);
        case A_OU:
            return evaluer_arbre_bool(a->fils_gauche) || evaluer_arbre_bool(a->fils_gauche->frere_droit);
        case A_NON:
            return !evaluer_arbre_bool(a->fils_gauche);
        case A_EGAL:
            return evaluer_arbre_int(a->fils_gauche) == evaluer_arbre_int(a->fils_gauche->frere_droit);
        case A_INF:
            return evaluer_arbre_int(a->fils_gauche) < evaluer_arbre_int(a->fils_gauche->frere_droit);
        case A_SUP:
            return evaluer_arbre_int(a->fils_gauche) > evaluer_arbre_int(a->fils_gauche->frere_droit);
        case A_IDF:
            return pile_exec[recuperer_case_variable(a)].contenu.donnees.valeur.bool;
        default: return 0;
    }
}

float evaluer_arbre_reel(arbre a) {
    if (a == NULL) return 0;

    switch (a->nature) {
        // CONSTANTES
        case A_CSTE_REELLE:
            return tab_reels[a->valeur];
        // OPERATIONS
        case A_PLUS: 
            return evaluer_arbre_reel(a->fils_gauche) + evaluer_arbre_reel(a->fils_gauche->frere_droit);
        case A_MULT:
            return evaluer_arbre_reel(a->fils_gauche) * evaluer_arbre_reel(a->fils_gauche->frere_droit);
        case A_MOINS:
            return evaluer_arbre_reel(a->fils_gauche) - evaluer_arbre_reel(a->fils_gauche->frere_droit);
        case A_DIV:
            return evaluer_arbre_reel(a->fils_gauche) / evaluer_arbre_reel(a->fils_gauche->frere_droit);
        // VARIABLE 
        case A_IDF:
            return pile_exec[recuperer_case_variable(a)].contenu.donnees.valeur.reel;
            break;
        // ERREUR
        default:
            return 0;
    }
}

val evaluer_expression(arbre a) {
    val res = {0};
    if (a == NULL) return res;

    int type_attendu = recuperer_type_noeud(a);

    switch (type_attendu) {
        case TREETYPE_ENTIER:
            res.entier = evaluer_arbre_int(a);
            break;

        case TREETYPE_REEL:
            res.reel = evaluer_arbre_reel(a);
            break;

        case TREETYPE_BOOL:
            res.bool = evaluer_arbre_bool(a);
            break;
        case TREETYPE_CHAR:
            res.caractere = (char) a->valeur;
            break;
        default:
            break;
    }
    return res;
}

// void appel_region(arbre a) {
//     debut_region()
// }

void lancer_execution() {
    BC = 0;
    init_pile_exec();
    region_courante = 0;
    retourne = 0;

    printf("\n --- L'éxécution commence ... --- \n");
    // on lance l'éxécution sur la région 0
    allouer_taille(tab_region[0].taille);
    afficher_pile_exec();
    if (tab_region[0].arbre_region != NULL) {
        execute_arbre(tab_region[0].arbre_region);
    }
    printf("\n ------ Éxécution terminée ----- \n");

}

