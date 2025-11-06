#ifndef _TAB_DESC_H
#define _TAB_DESC_H

/**
 * Définition de la table de description des types et des en-têtes
 * de sous-programme
 *
 * Auteur : Adam HADDADI
 */

#define D_FCT 0
#define D_PROC 1
#define D_STRUCT 2
#define D_TAB 3

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_BOOL 2
#define TYPE_CHAR 3

#define TAILLE_TAB_DESC 1000

extern int tab_desc[TAILLE_TAB_DESC];

/**
 * Initialise la table de description
 */
void init_tab_desc();

/**
 * Insère une entrée dans la table de description.
 * Attention à bien mettre les arguments dans le bon ordre :
 * Fonction :
 *      ..(D_FCT, nb d'arguments, type retourné, num lex du ième argument,
 *      type du ième argument, ...)
 *
 * Procédure :
 *      ..(D_PROC, nb d'arguments, num lex du ième argument, type du ième
 *      argument, ...)
 *
 * Structure :
 *      ..(D_STRUCT, nb champs, num lex du ième champ, type du ième champ,
 * deplacement à l'execution du ième champ, ...)
 *
 * Tableau :
 *      ..(D_TAB, type des éléments, nb dimensions, borne inf de la ième dim,
 * borne sup de la ième dim, ...)
 *
 * @param type_desc : Le type de description à inséré (D_FCT, D_PROC, D_STRUCT,
 * D_TAB)
 * @param nb : Le nombre de champs/arguments/dimensions
 * @param ... : Les détails de chaque champ/argument/dimension
 * @return Le numéro de description correspondant à l'entrée (son indice de
 * départ)
 */
int inserer_description(int type_desc, int nb, ...);

/**
 * Affiche la table descriptive de depart à arrivee, ou entierement si les
 * deux valeurs sont égales à -1
 *
 * @param depart : L'indice d'où l'affichage commence
 * @param arrivee : L'indice de fin de l'affichage
 */
void afficher_tab_desc(int depart, int arrivee);

#endif
