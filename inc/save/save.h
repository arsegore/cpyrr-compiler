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
#define NOM_FIC_SAVE_TAB_DECLA "saves/fic_save_tab_decla.txt"
#define NOM_FIC_SAVE_TAB_REGIONS "saves/fic_save_tab_regions.txt"
#define NOM_FIC_SAVE_TAB_REP "saves/fic_save_tab_rep.txt"

/**
 * Sauvegarde en mémoire la table lexicographique, sous la forme :
 *
 *
 * //------------(debut fichier)----------------------------------------------
 * 'valeur' 'valeur' 'valeur' ...               //--->pour chaque element de la table de hash code
 *
 * 'longueur' 'lexeme' 'suivant'
 * 'longueur' 'lexeme' 'suivant'             
 * ...                                                  //--->pour chaque element de la tab lexico
 *
 * //------------(fin fichier)------------------------------------------------
 *
 *
 */
void save_tab_lex();

/**
 * Sauvegarde en mémoire la table des déclarations, sous la forme :
 *
 *
 * //------------(debut fichier)----------------------------------------------
 * 'nature' 'suivant' 'region' 'description' 'exec'
 * 'nature' 'suivant' 'region' 'description' 'exec'
 * ...                                                  //--->pour chaque element de la tab des decla
 *
 * //------------(fin fichier)------------------------------------------------
 *
 *
 */
void save_tab_decla();

/**
 * Sauvegarde en mémoire la table des régions, sous la forme :
 *
 *
 * //------------(debut fichier)----------------------------------------------
 * 'taille' 'nis' 'arbre'
 * 'taille' 'nis' 'arbre'
 * ...                                                  //--->pour chaque element de la tab des regions
 *
 * //------------(fin fichier)------------------------------------------------
 *
 *
 */
void save_tab_regions();

/**
 * Sauvegarde en mémoire la table de représentation des types et entêtes de sous programmes, sous la forme :
 *
 *
 * //------------(debut fichier)----------------------------------------------
 * 'valeur' 'valeur' 'valeur' ...                       //--->pour chaque element de la tab rep
 *
 * //------------(fin fichier)------------------------------------------------
 *
 *
 */
void save_tab_rep();