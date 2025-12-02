#ifndef _TAB_DECLA_H_
#define _TAB_DECLA_H_

#define N_TYPE_B 0
#define N_STRUCT 1
#define N_TAB 2
#define N_VAR 3
#define N_PARAM 4 
#define N_PROC 5
#define N_FCT 6
#define N_CH_STRUCT 7
#define N_ARG 8
#define TYPE 9

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

extern int tab_decla[HAUTEUR][LARGEUR];
extern int decla_courante;
extern int decla_precedente;

/**
 * Initialise la table des déclarations 
 */
void init_tab_decla();

/**
 *  Initialise la variable decla_precedente, permet  de remplir le champs exec 
 */
void memoriser_precedente_decla(int decla_actuelle);

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
 * Détermine la ligne dans laquelle insérer la déclaration courante en 
 * fonction de son num lexico
 */
void determiner_ligne_decla(int num_lexico);

void remplir_nature(int num_decla, int nature);

void remplir_region(int num_decla, int region);

void remplir_desc(int num_decla, int desc);

void remplir_exec(int num_decla);

int taille_type(int num_type);

#endif
