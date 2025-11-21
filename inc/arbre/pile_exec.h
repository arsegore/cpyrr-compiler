#ifndef _PILE_EXEC_H_
#define _PILE_EXEC_H_

/**
 * pile_exec.h
 *
 * Définition de la pile d'exécution et de ses fonctions
 *
 * Auteur :  Damien
 */

#define TAILLE_PILE_EXEC 5000

typedef union {
    int entier;
    float reel;
    int booleen;
    char caractere;
} val;

typedef struct {
    char * lexeme;
    int a_valeur; // -1 si la variable n'a pas de valeur, sinon 0, 1, 2 ou 3
    val valeur;
} var;

typedef struct {
    int chainage;
    var variable;
} cellule;

extern cellule pile_exec[TAILLE_PILE_EXEC];

extern int base_courante;

extern int taille_pile_exec;

/**
 * Initialise la pile d'exécution
 */
void init_pile_exec();

/**
 * @return Le sommet de la pile d'exécution
 */
cellule sommet_pile_exec();

/**
 * @param chainage : valeur du chainage, -1 si on veut empiler une variable
 * @param variable : valeur de la variable
 */
void empiler_pile_exec();

/**
 * Met à jour la variable globale base_courante
 */
void maj_base_courante();

/**
 * Affiche la pile d'exécution
 */
void afficher_pile_exec();

#endif