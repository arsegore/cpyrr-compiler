/**
 * YACC 
 * Auteurs :
 *      Grammaire - Tout le groupe
 *      Actions :
            - Représentations : Louis PELOUX, Adam HADDADI
            - Régions : Baptiste MOULIN
            - Declarations : Adam HADDADI
 */ 

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tables/tab_lexico.h"
    #include "tables/tab_decla.h"
    #include "tables/tab_rep.h"
    #include "tables/tab_regions.h"
    #include "tables/pile_regions.h"
    #include "association_noms/association_noms.h"
    #include "save/save.h"
    #include "arbre/arbre.h"
    int yylex();
    int yyerror(char *msg);
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
%token CSTE_CHAR CSTE_CHAINE 
%token VAR TYPEDEF
%token PROC FCT RET RIEN
%token SI ALORS SINON 
%token TQ FAIRE 
%token OPAFF INF SUP PL MO MU DIV MOD NON ET OU EGAL INFEGAL SUPEGAL DIFF

%token <intval> CSTE_ENTIERE CSTE_BOOL
%token <floatval> CSTE_REELLE
%token <intval> IDF
%token <intval> ENTIER REEL BOOL CHAR  

%type <intval> type_simple nom_type
%type <treeval> exp expa expa1 expa2
%type <treeval> affectation variable
%type <treeval> expb expb1 expb2 expb3

%%
programme             : PROG {debut_depl(); inserer_region(deplacement);}
                        AO corps AF {depiler_pile_regions();}
                      ;

corps                 : liste_declarations_tv liste_declarations_pf liste_instructions
                      ;

liste_declarations_tv : // aucune decla
                      | liste_declarations_tv declaration_tv 
                      ;

liste_declarations_pf : // aucune decla
                      | liste_declarations_pf declaration_pf 
                      ;

liste_instructions    : instruction
                      | liste_instructions instruction
                      ;

// je note ici, il manque le remplissage du champ exec pour les déclas (!)
declaration_tv        : declaration_type PV
                      | declaration_variable PV 
                      ;

declaration_pf        : declaration_procedure
                      | declaration_fonction
                      ;

declaration_type      : TYPEDEF IDF {determiner_ligne_decla($2);} DP
                        suite_declaration_type { debut_depl();}
                      ;

suite_declaration_type : STRUCT                     {debut_struct(); debut_depl(); remplir_nature(decla_courante, N_STRUCT); remplir_region(decla_courante, num_region_courante); remplir_desc(decla_courante, id_rep_courante); memoriser_precedente_decla(decla_courante);} 
                         AO liste_champs AF         {inserer_tab_rep_nb_elem(nbchamps);remplir_exec(decla_precedente);}
                       | TAB                        {debut_tab(); remplir_nature(decla_courante, N_TAB); remplir_region(decla_courante, num_region_courante); remplir_desc(decla_courante, id_rep_courante);remplir_exec(decla_courante);}
                         dimension DE nom_type      {inserer_tab_rep_nb_elem(nbdimension); inserer_tab_rep_type($5);} 

dimension             : CO liste_dimensions CF
                      ;

liste_dimensions      : une_dimension {incr_nb_dim();}
                      | liste_dimensions VIR une_dimension{incr_nb_dim();}
                      ;

une_dimension         : CSTE_ENTIERE PP CSTE_ENTIERE {inserer_tab_rep($1); inserer_tab_rep($3);}
                      ;

liste_champs          : un_champ {incr_nb_champ();}
                      | liste_champs un_champ {incr_nb_champ();}
                      ;

                      // déplacement à revoir
un_champ              : IDF DP nom_type PV {inserer_tab_rep($1); inserer_tab_rep($3); inserer_tab_rep(deplacement); incr_depl($3); determiner_ligne_decla($1); remplir_nature(decla_courante, N_CH_STRUCT); remplir_region(decla_courante, num_region_courante); remplir_desc(decla_courante, $3); remplir_exec(decla_courante);}
                      ;

declaration_variable  : VAR IDF DP nom_type {determiner_ligne_decla($2); remplir_nature(decla_courante, N_VAR); remplir_region(decla_courante, num_region_courante); remplir_desc(decla_courante, $4); remplir_exec(decla_courante); incr_depl($4);}
                      ;

declaration_procedure : PROC {}
                        IDF {debut_proc(); determiner_ligne_decla($3); remplir_nature(decla_courante, N_PROC); remplir_region(decla_courante, num_region_courante); remplir_desc(decla_courante, id_rep_courante);;} 
                        PO {inserer_region(deplacement); remplir_exec(decla_courante); debut_depl();}
                        liste_param PF {inserer_tab_rep_nb_elem(nbparam);}
                        AO corps AF {depiler_pile_regions();}
                      ;
 
declaration_fonction  : nom_type FCT {}
                        IDF {debut_fct($1); determiner_ligne_decla($4); remplir_nature(decla_courante, N_FCT); remplir_region(decla_courante, num_region_courante); remplir_desc(decla_courante, id_rep_courante);}
                        PO {inserer_region(deplacement); remplir_exec(decla_courante); debut_depl(); }
                        liste_param PF {inserer_tab_rep_nb_elem(nbparam); }
                        AO corps AF {depiler_pile_regions();}
                      ;

liste_param           : // aucun parametre
                      | un_param
                      | liste_param VIR un_param
                      ;

un_param              : IDF DP nom_type {determiner_ligne_decla($1); remplir_nature(decla_courante, N_PARAM); remplir_region(decla_courante, num_region_courante); remplir_desc(decla_courante, $3); remplir_exec(decla_courante); inserer_tab_rep($1); inserer_tab_rep($3); incr_param(); incr_depl($3);}
                      ;

nom_type              : type_simple {$$ = $1;}
                      | IDF {$$ = association_noms($1, TYPE);}
                      ;

type_simple           : ENTIER                                              {$$ = $1;}
                      | REEL                                                {$$ = $1;}
                      | BOOL                                                {$$ = $1;}
                      | CHAR                                                {$$ = $1;}
                      | CHAR CO CSTE_ENTIERE CF
                      ;

instruction           : affectation PV
                      | condition
                      | tant_que
                      | appel PV
                      | RIEN PV
                      | RET resultat_retourne PV
                      ;

condition             : SI expb ALORS AO liste_instructions AF
                      | SI expb ALORS AO liste_instructions AF SINON AO liste_instructions AF
                      ;

tant_que              : TQ expb FAIRE AO liste_instructions AF
                      ;

resultat_retourne     : exp
                      ;

affectation           : variable OPAFF CSTE_BOOL      {$$ = a_cr_affect($1, a_cr_bool($3));}
                      | variable OPAFF CSTE_CHAR      {$$ = a_cr_affect($1, a_cr_char($3));}
                      | variable OPAFF CSTE_CHAINE    {$$ = a_cr_affect($1, a_cr_chaine($3));}
                      | variable OPAFF exp            {$$ = a_cr_affect($1, $3); afficher_arbre($$);}
                      ;

                      // description des formes possibles des variables 
variable              : IDF                     {$$ = a_cr_idf($1);}
                      | IDF CO CSTE_ENTIERE CF  {$$ = a_cr_acces_tab($1, $3);}
                      | IDF POINT variable      {$$ = a_cr_acces_struct($1, $3);}
                      ;

appel                 : IDF liste_arguments
                      ;

liste_arguments       : PO PF //modif (avant y avait rien)
                      | PO liste_args PF
                      ;

liste_args            : exp
                      | liste_args VIR exp
                      ;

exp                   : expa  {$$ = $1;}
                      | expb  {$$ = $1;}
                      ;

expa                  : expa PL expa1 {$$ = a_cr_plus($1, $3);}
                      | expa MO expa1 {$$ = a_cr_moins($1, $3);}
                      | expa1         {$$ = $1;}
                      ;

expa1                 : expa1 MU expa2  {$$ = a_cr_mult($1, $3);}
                      | expa1 DIV expa2 {$$ = a_cr_div($1, $3);}
                      | expa1 MOD expa2 {$$ = a_cr_mod($1, $3);}
                      | expa2           {$$ = $1;}
                      ;

expa2                 : PO expa PF    {$$ = $2;} 
                      | variable      
                      | appel         
                      | CSTE_REELLE   {$$ = a_cr_cste_reelle($1);}
                      | CSTE_ENTIERE  {$$ = a_cr_cste_entiere($1);}
                      ;

expb                  : expb OU expb1     {$$ = a_cr_ou($1, $3);}
                      | expb1             {$$ = $1;}
                      ;

expb1                 : expb1 ET expb2    {$$ = a_cr_et($1, $3);}
                      | expb2             {$$ = $1;}
                      ;

expb2                 : NON PO expb3 PF   {$$ = a_cr_non($3);}
                      | PO expb3 PF       {$$ = $2;}
                      ;

expb3                 : expa SUPEGAL expa         {$$ = a_cr_supegal($1, $3);}
                      | expa SUP expa             {$$ = a_cr_sup($1, $3);}
                      | expa INFEGAL expa         {$$ = a_cr_infegal($1, $3);}
                      | expa INF expa             {$$ = a_cr_inf($1, $3);}
                      | expa EGAL expa            {$$ = a_cr_egal_arith($1, $3);}
                      | expa DIFF expa            {$$ = a_cr_diff_arith($1, $3);}
                      | CSTE_BOOL EGAL variable   {$$ = a_cr_egal_bool($1, $3);}
                      | CSTE_BOOL DIFF variable   {$$ = a_cr_diff_bool($1, $3);}
                      | CSTE_BOOL                 {$$ = a_cr_cste_bool($1);}
                      // | variable EGAL CSTE_BOOL
                      // | variable DIFF CSTE_BOOL
                      ;



%%

int yyerror(char *msg) {
    printf("Erreur de syntaxe\n");
    return 1;
}

int main(int argc, char **argv){
    init_tab_lexico();
    init_tab_decla();
    init_tab_rep();
    init_tab_regions();

    yyparse();

/* 
    afficher_tab_lexico(0, 20);
    afficher_tab_decla();
    afficher_tab_rep(0, 30);
    afficher_tab_regions(0, 10); */

    /* save_tab_lex();
    save_tab_decla(); */

    exit(EXIT_SUCCESS);
    
}
