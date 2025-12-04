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
 */
void init_pile_regions();

/**
 * @return Le sommet de la pile des régions
 */
int sommet_pile_region();

/**
 * Empile un numéro de région et met à jour la région courante
 * @param num_region : La région qu'on veut empiler
 */
void empiler_pile_regions(int num_region);

/**
 * Depile la pile des régions
 */
void depiler_pile_regions();

/**
 * @return Le nombre de régions actuellement englobantes
 */
int nb_regions_englobantes();

/**
 * Met à jour la variable globale num_region_courante
 */
void maj_region_courante();

/**
 * Affiche la pile des régions
 */
void afficher_pile_regions(int n);

#endif