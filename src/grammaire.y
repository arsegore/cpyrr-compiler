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

condition             : SI exp ALORS AO liste_instructions AF SINON AO liste_instructions AF
                      ;

tant_que              : TQ exp FAIRE AO liste_instructions AF
                      ;

resultat_retourne     : exp
                      ;

affectation           : variable OPAFF exp
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

liste_args            : exp
                      | liste_args VIR exp
                      ;

exp : exp OU exp_et
           | exp_et
           ;

exp_et : exp_et ET exp_comp
       | exp_comp
       ;

exp_comp : exp_comp EGAL exp_arith1
         | exp_comp INF exp_arith1
         | exp_comp INFEGAL exp_arith1
         | exp_comp SUP exp_arith1
         | exp_comp SUPEGAL exp_arith1
         | exp_arith1
         ;

exp_arith1 : exp_arith1 PL exp_arith2
           | exp_arith1 MO exp_arith2
           | exp_arith2
           ;

exp_arith2 : exp_arith2 MU exp_finale
           | exp_arith2 DIV exp_finale
           | exp_finale
           ;

exp_finale : PO exp PF
           | CSTE_ENTIERE
           | CSTE_REELLE
           | CSTE_CHAR
           | CSTE_CHAINE
           | CSTE_BOOL
           | IDF
           ;

                    
%%

