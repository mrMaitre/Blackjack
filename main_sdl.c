#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "table.h"
#include "fonction_sdl.h"
#include <SDL2/SDL_ttf.h>

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
void afficher_carte(const char nom_fichier[], SDL_Renderer *renderer, SDL_Rect *dstrect, int x_offset, int y_offset);
void reinitialiser_plateau(SDL_Renderer *renderer);
void saisie_des_joueurs(SDL_Renderer *renderer);
void afficher_menu();
void afficher_texte(SDL_Renderer *renderer, char police[], int taille_police, SDL_Color TextColor, char texte[], SDL_Rect DstRect);
void remp_carte(SDL_Renderer *renderer, SDL_Rect *dstrect, int n);

int main(int argc, char **argv)
{
    if(init(&window, &renderer, 1280, 720) != 0 ) quitter();

    statut = EXIT_SUCCESS;
    
    int nb_joueur = 0;
    
    time_t heure;
    srand((unsigned int) time(&heure));
    TABLE* table;
    PIOCHE* pioche;
    JOUEUR *j;
    int tirage = 1,choix;
    table = init_table();

    
Menu:    
	afficher_menu(renderer);
    
    while(table->nb_joueurs == 0){	
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT: // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) goto Quit;
				    break;
				case SDL_MOUSEBUTTONDOWN : //Evenement de la souris
					if(event.button.y>420 && event.button.y<470){
						if(event.button.x>190 && event.button.x<240) table->nb_joueurs = 1;
						if(event.button.x>400 && event.button.x<450) table->nb_joueurs = 2;
						if(event.button.x>610 && event.button.x<660) table->nb_joueurs = 3;
						if(event.button.x>830 && event.button.x<880) table->nb_joueurs = 4;
						if(event.button.x>1040 && event.button.x<1090) table->nb_joueurs = 5;
					}
				    break;
			}
		}
	}
	
	SDL_Delay(500);
	
	saisie_des_joueurs(renderer);
	
	SDL_Delay(1000);
	
    reinitialiser_plateau(renderer);
    
    SDL_Delay(20);
    
    /* Test affichage nom, capital et mises joueurs */
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " Joueur1", nomj_emp1);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp1);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp1);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " Joueur2", nomj_emp2);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp2);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp2);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " Joueur3", nomj_emp3);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp3);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp3);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " Joueur4", nomj_emp4);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp4);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp4);
    
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, " Joueur5", nomj_emp5);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "1000 $", capital_emp5);
    afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "20 $", mise_emp5);
    
    demande_mises(table);
	
	while(1){
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT: // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // Fermeture de la fenêtre
				    {
				        quitter();
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
	
