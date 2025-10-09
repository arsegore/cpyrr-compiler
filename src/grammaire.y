%{
int yylex();
int yyerror(char *msg);
%}
%token PROG
%token PV DP CO CF VIR PP PO PF AO AF        // ; : [ ] , .. ( ) { }
%token TAB DE STRUCT
%token CSTE_ENTIERE CSTE_CHAR CSTE_CHAINE CSTE_BOOL CSTE_REELLE
%token ENTIER REEL BOOL CHAR CHAINE 
%token VAR TYPEDEF IDF
%token PROC FCT RET
%token SI ALORS SINON 
%token TQ FAIRE 
%token OPAFF INF SUP PL MO MU DIV MOD NON ET OU EGAL INFEGAL SUPEGAL


%%
programme             : PROG AO corps AF
                      ;

corps                 : liste_declarations liste_instructions
                      | liste_declarations 
                      ;

liste_declarations    : // aucune decla
                      | liste_declarations declaration 
                      ;

liste_instructions : instruction PV
                   | liste_instructions instruction PV
                   ;

declaration           : declaration_type PV
                      | declaration_variable PV
                      | declaration_procedure
                      | declaration_fonction
                      ;

declaration_type      : TYPEDEF IDF DP suite_declaration_type
                      ;

suite_declaration_type : STRUCT AO liste_champs AF PV
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
                      | CHAINE CO CSTE_ENTIERE CF
                      ;

instruction           : affectation
                      | condition
                      | tant_que
                      | appel
                      |
                      | RET resultat_retourne
                      ;

condition             : SI expression ALORS AO liste_instructions AF SINON AO liste_instructions AF
                      ;

tant_que              : TQ expression FAIRE AO liste_instructions AF
                      ;

resultat_retourne     : expression
                      ;

affectation           : variable OPAFF expression
                      ;

                      // description des formes possibles des variables 
variable              : IDF
                      | IDF CO CSTE_ENTIERE CF
                      ;

appel                 : IDF liste_arguments
                      ;

liste_arguments       :
                      | PO liste_args PF
                      ;

liste_args            : expression
                      | liste_args VIR expression
                      ;


expression
    : expression OU expression_et
    | expression_et
    ;

expression_et
    : expression_et ET expression_rel
    | expression_rel
    ;

expression_rel
    : expression_rel EGAL expression_arith
    | expression_rel INF expression_arith
    | expression_rel INFEGAL expression_arith
    | expression_rel SUP expression_arith
    | expression_rel SUPEGAL expression_arith
    | expression_arith
    ;

expression_arith
    : expression_arith PL expression_term
    | expression_arith MO expression_term
    | expression_term
    ;

expression_term
    : expression_term MU expression_fact
    | expression_term DIV expression_fact
    | expression_fact
    ;

expression_fact
    : PO expression PF
    | CSTE_ENTIERE
    | CSTE_REELLE
    | CSTE_CHAR
    | CSTE_CHAINE
    | CSTE_BOOL
    | IDF
    ;

                    
%%

