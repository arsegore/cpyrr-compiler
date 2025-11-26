#ifndef _TAB_CODE_H_
#define _TAB_CODE_H_

#define NB_LIGNES_MAX_PROG 1000

extern const char *tab_code[NB_LIGNES_MAX_PROG];
extern int nb_lignes_code;

void init_tab_code();

void ajouter_ligne_code(const char *ligne);

void recup_ligne_code(int num_ligne);

#endif