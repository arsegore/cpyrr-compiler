#ifndef MACHINE_VIRTUELLE_H
#define MACHINE_VIRTUELLE_H

#include "arbre/arbre.h"
#include "arbre/pile_exec.h"

extern int retourne;
extern val valeur_retour;
extern int region_courante;

int recuperer_case_variable(arbre a);
void debut_region(int num_decla);
void execute_arbre(arbre a);
int evaluer_arbre_int(arbre a);
int evaluer_arbre_bool(arbre a);
float evaluer_arbre_reel(arbre a);
val evaluer_expression(arbre a);
void appel_region(arbre a);
void lancer_execution();

#endif