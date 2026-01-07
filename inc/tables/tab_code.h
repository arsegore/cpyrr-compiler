#ifndef _TAB_CODE_H_
#define _TAB_CODE_H_

#define NB_LIGNES_MAX_PROG 1000
#define TAILLE_MAX_LIGNE 512

/**
 * Table contenant le code source pour pouvoir s'y référer dans les msg d'erreur
 */
extern const char *tab_code[NB_LIGNES_MAX_PROG];
extern int nb_lignes;

/**
 * Initialise la table de code 
 * 
 * @author : HADDADI Adam
 */
void init_tab_code();


/**
 * Affiche la table de code 
 * 
 * @author : HADDADI Adam
 */
void afficher_tab_code();

/**
 * Ajoute une ligne dans la table
 *  
 * @param ligne : La ligne à ajouter
 * @author : HADDADI Adam
 */
void ajouter_ligne_code(const char *ligne);

/**
 * Récupère une ligne de code
 * 
 * @param num_ligne : Le numéro de la ligne à récupérer
 * @author : HADDADI Adam
 */
void recup_ligne_code(int num_ligne);

#endif