#ifndef CROUPIER_H_INCLUDED
#define CROUPIER_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "pioche.h"

typedef struct croupier{
    CARTE tab_cartes[10]; /*cartes tirees par le croupier */
    int nb_cartes; /* nombre de cartes tirees */
    int score;
} CROUPIER;

CROUPIER *init_croupier();
void affiche_carte_croupier(CROUPIER *c);
void tirage_carte_croupier_debut(SDL_Renderer *renderer,PIOCHE *p,CROUPIER *c, SDL_Rect emp);
void liberer_croupier(CROUPIER *c);
int croupier_a_blackjack(CROUPIER *c);


#endif // CROUPIER_H_INCLUDED
