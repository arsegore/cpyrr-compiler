#ifndef _TAB_REGIONS_H
#define _TAB_REGIONS_H

#include "arbre/arbre.h"

/**
 * tab_regions.h
 *
 * Définition de la table des régions et de ses fonctions
 *
 * Auteur : HADDADI Adam, GRANJON Damien, Baptiste MOULIN
 */
#define TAILLE_TAB_REGIONS 150

typedef struct {
    int taille;
    int nis;
    arbre arbre_region;
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
void inserer_region(int taille);

/**
 * Affiche la table des régions
 */
void afficher_tab_regions();

/**
 *  Modifie le champ taille_exec d'une région
 *
 * @param num_region Le numéro de la région
 * @param taille Sa nouvelle taille à l'éxécution
 */
void modifier_taille(int num_region, int taille);

/**
 * Calcule la taille finale d'une région 
 * 
 * @param num_region : Le numéro de la région
 * @param deplacement_final : Le déplacement final en sortant de la région
 */
void mettre_a_jour_taille_region(int num_region, int deplacement_final);

/**
 * Evalue la taille de la région 0
 */
void evaluer_taille_programme();

/**
 * Modifie le pointeur vers l'arbre de la région d'une région
 *
 * @param num_region Le numéro de la région
 * @param a L'arbre de la région
 */
void modifier_arbre_region(int num_region, arbre a);



#endif  // _TAB_REGIONS_H
