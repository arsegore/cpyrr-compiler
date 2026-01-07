#ifndef _PILE_REGIONS_H_
#define _PILE_REGIONS_H_

#include "arbre/arbre.h"

/**
 * pile_regions.h
 *
 * Définition de la pile des régions et de ses fonctions
 *
 * Auteur :  Adam,  Damien
 */

#define TAILLE_PILE_REGIONS 150

extern int pile_regions[TAILLE_PILE_REGIONS];

extern int nb_regions_pile;

extern int num_region_courante;

/**
 * Initialise la pile des régions
 * 
 * @author :  Damien
 * @author :  Adam
 */
void init_pile_regions();

/**
 * @return Le sommet de la pile des régions
 * 
 * @author :  Damien
 * @author :  Adam
 */
int sommet_pile_region();

/**
 * Empile un numéro de région et met à jour la région courante
 * 
 * @param num_region : La région qu'on veut empiler
 * @author :  Damien
 * @author :  Adam
 
 */
void empiler_pile_regions(int num_region);

/**
 * Depile la pile des régions
 * @author :  Damien
 * @author :  Adam
 */
void depiler_pile_regions();

/**
 * @return Le nombre de régions actuellement englobantes
 * @author :  Damien
 * @author :  Adam
 */
int nb_regions_englobantes();

/**
 * Met à jour la variable globale num_region_courante
 * @author :  Damien
 * @author :  Adam
 */
void maj_region_courante();

/**
 * Affiche la pile des régions
 * @author :  Damien
 * @author :  Adam
 */
void afficher_pile_regions(int n);

#endif