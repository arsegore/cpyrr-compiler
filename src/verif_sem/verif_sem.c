#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "tables/tab_decla.h"
#include "verif_sem/verif_sem.h"

// gestion des couleurs pour l'affichage
#define ROUGE       "\033[1;31m"
#define JAUNE       "\033[1;33m"
#define BLEU        "\033[1;34m"
#define CYAN        "\033[1;36m"
#define GRAS        "\033[1m"
#define RESET       "\033[0m"

const char *msg_err_tab[NB_TYPE_ERREURS] = {
    "La variable '%s' n'a jamais été déclarée",                             // E_VAR_NON_DECLAREE
    "La fonction '%s' n'a jamais été déclarée",                             // E_FCT_NON_DECLAREE
    "La procédure '%s' n'a jamais été déclarée",                            // E_PROC_NON_DECLAREE
    "La structure '%s' n'a jamais été déclarée",                            // E_STRUCT_NON_DECLAREE
    "Le tableau '%s' n'a jamais été déclarée",                              // E_TAB_NON_DECLAREE
    "Le paramètre '%s' n'a jamais été déclarée",                            // E_PARAM_NON_DECLARE
    "Le champ '%s' de %s n'a jamais été déclaré",                           // E_CHAMP_NON_DECLARE
    "Tentative d'affectation entre %s et %s",                               // E_TYPE_AFF
    "Tentative de calcul entre deux types différents : %s et %s",           // E_TYPE_CALCUL
    "Le type donné n'est pas celui attendu dans une condition",             // E_TYPE_CONDITION
    "Les deux types donnés sont incompatibles : (%s) et (%s)",              // E_TYPE_NON_COMPATIBLE
    "Nombre d'arguments incorrects (%s attendu.s, %s donné.s)",             // E_NB_ARGS
    "L'argument n'est pas du bon type (%s attendu, %s donné)",              // E_TYPE_ARG
    "La procédure '%s' est appelée comme une fonction",                     // E_PROC_COMME_FCT
    "La fonction %s est appelée comme une procédure",                       // E_FCT_COMME_PROC
    "Tentative d'accès à %s comme si c'était un tableau ('%s': %s)",        // E_NON_TAB
    "Tentative d'accès à %s comme si c'était une structure ('%s': %s)",     // E_NON_STRUCT
    "L'indice d'accès est invalide (%s attendu, %s donné)",                 // E_ID_NON_ENTIER
    "Tentative d'écriture d'une fonction sans retour",                      // E_NE_RET_PAS
    "Type de retour incorrect (%s attendu, %s donné)"                       // E_RET_MAUVAIS_TYPE
    "Tentative de retour dans une procédure",                               // E_PROC_RET
};

const char *msg_indice_tab[NB_TYPE_ERREURS] = {
    "Déclarez la variable '%s':%s avant de l'utiliser",                                             // E_VAR_NON_DECLAREE
    "Déclarez la fonction %s '%s' avant de l'utiliser",                                             // E_FCT_NON_DECLAREE
    "Déclarez la procédure '%s' avant de l'utiliser",                                               // E_PROC_NON_DECLAREE
    "Déclarez la structure '%s' avant de l'utiliser",                                               // E_STRUCT_NON_DECLAREE
    "Déclarez le tableau '%s' avant de l'utiliser",                                                 // E_TAB_NON_DECLAREE
    "Déclarez le paramètre '%s' de '%s' avant de l'utiliser",                                       // E_PARAM_NON_DECLARE
    "Déclarez le champ '%s' dans '%s' avant de l'utiliser",                                         // E_CHAMP_NON_DECLARE
    "Vous tentez d'affecter %s à '%s':%s, vérifiez vos déclarations",                               // E_TYPE_AFF
    "Vous tentez d'effectuer une opération entre %s et %s, vérifiez vos types",                     // E_TYPE_CALCUL
    "Une condition attend forcément une expression booléenne (type bool)",                          // E_TYPE_CONDITION
    "Les types %s et %s ne sont pas compatibles, vérifiez vos déclarations",                        // E_TYPE_NON_COMPATIBLE
    "Vérifiez la déclaration de %d et les arguments avec lesquels vous l'appelez",                  // E_NB_ARGS
    "Vérifiez la déclaration de %d et les types des arguments avec lesquels vous l'appelez",        // E_TYPE_ARG
    "Une procédure ne peut pas retourner de valeur",                                                // E_PROC_COMME_FCT
    "Une fonction retourne forcément une valeur",                                                   // E_FCT_COMME_PROC
    "Seul un tableau peut être accédé avec la syntaxe x[y]",                                        // E_NON_TAB
    "Seule une structure peut être accédée avec la syntaxe x.y",                                    // E_NON_STRUCT
    "Pour accéder à un élément d'un tableau, l'indice doit être de type int",                       // E_ID_NON_ENTIER
    "Ajoutez ret <x: %s> à '%s'",                                                                   // E_NE_RET_PAS
    "Ajoutez ou corrigez ret <x:%s> à '%s'",                                                        // E_RET_MAUVAIS_TYPE
    "Retirez le ret dans %s"                                                                        // E_PROC_RET
};

int doit_stopper_exec(int type_erreur){
    return type_erreur < DEBUT_WARNINGS;
}

err_sem *generer_erreur(int ligne, int colonne, int type_erreur, ...){
    va_list args;
    va_start(args, type_erreur);
    
    err_sem *e = (err_sem *) malloc(sizeof(err_sem));
    char msg[512];

    e->ligne = ligne;
    e->colonne = colonne;
    e->type_erreur = type_erreur;

    vsnprintf(msg, 512,msg_err_tab[type_erreur], args);
    e->msg = strdup(msg);
    vsnprintf(msg, 512,msg_indice_tab[type_erreur], args);
    e->indice = strdup(msg);
    e->est_stoppante = doit_stopper_exec(type_erreur);
}

void erreur_semantique(err_sem *e){
    if (e == NULL) return;
    
    err_sem e_val = *e;

}