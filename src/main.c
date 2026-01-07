#include <stdio.h>
#include <stdlib.h>
#include "tables/tab_lexico.h"
#include "tables/tab_decla.h"
#include "tables/tab_rep.h"
#include "tables/tab_regions.h"
#include "tables/tab_code.h"
#include "tables/pile_regions.h"
#include "tables/pile_decla.h"
#include "association_noms/association_noms.h"
#include "save/save.h"
#include "verif_sem/verif_sem.h"
#include "arbre/arbre.h"
#include "machine_virtuelle/machine_virtuelle.h"
#include "y.tab.h"


int main(int argc, char **argv){
    init_tab_code();
    init_tab_lexico();
    init_tab_decla();
    init_tab_rep();
    init_pile_decla();
    init_tab_regions();

    int resultat = yyparse();

    if (resultat != 0 || nb_err_sem > 0) {
        printf("\n[!] Analyse terminée avec %d erreur(s).\n", nb_err_sem);
    } else {
        printf("\n[OK] Analyse réussie.\n");
    }

    afficher_tab_decla();
    afficher_tab_rep(0, 15);
    afficher_tab_regions(0, 15);
    afficher_tab_lexico(0,15);
    afficher_arbres_regions();

    lancer_execution();


    exit(EXIT_SUCCESS);
}