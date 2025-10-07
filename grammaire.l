%{

%}
IDF    [a-zA-Z][a-zA-Z0-9]*
ENTIER [1-9][0-9]*|0
%%
programme            {return(PROG);}
\{                   {return(AO);}
\}                   {return(AF);}
;                    {return(PV);}
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
float                {return(FLOAT);}
bool                 {return(BOOL);}
char                 {return(CHAR);}
string               {return(CHAINE);}
var                  {return(VAR);}
typedef              {return(TYPEDEF);}
proc                 {return(PROCEDURE);}
fct                  {return(FCT);}
ret                  {return(RET);}
si                   {return(SI);}
alors                {return(ALORS);}
sinon                {return(SINON);}
tq                   {return(TANT_QUE)}
faire                {return(FAIRE);}
=                    {return(OPAFF);}
\+                   {return(PL);}
-                    {return(MO);}
\/                   {return(DI);}
\*                   {return(MU);}
\<                   {return(INF);}
\>                   {return(SUP);}
\%                   {return(MOD);}
non                  {return(NON);}
et                   {return(ET);}
ou                   {return(OU);}
" "                  {}
[\t]                 {}
{IDF}                {return(IDF);}
{ENTIER}             {return(CSTE_ENTIERE);}
[\'.\']              {return(CSTE_CHAR);}
[\".*\"]             {return(CSTE_CHAINE);}
\true|\false                 {return(CSTE_BOOL);}
{ENTIER}|{ENTIER},{ENTIER} {return(CSTE_REELLE);}







%%