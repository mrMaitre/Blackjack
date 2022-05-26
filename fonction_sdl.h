#ifndef __FONCTION_H__
#define __FONCTION_H__
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "joueur.h"
#include <SDL2/SDL_ttf.h>


SDL_Window *window;
SDL_Texture *image;
int statut;
SDL_Renderer *renderer;
SDL_Event event;


/* Couleur du texte ici blanc*/
SDL_Color TextColor;



/* Rectangles avec l'emplacement des cartes du croupier */
SDL_Rect carte_croup_dos;
SDL_Rect carte_croup_autre;
    
/* Rectangles avec l'emplacement de la première carte de gauche à droite */
SDL_Rect carte_emp1;
SDL_Rect carte_emp2;
SDL_Rect carte_emp3;
SDL_Rect carte_emp4;
SDL_Rect carte_emp5;

/* Rectangles avec l'emplacement du nom du joueur de gauche à droite */
SDL_Rect nomj_emp1; 
SDL_Rect nomj_emp2;
SDL_Rect nomj_emp3; 
SDL_Rect nomj_emp4;
SDL_Rect nomj_emp5; 

/* Rectangles avec l'emplacement du capital du joueur de gauche à droite */
SDL_Rect capital_emp1; 
SDL_Rect capital_emp2;
SDL_Rect capital_emp3; 
SDL_Rect capital_emp4;
SDL_Rect capital_emp5; 

/* Rectangles avec l'emplacement de la mise du joueur de gauche à droite */
SDL_Rect mise_emp1; 
SDL_Rect mise_emp2;
SDL_Rect mise_emp3; 
SDL_Rect mise_emp4;
SDL_Rect mise_emp5; 

/* Rectangles avec l'emplacement de la zone a supprimer pour split */
SDL_Rect split_emp1; 
SDL_Rect split_emp2;
SDL_Rect split_emp3; 
SDL_Rect split_emp4;
SDL_Rect split_emp5; 

/*Rectangle écriture mise*/
SDL_Rect mise;
    

	
int quitter();

void afficher_carte(const char nom_fichier[], SDL_Renderer *renderer, SDL_Rect *dstrect, int x_offset, int y_offset);

/* Initialisation de la SDL*/
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

/* Fonction qui permet de passer d'une fichier à une texture*/
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);

/* Fonction qui change la couleur de la fenetre*/
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);

void reinitialiser_plateau(SDL_Renderer *renderer);
void saisie_des_joueurs(SDL_Renderer *renderer);
void afficher_menu(SDL_Renderer *renderer);
void afficher_vierge(SDL_Renderer *renderer);
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], SDL_Rect DstRect, int offsetX);
void afficher_entier(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, int entier, SDL_Rect DstRect, int offsetX);
void remp_carte(SDL_Renderer *renderer, SDL_Rect *dstrect, int n);

	


#endif //FONCTION_SDL_H_INCLUDED
