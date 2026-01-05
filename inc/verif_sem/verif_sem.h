#ifndef _VERIF_SEM_H_
#define _VERIF_SEM_H_

#include "arbre/arbre.h"

#define NB_TYPE_ERREURS 28

// erreurs de déclaration
#define E_VAR_NON_DECLAREE 0
#define E_FCT_NON_DECLAREE 1
#define E_PROC_NON_DECLAREE 2
#define E_STRUCT_NON_DECLAREE 3
#define E_TAB_NON_DECLAREE 4
#define E_PARAM_NON_DECLARE 5
#define E_CHAMP_NON_DECLARE 6
#define E_DOUBLE_DECLA      23

// erreurs de types non compatibles
#define E_TYPE_INCOMP 7
#define E_TYPE_AFF 8
#define E_TYPE_CALCUL 9
#define E_TYPE_CONDITION 10
#define E_TYPE_NON_COMPATIBLE 11

// erreurs sur un appel de fct/proc
#define E_NB_ARGS 12
#define E_TYPE_ARG 13
#define E_PROC_COMME_FCT 14
#define E_FCT_COMME_PROC 15
#define E_ARG_MAUVAIS_TYPE 22

// erreurs de tentative d'accès à un champ/un élément
#define E_NON_TAB 16
#define E_NON_STRUCT 17
#define E_ID_NON_ENTIER 18
#define E_ACCES_TAB_HORS_BORNES 25
#define E_ACCES_TAB_DIM_INCORRECTES 26

// erreurs de retours de fonction 
#define E_NE_RET_PAS 19
#define E_RET_MAUVAIS_TYPE 20
#define E_PROC_RET 21

#define DEBUT_WARNINGS 24

// TYPES 
#define TREETYPE_ENTIER 0
#define TREETYPE_REEL 1
#define TREETYPE_BOOL 2
#define TREETYPE_CHAR 3
#define TREETYPE_STR 4

extern int nb_err_sem;
extern int nb_av_sem;
extern const char *msg_err_tab[NB_TYPE_ERREURS];
extern const char *msg_indice_tab[NB_TYPE_ERREURS];

typedef struct {
    int         ligne;          
    int         colonne;
    int         type_erreur;            // cf macros
    const char  *msg;                   // un msg simple expliquant l'erreur
    const char  *indice;                // un indice pour la résoudre
    int         ligne_decla_depart;     // pour afficher la déclaration originale, si l'erreur s'y prête
    int         ligne_decla_fin;        // idem colonne
    int         est_stoppante;          // 1 si erreur, 0 si warning
}err_sem;

/**
 * S'occupera de remplir la structure.
 * Variadique car les formats différent selon le 
 * msg d'erreur, cf msg_err_tab et msg_indice_tab
 * 
 * ...
 */
err_sem *generer_erreur(int ligne, int colonne, int type_erreur, int id_decla, ...);

/**
 * Libére la mémoire allouée à une structure err_sem
 */
void supprimer_erreur(err_sem *e);

/**
 * Affiche une erreur sémantique
 * 
 * ...
 */
void erreur_semantique(err_sem *e);

void afficher_ligne_source(int num_ligne);

/**
 * Affiche un bloc de lignes du code source
 */
void afficher_bloc_source(int debut, int fin);

/**
 * Evalue le type d'une liste d'accès de champs (ex: x.a.b.c renvoie le type de c)
 */
int evaluer_type_acces_champ(int id_decla_parent, arbre liste_acces);

// Vérifie si un identifiant existe et renvoie son indice de déclaration
int verif_decla_idf(int num_lex, int nature, int ligne);

// Vérifie la compatibilité pour une affectation
void verif_compatibilite_affect(int num_lex, int t_dest, int t_src, int ligne);

// Vérifie si une condition est bien un booléen
void verif_condition_bool(int t_recu, int ligne);

// Vérifie le nombre d'arguments d'un appel
void verif_nombre_args(int num_lex, int nb_attendu, int nb_recu, int ligne);

// Helper pour transformer un code de type en chaîne lisible
const char *recup_nom_type(int type);

int verif_decla_appel(int num_lex, int ligne);

int compter_nombre_args(arbre a);

void verif_types_args(int num_lex, int decla, arbre liste_args, int ligne);

void verif_double_decla(int num_lex, int region, int nature, int ligne);

// verifie si l'acces a un tableau est bien dans les bornes
void verif_dim_hors_tab(int num_lex, int decla, arbre liste_dim, int ligne);

// verifie si on accede bien a un tableau avec toutes ses dimensions
void verif_nb_dim_taille(int num_lex, int decla, arbre liste_dim, int ligne);


//...

#endif
