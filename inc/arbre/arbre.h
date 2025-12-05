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

/**
 * Tout un tas de helper pour les arbres, ça devrait rendre le yacc plus lisible.. 
 * Elles sont toutes de la forme : a_cr_noeud_a_creer
 * 
 * A voir pour ajouter les verifs : directement dedans en modifiant la signatures ? autres helpers ?
 */
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
arbre a_cr_acces_tab(int idf, arbre liste_acces_dim);
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
arbre a_cr_si_alors(arbre si, arbre alors);
arbre a_cr_si_alors_sinon(arbre si, arbre alors, arbre sinon);
arbre a_cr_liste_i(arbre instruction, arbre liste_inst_suivantes);
arbre a_cr_inst(arbre instruction);
arbre a_cr_tant_que(arbre condition, arbre liste_inst);
arbre a_cr_liste_arg_fin(arbre un_arg);
arbre a_cr_liste_arg_suiv(arbre un_arg, arbre liste_suivants);
arbre a_cr_appel(int idf, arbre liste_args);
arbre a_cr_ret(arbre valeur);
arbre a_cr_feuille_dim(int val);
arbre a_cr_liste_dim_fin(arbre une_dim);
arbre a_cr_liste_dim_suiv(arbre une_dim, arbre liste_suivante);
#endif