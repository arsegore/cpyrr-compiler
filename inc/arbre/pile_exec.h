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

extern int pile_exec[TAILLE_PILE_EXEC];

extern int base_courante;

/**
 * Initialise la pile d'exécution
 */
void init_pile_exec();

/**
 * @return Le sommet de la pile d'exécution
 */
int sommet_pile_exec();

/**
 * 
 */
void empiler_pile_exec();

/**
 * Depile la pile d'exécution
 */
void depiler_pile_exec();

/**
 * Met à jour la variable globale base_courante
 */
void maj_base_courante();

/**
 * Affiche la pile d'exécution
 */
void afficher_pile_exec();

#endif