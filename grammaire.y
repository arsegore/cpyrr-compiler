%{

%}
%token PROG
%token PV DP CO CF VIR PP PO PF AO AF        // ; : [ ] , .. ( ) { }
%token TAB DE STRUCT
%token CSTE_ENTIERE CSTE_CHAR CSTE_CHAINE CSTE_BOOL
%token ENTIER REEL BOOL CHAR CHAINE 
%token VAR TYPEDEF IDF
%token PROC FCT RET
%token SI ALORS SINON 
%token TQ FAIRE 
%token OPAFF INF SUP PL MO MU DIV MOD NON ET OU


%%
programme             : PROG AO corps AF
                      ;

corps                 : liste_declarations liste_instructions
                      | liste_instructions
                      ;

liste_declarations    : declaration PV
                      | liste_declarations declaration PV
                      ;

liste_instructions    : instruction PV
                      | liste_instructions instruction PV
                      ;

declaration           : declaration_type
                      | declaration_variable
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

nom_type              : type_simple
                      | IDF
                      ;

type_simple           : ENTIER
                      | REEL
                      | BOOL
                      | CHAR
                      | CHAINE CO CSTE_ENTIERE CF
                      ;

declaration_variable  : VAR IDF DP nom_type
                      ;

/* LES 2 EN-DESSOUS LA FAUT METTRE RET PEUT-ETRE APRES CORPS DANS FONC, ET GERER PROC JSP COMMENT FORCE ET NTM PAUL PERSONNE T'AIME */

declaration_procedure : PROC IDF PO liste_param PF AO corps AF
                      ;

declaration_fonction  : nom_type FCT IDF PO liste_param PF AO corps AF
                      ;

liste_param           :
                      | un_param
                      | liste_param VIR un_param
                      ;

un_param              : IDF DP type_simple
                      ;

instruction           : affectation
                      | condition
                      | tant_que
                      | appel
                      |
                      | RET resultat_retourne
                      ;

resultat_retourne     :
                      | expression
                      ;

appel                 : IDF liste_arguments
                      ;

liste_arguments       :
                      | PO liste_args PF
                      ;

liste_args            : expression
                      | liste_args VIR expression
                      ;

condition             : SI expression_booleenne ALORS liste_instructions SINON liste_instructions
                      ;

tant_que              : TQ expression_booleenne FAIRE liste_instructions
                      ;

affectation           : variable OPAFF expression
                      ;

                      // description des formes possibles des variables 
variable              : IDF
                      | IDF CO CSTE_ENTIERE CF
                      ;


expression            : e
                      | expression_booleenne
                      ;

e                     : e PL e1
                      | e MO e1
                      | e1
                      ;

e1                    : e1 MU e2
                      | e1 DIV e2
                      | e2
                      ;

e2                    : PO e PF
                      | CSTE_ENTIERE
                      ;

egalite_booleenne     : IDF OPAFF OPAFF IDF
                      | IDF INF IDF
                      | IDF SUP IDF
                      | IDF INF OPAFF IDF
                      | IDF SUP OPAFF IDF
                      | CSTE_BOOL OPAFF OPAFF IDF
                      | IDF OPAFF OPAFF CSTE_BOOL
                      | CSTE_BOOL OPAFF OPAFF CSTE_BOOL
                      ;

expression_booleenne  : egalite_booleenne
                      | NON expression_booleenne
                      ;
%%