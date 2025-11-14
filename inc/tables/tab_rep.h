#ifndef _TAB_DESC_H
#define _TAB_DESC_H

// TODO: CORRIGER LES FONCTIONS (et/ou actions ?) SUR LES TYPES TAB

/**
 * Définition de la table de description des types et des en-têtes
 * de sous-programme
 *
 * Auteur : Louis , Adam , Baptiste 
 */

#define D_FCT 0
#define D_PROC 1
#define D_STRUCT 2
#define D_TAB 3

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_BOOL 2
#define TYPE_CHAR 3

#define TAILLE_TAB_REP 1000

extern int tab_rep[TAILLE_TAB_REP];
extern int id_rep_courante;
extern int idx_premier_libre;
extern int idx_nb_element;
extern int nbparam;
extern int nbchamps;
extern int nbdimension;
extern int deplacement;
extern int idx_type_element;

/**
 * Initialise la table de représentation
 */
void init_tab_rep();

/**
 * Affiche la table de représentation de départ à arrivée,
 * ou entièrement si départ = arrivée = -1 
 * 
 * @param depart Indice de départ
 * @param arrivee Indice d'arrivée
 */
void afficher_tab_rep(int depart, int arrivee);

/**
 * Insère val dans la première case libre de la table rep
 * 
 * @param val La valeur à insérer
 */
void inserer_tab_rep(int val);

/**
 * Insère le nb d'éléments (param/champs/dim) dans la table rep,
 * à l'indice préparé par la fonction "début" correspondante
 * 
 * @param val Le nb d'éléments à insérer
 */
void inserer_tab_rep_nb_elem(int val);

/**
 * Insère le type des élements d'un tableau dans la table rep,
 * à l'indice préparé par la fonction debut_tab
 * 
 * @param val Le type des élements du tableau
 */
void inserer_tab_rep_type(int type);

/*------------------------------------------------------*/
/* Fonctions appelées pour préparer les indices globaux */
/*------------------------------------------------------*/
void debut_proc();

void debut_struct();

/**
 * @param type Le type de retour de la fonction
 */
void debut_fct(int type);

void debut_tab();

void incr_nb_dim();

void incr_nb_champ();

void incr_depl();

void incr_param();

#endif
