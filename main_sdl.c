#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "table.h"
#include <SDL2/SDL_ttf.h>

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
void afficher_carte(const char nom_fichier[], SDL_Renderer *renderer, SDL_Rect *dstrect, int x_offset, int y_offset);
void reinitialiser_plateau(SDL_Renderer *renderer);
void afficher_menu();
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], SDL_Rect DstRect);
void remp_carte(SDL_Renderer *renderer, SDL_Rect *dstrect, int n);

int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    int statut = EXIT_FAILURE;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    
    int nb_joueur = 0;

	/* Couleur du texte ici blanc*/
	SDL_Color TextColor;
	TextColor.r = 255;
	TextColor.g = 255;
	TextColor.b = 255;
	
    if(init(&window, &renderer, 1280, 720) != 0 )
        goto Quit;

    statut = EXIT_SUCCESS;
    
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
    
Menu:    
	afficher_menu(renderer);
    
    while(nb_joueur == 0){	
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT: // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) goto Quit;
				    break;
				case SDL_MOUSEBUTTONDOWN : //Evenement de la souris
					if(event.button.y>420 && event.button.y<470){
						if(event.button.x>190 && event.button.x<240) nb_joueur = 1;
						if(event.button.x>400 && event.button.x<450) nb_joueur = 2;
						if(event.button.x>610 && event.button.x<660) nb_joueur = 3;
						if(event.button.x>830 && event.button.x<880) nb_joueur = 4;
						if(event.button.x>1040 && event.button.x<1090) nb_joueur = 5;
					}
				    break;
			}
		}
	}
	
	SDL_Delay(500);
	
    reinitialiser_plateau(renderer);
    
    SDL_Delay(20);
    
    /* Test affichage nom, capital et mises joueurs */
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " John", nomj_emp1);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp1);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp1);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " John", nomj_emp2);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp2);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp2);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " John", nomj_emp3);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp3);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp3);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " John", nomj_emp4);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp4);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp4);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " John", nomj_emp5);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp5);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp5);
	
	while(1){
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT: // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // Fermeture de la fenêtre
				    {
				        goto Quit;
				    }
				    break;
				case SDL_KEYDOWN	: // Événement de relâchement d'une touche clavier
				    if ( event.key.keysym.sym == SDLK_ESCAPE ) //Touche Échap
				    {
				    	nb_joueur = 0;
				        goto Menu;
				    }
				    if ( event.key.keysym.sym == SDLK_a) //Touche a
				    {
						afficher_carte("cartes/3c.bmp", renderer, &carte_emp1, 15, 15);
				    }
				    if ( event.key.keysym.sym == SDLK_e ) //Touche e
				    {
				        afficher_carte("cartes/10c.bmp", renderer, &carte_emp2, 15, 15);
				    }
				    if ( event.key.keysym.sym == SDLK_r) //Touche r
				    {
						afficher_carte("cartes/3c.bmp", renderer, &carte_emp3, 15, 15);
				    }
				    if ( event.key.keysym.sym == SDLK_t ) 
				    {
				        afficher_carte("cartes/6d.bmp", renderer, &carte_emp4, 15, 15);
				    }
				    if ( event.key.keysym.sym == SDLK_y )
				    {
				        afficher_carte("cartes/Js.bmp", renderer, &carte_emp5, 15, 15);
				    }
				    if ( event.key.keysym.sym == SDLK_u) 
				    {
						afficher_carte("cartes/Dos.bmp", renderer, &carte_croup_dos, 0, 0);
				    }
				    if ( event.key.keysym.sym == SDLK_i ) 
				    {
				        afficher_carte("cartes/Ah.bmp", renderer, &carte_croup_autre, 0, 73);
				    }
				    if ( event.key.keysym.sym == SDLK_c ) 
				    {
				        reinitialiser_plateau(renderer);
				    }
				    if ( event.key.keysym.sym == SDLK_z) 
				    {
						afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "mange tes morts", nomj_emp1);
				    }
				    if ( event.key.keysym.sym == SDLK_f) 
				    {
						remp_carte(renderer, &split_emp1, 1);

				    }
				    if ( event.key.keysym.sym == SDLK_g) 
				    {
						remp_carte(renderer, &split_emp2, 2);

				    }
				    if ( event.key.keysym.sym == SDLK_h) 
				    {
						remp_carte(renderer, &split_emp3, 3);

				    }
				    if ( event.key.keysym.sym == SDLK_j) 
				    {
						remp_carte(renderer, &split_emp4, 4);

				    }
				    if ( event.key.keysym.sym == SDLK_k) 
				    {
						remp_carte(renderer, &split_emp5, 5);

				    }
				    break;
			}
		}
	}
	
Quit:
	if(NULL != image)
	    SDL_DestroyTexture(image);
	if(NULL != renderer)
	    SDL_DestroyRenderer(renderer);
	if(NULL != window)
	    SDL_DestroyWindow(window);
	
	TTF_Quit();
	SDL_Quit();
		return statut;
}

/* Initialisation de la SDL*/
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return -1;
    }
    if(SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer) != 0)
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s\n", SDL_GetError());
        return -1;
    }
    TTF_Init();
    return 0;
}

/* Fonction qui permet de passer d'une fichier à une texture*/
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL; 
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s\n", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

/* Fonction qui change la couleur de la fenetre*/
int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;  
}

/* Fonction qui permet d'afficher une image a partir de son nom de fichier et de son rectangle avec la possibilité d'ajouter un offset*/
void afficher_carte(const char nom_fichier[], SDL_Renderer *renderer, SDL_Rect *dstrect, int x_offset, int y_offset){
	SDL_Texture *image = NULL;
	dstrect->y += x_offset;
	dstrect->x += y_offset;
	image = loadImage(nom_fichier, renderer);
    if(NULL == image) return;
	SDL_RenderCopy(renderer, image, NULL, dstrect);
	SDL_RenderPresent(renderer);
}

/* Fonction qui revient au plateau vide */
void reinitialiser_plateau(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("Plateau.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/* Fonction qui affiche le menu du jeu */
void afficher_menu(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("Menu.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/* Affiche texte */
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], SDL_Rect DstRect){
	TTF_Font* Font = TTF_OpenFont(police, taille_police); /* Charge une police depuis un fichier .ttf*/
	if(!Font)
	{
		printf("Erreur de création de la police : %s", TTF_GetError());
		return;
	}

	SDL_Surface * surf = TTF_RenderText_Blended(Font, texte, TextColor);
	SDL_Texture * TextSurface = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_QueryTexture(TextSurface, NULL, NULL, &DstRect.w, &DstRect.h);
	SDL_RenderCopy(renderer, TextSurface, NULL, &DstRect);
	
	SDL_RenderPresent(renderer);
	
	SDL_FreeSurface(surf);
	TTF_CloseFont(Font);
}

void remp_carte(SDL_Renderer *renderer, SDL_Rect *dstrect, int n){
	SDL_Texture *image = NULL;
	if(n==1) image = loadImage("remp1.bmp", renderer);
	if(n==2) image = loadImage("remp2.bmp", renderer);
	if(n==3) image = loadImage("remp3.bmp", renderer);
	if(n==4) image = loadImage("remp4.bmp", renderer);
	if(n==5) image = loadImage("remp5.bmp", renderer);
	
    if(NULL == image) return;
	SDL_RenderCopy(renderer, image, NULL, dstrect);
	SDL_RenderPresent(renderer);
}

