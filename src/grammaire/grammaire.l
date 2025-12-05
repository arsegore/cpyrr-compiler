%{
    #include "arbre/arbre.h"
    #include "y.tab.h"
    #include "tables/tab_lexico.h"
    #include "tables/tab_rep.h"
    #include "tables/tab_code.h"

    #define BUFFER_LIGNE() \
        do { \
            for (int i = 0; yytext[i] && pos < TAILLE_MAX_LIGNE - 1; i++) { \
                ligne[pos++] = yytext[i]; \
            } \
            ligne[pos] = '\0'; \
        } while(0)

    char ligne[TAILLE_MAX_LIGNE];
    int pos = 0;
    int ligne_courante = 1;
%}
IDF [a-zA-Z][a-zA-Z0-9_]*
INT [1-9][0-9]*|0
%%
programme            {return(PROG);}
\{                   {return(AO);}
\}                   {return(AF);}
\;                   {return(PV);}
:                    {return(DP);}
\[                   {return(CO);}
\]                   {return(CF);}
,                    {return(VIR);}
\.\.                 {return(PP);}
\(                   {return(PO);}
\)                   {return(PF);}
tab                  {return(TAB);}
of                   {return(DE);}
struct               {return(STRUCT);}
int                  {yylval.intval = TYPE_INT; return(ENTIER);}
float                {yylval.intval = TYPE_FLOAT; return(REEL);}
bool                 {yylval.intval = TYPE_BOOL; return(BOOL);}
char                 {yylval.intval = TYPE_CHAR; return(CHAR);}
var                  {return(VAR);}
typedef              {return(TYPEDEF);}
proc                 {return(PROC);}
fct                  {return(FCT);}
ret                  {return(RET);}
if                   {return(SI);}
then                 {return(ALORS);}
else                 {return(SINON);}
while                {return(TQ);}
do                   {return(FAIRE);}
==                   {return(EGAL);}
\<=                  {return(INFEGAL);}
\>=                  {return(SUPEGAL);}
\=                   {return(OPAFF);}
\+                   {return(PL);}
-                    {return(MO);}
\/                   {return(DIV);}
\*                   {return(MU);}
\<                   {return(INF);}
\>                   {return(SUP);}
\%                   {return(MOD);}
!=                   {return(DIFF);}
!                    {return(NON);}
\.                   {return(POINT);}
"&&"                 {return(ET);}
"||"                 {return(OU);}
true                 {return(CSTE_BOOL);}
false                {return(CSTE_BOOL);}
none                 {return(RIEN);}
{IDF}                {
                        yylval.intval = inserer_lexeme(yytext, yyleng);
                        BUFFER_LIGNE();
                        return(IDF);
                     }
{INT}                {yylval.intval = atoi(yytext); BUFFER_LIGNE(); return(CSTE_ENTIERE);}
\'([^\'\\]|\\.)\'    {BUFFER_LIGNE(); return(CSTE_CHAR);}
\"([^\"\\]|\\.)*\"   {BUFFER_LIGNE(); return(CSTE_CHAINE);}
{INT}"."{INT}        {BUFFER_LIGNE(); return(CSTE_REELLE);}
" "                  {BUFFER_LIGNE();}
\t                   {BUFFER_LIGNE();}
\n                   {ajouter_ligne_code(ligne); pos = 0; ligne[0] = '\0'; ligne_courante++;}
.                    {printf("Mauvais caractère : %s\n", yytext);}

%%

int yywrap(){
    return(1);
}



