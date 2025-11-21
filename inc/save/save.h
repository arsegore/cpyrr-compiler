#include <stdio.h>
#include <stdlib.h>
#include "tables/tab_lexico.h"
#include "tables/tab_decla.h"
#include "tables/tab_regions.h"
#include "tables/tab_rep.h"

/**
 * save.h 
 *
 * Définition des fonctions de sauvergarde en mémoire des tables
 *
 * Auteur : Baptiste MOULIN
 */

#define NOM_DOSSIER_SAVES "saves"
#define NOM_FIC_SAVE_TAB_LEX "saves/fic_save_tab_lex.txt"

/**
 * Sauvegarde en mémoire la tab lexico, sous la forme :
 *
 *
 * //------------(debut fichier)----------------------------------------------
 * 'valeur' ' ' 'valeur' ' ' 'valeur' ...               //--->pour chaque element de la table de hash code
 *
 * 'longueur' ' ' 'lexeme' ' ' 'suivant'
 * 'longueur' ' ' 'lexeme' ' ' 'suivant'             
 * ...                                                  //--->pour chaque element de la tab lexico
 *
 * //------------(fin fichier)------------------------------------------------
 *
 *
 */
void save_tab_lex();