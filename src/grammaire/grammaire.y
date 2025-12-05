/**
 * YACC 
 * Auteurs :
 *      Grammaire - Tout le groupe
 *      Actions :
            - Représentations : Louis , Adam 
            - Régions : Baptiste 
            - Declarations : Adam 
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
    arbre treeval;
}

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
%token <intval> CSTE_CHAR // code ASCII ? ou stocker en charval ? A voir
%token <floatval> CSTE_REELLE
%token <intval> IDF
%token <intval> ENTIER REEL BOOL CHAR  

%type <intval> type_simple nom_type
%type <treeval> exp expa expa1 expa2
%type <treeval> affectation variable
%type <treeval> expb expb1 expb2 expb3
%type <treeval> liste_instructions instruction
%type <treeval> liste_acces_dim acces_dim
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
                          afficher_arbre($4); // debug
                        }
                      ;

corps                 : liste_declarations_tv liste_declarations_pf liste_instructions {
                          $$ = $3; /*ici on pourra associer la région à son arbre */
                        }
                      ;

liste_declarations_tv : // aucune decla
                      | liste_declarations_tv declaration_tv 
                      ;

liste_declarations_pf : // aucune decla
                      | liste_declarations_pf declaration_pf 
                      ;

liste_instructions    : instruction {
                          $$ = a_cr_inst($1);
                        }
                      | liste_instructions instruction  {
                          $$ = a_cr_liste_i($1, $2);
                        }
                      ;

// je note ici, il manque le remplissage du champ exec pour les déclas (!)
declaration_tv        : declaration_type PV { remplir_fin_decla(sommet_pile_decla(), ligne_courante); depiler_pile_decla();}
                      | declaration_variable PV 
                      ;

declaration_pf        : declaration_procedure { remplir_fin_decla(sommet_pile_decla(), ligne_courante); depiler_pile_decla();}
                      | declaration_fonction { remplir_fin_decla(sommet_pile_decla(), ligne_courante); depiler_pile_decla();}
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
                       | TAB {
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
                      | liste_dimensions VIR une_dimension{
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

declaration_variable  : VAR IDF DP nom_type {
                          determiner_ligne_decla($2); 
                          remplir_debut_decla(decla_courante, ligne_courante);
                          remplir_nature(decla_courante, N_VAR); 
                          remplir_region(decla_courante, num_region_courante); 
                          remplir_desc(decla_courante, $4); 
                          remplir_exec(decla_courante); 
                          incr_depl($4);
                          remplir_fin_decla(decla_courante, ligne_courante);
                        }
                      ;

declaration_procedure : PROC {}
                        IDF {
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
                      | un_param  {
                        }
                      | un_param VIR liste_param  {
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
                      | IDF {
                          $$ = association_noms($1, TYPE);
                        }
                      ;

type_simple           : ENTIER  {
                          $$ = $1;
                        }
                      | REEL {
                          $$ = $1;
                        }
                      | BOOL  {
                          $$ = $1;
                        }
                      | CHAR  {
                          $$ = $1;
                        }

instruction           : affectation PV {
                          $$ = $1;
                        }
                      | condition {
                          $$ = $1;
                        }     
                      | tant_que {
                          $$ = $1;
                        }
                      | appel PV {
                          $$ = $1;
                        }
                      | RIEN PV {
                          $$ = NULL;  // j'ai ptet pété un cable mais ça me parait OK, à vérifier si on a pas des SEGF qui sortent de nulle part
                        }
                      | RET resultat_retourne PV {
                          $$ = $2;
                        }
                      ;

condition             : SI expb ALORS AO liste_instructions AF  {
                          $$ = a_cr_si_alors($2, $5);
                        }
                      | SI expb ALORS AO liste_instructions AF SINON AO liste_instructions AF {
                          $$ = a_cr_si_alors_sinon($2, $5, $9);
                        }
                      ;

tant_que              : TQ expb FAIRE AO liste_instructions AF  {
                          $$ = a_cr_tant_que($2, $5);
                        }
                      ;

resultat_retourne     : exp {
                          $$ = a_cr_ret($1);
                        }
                      ;

affectation           : variable OPAFF CSTE_BOOL  {
                          $$ = a_cr_affect($1, a_cr_cste_bool($3));
                        }
                      | variable OPAFF CSTE_CHAR {
                          $$ = a_cr_affect($1, a_cr_cste_char($3));
                        }
                      | variable OPAFF CSTE_CHAINE    // {$$ = a_cr_affect($1, a_cr_cste_chaine($3));}
                      | variable OPAFF exp  {
                          $$ = a_cr_affect($1, $3);
                        }
                      ;

                      // description des formes possibles des variables 
variable              : IDF {
                          $$ = a_cr_idf($1);
                        }
                      | IDF CO liste_acces_dim CF {
                          $$ = a_cr_acces_tab($1, $3);
                        }
                      | IDF POINT variable  {
                          $$ = a_cr_acces_struct($1, $3);
                        }
                      ;

liste_acces_dim       : acces_dim {
                          $$ = a_cr_liste_dim_fin($1);
                        }
                      | acces_dim VIR liste_acces_dim {
                          $$ = a_cr_liste_dim_suiv($1, $3);
                        }
                      ;

acces_dim             : CSTE_ENTIERE  {
                          $$ = a_cr_feuille_dim($1);
                        }
                      ;

appel                 : IDF PO liste_args PF {
                          $$ = a_cr_appel($1, $3);
                        }
                      ;
liste_args            : exp {
                          $$ = a_cr_liste_arg_fin($1);                         
                        }
                      | exp VIR liste_args {
                          $$ = a_cr_liste_arg_suiv($1, $3);
                        }
                      ;

exp                   : expa  {
                          $$ = $1;
                        }
                      | expb  {
                          $$ = $1;
                        }
                      ;

expa                  : expa PL expa1 {
                          $$ = a_cr_plus($1, $3);
                        }
                      | expa MO expa1 {
                          $$ = a_cr_moins($1, $3);
                        }
                      | expa1 {
                          $$ = $1;
                        }
                      ;

expa1                 : expa1 MU expa2  {
                          $$ = a_cr_mult($1, $3);
                        }
                      | expa1 DIV expa2 {
                          $$ = a_cr_div($1, $3);
                        }
                      | expa1 MOD expa2 {
                          $$ = a_cr_mod($1, $3);
                        }
                      | expa2 {
                          $$ = $1;
                        }
                      ;

expa2                 : PO expa PF    {
                          $$ = $2;
                        } 
                      | variable      
                      | appel         
                      | CSTE_REELLE   {
                          $$ = a_cr_cste_reelle($1);
                        }
                      | CSTE_ENTIERE  {
                          $$ = a_cr_cste_entiere($1);
                        }
                      ;

expb                  : expb OU expb1 {
                          $$ = a_cr_ou($1, $3);
                        }
                      | expb1 {
                          $$ = $1;
                        }
                      ;

expb1                 : expb1 ET expb2    {
                          $$ = a_cr_et($1, $3);
                        }
                      | expb2 {
                          $$ = $1;
                        }
                      ;

expb2                 : NON PO expb3 PF   {
                          $$ = a_cr_non($3);
                        }
                      | PO expb3 PF       {
                          $$ = $2;
                        }
                      ;

expb3                 : expa SUPEGAL expa {
                          $$ = a_cr_supegal($1, $3);
                        }
                      | expa SUP expa {
                          $$ = a_cr_sup($1, $3);
                        }
                      | expa INFEGAL expa {
                          $$ = a_cr_infegal($1, $3);
                        }
                      | expa INF expa {
                          $$ = a_cr_inf($1, $3);
                        }
                      | expa EGAL expa {
                          $$ = a_cr_egal_arith($1, $3);
                        }
                      | expa DIFF expa  {
                          $$ = a_cr_diff_arith($1, $3);
                        }
                      | CSTE_BOOL EGAL variable {
                          $$ = a_cr_egal_bool($1, $3);
                        }
                      | CSTE_BOOL DIFF variable {
                          $$ = a_cr_diff_bool($1, $3);
                        }
                      | CSTE_BOOL {
                          $$ = a_cr_cste_bool($1);
                        }
                      // | variable EGAL CSTE_BOOL
                      // | variable DIFF CSTE_BOOL
                      ;



%%

int yyerror(char *msg) {
    printf("Erreur de syntaxe\n");
    return 1;
}

int main(int argc, char **argv){
    err_sem *e;

    init_tab_code();
    init_tab_lexico();
    init_tab_decla();
    init_tab_rep();
    init_pile_decla();
    init_tab_regions();

    yyparse();
    
    e = generer_erreur(18, 4, E_PROC_NON_DECLAREE, "test");
    erreur_semantique(e);

    afficher_tab_decla();
    afficher_tab_code();
    afficher_tab_lexico(0, 20);
    afficher_tab_rep(0, 30);
    afficher_tab_regions(0, 10);

    //save_tab_lex();
    //save_tab_decla();
    //save_tab_regions();
    //save_tab_rep();

    exit(EXIT_SUCCESS);
    
}
