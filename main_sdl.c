#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "table.h"



int main(int argc, char **argv)
{

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
    

	window = NULL;
    image = NULL;
    statut = EXIT_FAILURE;
    renderer = NULL;
    

	/* Couleur du texte ici blanc*/
	TextColor.r = 255;
	TextColor.g = 255;
	TextColor.b = 255;
	
    /* Rectangles avec l'emplacement des cartes du croupier */
    carte_croup_dos.x = 380;
    carte_croup_dos.y = 180;
    carte_croup_dos.w = 71;
    carte_croup_dos.h = 96;
    
    carte_croup_autre.x = 380;
    carte_croup_autre.y = 180;
    carte_croup_autre.w = 71;
    carte_croup_autre.h = 96;
    
    SDL_Rect choix_emp = {33, 645, 220, 75};
    SDL_Rect start = {40, 40, 150, 160};
        
    /* Rectangles avec l'emplacement de la première carte de gauche à droite */
    carte_emp1.x = 48;
    carte_emp1.y = 410;
    carte_emp1.w = 71;
    carte_emp1.h = 96;
    
    carte_emp2.x = 78;
    carte_emp2.y = 440;
    carte_emp2.w = 71;
    carte_emp2.h = 96;
    
    carte_emp3.x = 550;
    carte_emp3.y = 410;
    carte_emp3.w = 71;
    carte_emp3.h = 96;
    
    carte_emp4.x = 806;
    carte_emp4.y = 410;
    carte_emp4.w = 71;
    carte_emp4.h = 96;
    
    carte_emp5.x = 1062;
    carte_emp5.y = 410;
    carte_emp5.w = 71;
    carte_emp5.h = 96;
    
    /* Rectangles avec l'emplacement du nom du joueur de gauche à droite */
    nomj_emp1.x = 48; 
    nomj_emp1.y = 320;
    nomj_emp1.w = 0;
    nomj_emp1.h = 0;
    
    nomj_emp2.x = 304; 
    nomj_emp2.y = 320;
    nomj_emp2.w = 0;
    nomj_emp2.h = 0;
    
    nomj_emp3.x = 560; 
    nomj_emp3.y = 320;
    nomj_emp3.w = 0;
    nomj_emp3.h = 0;
    
    nomj_emp4.x = 816; 
    nomj_emp4.y = 320;
    nomj_emp4.w = 0;
    nomj_emp4.h = 0;
    
    nomj_emp5.x = 1072; 
    nomj_emp5.y = 320;
    nomj_emp5.w = 0;
    nomj_emp5.h = 0;
    
    
    /* Rectangles avec l'emplacement du capital du joueur de gauche à droite */
    capital_emp1.x = 48; 
    capital_emp1.y = 355;
    capital_emp1.w = 0;
    capital_emp1.h = 0;
    
    capital_emp2.x = 304; 
    capital_emp2.y = 345;
    capital_emp2.w = 0;
    capital_emp2.h = 0;
    
    capital_emp3.x = 560; 
    capital_emp3.y = 345;
    capital_emp3.w = 0;
    capital_emp3.h = 0;
    
    capital_emp4.x = 816; 
    capital_emp4.y = 345;
    capital_emp4.w = 0;
    capital_emp4.h = 0;
    
    capital_emp5.x = 1072; 
    capital_emp5.y = 345;
    capital_emp5.w = 0;
    capital_emp5.h = 0;
    
    
    /* Rectangles avec l'emplacement de la mise du joueur de gauche à droite */
    mise_emp1.x = 48; 
    mise_emp1.y = 660;
    mise_emp1.w = 0;
    mise_emp1.h = 0;
    
    mise_emp2.x = 304; 
    mise_emp2.y = 660;
    mise_emp2.w = 0;
    mise_emp2.h = 0;
    
    mise_emp3.x = 560; 
    mise_emp3.y = 660;
    mise_emp3.w = 0;
    mise_emp3.h = 0;
    
    mise_emp4.x = 816; 
    mise_emp4.y = 660;
    mise_emp4.w = 0;
    mise_emp4.h = 0;
    
    mise_emp5.x = 1072; 
    mise_emp5.y = 660;
    mise_emp5.w = 0;
    mise_emp5.h = 0;
    
    
    /* Rectangles avec l'emplacement de la zone a supprimer pour split */
    split_emp1.x = 44; 
    split_emp1.y = 410;
    split_emp1.w = 200;
    split_emp1.h = 160;
    
    split_emp2.x = 292; 
    split_emp2.y = 410;
    split_emp2.w = 200;
    split_emp2.h = 160;
    
    split_emp3.x = 540; 
    split_emp3.y = 410;
    split_emp3.w = 200;
    split_emp3.h = 160;
    
    split_emp4.x = 788; 
    split_emp4.y = 410;
    split_emp4.w = 200;
    split_emp4.h = 160;
    
    split_emp5.x = 1036; 
    split_emp5.y = 410;
    split_emp5.w = 200;
    split_emp5.h = 160;
    
    
    /*Rectangle écriture mise*/
    mise.x = 500;
    mise.y = 400;
    mise.w = 0;
    mise.h = 0;
    
    
    if(init(&window, &renderer, 1280, 720) != 0 ) quitter(window, image, renderer);

    statut = EXIT_SUCCESS;
    
    time_t heure;
    srand((unsigned int) time(&heure));
    TABLE* table;
    PIOCHE* pioche;
    //JOUEUR *j;
    //int tirage = 1,choix;
    table = init_table();

    
Menu:    
	afficher_menu(renderer);
    
    while(table->nb_joueurs == 0){	
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT: // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) quitter(window, image, renderer);
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
	
	saisie_joueurs_dans_table(renderer, table);
	SDL_Delay(500);
    reinitialiser_plateau(renderer);
    afficher_start(renderer, start);
    afficher_nom_capital(renderer, table, nomj_emp1, capital_emp1);
    table->croupier->nb_cartes = 0;
   	pioche = init_pioche();
   	assigner_pioche(table,pioche);
   	SDL_Delay(500);
   	int continuer = 1;
   	while(continuer){	
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT : // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) quitter(window, image, renderer);
				    break;
				case SDL_MOUSEBUTTONDOWN : //Evenement de la souris
					if(event.button.y>40 && event.button.y<200 && event.button.x>40 && event.button.x<190){
						continuer = 0;
					}
				    break;
			}
		}
	}
    demande_mises(renderer,table);
    SDL_Delay(20);
    reinitialiser_plateau(renderer);

    afficher_nom_capital(renderer, table, nomj_emp1, capital_emp1);
    afficher_mise(renderer, table, mise_emp1);
    SDL_Delay(1000);
    tirage_debut_partie(renderer, table, carte_emp1, carte_croup_autre);
    
    int i = 1;
    int offset = 0;
    int offset_cartes = 0;
    int tirage = 1;
    JOUEUR *j = table->tete;
    int a_split = 0;;
	while(j!=NULL){
		if(j->en_jeu){
			j->score = comptage_score_joueur(j);
			if(joueur_a_blackjack(j)) {
				SDL_Delay(20);
				afficher_blackjack(renderer, j, offset);
				SDL_Delay(20);
			}
			while(tirage!=0 && tirage!=2 && j->score<21){
				choix(renderer, &choix_emp, i);
				if(j->nb_cartes==2 && j->capital >= j->mise && j->tab_cartes[0].num == j->tab_cartes[1].num && j->split == 0){
					action(renderer, &choix_emp, 2);
					tirage = gestion_action(renderer, table, offset, 2, j);
				}
				else {
					action(renderer, &choix_emp, 1);
					tirage = gestion_action(renderer, table, offset, 1, j);
					printf("OK");
				}
				switch(tirage){
					case 0 :
						tirage = 0;
						SDL_Delay(20);
						break;
					case 1 : 
						tirage_carte_joueur_mises(renderer,table,j,carte_emp2,offset_cartes); 
						offset_cartes+=15;
						break;
					case 2 : 
						joueur_double(j,table); 
						tirage_carte_joueur_mises(renderer,table,j,carte_emp2,offset_cartes);
						break;
					case 3 : 
						joueur_split(j); 
						SDL_Delay(20);
						remp_carte(renderer, &split_emp1, i);
						SDL_Delay(20);
						afficher_cartes_split(renderer, j, offset);
						SDL_Delay(20);
						a_split = 1;
						break;
				}
				j->score = comptage_score_joueur(j);
				if(tirage==3){
					jeu_split(renderer, table, j, offset, choix_emp, mise_emp1, i);
					choix(renderer, &choix_emp, i);
					tirage = 0;
				}
			}
		}
		if(a_split) afficher_score_split(renderer, j, offset);
		else afficher_score(renderer, j, offset);
		SDL_Delay(20);
		choix(renderer, &choix_emp, i);
		afficher_mise(renderer, table, mise_emp1);
		if(a_split) afficher_mise_split(j, renderer, table, mise_emp1, offset);
		i++;
		choix_emp.x+=248;
		carte_emp2.x+=248;
		split_emp1.x += 248;
		offset+=248;
		tirage = 1;
		offset_cartes = 0;
		j = j->suivant;
		a_split = 0;
	}
	SDL_Delay(2000);
	afficher_carte(table->croupier->tab_cartes[0].nom_image, renderer, &carte_croup_dos, 0, 0);
	table->croupier->score = comptage_score_croupier(table->croupier);
	SDL_Delay(500);
	offset = 162;
	while(table->croupier->score<17){
		tirage_carte_croupier_apres_mises(renderer, table, carte_croup_dos, offset);
		table->croupier->score = comptage_score_croupier(table->croupier);
		offset+=81;
		SDL_Delay(500);
	}
	afficher_score_croupier(renderer, table->croupier);
	repartition_gains(renderer, table);
    
	
	while(1){
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT: // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // Fermeture de la fenêtre
				    {
				    	liberer_table(table);
				        return quitter(window, image, renderer);
				    }
				    break;
				case SDL_KEYDOWN	: // Événement de relâchement d'une touche clavier
				    if ( event.key.keysym.sym == SDLK_ESCAPE ) //Touche Échap
				    {
				        goto Menu;
				    }
				    if ( event.key.keysym.sym == SDLK_a) //Touche a
				    {
						afficher_carte("cartes/3c.bmp", renderer, &carte_emp1, 15, 15);
				    }
				    if ( event.key.keysym.sym == SDLK_e ) //Touche e
				    {
				        afficher_carte("cartes/Dc.bmp", renderer, &carte_emp2, 15, 15);
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
				        afficher_carte("cartes/Ah.bmp", renderer, &carte_croup_autre, 73, 0);
				    }
				    if ( event.key.keysym.sym == SDLK_z) 
				    {
						afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "mange tes morts", nomj_emp1, 0);
				    }
				    if ( event.key.keysym.sym == SDLK_c ) 
				    {
				        reinitialiser_plateau(renderer);
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
}
	
