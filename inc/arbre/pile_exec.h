#ifndef _PILE_EXEC_H_
#define _PILE_EXEC_H_

/**
 * pile_exec.h
 *
 * Définition de la pile d'exécution et de ses fonctions
 *
 * Auteur : GRANJON Damien
 */

#define TAILLE_PILE_EXEC 5000
#define BC base_courante

typedef enum {
    CHAINAGE,
    VARIABLE
} type_cellule;

typedef union {
    int entier;
    float reel;
    int bool;
    char caractere;
} val;

typedef struct {
    char *lexeme;
    int type_var; // 0, 1, 2, 3
    val valeur;
} var;

typedef struct {
    union {
        int chainage;
        var donnees;
    } contenu;
    type_cellule type;
} cellule;

extern cellule pile_exec[TAILLE_PILE_EXEC];

extern int base_courante;

extern int taille_pile_exec;

/**
 * Initialise la pile d'exécution
 * @author : GRANJON Damien
 * @author : HADDADI Adam
 */
void init_pile_exec();


/**
 * Empile un chainage 
 * 
 * @param base_courante : La valeur de BC à empiler
 * @author : GRANJON Damien
 * @author : HADDADI Adam
 */
void empiler_pile_exec_chainage(int base_courante);

/**
 * Empile une variable
 * 
 * @param variable : valeur de la variable
 * @author : GRANJON Damien
 * @author : HADDADI Adam
 */
void empiler_pile_exec_variable(var variable);

/**
 * Affiche la pile d'exécution
 * @author : HADDADI Adam
 */
void afficher_pile_exec();

/**
 * Fait des empilements "fantomes" pour augmenter la taille de la pile en prévision de ce qu'on va y remplir
 * @author : HADDADI Adam
 */
void allouer_taille(int taille);

#endif