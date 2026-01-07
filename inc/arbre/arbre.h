#ifndef _ARBRE_H_
#define _ARBRE_H_

/**
 * Définition d'un TAD Arbre utilisé pour la construction
 * des arbres abstraits
 *
 * Auteurs : TAD : Damien 
 *           Génération : Adam 
 */

 // 05/12 - Adam
 // NOTE GEN : pr le moment, génération OK sauf pour les chaînes (jsuis pas sûr de la 
 // façon dont on doit les gérer, à éclaircir). Idem fct et proc, il faut qu'on distingue
 // les deux noeuds mais la règle dans la grammaire est commune.
 // => Association de noms à la création du noeud ? Ou séparation de la grammaire
 // Sinon, globalement c'est cool mais pour l'instant les valeurs (notamment les num decla)
 // sont pas tout à fait remplis. 
 // Les vérifications ne sont pas faites non plus, si qqn d'autre que moi reprend ce morceau (l'espoir fait vivre)
 // il faudra penser à faire les vérifications AVANT la construction, et en cas d'erreur
 // enclencher la création d'une err_sem (cf branche AnalyseSemantique, normalement merge
 // dans dev entre temps)


#define A_IDF               1   // ok gen

#define A_CSTE_ENTIERE      2   // ok gen
#define A_CSTE_BOOL         3   // ok gen
#define A_CSTE_CHAINE       4   // à faire
#define A_CSTE_CHAR         5   // ok gen
#define A_CSTE_REELLE       6   // ok gen

#define A_AFFECT            7   // ok gen
#define A_PLUS              8   // ok gen
#define A_MOINS             9   // ok gen
#define A_MULT              10  // ok gen
#define A_DIV               11  // ok gen
#define A_MOD               12  // ok gen

#define A_RIEN              13  // ok gen

#define A_APPEL_PROC        14  // à faire
#define A_APPEL_FCT         15  // à faire
#define A_RET               16  // ok gen

#define A_LISTE_I           17  // ok gen
#define A_LISTE_ARG         32  // ok gen

#define A_LISTE_DIM         33  // ok gen
#define A_LISTE_CHAMPS      34
#define A_CHAMP             35
#define A_DIM               36

#define A_TANT_QUE          18  // ok gen
#define A_SI_ALORS_SINON    19  // ok gen
#define A_SI_ALORS          31  // ok gen

#define A_ET                20  // ok gen
#define A_OU                21  // ok gen
#define A_NON               22  // ok gen
#define A_EGAL              23  // ok gen
#define A_DIFF              24  // ok gen
#define A_INF               25  // ok gen
#define A_SUP               26  // ok gen
#define A_INFEGAL           27  // ok gen
#define A_SUPEGAL           28  // ok gen

#define A_ACCES_TAB         29  // ok gen
#define A_ACCES_STRUCT      30  // ok gen

#define TREETYPE_ENTIER     0
#define TREETYPE_REEL       1
#define TREETYPE_BOOL       2
#define TREETYPE_CHAR       3

/**
 * Chaque noeud connait sa nature et sa valeur, ainsi qu'évidemment
 * qui sont ses fils (sous forme d'un pointeur sur le fils gauche
 * et d'une chaîne de frères droits)
 */
typedef struct noeud {
    int             nature;     
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
 * @author :  Damien
 */
arbre concat_pere_fils(arbre pere, arbre fils);

/**
 * Ajoute un frère à un arbre
 *
 * @param pere : L'arbre à qui ajouter un frère
 * @param frere : Le frère à ajouter
 * @return : L'arbre résultat
 * @author :  Damien
 */
arbre concat_pere_frere(arbre pere, arbre frere);

/**
 * Crée un noeud (un nouvel arbre)
 *
 * @param nature : La nature du noeud
 * @param valeur : La valeur du noeud
 * @param decla : L'éventuel numéro de déclaration
 * @return : L'arbre résultat
 * @author :  Damien
 */
arbre creer_noeud(int nature, int valeur, int decla);

/**
 * Affiche un arbre
 *
 * @param a : L'arbre à afficher
 * @author :  Adam
 */
void afficher_arbre(arbre a);

/**
 * Affiche les arbres de toutes les régions du programme
 * @author :  Adam
 */
void afficher_arbres_regions();

/**
 * Tout un tas de helper pour les arbres, ça devrait rendre le yacc plus lisible.. 
 * Elles sont toutes de la forme : a_cr_noeud_a_creer
 * 
 * A voir pour ajouter les verifs : directement dedans en modifiant la signatures ? autres helpers ?
 */

/** @author :  Adam */
arbre a_cr_a_idf(int num_lex, int num_dec);
/** @author :  Adam */
arbre a_cr_cste_entiere(int valeur);
/** @author :  Adam */
arbre a_cr_cste_bool(int valeur);
/** @author :  Adam */
arbre a_cr_cste_chaine(int valeur);
/** @author :  Adam */
arbre a_cr_cste_char(int valeur);
/** @author :  Adam */
arbre a_cr_cste_reelle(float valeur);
/** @author :  Adam */
arbre a_cr_plus(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_moins(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_mult(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_div(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_mod(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_affect(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_idf(int idf, int num_dec);
/** @author :  Adam */
arbre a_cr_sup(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_inf(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_supegal(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_infegal(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_egal_arith(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_diff_arith(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_egal_bool(int bool, arbre droit);
/** @author :  Adam */
arbre a_cr_diff_bool(int bool, arbre droit);
/** @author :  Adam */
arbre a_cr_non(arbre arbre);
/** @author :  Adam */
arbre a_cr_et(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_ou(arbre gauche, arbre droit);
/** @author :  Adam */
arbre a_cr_si_alors(arbre si, arbre alors);
/** @author :  Adam */
arbre a_cr_si_alors_sinon(arbre si, arbre alors, arbre sinon);
/** @author :  Adam */
arbre a_cr_liste_i(arbre instruction, arbre liste_inst_suivantes);
/** @author :  Adam */
arbre a_cr_inst(arbre instruction);
/** @author :  Adam */
arbre a_cr_tant_que(arbre condition, arbre liste_inst);
/** @author :  Adam */
arbre a_cr_liste_arg_fin(arbre un_arg);
/** @author :  Adam */
arbre a_cr_liste_arg_suiv(arbre un_arg, arbre liste_suivants);
/** @author :  Adam */
arbre a_cr_appel(int idf, arbre liste_args, int decla);
/** @author :  Adam */
arbre a_cr_appel_fct(int idf, arbre liste_args, int num_dec);
/** @author :  Adam */
arbre a_cr_appel_proc(int idf, arbre liste_args, int num_dec);
/** @author :  Adam */
arbre a_cr_ret(arbre valeur);
/** @author :  Adam */
arbre a_cr_dim(int val);
/** @author :  Adam */
arbre a_cr_liste_dim_fin(arbre une_dim);
/** @author :  Adam */
arbre a_cr_liste_dim_suiv(arbre une_dim, arbre suite);
/** @author :  Adam */
arbre a_cr_acces_tab(int idf, arbre liste, int num_dec);
/** @author :  Adam */
arbre a_cr_champ(int num_lex, arbre liste_dim);
/** @author :  Adam */
arbre a_cr_liste_champs_fin(arbre noeud_champ);
/** @author :  Adam */
arbre a_cr_liste_champs_suiv(arbre noeud_champ, arbre suite_liste);
/** @author :  Adam */
arbre a_cr_acces_struct(int idf, arbre liste, int num_dec);

// Gestion des types pour types complexes
/**
 * Recherche le type d'un champ à l'intérieur d'une structure.
 * @param id_decla_struct : L'indice de la structure dans tab_decla.
 * @param num_lex_champ : Le lexème du champ recherché.
 * @return : L'indice du type du champ dans tab_decla, ou -1 si non trouvé.
 * @author :  Adam
 */
int trouver_type_champ(int id_decla_struct, int num_lex_champ);

/**
 * Recherche l'exec d'un champ à l'intérieur d'une structure.
 * @param id_decla_struct : L'indice de la structure dans tab_decla.
 * @param num_lex_champ : Le lexème du champ recherché.
 * @return : L'indice du type du champ dans tab_decla, ou -1 si non trouvé.
 * @author :  Adam
 */
int trouver_exec_champ(int id_decla_struct, int num_lex_champ);

/**
 * Recherche le type des éléments d'un tableau.
 * @param id_decla_tab : L'indice du tableau dans tab_decla.
 * @author :  Adam
 */
int trouver_type_tab(int id_decla_tab);

/**
 * Renvoie le type d'un noeud (au sens des types du YACC, TREETYPE_TRUC)
 * @param a : Le noeud dont on cherche le type
 * @author :  Adam
 */
int recuperer_type_noeud(arbre a);

/**
 * Evalue le type d'un corps, déterminé par ce qu'il retourne. Le type est placé dans le pointeur
 * donné en param, et la fonction renvoie 0 si tout va bien, 1 en cas d'erreur (un corps qui renvoie
 * deux types différents)
 * @param a : L'arbre représentant les instructions à parcourir
 * @param num_lex : Le num lex de la fct/proc
 * @param type_corps : Un pointeur vers là ou sera stocké le résultat (le type du corps)
 * @param ligne : La ligne courante
 * @author :  Adam
 */
int evaluer_type_corps(arbre a, int num_lex, int *type_corps, int decla, int ligne);

#endif