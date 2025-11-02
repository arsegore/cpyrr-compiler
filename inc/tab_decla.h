#ifndef _TAB_DECLA_H_
#define _TAB_DECLA_H_

#define N_TYPE_B 0
#define N_STRUCT 1
#define N_TAB 2
#define N_VAR 3
#define N_PARAM 4 
#define N_PROC 5
#define N_FONC 6
#define N_CH_STRUCT 7

#define HAUTEUR 5000
#define LARGEUR 5
#define NATURE 0
#define SUIVANT 1 
#define REGION 2
#define DESCRIPTION 3
#define EXECUTION 4

#define DEBORDEMENT 500


/**
 * Implantation de la table des déclarations (pas encore au point) 
 *
 * Auteurs: PELOUX Louis, RODRIGUES Paul, HADDADI Adam 
 */

extern int table_decl[HAUTEUR][LARGEUR];

/**
 * Initialise la table des déclarations 
 */
void init_tab_decla();

/**
 * Afficher une ligne donnée de la table des déclarations 
 *
 * @param num : Le numéro de la ligne à afficher 
 * @param entete : 1 si on veut afficher l'entete, 0 sinon
 */
void afficher_ligne(int num, int entete);

/**
 * Affiche la table des déclarations
 */
void afficher_tab_decla();

/**
 * Insère un nouvel élement dans la table des déclarations
 *
 * @param num_lexico : Le numéro lexico du léxème correspondant
 * @param nature : La nature de la déclaration 
 * @param region : La région dans laquelle elle a été rencontrée 
 * ... pas terminé
 */
void inserer_declaration(int num_lexico, int nature, int region);

#endif
