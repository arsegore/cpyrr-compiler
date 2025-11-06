%{
    #include "../inc/y.tab.h"
%}
IDF [a-zA-Z][a-zA-Z0-9]*
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
int                  {return(ENTIER);}
float                {return(REEL);}
bool                 {return(BOOL);}
char                 {return(CHAR);}
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
!                    {return(NON);}
!=                   {return(DIFF);}
et                   {return(ET);}
ou                   {return(OU);}
vrai                 {return(CSTE_BOOL);}
faux                 {return(CSTE_BOOL);}
rien                 {return(RIEN);}
{IDF}                {return(IDF);}
{INT}                {return(CSTE_ENTIERE);}
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



