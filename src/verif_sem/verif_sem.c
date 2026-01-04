#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables/tab_decla.h"
#include "tables/tab_code.h"
#include "tables/tab_lexico.h"
#include "tables/tab_rep.h"
#include "verif_sem/verif_sem.h"
#include "association_noms/association_noms.h"
#include "arbre/arbre.h"

// gestion des couleurs pour l'affichage
#define ROUGE       "\033[1;31m"
#define JAUNE       "\033[1;33m"
#define BLEU        "\033[1;34m"
#define CYAN        "\033[1;36m"
#define MAGENTA     "\x1B[35m"
#define GRAS        "\033[1m"
#define RESET       "\033[0m"

int nb_err_sem;
int nb_av_sem;
char ligne[TAILLE_MAX_LIGNE];
extern int ligne_courante;

const char *msg_err_tab[NB_TYPE_ERREURS] = {
    [E_VAR_NON_DECLAREE]   = "La variable '%1$s' n'est pas déclarée",
    [E_FCT_NON_DECLAREE]   = "La fonction '%1$s' n'est pas déclarée",
    [E_PROC_NON_DECLAREE]  = "La procédure '%1$s' n'est pas déclarée",
    [E_TYPE_AFF]           = "Affectation impossible pour '%1$s' : %2$s attendu, %3$s reçu",
    [E_TYPE_CONDITION]     = "La condition doit être de type bool (reçu: %1$s)",
    [E_NB_ARGS]            = "Appel de '%1$s' incorrect : %2$d argument.s attendu.s, %3$d reçu.s",
    [E_RET_MAUVAIS_TYPE]   = "Retour de fonction incorrect : attendu %1$s, reçu %2$s",
    [E_PROC_RET]           = "Une procédure ('%1$s') ne peut pas retourner de valeur",
    [E_ARG_MAUVAIS_TYPE]   = "Argument %1$d de '%2$s' incorrect : %3$s attendu, %4$s reçu",
    [E_DOUBLE_DECLA]       = "L'identificateur '%1$s' est déjà utilisé pour une %2$s dans cette portée",
};

const char *msg_indice_tab[NB_TYPE_ERREURS] = {
    [E_VAR_NON_DECLAREE]   = "Ajoutez 'var %1$s : [type]' dans vos déclarations",
    [E_FCT_NON_DECLAREE]   = "Vérifiez l'orthographe ou déclarez la fonction %1$s",
    [E_PROC_NON_DECLAREE]  = "Vérifiez l'orthographe ou déclarez la procédure %1$s",
    [E_TYPE_AFF]           = "Modifiez la valeur affectée pour qu'elle soit de type %2$s",
    [E_TYPE_CONDITION]     = "Une condition est forcément une expression booléenne",
    [E_NB_ARGS]            = "Selon sa signature, '%1$s' ne nécessite que %2$d argument.s",
    [E_RET_MAUVAIS_TYPE]   = "Changez l'expression après 'ret' pour renvoyer un %1$s",
    [E_PROC_RET]           = "Supprimez l'expression après 'ret' ou transformez '%1$s' en fonction",
    [E_ARG_MAUVAIS_TYPE]   = "L'argument n°%1$d doit être converti en %3$s",
    [E_DOUBLE_DECLA]       = "Modifiez le nom ou assurez-vous que la %2$s '%1$s' n'est pas redéfinie (cf. ligne %3$d)",
};

int doit_stopper_exec(int type_erreur){
    return type_erreur < DEBUT_WARNINGS;
}

err_sem *generer_erreur(int ligne, int colonne, int type_erreur, int id_decla, ...) {
    err_sem *e;
    va_list args;
    char msg[TAILLE_MAX_LIGNE];

    va_start(args, id_decla);
    
    e = (err_sem *) malloc(sizeof(err_sem));
    if (e == NULL) return NULL;

    e->ligne = ligne;
    e->colonne = colonne;
    e->type_erreur = type_erreur;

    if (id_decla != -1 && id_decla < HAUTEUR) {
        e->ligne_decla_depart = tab_decla[id_decla][DEBUT_DECLA];
        e->ligne_decla_fin = tab_decla[id_decla][FIN_DECLA];
    } else {
        e->ligne_decla_depart = -1;
        e->ligne_decla_fin = -1;
    }

    vsnprintf(msg, TAILLE_MAX_LIGNE, msg_err_tab[type_erreur], args);
    e->msg = strdup(msg);
    vsnprintf(msg, TAILLE_MAX_LIGNE, msg_indice_tab[type_erreur], args);
    e->indice = strdup(msg);
    e->est_stoppante = 1;

    va_end(args);
    return e;
}

void erreur_semantique(err_sem *e){
    err_sem e_val;

    if (e == NULL) return;
    e_val = *e;

    // erreur ou warning ?
    if (e_val.est_stoppante) {
        printf(ROUGE GRAS "Erreur" RESET);
        printf(GRAS " (E%03d)" RESET, e_val.type_erreur);
        nb_err_sem++;
    } else {
        printf(JAUNE GRAS "Avertissement" RESET);
        printf(GRAS " (W%03d)" RESET, e_val.type_erreur);
        nb_av_sem++;
    }

    // affichage du message d'erreur
    printf(": %s\n", e_val.msg);

    // position 
    printf("À la position" GRAS " %d:%d\n" RESET, 
        e_val.ligne, 
        e_val.colonne);
    
    afficher_ligne_source(e_val.ligne);

    if (e->ligne_decla_depart != -1) {
        afficher_bloc_source(e->ligne_decla_depart, e->ligne_decla_fin);
    }

    // affichage de l'indice
    if (e_val.indice && strlen(e_val.indice) > 0){
        printf(CYAN "   >" RESET " Indice : " GRAS "%s\n", e_val.indice);
    }
}

void afficher_ligne_source(int num_ligne){
    const char *contenu_ligne = NULL;

    if (num_ligne == ligne_courante) {
        contenu_ligne = ligne; 
    } else if (num_ligne > 0 && num_ligne <= nb_lignes) {
        contenu_ligne = tab_code[num_ligne - 1];
    }

    if (contenu_ligne == NULL) return;

    printf(CYAN "   |\n");
    printf("%3d|" RESET GRAS " %s\n" RESET, num_ligne, contenu_ligne);
    printf(CYAN "   | " RESET);
    for (int i = 0; i < strlen(contenu_ligne); i++){
        if (contenu_ligne[i] == ' ' || contenu_ligne[i] == '\t') {
            printf("%c", contenu_ligne[i]);
        } else {
            printf(ROUGE "^" RESET);
        }
    }
    printf("\n");
}

void afficher_bloc_source(int debut, int fin) {
    if (debut <= 0 || fin <= 0 || debut > nb_lignes) return;

    if (debut == fin) {
        printf(RESET "   --- Rappel de la déclaration (ligne %d) ---\n", debut);
    } else {
        printf(RESET "   --- Rappel de la déclaration (lignes %d à %d) ---\n", debut, fin);
    }

    for (int i = debut; i <= fin && i <= nb_lignes; i++) {
        if (tab_code[i-1] != NULL) {
            printf(CYAN "%3d|" MAGENTA GRAS "%s\n" RESET, i, tab_code[i-1]);
        }
    }
}

int evaluer_type_acces_champ(int id_decla_parent, arbre liste_acces) {
    int type_actuel = tab_decla[id_decla_parent][DESCRIPTION]; 
    arbre courant = liste_acces;
    arbre noeud_champ;

    if (liste_acces == NULL || id_decla_parent == -1) return id_decla_parent;

    while (courant != NULL && type_actuel != -1) {
        if (courant->nature == A_LISTE_CHAMPS) {
            noeud_champ = courant->fils_gauche;
            
            type_actuel = trouver_type_champ(type_actuel, noeud_champ->valeur);
            
            if (noeud_champ->fils_gauche != NULL && type_actuel != -1 && noeud_champ->fils_gauche->nature == A_LISTE_DIM) {
                type_actuel = trouver_type_tab(type_actuel);
            }
        }
        courant = courant->frere_droit;
    }
    return type_actuel;
}

/**
 * Fonctions de vérifications
 */
const char *recup_nom_type(int type) {
    switch (type) {
        case TREETYPE_ENTIER: return "int";
        case TREETYPE_REEL:   return "float";
        case TREETYPE_BOOL:   return "bool";
        case TREETYPE_CHAR:   return "char";
        default:              return "type inconnu";
    }
}

int verif_decla_idf(int num_lex, int nature, int ligne) {
    int decla = association_noms(num_lex, nature);
    int code;
    if (decla == -1) {
        switch (nature) {
            case N_VAR:
                code = E_VAR_NON_DECLAREE; break;
            // case N_FCT:
            //     code = E_FCT_NON_DECLAREE; break;
            // case N_PROC:
            //     code = E_PROC_NON_DECLAREE; break;
            default: 
                break;// JSP MDR
        }
        erreur_semantique(generer_erreur(ligne, 0, code, -1, recuperer_lexeme(num_lex)));
    }
    return decla;
}

void verif_compatibilite_affect(int num_lex, int t_dest, int t_src, int ligne) {
    const char *nom;
    if (t_dest != t_src) {
        nom = recuperer_lexeme(num_lex);
        int decla = association_noms(num_lex, N_VAR);
        erreur_semantique(generer_erreur(ligne, 0, E_TYPE_AFF, 
                          decla, nom, recup_nom_type(t_dest), recup_nom_type(t_src)));
    }
}

void verif_condition_bool(int t_recu, int ligne) {
    if (t_recu != TREETYPE_BOOL) {
        erreur_semantique(generer_erreur(ligne, 0, E_TYPE_CONDITION, -1, recup_nom_type(t_recu)));
    }
}

void verif_nombre_args(int num_lex, int nb_attendu, int nb_recu, int ligne) {
    if (nb_attendu != nb_recu) {
        int decla = association_noms(num_lex, N_FCT);
        if (decla == -1) decla = association_noms(num_lex, N_PROC);
        erreur_semantique(generer_erreur(ligne, 0, E_NB_ARGS, 
                          decla, recuperer_lexeme(num_lex), nb_attendu, nb_recu));
    }
}

int verif_decla_appel(int num_lex, int ligne) {
    int decla = association_noms(num_lex, N_FCT);
    if (decla == -1) {
        decla = association_noms(num_lex, N_PROC);
    }
    
    if (decla == -1) {
        erreur_semantique(generer_erreur(ligne, 0, E_FCT_NON_DECLAREE, -1, recuperer_lexeme(num_lex)));
    }
    return decla;
}

int compter_nombre_args(arbre a) {
    int nb = 0;
    while (a != NULL && a->nature == A_LISTE_ARG) {
        nb++;
        if (a->fils_gauche != NULL) {
            a = a->fils_gauche->frere_droit;
        } else {
            break;
        }
    }
    return nb;
}

void verif_types_args(int num_lex, int decla, arbre liste_args, int ligne) {
    int id_rep, nb_params, depart_params, type_attendu, type_recu, i;
    arbre curr_liste;

    if (decla == -1) return;

    id_rep = tab_decla[decla][DESCRIPTION];
    curr_liste = liste_args;
    nb_params = tab_rep[id_rep];

    if (tab_decla[decla][NATURE] == N_FCT) {
        depart_params = id_rep + 2; 
    } else {
        depart_params = id_rep + 1;
    }
    printf("%d\n", nb_params);
    for (i = 0; i < nb_params; i++) {
        type_attendu = tab_rep[depart_params + (i * 2) + 1];
        
        if (curr_liste == NULL || curr_liste->fils_gauche == NULL) break;

        type_recu = recuperer_type_noeud(curr_liste->fils_gauche);
        printf("Type reçu : %d  VS Type attendu : %d\n", type_recu, type_attendu);

        if (type_attendu != type_recu) {
            erreur_semantique(generer_erreur(ligne, 0, E_ARG_MAUVAIS_TYPE, 
                              decla, i + 1, recuperer_lexeme(num_lex), 
                              recup_nom_type(type_attendu), recup_nom_type(type_recu)));
        }

        curr_liste = curr_liste->fils_gauche->frere_droit;
    }
}

const char* recup_nom_nature(int nature) {
    switch(nature) {
        case N_VAR:    return "variable";
        case N_TYPE_B: return "type";
        case N_STRUCT: return "structure";
        case N_FCT:    return "fonction";
        case N_PROC:   return "procédure";
        case N_TAB:    return "tableau";
        default:       return "entité";
    }
}

void verif_double_decla(int num_lex, int region, int nature, int ligne) {
    int id_courant = num_lex;
     const char* nom_nature;

    while (id_courant != -1) {
        if (tab_decla[id_courant][NATURE] == nature && 
            tab_decla[id_courant][REGION] == region) {
            
            nom_nature = recup_nom_nature(nature);
            
            erreur_semantique(generer_erreur(ligne, 0, E_DOUBLE_DECLA, id_courant, 
                              recuperer_lexeme(num_lex), 
                              nom_nature,
                              tab_decla[id_courant][DEBUT_DECLA]));
            return;
        }
        id_courant = tab_decla[id_courant][SUIVANT];
    }
}



