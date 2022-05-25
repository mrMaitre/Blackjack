#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>


SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    int statut = EXIT_FAILURE;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    

	/* Couleur du texte ici blanc*/
	SDL_Color TextColor = {255, 255, 255};
	
    
    
    /* Rectangles avec l'emplacement des cartes du croupier */
    SDL_Rect carte_croup_dos = {380, 180, 71, 96};
    SDL_Rect carte_croup_autre = {380, 180, 71, 96};
        
    /* Rectangles avec l'emplacement de la première carte de gauche à droite */
    SDL_Rect carte_emp1 = {38, 410, 71, 96};
    SDL_Rect carte_emp2 = {294, 410, 71, 96};
    SDL_Rect carte_emp3 = {550, 410, 71, 96};
    SDL_Rect carte_emp4 = {806, 410, 71, 96};
    SDL_Rect carte_emp5 = {1062, 410, 71, 96};
    
    /* Rectangles avec l'emplacement du nom du joueur de gauche à droite */
    SDL_Rect nomj_emp1 = {48, 320, 0, 0}; 
    SDL_Rect nomj_emp2 = {304, 320, 0, 0};
    SDL_Rect nomj_emp3 = {560, 320, 0, 0}; 
    SDL_Rect nomj_emp4 = {816, 320, 0, 0};
    SDL_Rect nomj_emp5 = {1072, 320, 0, 0}; 
    
    /* Rectangles avec l'emplacement du capital du joueur de gauche à droite */
    SDL_Rect capital_emp1 = {48, 345, 0, 0}; 
    SDL_Rect capital_emp2 = {304, 345, 0, 0};
    SDL_Rect capital_emp3 = {560, 345, 0, 0}; 
    SDL_Rect capital_emp4 = {816, 345, 0, 0};
    SDL_Rect capital_emp5 = {1072, 345, 0, 0}; 
    
    /* Rectangles avec l'emplacement de la mise du joueur de gauche à droite */
    SDL_Rect mise_emp1 = {48, 660, 0, 0}; 
    SDL_Rect mise_emp2 = {304, 660, 0, 0};
    SDL_Rect mise_emp3 = {560, 660, 0, 0}; 
    SDL_Rect mise_emp4 = {816, 660, 0, 0};
    SDL_Rect mise_emp5 = {1072, 660, 0, 0}; 
    
    /* Rectangles avec l'emplacement de la zone a supprimer pour split */
    SDL_Rect split_emp1 = {44, 410, 200, 160}; 
    SDL_Rect split_emp2 = {292, 410, 200, 160};
    SDL_Rect split_emp3 = {540, 410, 200, 160}; 
    SDL_Rect split_emp4 = {788, 410, 200, 160};
    SDL_Rect split_emp5 = {1036, 410, 200, 160}; 
    

	
int quitter();

/* Initialisation de la SDL*/
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

/* Fonction qui permet de passer d'une fichier à une texture*/
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);

/* Fonction qui change la couleur de la fenetre*/
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);

void reinitialiser_plateau(SDL_Renderer *renderer);
void saisie_des_joueurs(SDL_Renderer *renderer);
void afficher_menu(SDL_Renderer *renderer);
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], SDL_Rect DstRect);
void remp_carte(SDL_Renderer *renderer, SDL_Rect *dstrect, int n);
	


#endif //FONCTION_H_INCLUDED
