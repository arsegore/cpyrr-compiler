#ifndef _TAB_REGIONS_H
#define _TAB_REGIONS_H

#include "../inc/arbre.h"

extern int num_region_courante;

typedef struct {
    int taille_exec;
    int nis;
    arbre arbre_region;
}cellule_region;

/**
 * Augmente le numéro de région courante (à appeler à l'entrée dans
 * une nouvelle région)
 */
void incrementer_region_courante();

/**
 * Diminue le numéro de région courante (à appeler en sortie de
 * région)
 */
void decrementer_region_courante();

/**
 * @return Le numéro de la région courante
 */
int region_courante();

/**
 *
 * @return Le nombre de régions actuellement englobantes
 */
int nb_regions_englobantes();

void init_tab_regions();



#endif  // _TAB_REGIONS_H
