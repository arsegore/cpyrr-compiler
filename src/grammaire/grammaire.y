%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "../inc/tables/tab_lexico.h"
    #include "../inc/tables/tab_decla.h"
    #include "../inc/tables/tab_desc.h"
    #include "../inc/tables/tab_regions.h"
    int yylex();
    int yyerror(char *msg);
%}
%token PROG
%token PV DP CO CF VIR PP PO PF AO AF POINT        // ; : [ ] , .. ( ) { } .
%token TAB DE STRUCT
%token CSTE_ENTIERE CSTE_CHAR CSTE_CHAINE CSTE_BOOL CSTE_REELLE
%token ENTIER REEL BOOL CHAR //on a enlevé CHAINE (aussi dans le lex) 
%token VAR TYPEDEF IDF
%token PROC FCT RET RIEN
%token SI ALORS SINON 
%token TQ FAIRE 
%token OPAFF INF SUP PL MO MU DIV MOD NON ET OU EGAL INFEGAL SUPEGAL DIFF


%%
programme             : PROG AO corps AF
                      ;

corps                 : liste_declarations liste_instructions
                      ;

liste_declarations    : // aucune decla
                      | liste_declarations declaration 
                      ;

liste_instructions : instruction
                   | liste_instructions instruction
                   ;

declaration           : declaration_type PV
                      | declaration_variable PV
                      | declaration_procedure
                      | declaration_fonction
                      ;

declaration_type      : TYPEDEF IDF DP suite_declaration_type
                      ;

suite_declaration_type : STRUCT AO liste_champs AF
                       | TAB dimension DE nom_type
                       ;

dimension             : CO liste_dimensions CF
                      ;

liste_dimensions      : une_dimension
                      | liste_dimensions VIR une_dimension
                      ;

une_dimension         : CSTE_ENTIERE PP CSTE_ENTIERE
                      ;

liste_champs          : un_champ
                      | liste_champs PV un_champ
                      ;

un_champ              : IDF DP nom_type PV
                      ;

declaration_variable  : VAR IDF DP nom_type
                      ;

declaration_procedure : PROC IDF PO liste_param PF AO corps AF
                      ;

declaration_fonction  : nom_type FCT IDF PO liste_param PF AO corps AF
                      ;

liste_param           : // aucun parametre
                      | un_param
                      | liste_param VIR un_param
                      ;

un_param              : IDF DP nom_type
                      ;

nom_type              : type_simple
                      | IDF
                      ;

type_simple           : ENTIER
                      | REEL
                      | BOOL
                      | CHAR
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

affectation           : variable OPAFF CSTE_BOOL
                      | variable OPAFF exp
                      ;

                      // description des formes possibles des variables 
variable              : IDF
                      | IDF CO CSTE_ENTIERE CF
                      | IDF POINT variable
                      ;

appel                 : IDF liste_arguments
                      ;

liste_arguments       : PO PF //modif (avant y avait rien)
                      | PO liste_args PF
                      ;

liste_args            : exp
                      | liste_args VIR exp
                      ;

exp                   : expa
                      | expb
                      ;

expa                  : expa PL expa1
                      | expa MO expa1
                      | expa1
                      ;

expa1                 : expa1 MU expa2
                      | expa1 DIV expa2
                      | expa1 MOD expa2 
                      | expa2
                      ;

expa2                 : PO expa PF 
                      | variable
                      | appel
                      | CSTE_REELLE
                      | CSTE_ENTIERE
                      ;

expb                  : expb OU expb1
                      | expb1
                      ;

expb1                 : expb1 ET expb2
                      | expb2 
                      ;

expb2                 : NON PO expb3 PF
                      | PO expb3 PF
                      ;

expb3                 : expa SUPEGAL expa 
                      | expa SUP expa
                      | expa INFEGAL expa
                      | expa INF expa
                      | expa EGAL expa
                      | expa DIFF expa
                      | CSTE_BOOL EGAL variable
                      | CSTE_BOOL DIFF variable
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

    yyparse();

    // afficher_tab_lexico(0, 5);
 
    exit(EXIT_SUCCESS);
    
}
