#include "../../inc/association_noms/association_noms.h"
#include <stdio.h>
#include <stdlib.h>

#include "../../inc/tables/tab_decla.h"
#include "../../inc/tables/tab_lexico.h"

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