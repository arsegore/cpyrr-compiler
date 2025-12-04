#ifndef _ARBRE_H_
#define _ARBRE_H_

/**
 * Définition d'un TAD Arbre utilisé pour la construction
 * des arbres abstraits
 *
 * Auteurs : TAD : Damien 
 *           Génération : Adam 
 */

#define A_IDF               1

#define A_CSTE_ENTIERE      2
#define A_CSTE_BOOL         3
#define A_CSTE_CHAINE       4
#define A_CSTE_CHAR         5
#define A_CSTE_REELLE       6

#define A_AFFECT            7
#define A_PLUS              8
#define A_MOINS             9
#define A_MULT              10
#define A_DIV               11
#define A_MOD               12

#define A_RIEN              13

#define A_APPEL_PROC        14 
#define A_APPEL_FCT         15
#define A_RET               16

#define A_LISTE_I           17 

#define A_TANT_QUE          18
#define A_SI_ALORS_SINON    19

#define A_ET                20
#define A_OU                21
#define A_NON               22
#define A_EGAL              23
#define A_DIFF              24
#define A_INF               25
#define A_SUP               26
#define A_INFEGAL           27
#define A_SUPEGAL           28

#define A_ACCES_TAB         29
#define A_ACCES_STRUCT      30

/**
 * Chaque noeud connait sa nature et sa valeur, ainsi qu'évidemment
 * qui sont ses fils (sous forme d'un pointeur sur le fils gauche
 * et d'une chaîne de frères droits)
 */
typedef struct noeud {
    int             nature;     // num decl 
    int             valeur;
    int             decla;
    struct noeud *  fils_gauche;
    struct noeud *  frere_droit;
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
 * @param decla : L'éventuel numéro de déclaration
 * @return : L'arbre résultat
 */
arbre creer_noeud(int nature, int valeur, int decla);

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

/**********************
 * Helpers pr créer les arbres
 **********************/
arbre a_cr_a_idf(int num_lex, int num_dec);
arbre a_cr_cste_entiere(int valeur);
arbre a_cr_cste_bool(int valeur);
arbre a_cr_cste_chaine(int valeur);
arbre a_cr_cste_char(int valeur);
arbre a_cr_cste_reelle(int valeur);
arbre a_cr_plus(arbre gauche, arbre droit);
arbre a_cr_moins(arbre gauche, arbre droit);
arbre a_cr_mult(arbre gauche, arbre droit);
arbre a_cr_div(arbre gauche, arbre droit);
arbre a_cr_mod(arbre gauche, arbre droit);
arbre a_cr_affect(arbre gauche, arbre droit);
arbre a_cr_idf(int idf);
arbre a_cr_acces_tab(int idf, int decalage);
arbre a_cr_acces_struct(int idf, arbre champ);
arbre a_cr_sup(arbre gauche, arbre droit);
arbre a_cr_inf(arbre gauche, arbre droit);
arbre a_cr_supegal(arbre gauche, arbre droit);
arbre a_cr_infegal(arbre gauche, arbre droit);
arbre a_cr_egal_arith(arbre gauche, arbre droit);
arbre a_cr_diff_arith(arbre gauche, arbre droit);
arbre a_cr_egal_bool(int bool, arbre droit);
arbre a_cr_diff_bool(int bool, arbre droit);
arbre a_cr_non(arbre arbre);
arbre a_cr_et(arbre gauche, arbre droit);
arbre a_cr_ou(arbre gauche, arbre droit);

#endif