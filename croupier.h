#ifndef CROUPIER_H_INCLUDED
#define CROUPIER_H_INCLUDED
#include "pioche.h"

typedef struct croupier{
    CARTE tab_cartes[10]; /*cartes tirees par le croupier */
    int nb_cartes; /* nombre de cartes tirees */
    int score;
} CROUPIER;

CROUPIER *init_croupier();
void affiche_carte_croupier(CROUPIER *c);
void tirage_carte_croupier_debut(PIOCHE *p,CROUPIER *c);
void liberer_croupier(CROUPIER *c);
int croupier_a_blackjack(CROUPIER *c);


#endif // CROUPIER_H_INCLUDED
