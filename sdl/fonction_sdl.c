#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonction_sdl.h"

/* Permet de quitter la sdl en liberant la memoire */
int quitter(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer){
	if(NULL != image)
	    SDL_DestroyTexture(image);
	if(NULL != renderer)
	    SDL_DestroyRenderer(renderer);
	if(NULL != window)
	    SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
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

/* Permet de charger un fichier au format PNG sur une texture */ 
SDL_Texture *loadPNG(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL; 
    SDL_Texture *texture = NULL;
    tmp = IMG_Load(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur IMG_Load : %s\n", SDL_GetError());
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

/* Affiche une image sur un renderer avec possibilité d'ajouter un décalage */ 
void afficher_carte(const char nom_fichier[], SDL_Renderer *renderer, SDL_Rect *dstrect, int x_offset, int y_offset){
	SDL_Texture *image = NULL;
	dstrect->x += x_offset;
	dstrect->y += y_offset;
	image = loadImage(nom_fichier, renderer);
    if(NULL == image) return;
	SDL_RenderCopy(renderer, image, NULL, dstrect);
	SDL_RenderPresent(renderer);
}

/* Fonction qui revient au plateau vide */
void reinitialiser_plateau(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("sdl/images/Plateau.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/* Affiche l'ecran de saisie des joueurs */
void saisie_des_joueurs(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("sdl/images/saisie_joueur.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/* Fonction qui affiche le menu du jeu */
void afficher_menu(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("sdl/images/Menu.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/* Fonction qui affiche le menu du jeu */
void afficher_vierge(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("sdl/images/Vierge.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/* Affiche le bouton start */
void afficher_start(SDL_Renderer *renderer, SDL_Rect start){
	SDL_Texture *image = NULL;
	image = loadPNG("sdl/images/Start.png", renderer);
	SDL_RenderCopy(renderer, image, NULL, &start);
    SDL_RenderPresent(renderer);
}

/* Affiche texte */
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], SDL_Rect DstRect, int offsetX){
	TTF_Font* Font = TTF_OpenFont(police, taille_police); /* Charge une police depuis un fichier .ttf*/
	if(!Font)
	{
		printf("Erreur de création de la police : %s", TTF_GetError());
		return;
	}
	DstRect.x += offsetX;
	SDL_Surface * surf = TTF_RenderText_Blended(Font, texte, TextColor);
	SDL_Texture * TextSurface = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_QueryTexture(TextSurface, NULL, NULL, &DstRect.w, &DstRect.h);
	SDL_RenderCopy(renderer, TextSurface, NULL, &DstRect);
	
	SDL_RenderPresent(renderer);
	
	SDL_FreeSurface(surf);
	TTF_CloseFont(Font);
}

/* Affiche un entier */ 
void afficher_entier(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, int entier, SDL_Rect DstRect, int offsetX){
	TTF_Font* Font = TTF_OpenFont(police, taille_police); /* Charge une police depuis un fichier .ttf*/
	if(!Font)
	{
		printf("Erreur de création de la police : %s", TTF_GetError());
		return;
	}
	DstRect.x += offsetX;
	char texte[6];
	sprintf(texte, "%d", entier);
	SDL_Surface * surf = TTF_RenderText_Blended(Font, texte, TextColor);
	SDL_Texture * TextSurface = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_QueryTexture(TextSurface, NULL, NULL, &DstRect.w, &DstRect.h);
	SDL_RenderCopy(renderer, TextSurface, NULL, &DstRect);
	
	SDL_RenderPresent(renderer);
	
	SDL_FreeSurface(surf);
	TTF_CloseFont(Font);
}

/* Reinitialise le carre du joueur passé en paramètre */
void remp_carte(SDL_Renderer *renderer, SDL_Rect *dstrect, int n){
	SDL_Texture *image = NULL;
	if(n==1) image = loadImage("sdl/images/remp1.bmp", renderer);
	if(n==2) image = loadImage("sdl/images/remp2.bmp", renderer);
	if(n==3) image = loadImage("sdl/images/remp3.bmp", renderer);
	if(n==4) image = loadImage("sdl/images/remp4.bmp", renderer);
	if(n==5) image = loadImage("sdl/images/remp5.bmp", renderer);
	
    if(NULL == image) return;
	SDL_RenderCopy(renderer, image, NULL, dstrect);
	SDL_RenderPresent(renderer);
}

/* Enleve le carre du choix d'action du joueur */ 
void choix(SDL_Renderer *renderer, SDL_Rect *dstrect, int n){
	SDL_Texture *image = NULL;
	if(n==1) image = loadImage("sdl/images/Choix1.bmp", renderer);
	if(n==2) image = loadImage("sdl/images/Choix2.bmp", renderer);
	if(n==3) image = loadImage("sdl/images/Choix3.bmp", renderer);
	if(n==4) image = loadImage("sdl/images/Choix4.bmp", renderer);
	if(n==5) image = loadImage("sdl/images/Choix5.bmp", renderer);
	
    if(NULL == image) return;
	SDL_RenderCopy(renderer, image, NULL, dstrect);
	SDL_RenderPresent(renderer);
}

/* Affiche le carré d'action du joueur */ 
void action(SDL_Renderer *renderer, SDL_Rect *dstrect, int n){
	SDL_Texture *image = NULL;
	if(n==1) image = loadPNG("sdl/images/Action1.png", renderer);
	if(n==2) image = loadPNG("sdl/images/Action2.png", renderer);
	
    if(NULL == image) return;
	SDL_RenderCopy(renderer, image, NULL, dstrect);
	SDL_RenderPresent(renderer);
}

/* Affiche l'ecran de choix de depart du joueur */ 
void reste_part(SDL_Renderer *renderer, char txt[]){
	SDL_Rect rect = {140, 235, 1000, 250};
	SDL_Texture *image = NULL;
	image = loadPNG(txt, renderer);
	
    if(NULL == image) return;
	SDL_RenderCopy(renderer, image, NULL, &rect);
	SDL_RenderPresent(renderer);
}



