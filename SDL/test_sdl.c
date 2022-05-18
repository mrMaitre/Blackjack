#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
void afficher_carte(const char nom_fichier[], SDL_Renderer *renderer, SDL_Rect *dstrect, int x_offset, int y_offset);
void reinitialiser_plateau(SDL_Renderer *renderer);
void afficher_menu();
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], int coord_x, int coord_y);

int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Texture *image = NULL;
    int statut = EXIT_FAILURE;
    SDL_Renderer *renderer = NULL;
    SDL_Renderer *renderer_save = NULL;
    SDL_Event event;
    	
    if(init(&window, &renderer, 1080, 720) != 0 )
        goto Quit;

    statut = EXIT_SUCCESS;
    
        
    SDL_Rect rect_carte = {60, 60, 71, 96};
    
    int nb_joueur = 0;

	/* Couleur du texte (ici rouge) */
	SDL_Color TextColor;
	TextColor.r = 255;
	TextColor.g = 0;
	TextColor.b = 0;
	
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
				case SDL_KEYDOWN:
					if ( event.key.keysym.sym == SDLK_ESCAPE ) goto Quit;
					if ( event.key.keysym.sym == SDLK_a) nb_joueur = 1;
					if ( event.key.keysym.sym == SDLK_b) nb_joueur = 2;
					if ( event.key.keysym.sym == SDLK_c) nb_joueur = 3;
					if ( event.key.keysym.sym == SDLK_d) nb_joueur = 4;
					if ( event.key.keysym.sym == SDLK_e) nb_joueur = 5;
					break;
			}
		}
	}
	
	SDL_Delay(500);
	
    reinitialiser_plateau(renderer);
	
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
				    if ( event.key.keysym.sym == SDLK_b) //Touche b
				    {
						afficher_carte("cartes/3c.bmp", renderer, &rect_carte, 20, 20);
				    }
				    if ( event.key.keysym.sym == SDLK_a ) //Touche a
				    {
				        afficher_carte("cartes/2c.bmp", renderer, &rect_carte, 20, 20);
				    }
				    if ( event.key.keysym.sym == SDLK_c ) //Touche c
				    {
				        reinitialiser_plateau(renderer);
				    }
				    if ( event.key.keysym.sym == SDLK_z) //Touche z
				    {
						afficher_texte(renderer, "Roboto-Regular.ttf", 50, TextColor, "mange tes morts", 0, 0);
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
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], int coord_x, int coord_y){
	TTF_Font* Font = TTF_OpenFont(police, taille_police); /* Charge une police depuis un fichier .ttf*/
	if(!Font)
	{
		printf("Erreur de création de la police : %s", TTF_GetError());
		return;
	}
	
	SDL_Rect DstRect;
	DstRect.x = coord_x;
	DstRect.y = coord_y;
	
	SDL_Surface * surf = TTF_RenderText_Blended(Font, texte, TextColor);
	SDL_Texture * TextSurface = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_QueryTexture(TextSurface, NULL, NULL, &DstRect.w, &DstRect.h);
	SDL_RenderCopy(renderer, TextSurface, NULL, &DstRect);
	
	SDL_RenderPresent(renderer);
	
	SDL_FreeSurface(surf);
	TTF_CloseFont(Font);
}

