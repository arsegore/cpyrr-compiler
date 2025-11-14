#ifndef _ARBRE_H_
#define _ARBRE_H_

/**
 * Définition d'un TAD Arbre utilisé pour la construction
 * des arbres abstraits
 *
 * Auteurs : GRANJON Damien, HADDADI Adam
 */

#define A_IDF 1
#define A_CSTE_ENTIERE 2
#define A_AFFECT 3
#define A_PLUS 4
#define A_MOINS 5
#define A_MULT 6
#define A_DIV 7
#define A_OPAFF 8
#define A_APPEL_PROC 9
#define A_APPEL_FCT 10
#define A_LISTE_I 11
#define A_TANT_QUE 12
#define A_IF_THEN_ELSE 13

/**
 * Chaque noeud connait sa nature et sa valeur, ainsi qu'évidemment
 * qui sont ses fils (sous forme d'un pointeur sur le fils gauche
 * et d'une chaîne de frères droits)
 */
typedef struct noeud {
    int nature;
    int valeur;
    struct noeud *fils_gauche;
    struct noeud *frere_droit;
} noeud;
typedef struct noeud *arbre;

/**
 * Ajoute un fils à un arbre
 *
 * @param pere : L'arbre à qui ajouter un fils
 * @param fils : Le fils à ajouter
 * @return : L'arbre résultat
 */
arbre concat_pere_fils(arbre pere, arbre fils);

/**
 * Ajoute un frère à un arbre
 *
 * @param pere : L'arbre à qui ajouter un frère
 * @param frere : Le frère à ajouter
 * @return : L'arbre résultat
 */
arbre concat_pere_frere(arbre pere, arbre frere);

/**
 * Crée un noeud (un nouvel arbre)
 *
 * @param nature : La nature du noeud
 * @param valeur : La valeur du noeud
 * @return : L'arbre résultat
 */
arbre creer_noeud(int nature, int valeur);

/**
 * Affiche un arbre
 *
 * @param a : L'arbre à afficher
 */
void afficher_arbre(arbre a);

/**
 * Exécute un arbre
 * 
 * @param a : L'arbre à exécuter
 */
void execute_arbre(arbre a);

// à faire
int execute_arbre_fct(arbre a);

/**
 * Evalue un arbre
 * 
 * @param a : L'arbre à évaluer
 * @return : L'évaluation de l'arbre
 */
int evalue_arbre_int(arbre a);

#endif