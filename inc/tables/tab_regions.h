#ifndef _TAB_REGIONS_H
#define _TAB_REGIONS_H

#include "arbre/arbre.h"

/**
 * tab_regions.h
 *
 * Définition de la table des régions et de ses fonctions
 *
 * Auteur :  Adam,  Damien, Baptiste 
 */
#define TAILLE_TAB_REGIONS 150

typedef struct {
    int taille;
    int nis;
    arbre *arbre_region;
}cellule_region;

typedef cellule_region tab_region_t[TAILLE_TAB_REGIONS];

extern tab_region_t tab_region;

/**
 * Initialise la table des régions
 */
void init_tab_regions();

/**
 * Insère une nouvelle région dans la table, remplit automatiquement son
 * champ NIS
 */
void inserer_region();

/**
 * Affiche la table des régions de depart à arrivee, ou entierement si les
 * deux valeurs sont égales à -1
 *
 * @param depart : L'indice d'où l'affichage commence
 * @param arrivee : L'indice de fin de l'affichage
 */
void afficher_tab_regions(int depart, int arrivee);

/**
 *  Modifie le champ taille_exec d'une région
 *
 * @param num_region Le numéro de la région
 * @param taille Sa nouvelle taille à l'éxécution
 */
void modifier_taille(int num_region, int taille);

/**
 * Modifie le pointeur vers l'arbre de la région d'une région
 *
 * @param num_region Le numéro de la région
 * @param a Le pointeur vers l'arbre de la région
 */
void modifier_arbre_region(int num_region, arbre *a);



#endif  // _TAB_REGIONS_H
