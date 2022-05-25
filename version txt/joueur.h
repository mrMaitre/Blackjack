#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "pioche.h"


typedef struct joueur{
    char nom[25];
    int en_jeu;
    float capital;
    float mise;
    int score;
    CARTE tab_cartes[10];
    int nb_cartes;
    int split;
    float mise_split;
    int score_split;
    CARTE tab_cartes_split[10];
    int nb_cartes_split;
    struct joueur * suivant;
} JOUEUR;


JOUEUR* saisie_joueur();
void affiche_joueur(JOUEUR* j);
void affiche_carte_joueur(JOUEUR* j);
void tirage_carte_joueur_debut(PIOCHE *p,JOUEUR *j);
void liberer_joueur(JOUEUR *j);
int joueur_a_blackjack(JOUEUR *j);
void joueur_split(JOUEUR *j);

#endif // JOUEUR_H_INCLUDED
