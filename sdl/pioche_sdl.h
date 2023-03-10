#ifndef PIOCHE_H_INCLUDED
#define PIOCHE_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction_sdl.h"


#define NB_JEUX_CARTES 3

typedef enum couleur {CARREAU,COEUR,PIC,TREFLE} COULEUR;

typedef struct carte{
    int num;
    COULEUR couleur;
    struct carte * suivant;
    char nom_image[18];
}CARTE;

typedef struct pioche{
    int nb_cartes;
    CARTE * tete;
}PIOCHE;

PIOCHE* init_pioche();
CARTE* tirer_carte(PIOCHE *p);
void liberer_pioche(PIOCHE *p);
char *StructToChaine(CARTE *c);

#endif // PIOCHE_H_INCLUDED
