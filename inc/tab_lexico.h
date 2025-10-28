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

typedef struct {
    int longueur;
    char *lexeme;
    int suivant;
}t_cellule_lexico; 

typedef t_cellule_lexico t_tab_lexico[TAILLE_TAB_LEXICO];

extern t_tab_lexico tab_lexico;

extern int tab_hash_code[TAILLE_TAB_HASH_CODE];

void init_tab_lexico();

int calculer_hash_code(char *lexeme);

char *recuperer_lexeme(int num_lexico);

int inserer_lexeme(char *lexeme);

void afficher_tab_lexico(int depart, int arrivee);

#endif
