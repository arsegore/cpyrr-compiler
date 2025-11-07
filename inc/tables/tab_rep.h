#ifndef _TAB_DESC_H
#define _TAB_DESC_H

/**
 * Définition de la table de description des types et des en-têtes
 * de sous-programme
 *
 * Auteur : Adam 
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
extern int indice_pv;
extern int indice_dv;



/**
 * Initialise la table de description
 */
void init_tab_rep();

/**
 * Insère une entrée dans la table de description.
 * @return Le numéro de description correspondant à l'entrée (son indice de
 * départ)
 */

void afficher_tab_rep(int depart, int arrivee);

void inserer_tab_rep(int val);

#endif
