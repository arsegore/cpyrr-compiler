#ifndef _TABLE_DECLARATIONS_H_
#define _TABLE_DECLARATIONS_H_

#define N_STRUCT 1
#define N_TAB 2
#define N_VAR 3
#define N_PARAM 4 
#define N_PROC 5
#define N_FONC 6
#define HAUTEUR 5000
#define DEBORDEMENT 500

// on définit une matrice qui est capable de stocker pour chaque variable sa nature
// col 0 -> Nature
// col 1 -> Chainage sur declaration du meme nom
// col 2 -> Num de region qui contient la declaration
// col 3 -> si nature = 1 ou 2 index de la table contenant descrip
// col 3 -> si nature = 3 ou 4 index du type ( si 0, 1, 2 ou 3 alors type primaire
// col 3 -> sinon index de la table description d'entête
// col 4 -> si nature = 1 ou 2 taille a l'execution de la valeur de ce type
// col 4 -> si nature = 3 ou 4  deplacement a l'execution de l'emplacement associe
// col 4 -> sinon numero de la regio nassocie a la procedure ou fonction
typedef int table_decl[HAUTEUR][5];

// initialise la table jusqu'a n avec -1 a chaque champs
void initialiser(table_decl table, int n);

// permet de modifier le champ d'une ligne  en inserant une valeur
void modifier_champ(table_decl table, int ligne, int colonne, int val);

// affiche tous les champs d'une ligne passe en parametre
void afficher_element(table_decl table, int ligne);

// fait l'affichage de la table jusqu'a n valeur
void affichage(table_decl table, int n);

// permet d'ajouter une nouvelle ligne a la table
void ajouter_element(table_decl table, int nature, int region);

#endif