#ifndef _PILE_DECLA_H_
#define _PILE_DECLA_H_

#include "arbre/arbre.h"

/**
 * pile_decla.h
 *
 * Définition de la pile des decla et de ses fonctions
 *
 * Auteur : PELOUX louis
 */

#define TAILLE_PILE_DECLA 256

extern int pile_decla[TAILLE_PILE_DECLA];

extern int nb_decla_pile;

/**
 * Initialise la pile des decla
 * 
 * @author : PELOUX Louis
 */
void init_pile_decla();
/**
 * Empile un numéro de declaration 
 * 
 * @param num_decla : Le num_decla qu'on veut empiler
 * 
 * @author : PELOUX Louis
 */
void empiler_pile_decla(int num_region);

/**
 * Renvoie le sommet de la pile des déclarations
 * 
 * @author : PELOUX Louis
 */
int sommet_pile_decla();

/**
 * Depile la pile des declarations
 * 
 * @author : PELOUX Louis
 */
void depiler_pile_decla();

/**
 * Affiche la pile des déclarations
 * 
 * @author : PELOUX Louis
 */
void afficher_pile_decla();

#endif