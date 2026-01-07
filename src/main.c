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

// Macros pour les couleurs de texte
#define RESET   "\x1B[0m"
#define ROUGE   "\x1B[31m"
#define VERT    "\x1B[32m"
#define JAUNE   "\x1B[33m"
#define BLEU    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define BLANC   "\x1B[37m"

// Macros pour mettre en gras
#define GRAS    "\x1B[1m"

extern int yyparse();

int main(int argc, char **argv){
    init_tab_code();
    init_tab_lexico();
    init_tab_decla();
    init_tab_rep();
    init_pile_decla();
    init_tab_regions();

    printf(GRAS JAUNE "--- Démarrage de l'analyse... --- \n " RESET);

    int resultat = yyparse();

    if (resultat != 0 || nb_err_sem > 0) {
        printf(GRAS ROUGE "\n[!] Analyse terminée avec %d erreur(s).\n" RESET, nb_err_sem);
    } else {
        printf(GRAS VERT "\n[OK] Analyse réussie.\n" RESET);
    }

    printf("\n\n --- Affichage des tables --- \n\n");
    afficher_tab_lexico(0,15);
    afficher_tab_decla();
    afficher_tab_rep(0, 15);
    afficher_tab_regions();
    printf("\n\n ---------------------------- \n\n");

    // affichage des arbres
    afficher_arbres_regions();

    // si pas d'erreur, on lance l'éxécution
    if (nb_err_sem == 0){
        lancer_execution();
    }


    exit(EXIT_SUCCESS);
}