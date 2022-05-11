#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "croupier.h"

#define MAX_JOUEURS 5

typedef struct table{
    int nb_joueurs;
    JOUEUR * tete;
} TABLE;



TABLE* init_table();
int table_est_pleine(TABLE* p);
int table_est_vide(TABLE* p);
void saisie_joueurs_dans_table(TABLE* table);
void affiche_table(TABLE* p);
void demande_mises(TABLE* p);
int comptage_score_croupier(CROUPIER *c);
int comptage_score_joueurs(JOUEUR *j);
void compter_score(CARTE* tab_cartes, int nb_cartes);
