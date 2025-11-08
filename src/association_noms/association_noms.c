#include <stdio.h>
#include <stdlib.h>

#include "association_noms/association_noms.h"
#include "tables/tab_decla.h"
#include "tables/tab_lexico.h"

// NOTE : il faut aussi se servir de la pile des régions, voir notes tp
#include "tables/pile_regions.h"

/*
Probleme : si on imagine 2 variable x déclaree comme des INT, on recuperera toujours la premiere alors qu'on voulait peut-etre la 2eme
Solution? : parem en + pour différencier?
Est-ce vraiment un probleme?
*/
int association_noms(int num_lex, int nature){
    int i = num_lex;
    
    while (table_decl[i][NATURE] != nature){
        i = table_decl[i][SUIVANT];
    }
    
    return i;
}