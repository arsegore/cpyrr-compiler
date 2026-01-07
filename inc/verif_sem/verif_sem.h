#ifndef _VERIF_SEM_H_
#define _VERIF_SEM_H_

/**
 * Auteur : HADDADI Adam
 */

#include "arbre/arbre.h"

#define NB_TYPE_ERREURS 30

// erreurs de déclaration
#define E_VAR_NON_DECLAREE 0
#define E_FCT_NON_DECLAREE 1
#define E_PROC_NON_DECLAREE 2
#define E_TYPE_NON_DECLARE 3
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
#define E_TYPE_INEXISTANT 27
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
#define E_RET_MANQUANT 19
#define E_RET_MAUVAIS_TYPE 20
#define E_PROC_RET 21
#define E_RET_INCOHERENT 24

#define DEBUT_WARNINGS 25

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
 * @param ligne : La ligne où l'erreur a été rencontrée
 * @param colonne : La colonne où l'erreur a été rencontrée 
 * @param type_erreur : Le code représentant le type d'erreur
 * @param id_decla : Le numéro de déclaration qui va bien (c contextuel)
 * @param ... : Les divers arguments des messages d'erreur
 * @author : HADDADI Adam
 */
err_sem *generer_erreur(int ligne, int colonne, int type_erreur, int id_decla, ...);

/**
 * Libére la mémoire allouée à une structure err_sem
 * 
 * @param e : L'erreur à supprimer
 * @author : HADDADI Adam
 */
void supprimer_erreur(err_sem *e);

/**
 * Affiche une erreur sémantique
 * 
 * @param e : L'erreur à afficher
 * @author : HADDADI Adam
 */
void erreur_semantique(err_sem *e);

/**
 * Affiche une ligne du code source
 * 
 * @param num_ligne : Le numéro de la ligne ) afficher
 * @author : HADDADI Adam
 */
void afficher_ligne_source(int num_ligne);

/**
 * Affiche un bloc de lignes du code source
 * 
 * @param debut : Le numéro de la ligne de début du bloc
 * @param fin : Le numéro de la ligne de fin du bloc
 * @author : HADDADI Adam
 */
void afficher_bloc_source(int debut, int fin);

/**
 * Evalue le type d'une liste d'accès de champs (ex: x.a.b.c renvoie le type de c)
 * 
 * @param id_decla_parent : Le numéro de déclaration de la variable dans laquelle se font les accès
 * @param liste_acces : L'arbre représentant la liste d'accès
 * @author : HADDADI Adam
 */
int evaluer_type_acces_champ(int id_decla_parent, arbre liste_acces);

/**
 * Vérifie si un IDF utilisé est bien déclaré et renvoie son numéro de déclaration
 * 
 * @param num_lex : Le numéro du léxème
 * @param nature : La nature recherchée
 * @param ligne : La ligne à laquelle est lancée la verif 
 * @author : HADDADI Adam
 */
int verif_decla_idf(int num_lex, int nature, int ligne);

/**
 * Vérifie que les deux types d'une affectation sont bien compatibles
 * 
 * @param num_lex : Le num lex du membre de gauche
 * @param t_dest : Le type attendu a gauche
 * @param t_src : Le type passé à droite
 * @param ligne : La ligne à laquelle est lancée la verif 
 * @author : HADDADI Adam
 */
void verif_compatibilite_affect(int num_lex, int t_dest, int t_src, int ligne);

/**
 * Vérifie qu'une condition est bien une expression booléenne
 * 
 * @param t_recu : Le type reçu dans la condition
 * @param ligne : La ligne à laquelle est lancée la verif 
 * @author : HADDADI Adam
 */
void verif_condition_bool(int t_recu, int ligne);

/**
 * Vérifie qu'un appel de fonction ou procédure a le bon nombre d'arguments
 * 
 * @param num_lex : Le numéro lexico de la fct/proc
 * @param nb_attendu : Le nombre d'arguments attendus
 * @param nb_recu : Le nombre d'arguments recus
 * @param ligne : La ligne à laquelle est lancée la verif 
 * @author : HADDADI Adam
 */
void verif_nombre_args(int num_lex, int nb_attendu, int nb_recu, int ligne);

/**
 * Vérifie qu'il existe une procédure ou fonction déclarée 
 * 
 * @param num_lex : Le numéro lexico de la fct/proc
 * @param ligne : La ligne à laquelle est lancée la verif 
 * @author : HADDADI Adam
 */
int verif_decla_appel(int num_lex, int ligne);

/**
 * Vérifie que tous les arguments d'un appel sont des types attendus
 * 
 * @param num_lex : Le numéro lexico de la fct/proc
 * @param decla : Le numéro de déclaration de la fct/proc
 * @author : HADDADI Adam
 */
void verif_types_args(int num_lex, int decla, arbre liste_args, int ligne);

/**
 * Vérifie qu'il n'y a pas de double déclaration du même type dans la même scope
 * (surcharge autorisée donc seul le type est contraignant)
 * 
 * @param num_lex : Le numéro lexico du léxème à verifier
 * @param region : La région dans laquelle chercher (sa scope, donc aussi régions englobantes)
 * @param nature : La nature de la déclaration 
 * @param ligne : La ligne à laquelle a été lancée la verif
 * @author : HADDADI Adam
 */
void verif_double_decla(int num_lex, int region, int nature, int ligne);

/**
 * Vérifie qu'une fonction renvoie bien le type attendu (aussi utile avec une procédure, on
 * dit que son type de retour est -1)
 * 
 * @param num_lex : Le numéro lexico de la fct/proc
 * @param t_attendu : Le type de retour attendu
 * @param t_recu : Le type de retour recu
 * @param decla : Le numero de décla de la fct/proc
 * @param ligne : La ligne à laquelle a été lancée la verif
 * @author : HADDADI Adam
 */
void verif_type_retour(int num_lex, int t_attendu, int t_recu, int decla, int ligne);

/**
* Verifie que les dimension données lors d'un acces a un tableau sont coherente
*(c'est a dire compris dans les bornes données)
*
* @param num_lex : Le numéro lexico du tableau
* @param decla : Le numero de décla du tableau
* @param liste_dim : un abre pointant sur la ou les dimension données
* @param ligne : La ligne à laquelle a été lancée la verif
* @author PELOUX Louis
*/
void verif_dim_hors_tab(int num_lex, int decla, arbre liste_dim, int ligne);

/**
* Verifie lors de l'accès a un tablea uqu'on utilise le même nombre de 
* dimension que la declaration 
*
* @param num_lex : Le numéro lexico du tableau
* @param decla : Le numero de décla du tableau
* @param liste_dim : un abre pointant sur la ou les dimension données
* @param ligne : La ligne à laquelle a été lancée la verif
* @author PELOUX Louis
*/
void verif_nb_dim_taille(int num_lex, int decla, arbre liste_dim, int ligne);

/* helpers ... */
const char *recup_nom_type(int type);

/**
* Permet de compter le nombre de dimension passé lors d'un acces au tableau
*
* @param a : nombre de dimension passé
* @author PELOUX louis
*/
int compter_nombre_args(arbre a);




//...

#endif
