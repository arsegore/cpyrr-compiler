#ifndef MACHINE_VIRTUELLE_H
#define MACHINE_VIRTUELLE_H

#include "arbre/arbre.h"
#include "arbre/pile_exec.h"

extern int retourne;
extern val valeur_retour;
extern int region_courante;

/**
 * Renvoie l'adresse dans la pile d'une variable 
 * 
 * @param a : L'arbre de la variable
 * @author :  Adam
 */
int recuperer_case_variable(arbre a);

/**
 * Initialise une nouvelle région dans la pile (chainages..)
 * 
 * @param num_decla : Le numéro de déclaration de la fct/procédure
 * @author  Adam
 */
void debut_region(int num_decla);

/**
 * Execute l'arbre d'une région
 * 
 * @param a : L'arbre de la région à éxécuter
 * @author :  Adam
 */
void execute_arbre(arbre a);

/**
 * Execute un appel (préparation des arguments et de la "zone mémoire")
 * 
 * @param a : L'arbre de la région à éxécuter
 * @author :  Adam
 */
void appel_region(arbre a);

/**
 * Evalue l'arbre d'une valeur entière (expression arithmétique entière)
 * 
 * @param a : L'arbre à évaluer
 * @author :  Adam
 * @author :  Damien
 */
int evaluer_arbre_int(arbre a);

/**
 * Evalue l'arbre d'une valeur booléenne (expression booléenne)
 * 
 * @param a : L'arbre à évaluer
 * @author :  Adam
 */
int evaluer_arbre_bool(arbre a);

/**
 * Evalue l'arbre d'une valeur rééelle (expression arithmétique rééelle)
 * 
 * @param a : L'arbre à évaluer
 * @author :  Adam
 */
float evaluer_arbre_reel(arbre a);

/**
 * Evalue une expression quelconque (se charge d'appeler la fonction pour le 
 * bon type)
 * 
 * @param a : L'arbre à évaluer
 * @author :  Adam
 */
val evaluer_expression(arbre a);

/**
 * Démarre l'éxécution du programme 
 * 
 * @author :  Adam
 */
void lancer_execution();

#endif