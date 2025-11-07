#ifndef _ARBRE_H_
#define _ARBRE_H_

/**
 * Définition d'un TAD Arbre utilisé pour la construction
 * des arbres abstraits
 *
 * Auteur : Adam 
 */

#define A_IDF 1
#define A_CSTE_ENTIERE 2
#define A_AFFECT 3
#define A_PLUS 4
#define A_MOINS 5
#define A_MULT 6
#define A_DIV 7

/**
 * Chaque noeud connait sa nature et sa valeur, ainsi qu'évidemment
 * qui sont ses fils (sous forme d'un pointeur sur le fils gauche
 * et d'une chaîne de frères droits
 */
struct noeud {
    int nature;
    int valeur;
    struct noeud *filsGauche;
    struct noeud *frereDroit;
};
typedef struct noeud *arbre;

/**
 * Ajoute un fils à un arbre
 *
 * @param pere : L'arbre à qui ajouter un fils
 * @param fils : Le fils à ajouter
 * @return : L'arbre résultat
 */
arbre concatPereFils(arbre pere, arbre fils);

/**
 * Ajoute un frère à un arbre
 *
 * @param pere : L'arbre à qui ajouter un frère
 * @param frere : Le frère à ajouter
 * @return : L'arbre résultat
 */
arbre concatPereFrere(arbre pere, arbre frere);

/**
 * Crée un noeud (un nouvel arbre)
 *
 * @param nature : La nature du noeud
 * @param valeur : La valeur du noeud
 * @return : L'arbre résultat
 */
arbre creerNoeud(int nature, int valeur);

/**
 * Affiche un arbre
 *
 * @param a : L'arbre à afficher
 */
void afficher_arbre(arbre a);

#endif
