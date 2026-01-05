/**
 * YACC 
 * Auteurs :
 * Grammaire - Tout le groupe
 * Actions :
            - Représentations : Louis , Adam 
            - Régions : Baptiste 
            - Declarations : Adam , Louis 
            - Génération d'arbres ; Adam 
 */ 

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tables/tab_lexico.h"
    #include "tables/tab_decla.h"
    #include "tables/tab_rep.h"
    #include "tables/tab_regions.h"
    #include "tables/tab_code.h"
    #include "tables/pile_regions.h"
    #include "tables/pile_decla.h"
    #include "association_noms/association_noms.h"
    #include "save/save.h"
    #include "verif_sem/verif_sem.h"
    #include "arbre/arbre.h"

    int yylex();
    int yyerror(char *msg);
    extern int ligne_courante;
    arbre test;
%}


// pr les types, cf https://www.ibm.com/docs/en/zos/3.1.0?topic=yacc-types 
%union {
    int   intval;
    float floatval;
    struct {
      arbre treeptr;
      int treetype;
      int lineno;
      int ch_numlex; // utile juste pour les structures, pour pouvoir retrouver le dernier champ d'une liste d'acces
    } treeval;

}
%error-verbose

%token PROG
%token PV DP CO CF VIR PP PO PF AO AF POINT        // ; : [ ] , .. ( ) { } .
%token TAB DE STRUCT
%token CSTE_CHAINE 
%token VAR TYPEDEF
%token PROC FCT RET RIEN
%token SI ALORS SINON 
%token TQ FAIRE 
%token OPAFF INF SUP PL MO MU DIV MOD NON ET OU EGAL INFEGAL SUPEGAL DIFF

%token <intval> CSTE_ENTIERE CSTE_BOOL
%token <intval> CSTE_CHAR // code ASCII ?
// ou stocker en charval ? A voir
%token <floatval> CSTE_REELLE
%token <intval> IDF
%token <intval> ENTIER REEL BOOL CHAR  

%type <intval> type_simple nom_type
%type <treeval> exp expa expa1 expa2
%type <treeval> affectation variable
%type <treeval> expb expb1 expb2 expb3
%type <treeval> liste_instructions instruction
%type <treeval> acces_dim liste_acces_dim acces_champ liste_acces_champs
%type <treeval> liste_args
%type <treeval> condition tant_que
%type <treeval> corps
%type <treeval> appel
%type <treeval> resultat_retourne

%%
programme             : PROG {
                          debut_depl();
                          inserer_region(deplacement);
                        }
                        AO corps AF {
                          depiler_pile_regions();
                          afficher_arbre($4.treeptr); // debug
                        }
                      ;

corps                 : liste_declarations_tv liste_declarations_pf liste_instructions {
                          $$ = $3;
                          /*ici on pourra associer la région à son arbre */
                        }
                      ;

liste_declarations_tv : // aucune decla
                      |
                        liste_declarations_tv declaration_tv 
                      ;

liste_declarations_pf : // aucune decla
                      |
                        liste_declarations_pf declaration_pf 
                      ;

liste_instructions    : instruction {
                          $$.treeptr = a_cr_inst($1.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        liste_instructions instruction  {
                          $$.treeptr = a_cr_liste_i($1.treeptr, $2.treeptr);
                          $$.treetype = $2.treetype;
                          $$.lineno = $2.lineno;
                        }
                      ;

// je note ici, il manque le remplissage du champ exec pour les déclas (!)
declaration_tv        : declaration_type PV { remplir_fin_decla(sommet_pile_decla(), ligne_courante);
                        depiler_pile_decla();}
                      |
                        declaration_variable PV 
                      ;

declaration_pf        : declaration_procedure { remplir_fin_decla(sommet_pile_decla(), ligne_courante);
                        depiler_pile_decla();}
                      |
                        declaration_fonction { remplir_fin_decla(sommet_pile_decla(), ligne_courante); depiler_pile_decla();}
                      ;

declaration_type      : TYPEDEF IDF {
                          determiner_ligne_decla($2);
                          empiler_pile_decla(decla_courante); 
                          remplir_debut_decla(decla_courante, ligne_courante);
                        } DP
                        suite_declaration_type {
                          remplir_exec($2);
                          debut_depl();
                        }
                      ;

suite_declaration_type : STRUCT {
                          debut_struct();
                          debut_depl(); 
                          remplir_nature(decla_courante, N_STRUCT); 
                          remplir_region(decla_courante, num_region_courante); 
                          remplir_desc(decla_courante, id_rep_courante); 
                          memoriser_precedente_decla(decla_courante);
                        } AO liste_champs AF {
                            inserer_tab_rep_nb_elem(nbchamps);
                            remplir_exec(decla_precedente);
                          }
                       |
                        TAB {
                            debut_tab();
                            remplir_nature(decla_courante, N_TAB); 
                            remplir_region(decla_courante, num_region_courante); 
                            remplir_desc(decla_courante, id_rep_courante);
                            remplir_exec(decla_courante);
                          }
                         dimension DE nom_type  {
                          inserer_tab_rep_nb_elem(nbdimension);
                          inserer_tab_rep_type($5);
                        } 

dimension             : CO liste_dimensions CF
                      ;

liste_dimensions      : une_dimension {
                          incr_nb_dim();
                        }
                      |
                        liste_dimensions VIR une_dimension{
                          incr_nb_dim();
                        }
                      ;

une_dimension         : CSTE_ENTIERE PP CSTE_ENTIERE {
                          inserer_tab_rep($1);
                          inserer_tab_rep($3);
                        }
                      ;

liste_champs          : un_champ {
                          incr_nb_champ();
                        }
                      | liste_champs un_champ {
                          incr_nb_champ();
                        }
                      ;
                      
un_champ              : IDF DP nom_type PV {
                          inserer_tab_rep($1);
                          inserer_tab_rep($3); 
                          inserer_tab_rep(deplacement); 
                          incr_depl($3); 
                          determiner_ligne_decla($1); 
                          remplir_nature(decla_courante, N_CH_STRUCT); 
                          remplir_region(decla_courante, num_region_courante); 
                          remplir_desc(decla_courante, $3); 
                          remplir_exec(decla_courante);
                        }
                      ;

declaration_variable  : VAR IDF {
                          verif_double_decla($2, num_region_courante, N_VAR, ligne_courante);
                        } DP nom_type {
                          determiner_ligne_decla($2);
                          remplir_debut_decla(decla_courante, ligne_courante);
                          remplir_nature(decla_courante, N_VAR); 
                          remplir_region(decla_courante, num_region_courante); 
                          remplir_desc(decla_courante, $5); 
                          remplir_exec(decla_courante); 
                          incr_depl($5);
                          remplir_fin_decla(decla_courante, ligne_courante);
                        }
                      ;

declaration_procedure : PROC {}
                        IDF {
                          verif_double_decla($3, num_region_courante, N_PROC, ligne_courante);
                          debut_proc();
                          determiner_ligne_decla($3); 
                          empiler_pile_decla(decla_courante);
                          remplir_debut_decla(decla_courante, ligne_courante);
                          remplir_nature(decla_courante, N_PROC); 
                          remplir_region(decla_courante, num_region_courante); 
                          remplir_desc(decla_courante, id_rep_courante);
                          remplir_exec(decla_courante);
                        } 
                        PO {
                          inserer_region(deplacement);
                          debut_depl();
                        }
                        liste_param PF {
                          inserer_tab_rep_nb_elem(nbparam);
                        }
                        AO corps AF {
                          depiler_pile_regions();
                        }
                      ;

declaration_fonction  : nom_type FCT {} IDF {
                          verif_double_decla($4, num_region_courante, N_FCT, ligne_courante);
                          debut_fct($1);
                          determiner_ligne_decla($4); 
                          empiler_pile_decla(decla_courante);
                          remplir_debut_decla(decla_courante, ligne_courante);
                          remplir_nature(decla_courante, N_FCT); 
                          remplir_region(decla_courante, num_region_courante); 
                          remplir_desc(decla_courante, id_rep_courante);
                          remplir_exec(decla_courante);
                        } PO {
                            inserer_region(deplacement);
                            debut_depl(); 
                        } liste_param PF {
                            inserer_tab_rep_nb_elem(nbparam);
                        } AO corps AF {
                            depiler_pile_regions();
                        }
                      ;

liste_param           : // aucun parametre
                      |
                        un_param  {
                        }
                      |
                        un_param VIR liste_param  {
                        }
                      ;

un_param              : IDF DP nom_type {
                          determiner_ligne_decla($1);
                          remplir_debut_decla(decla_courante, ligne_courante);
                          remplir_nature(decla_courante, N_PARAM); 
                          remplir_region(decla_courante, num_region_courante); 
                          remplir_desc(decla_courante, $3); 
                          remplir_exec(decla_courante); 
                          inserer_tab_rep($1); 
                          inserer_tab_rep($3); 
                          incr_param(); 
                          incr_depl($3);
                          remplir_fin_decla(decla_courante, ligne_courante);
                        }
                      ;

nom_type              : type_simple {
                          $$ = $1;
                        }
                      |
                        IDF {
                          $$ = verif_decla_idf($1, TYPE, ligne_courante);
                        }
                      ;

type_simple           : ENTIER  {
                          $$ = $1;
                        }
                      |
                        REEL {
                          $$ = $1;
                        }
                      |
                        BOOL  {
                          $$ = $1;
                        }
                      |
                        CHAR  {
                          $$ = $1;
                        }
                      ;

instruction           : affectation PV {
                          $$ = $1;
                        }
                      |
                        condition {
                          $$ = $1;
                        }     
                      |
                        tant_que {
                          $$ = $1;
                        }
                      |
                        appel PV {
                          $$ = $1;
                        }
                      |
                        RIEN PV {
                          $$.treeptr = NULL;
                          $$.treetype = -1;
                          $$.lineno = ligne_courante;
                        }
                      |
                        RET resultat_retourne PV {
                          $$ = $2;
                        }
                      ;

condition             : SI exp ALORS AO liste_instructions AF  {
                          verif_condition_bool($2.treetype, $2.lineno);
                          $$.treeptr = a_cr_si_alors($2.treeptr, $5.treeptr);
                          $$.treetype = -1;
                          $$.lineno = $2.lineno;
                        }
                      |
                        SI exp ALORS AO liste_instructions AF SINON AO liste_instructions AF {
                          verif_condition_bool($2.treetype, $2.lineno);
                          $$.treeptr = a_cr_si_alors_sinon($2.treeptr, $5.treeptr, $9.treeptr);
                          $$.treetype = -1;
                          $$.lineno = $2.lineno;
                        }
                      ;

tant_que              : TQ exp FAIRE AO liste_instructions AF  {
                          verif_condition_bool($2.treetype, $2.lineno);
                          $$.treeptr = a_cr_tant_que($2.treeptr, $5.treeptr);
                          $$.treetype = -1;
                          $$.lineno = $2.lineno;
                        }
                      ;

resultat_retourne     : exp {
                          $$.treeptr = a_cr_ret($1.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      ;

affectation           : variable OPAFF CSTE_BOOL  {
                          verif_compatibilite_affect($1.ch_numlex, $1.treetype, TREETYPE_BOOL, $1.lineno);
                          $$.treeptr = a_cr_affect($1.treeptr, a_cr_cste_bool($3));
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        variable OPAFF CSTE_CHAR {
                          verif_compatibilite_affect($1.ch_numlex, $1.treetype, TREETYPE_CHAR, $1.lineno);
                          $$.treeptr = a_cr_affect($1.treeptr, a_cr_cste_char($3));
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        variable OPAFF CSTE_CHAINE    // {$$ = a_cr_affect($1, a_cr_cste_chaine($3));}
                      |
                        variable OPAFF exp  {
                          verif_compatibilite_affect($1.ch_numlex, $1.treetype, $3.treetype, $1.lineno);
                          $$.treeptr = a_cr_affect($1.treeptr, $3.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      ;

// description des formes possibles des variables 
variable              : IDF {
                          int decla = verif_decla_idf($1, N_VAR, ligne_courante);
                          $$.treeptr = a_cr_idf($1, decla);
                          $$.treetype = (decla != -1) ? tab_decla[decla][DESCRIPTION] : -1;
                          $$.lineno = ligne_courante;
                          $$.ch_numlex = $1;
                        }
                      | IDF POINT liste_acces_champs {
                          int decla = verif_decla_idf($1, N_VAR, ligne_courante);
                          $$.treeptr = a_cr_acces_struct($1, $3.treeptr, decla);
                          $$.treetype = evaluer_type_acces_champ(decla, $3.treeptr);
                          $$.lineno = ligne_courante;
                          $$.ch_numlex = $3.ch_numlex;
                        }
                      | IDF CO liste_acces_dim CF {
                          int decla = verif_decla_idf($1, N_VAR, ligne_courante);
                          verif_nb_dim_taille($1, decla, $3.treeptr, ligne_courante);
                          verif_dim_hors_tab($1, decla, $3.treeptr, ligne_courante);
                          $$.treeptr = a_cr_acces_tab($1, $3.treeptr, decla);
                          $$.treetype = (decla != -1) ? trouver_type_tab(decla) : -1;
                          $$.lineno = ligne_courante;
                          $$.ch_numlex = $1;
                        }
                      ;

liste_acces_dim       : acces_dim {
                          $$.treeptr = a_cr_liste_dim_fin($1.treeptr);
                        }
                      | acces_dim VIR liste_acces_dim {
                          $$.treeptr = a_cr_liste_dim_suiv($1.treeptr, $3.treeptr);
                        }
                      ;

acces_dim             : exp {
                          $$.treeptr = a_cr_dim($1.treeptr->valeur); 
                          $$.treetype = TREETYPE_ENTIER;
                          $$.lineno = $1.lineno;
                        }
                      ;

liste_acces_champs    : acces_champ {
                          $$.treeptr = a_cr_liste_champs_fin($1.treeptr);
                          $$.treetype = $1.treetype;
                          $$.ch_numlex = $1.ch_numlex;
                        }
                      | acces_champ POINT liste_acces_champs {
                          $$.treeptr = a_cr_liste_champs_suiv($1.treeptr, $3.treeptr);
                          $$.treetype = $3.treetype;
                          $$.ch_numlex = $3.ch_numlex;
                        }
                      ;

acces_champ           : IDF {
                          $$.treeptr = a_cr_champ($1, NULL);
                          $$.treetype = -1; 
                          $$.ch_numlex = $1;
                        }
                      | IDF CO liste_acces_dim CF {
                          $$.treeptr = a_cr_champ($1, $3.treeptr);
                          $$.treetype = $3.treetype;
                          $$.ch_numlex = $1;
                        }
                      ;

appel                 : IDF PO liste_args PF {
                          int decla = verif_decla_appel($1, ligne_courante);
                          
                          if (decla != -1) {
                              int id_rep = tab_decla[decla][DESCRIPTION];
                              int nb_attendus = tab_rep[id_rep];
                              int nb_recus = compter_nombre_args($3.treeptr);
                              
                              //verif du nb d'args..
                              verif_nombre_args($1, nb_attendus, nb_recus, ligne_courante);

                              // puis des types
                              if (nb_attendus == nb_recus) {
                                  verif_types_args($1, decla, $3.treeptr, ligne_courante);
                              }
                          }

                          $$.treeptr = a_cr_appel($1, $3.treeptr, decla);
                          
                          if (decla != -1 && tab_decla[decla][NATURE] == N_FCT) {
                              // si c'est une fct on fait remonter le type de retour
                              $$.treetype = tab_rep[tab_decla[decla][DESCRIPTION] + 1];
                          } else {
                              $$.treetype = -1; // Procédure ou erreur
                          }
                          
                          $$.lineno = ligne_courante;
                        }
                      ;

liste_args            : exp {
                          $$.treeptr = a_cr_liste_arg_fin($1.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        exp VIR liste_args {
                          $$.treeptr = a_cr_liste_arg_suiv($1.treeptr, $3.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      ;

exp                   : expa  {
                          $$ = $1;
                        }
                      |
                        expb  {
                          $$ = $1;
                        }
                      ;

expa                  : expa PL expa1 {
                          $$.treeptr = a_cr_plus($1.treeptr, $3.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa MO expa1 {
                          $$.treeptr = a_cr_moins($1.treeptr, $3.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa1 {
                          $$ = $1;
                        }
                      ;

expa1                 : expa1 MU expa2  {
                          $$.treeptr = a_cr_mult($1.treeptr, $3.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa1 DIV expa2 {
                          $$.treeptr = a_cr_div($1.treeptr, $3.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa1 MOD expa2 {
                          $$.treeptr = a_cr_mod($1.treeptr, $3.treeptr);
                          $$.treetype = $1.treetype;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa2 {
                          $$ = $1;
                        }
                      ;

expa2                 : PO expa PF    {
                          $$ = $2;
                        } 
                      |
                        variable      {
                          $$ = $1;
                        }  
                      |
                        appel         {
                          $$ = $1;
                        }    
                      |
                        CSTE_REELLE   {
                          $$.treeptr = a_cr_cste_reelle($1);
                          $$.treetype = TREETYPE_REEL;
                          $$.lineno = ligne_courante;
                        }
                      |
                        CSTE_ENTIERE  {
                          $$.treeptr = a_cr_cste_entiere($1);
                          $$.treetype = TREETYPE_ENTIER;
                          $$.lineno = ligne_courante;
                        }
                      ;

expb                  : expb OU expb1 {
                          $$.treeptr = a_cr_ou($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expb1 {
                          $$ = $1;
                        }
                      ;

expb1                 : expb1 ET expb2    {
                          $$.treeptr = a_cr_et($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expb2 {
                          $$ = $1;
                        }
                      ;

expb2                 : NON PO expb3 PF   {
                          $$.treeptr = a_cr_non($3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $3.lineno;
                        }
                      |
                        PO expb3 PF       {
                          $$.treeptr = $2.treeptr;
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $2.lineno;
                        }
                      ;

expb3                 : expa SUPEGAL expa {
                          $$.treeptr = a_cr_supegal($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa SUP expa {
                          $$.treeptr = a_cr_sup($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa INFEGAL expa {
                          $$.treeptr = a_cr_infegal($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa INF expa {
                          $$.treeptr = a_cr_inf($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa EGAL expa {
                          $$.treeptr = a_cr_egal_arith($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        expa DIFF expa  {
                          $$.treeptr = a_cr_diff_arith($1.treeptr, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $1.lineno;
                        }
                      |
                        CSTE_BOOL EGAL variable {
                          $$.treeptr = a_cr_egal_bool($1, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $3.lineno;
                        }
                      |
                        CSTE_BOOL DIFF variable {
                          $$.treeptr = a_cr_diff_bool($1, $3.treeptr);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = $3.lineno;
                        }
                      |
                        CSTE_BOOL {
                          $$.treeptr = a_cr_cste_bool($1);
                          $$.treetype = TREETYPE_BOOL;
                          $$.lineno = ligne_courante;
                        }
                      ;

%%

int yyerror(char *msg) {
    printf("Erreur de syntaxe : %s\n", msg);
    return 1;
}

int main(int argc, char **argv){
    init_tab_code();
    init_tab_lexico();
    init_tab_decla();
    init_tab_rep();
    init_pile_decla();
    init_tab_regions();

    int resultat = yyparse();

    if (resultat != 0 || nb_err_sem > 0) {
        printf("\n[!] Analyse terminée avec %d erreur(s).\n", nb_err_sem);
    } else {
        printf("\n[OK] Analyse réussie.\n");
    }

    afficher_tab_lexico(0, 15);
    afficher_tab_decla();
    afficher_tab_rep(0,10);

    exit(EXIT_SUCCESS);
}