#ifndef _TAB_LEXICO_H_
#define _TAB_LEXICO_H_

/**
 * tab_lexico.h 
 *
 * Définition de la table et de ses fonctions. 
 * La table lexicographique est représentée par un tableau de t_cellule_lexico
 *
 * Auteur : Adam 
 */

#define TAILLE_TAB_LEXICO 500
#define TAILLE_TAB_HASH_CODE 32

/**
 * La table lexico est l'assemblage de deux structures : 
 * - Un tableau de t_cellule_lexico
 * - Une table de hash-code
 */ 
typedef struct {
    int longueur;
    char *lexeme;
    int suivant;
}t_cellule_lexico; 
typedef t_cellule_lexico t_tab_lexico[TAILLE_TAB_LEXICO];
extern t_tab_lexico tab_lexico;
extern int tab_hash_code[TAILLE_TAB_HASH_CODE];

/**
 * Initialise la table lexico, (-1 pour les entiers, NULL pour les léxèmes)
 * 
 * @author :  Adam
 */
void init_tab_lexico();

/**
 * Renvoie le hash-code d'un léxème, permettant de définir 
 * dans quelle zone de la table lexico il sera doit être inséré
 *
 * @param lexeme : Un léxème 
 * @return : Le hash-code du léxème
 * 
 * @author :  Adam
 */
int calculer_hash_code(char *lexeme);

/**
 * Renvoie le léxème correspondant à un numéro lexicographique 
 * donné 
 *
 * @param num_lexico : Le numéro lexico du léxème recherché
 * @return : Le léxème correspondant dans la table
 * 
 * @author :  Adam
 */
char *recuperer_lexeme(int num_lexico);

/** 
 * Insère un léxème dans la table lexico.
 *
 * @param lexeme : Le léxème à insérer dans la table lexico
 * @param longueur : La longueur du léxème
 * @return : Le numéro lexico du léxème inséré (ou du léxème déjà présent le
 * cas écheant)
 * @author :  Adam
 */
int inserer_lexeme(char *lexeme, int longueur);

/**
 * Affiche la table lexico de depart à arrivee, ou entierement si les 
 * deux valeurs sont égales à -1
 *
 * @param depart : L'indice d'où l'affichage commence
 * @param arrivee : L'indice de fin de l'affichage
 * @author :  Adam
 */
void afficher_tab_lexico(int depart, int arrivee);

#endif
