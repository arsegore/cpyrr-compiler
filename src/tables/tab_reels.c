#include "tables/tab_reels.h"
#include <stdio.h>

/**
 * Table vrm simpliste pour stocker les réels et les faire correspondre à un id int
 */

float tab_reels[TAILLE_TAB_REELS];
int nb_reels = 0;

int inserer_reel(float f) {
    tab_reels[nb_reels] = f;
    return nb_reels++;
}