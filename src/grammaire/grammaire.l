%{
    #include "y.tab.h"
    #include "tables/tab_lexico.h"
    #include "tables/tab_rep.h"
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
de                   {return(DE);}
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
si                   {return(SI);}
alors                {return(ALORS);}
sinon                {return(SINON);}
tq                   {return(TQ);}
faire                {return(FAIRE);}
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
et                   {return(ET);}
ou                   {return(OU);}
vrai                 {return(CSTE_BOOL);}
faux                 {return(CSTE_BOOL);}
rien                 {return(RIEN);}
{IDF}                {
                        yylval.intval = inserer_lexeme(yytext, yyleng);
                        return(IDF);
                     }
{INT}                {yylval.intval = atoi(yytext); return(CSTE_ENTIERE);}
\'([^\'\\]|\\.)\'    {return(CSTE_CHAR);}
\"([^\"\\]|\\.)*\"   {return(CSTE_CHAINE);}
{INT}"."{INT}        {return(CSTE_REELLE);}
" "                  ;
\t                   ;
\n                   ;
.                    {printf("Mauvais caractère : %s\n", yytext);}

%%

int yywrap(){
    return(1);
}



