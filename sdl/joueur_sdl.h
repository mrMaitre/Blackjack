#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "pioche_sdl.h"


typedef struct joueur{
    char nom[25];
    int en_jeu;
    int capital;
    int mise;
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



void tirage_carte_joueur_debut(SDL_Renderer *renderer, PIOCHE *p,JOUEUR *j, SDL_Rect emp, int offset);
void liberer_joueur(JOUEUR *j);
int joueur_a_blackjack(JOUEUR *j);
void joueur_split(JOUEUR *j);

#endif // JOUEUR_H_INCLUDED
