#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "croupier.h"

#define MAX_JOUEURS 5

typedef struct table{
    int nb_joueurs;
    JOUEUR * tete;
    CROUPIER * croupier;
    PIOCHE * pioche;
} TABLE;



TABLE* init_table();
int table_est_pleine(TABLE* p);
int table_est_vide(TABLE* p);
void saisie_joueurs_croupier_dans_table(TABLE* table);
void affiche_table(TABLE* p);
void demande_mises(TABLE* p);
int comptage_score_croupier(CROUPIER *c);
int comptage_score_joueur(JOUEUR *j);
int compter_score(CARTE* tab_cartes, int nb_cartes);
void repartition_gains(TABLE *t);
void tirage_debut_partie(TABLE *t);
void reste_sur_table(TABLE *t);
void assigner_pioche(TABLE *t, PIOCHE *p);
void tirage_carte_croupier_apres_mises(TABLE *t);
void tirage_carte_joueur_mises(TABLE *t,JOUEUR *j);
void sortie_joueur_table(JOUEUR *j,TABLE *t);
void joueur_double(JOUEUR *j, TABLE *t);
int comptage_score_split_joueur(JOUEUR* j);

#endif //TABLE_H_INCLUDED
