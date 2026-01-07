%{
#include "arbre/arbre.h"
#include "y.tab.h"
#include "tables/tab_lexico.h"
#include "tables/tab_rep.h"
#include "tables/tab_code.h"
#include "tables/tab_reels.h"

#define BUFFER_LIGNE() \
    do { \
        for (int i = 0; yytext[i] && pos < TAILLE_MAX_LIGNE - 1; i++) { \
            ligne[pos++] = yytext[i]; \
        } \
        ligne[pos] = '\0'; \
    } while(0)

extern char ligne[TAILLE_MAX_LIGNE];
int pos = 0;
int ligne_courante = 1;

%}
IDF [a-zA-Z][a-zA-Z0-9_]*
INT [1-9][0-9]*|0
%%
main                 {BUFFER_LIGNE(); return(PROG);}
\{                   {BUFFER_LIGNE(); return(AO);}
\}                   {BUFFER_LIGNE(); return(AF);}
\;                   {BUFFER_LIGNE(); return(PV);}
:                    {BUFFER_LIGNE(); return(DP);}
\[                   {BUFFER_LIGNE(); return(CO);}
\]                   {BUFFER_LIGNE(); return(CF);}
,                    {BUFFER_LIGNE(); return(VIR);}
\.\.                 {BUFFER_LIGNE(); return(PP);}
\(                   {BUFFER_LIGNE(); return(PO);}
\)                   {BUFFER_LIGNE(); return(PF);}
tab                  {BUFFER_LIGNE(); return(TAB);}
of                   {BUFFER_LIGNE(); return(DE);}
struct               {BUFFER_LIGNE(); return(STRUCT);}
int                  {yylval.intval = TYPE_INT; BUFFER_LIGNE(); return(ENTIER);}
float                {yylval.intval = TYPE_FLOAT; BUFFER_LIGNE(); return(REEL);}
bool                 {yylval.intval = TYPE_BOOL; BUFFER_LIGNE(); return(BOOL);}
char                 {yylval.intval = TYPE_CHAR; BUFFER_LIGNE(); return(CHAR);}
var                  {BUFFER_LIGNE(); return(VAR);}
typedef              {BUFFER_LIGNE(); return(TYPEDEF);}
proc                 {BUFFER_LIGNE(); return(PROC);}
fct                  {BUFFER_LIGNE(); return(FCT);}
ret                  {BUFFER_LIGNE(); return(RET);}
if                   {BUFFER_LIGNE(); return(SI);}
then                 {BUFFER_LIGNE(); return(ALORS);}
else                 {BUFFER_LIGNE(); return(SINON);}
while                {BUFFER_LIGNE(); return(TQ);}
do                   {BUFFER_LIGNE(); return(FAIRE);}
==                   {BUFFER_LIGNE(); return(EGAL);}
\<=                  {BUFFER_LIGNE(); return(INFEGAL);}
\>=                  {BUFFER_LIGNE(); return(SUPEGAL);}
\=                   {BUFFER_LIGNE(); return(OPAFF);}
\+                   {BUFFER_LIGNE(); return(PL);}
-                    {BUFFER_LIGNE(); return(MO);}
\/                   {BUFFER_LIGNE(); return(DIV);}
\*                   {BUFFER_LIGNE(); return(MU);}
\<                   {BUFFER_LIGNE(); return(INF);}
\>                   {BUFFER_LIGNE(); return(SUP);}
\%                   {BUFFER_LIGNE(); return(MOD);}
!=                   {BUFFER_LIGNE(); return(DIFF);}
!                    {BUFFER_LIGNE(); return(NON);}
\.                   {BUFFER_LIGNE(); return(POINT);}
"&&"                 {BUFFER_LIGNE(); return(ET);}
"||"                 {BUFFER_LIGNE(); return(OU);}
true                 {BUFFER_LIGNE(); return(CSTE_BOOL);}
false                {BUFFER_LIGNE(); return(CSTE_BOOL);}
none                 {BUFFER_LIGNE(); return(RIEN);}
{IDF}                {
                        yylval.intval = inserer_lexeme(yytext, yyleng);
                        BUFFER_LIGNE();
                        return(IDF);
                     }
{INT}                {yylval.intval = atoi(yytext); BUFFER_LIGNE(); return(CSTE_ENTIERE);}
\'([^\'\\]|\\.)\'    {yylval.intval = (int) *(yytext + 1); BUFFER_LIGNE(); return(CSTE_CHAR); /* remonte le code ascii, décalage de 1 sur le ptr car 1er char de yytext = ' */}
\"([^\"\\]|\\.)*\"   {BUFFER_LIGNE(); return(CSTE_CHAINE);}
{INT}"."{INT}        {yylval.intval = inserer_reel(atof(yytext)); BUFFER_LIGNE(); return(CSTE_REELLE);}
" "                  {BUFFER_LIGNE();}
\t                   {BUFFER_LIGNE();}
\n                   {ajouter_ligne_code(ligne); pos = 0; ligne[0] = '\0'; ligne_courante++;}
.                    {printf("Mauvais caractère : %s\n", yytext);}

%%

int yywrap(){
    return(1);
}



