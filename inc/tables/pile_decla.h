#ifndef _PILE_DECLA_H_
#define _PILE_DECLA_H_

#include "arbre/arbre.h"

/**
 * pile_decla.h
 *
 * Définition de la pile des decla et de ses fonctions
 *
 * Auteur :  louis
 */

#define TAILLE_PILE_DECLA 256

extern int pile_decla[TAILLE_PILE_DECLA];

extern int nb_decla_pile;

/**
 * Initialise la pile des decla
 */
void init_pile_decla();
/**
 * Empile un numéro de declaration 
 * @param num_decla : Le num_decla qu'on veut empiler
 */
void empiler_pile_decla(int num_region);

/**
 * Depile la pile des declarations
 */
void depiler_pile_decla();

/**
 * Affiche la pile des déclarations
 */
void afficher_pile_decla();

#endif