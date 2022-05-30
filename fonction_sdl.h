#ifndef __FONCTION_H__
#define __FONCTION_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int quitter(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer);

void afficher_carte(const char nom_fichier[], SDL_Renderer *renderer, SDL_Rect *dstrect, int x_offset, int y_offset);

/* Initialisation de la SDL*/
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

/* Fonction qui permet de passer d'une fichier à une texture*/
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
SDL_Texture *loadPNG(const char path[], SDL_Renderer *renderer);

/* Fonction qui change la couleur de la fenetre*/
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);

void reinitialiser_plateau(SDL_Renderer *renderer);
void saisie_des_joueurs(SDL_Renderer *renderer);
void afficher_menu(SDL_Renderer *renderer);
void afficher_vierge(SDL_Renderer *renderer);
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], SDL_Rect DstRect, int offsetX);
void afficher_entier(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, int entier, SDL_Rect DstRect, int offsetX);
void remp_carte(SDL_Renderer *renderer, SDL_Rect *dstrect, int n);
void choix(SDL_Renderer *renderer, SDL_Rect *dstrect, int n);

	


#endif //FONCTION_SDL_H_INCLUDED
