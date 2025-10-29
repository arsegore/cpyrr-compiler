#ifndef _TAB_DECLA_H_
#define _TAB_DECLA_H_

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



// on définit une matrice qui est capable de stocker pour chaque variable sa nature
// col 0 -> Nature
// col 1 -> Chainage sur declaration du meme nom
// col 2 -> Num de region qui contient la declaration
// col 3 -> si nature = 1 ou 2 index de la table contenant descrip
// col 3 -> si nature = 3 ou 4 index du type ( si 0, 1, 2 ou 3 alors type primaire
// col 3 -> sinon index de la table description d'entête
// col 4 -> si nature = 1 ou 2 taille a l'execution de la valeur de ce type
// col 4 -> si nature = 3 ou 4  deplacement a l'execution de l'emplacement associe
// col 4 -> sinon numero de la regio nassocie a la procedure ou fonction

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
 * todo
 */
void inserer_declaration(int num_lexico, int nature, int region);

#endif
