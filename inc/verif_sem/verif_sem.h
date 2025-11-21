#ifndef _VERIF_SEM_H_
#define _VERIF_SEM_H_

#define NB_TYPE_ERREURS 22

// erreurs de déclaration
#define E_VAR_NON_DECLAREE 0
#define E_FCT_NON_DECLAREE 1
#define E_PROC_NON_DECLAREE 2
#define E_STRUCT_NON_DECLAREE 3
#define E_TAB_NON_DECLAREE 4
#define E_PARAM_NON_DECLARE 5
#define E_CHAMP_NON_DECLARE 6

// erreurs de types non compatibles
#define E_TYPE_AFF 8
#define E_TYPE_CALCUL 9
#define E_TYPE_CONDITION 10
#define E_TYPE_NON_COMPATIBLE 11

// erreurs sur un appel de fct/proc
#define E_NB_ARGS 12
#define E_TYPE_ARG 13
#define E_PROC_COMME_FCT 14
#define E_FCT_COMME_PROC 15

// erreurs de tentative d'accès à un champ/un élément
#define E_NON_TAB 16
#define E_NON_STRUCT 17
#define E_ID_NON_ENTIER 18

// erreurs de retours de fonction 
#define E_NE_RET_PAS 19
#define E_RET_MAUVAIS_TYPE 20
#define E_PROC_RET 21

#define DEBUT_WARNINGS 22

extern int nb_err_sem;
extern int nb_av_sem;
extern const char *msg_err_tab[NB_TYPE_ERREURS];
extern const char *msg_indice_tab[NB_TYPE_ERREURS];

typedef struct {
    int ligne;          
    int colonne;
    int type_erreur;        // cf macros
    const char *msg;        // un msg simple expliquant l'erreur
    const char *indice;     // un indice pour la résoudre
    int ligne_decla;        // pour afficher la déclaration originale, si l'erreur s'y prête
    int colonne_decla;      // idem colonne
    int est_stoppante;      // 1 si erreur, 0 si warning
}err_sem;

/**
 * S'occupera de remplir la structure
 * variadique car les formats différent selon le 
 * msg d'erreur, cf msg_err_tab et msg_indice_tab
 * 
 * ...
 */
err_sem *generer_erreur(int ligne, int colonne, int type_erreur, ...);

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

//...

#endif
