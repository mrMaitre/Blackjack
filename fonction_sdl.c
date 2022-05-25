#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonction_sdl.h"





int quitter(){
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
	image = loadImage("Plateau.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void saisie_des_joueurs(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("saisie_joueur.bmp", renderer);
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

/* Fonction qui affiche le menu du jeu */
void afficher_vierge(SDL_Renderer *renderer){
	SDL_Texture *image = NULL;
	image = loadImage("Vierge.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
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

JOUEUR* saisie_joueur(SDL_Renderer* renderer){
	JOUEUR * j;
    j=(JOUEUR *) malloc(sizeof(JOUEUR));
	
	char tab_nom[10];
	int num_lettre = 0;
	SDL_Rect RectTexte = {360, 425, 0, 0};
	SDL_Event event;
	
	SDL_Color TextColor;
	TextColor.r = 255;
	TextColor.g = 255;
	TextColor.b = 255;
	
	/* Remplir la structure */ 
	j->mise=0;
    j->score = 0;
    j->en_jeu=1;
    j->nb_cartes=0;
    j->split=0;
    j->mise_split=0;
    j->nb_cartes_split=0;
    j->score_split=0;
    j->suivant=NULL;

	int continuer = 1;
	
	/*Affiche le plateau vierge*/
	SDL_Texture *image = NULL;
	image = loadImage("Vierge.bmp", renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
	SDL_RenderPresent(renderer);
		
	SDL_Rect rect = {100, 275, 0, 0};
	afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "Entrez le nom du joueur et son capital (entrez pour valider)", &rect, 0);

	/* Boucle pour afficher les lettres tapées au clavier */ 
	while(continuer){
			if ( SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_WINDOWEVENT: // Événement de la fenêtre
						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) return j;
						break;
					case SDL_KEYDOWN: // Événement de relâchement d'une touche clavier
						if (event.key.keysym.sym == SDLK_RETURN)
						{
							continuer = 0;
						}
						if ( event.key.keysym.sym == SDLK_a){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "a", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "a");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_b){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "b", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "b");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_c){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "c", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "c");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_d){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "d", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "d");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_e){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "e", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "e");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_f){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "f", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "f");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_g){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "g", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "g");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_h){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "h", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "h");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_i){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "i", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "i");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_j){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "j", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "j");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_k){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "k", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "k");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_l){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "l", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "l");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_m){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "m", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "m");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_n){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "n", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "n");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_o){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "o", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "o");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_p){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "p", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "p");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_q){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "q", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "q");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_r){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "r", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "r");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_s){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "s", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "s");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_t){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "t", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "t");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_u){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "u", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "u");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_v){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "v", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "v");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_w){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "w", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "w");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_x){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "x", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "x");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_y){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "y", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "y");
							num_lettre++;
						}
						if ( event.key.keysym.sym == SDLK_z){
							afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "z", &RectTexte, 35);
							strcpy(&tab_nom[num_lettre], "z");
							num_lettre++;
						}
						break;
			}
		}
	}
	strcpy(j->nom, tab_nom);
	return j;
}

