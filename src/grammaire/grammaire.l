%{
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
    int ligne_courante = 0;
%}
IDF [a-zA-Z][a-zA-Z0-9_]*
INT [1-9][0-9]*|0
%%
programme            {BUFFER_LIGNE(); return(PROG);}
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
de                   {BUFFER_LIGNE(); return(DE);}
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
si                   {BUFFER_LIGNE(); return(SI);}
alors                {BUFFER_LIGNE(); return(ALORS);}
sinon                {BUFFER_LIGNE(); return(SINON);}
tq                   {BUFFER_LIGNE(); return(TQ);}
faire                {BUFFER_LIGNE(); return(FAIRE);}
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
et                   {BUFFER_LIGNE(); return(ET);}
ou                   {BUFFER_LIGNE(); return(OU);}
vrai                 {BUFFER_LIGNE(); return(CSTE_BOOL);}
faux                 {BUFFER_LIGNE(); return(CSTE_BOOL);}
rien                 {BUFFER_LIGNE(); return(RIEN);}
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



