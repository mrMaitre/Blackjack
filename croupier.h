#ifndef CROUPIER_H_INCLUDED
#define CROUPIER_H_INCLUDED
#include "pioche.h"

typedef struct croupier{
    CARTE tab_cartes[10]; /*cartes tirees par le croupier */
    int nb_cartes; /* nombre de cartes tirees */
} CROUPIER;

CROUPIER *init_croupier();
void tirage_carte_croupier_debut(PIOCHE *p,CROUPIER *c);
void tirage_carte_croupier_apres_mises(PIOCHE *p,CROUPIER *c);
int comptage_score_croupier(CROUPIER *c);
void liberer_croupier(CROUPIER *c);


#endif // CROUPIER_H_INCLUDED
