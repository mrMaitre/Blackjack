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
	SDL_Renderer *renderer;
	SDL_Event event;
	int statut = EXIT_FAILURE;

	/* Rectangle avec l'emplacement de la première carte du croupier (x coin supérieur gauche, y coin supérieur gauche, largeur, hauteur) */
	SDL_Rect carte_croup_dos = {380, 180, 71, 96};
	
	/* Rectangle avec l'emplacement du bouton start */
    SDL_Rect start = {40, 40, 150, 160};
    
    /* Rectangle avec l'emplacement du premier rectangle de choix (stand, hit, double ou split)*/
    SDL_Rect choix_emp = {33, 645, 220, 75};
		
	/* Rectangles avec l'emplacement de la première et de la deuxième carte de gauche à droite */
	SDL_Rect carte_emp1 = {48, 410, 71, 96};
	SDL_Rect carte_emp2 = {78, 440, 71, 96};

	/* Rectangles avec l'emplacement du premier nom de joueur (pas besoin de largeur ou hauteur pour du texte) */
	SDL_Rect nomj_emp1 = {48, 320, 0, 0}; 

	/* Rectangles avec l'emplacement du premier capital de joueur */
	SDL_Rect capital_emp1 = {48, 355, 0, 0}; 

	/* Rectangles avec l'emplacement de la première mise de joueur */
	SDL_Rect mise_emp1 = {48, 660, 0, 0}; 

	/* Rectangles avec l'emplacement de la première zone a supprimer pour split */
	SDL_Rect split_emp1 = {44, 410, 200, 160}; 
    
	window = NULL;
    image = NULL;
    renderer = NULL;
    
    if(init(&window, &renderer, 1280, 720) != 0 ) {
    	quitter(window, image, renderer);
		statut = EXIT_SUCCESS;
		return statut;
    }
    time_t heure;
    srand((unsigned int) time(&heure));
    TABLE* table;
    PIOCHE* pioche;
    table = init_table();
    
    if ( SDL_PollEvent(&event) ) //Quitter la sdl si clic sur le bouton fermer la fenetre 
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
			}

    //Debut de la partie : 
    //Ajout des joueurs 
	afficher_menu(renderer);
    
    while(table->nb_joueurs == 0){	
		if ( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT: // Événement de la fenêtre
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) {
				    	liberer_table(table);
				    	return quitter(window, image, renderer);
				    }
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
	
	int statut = saisie_joueurs_dans_table(window, image, renderer, table);
	if(statut == EXIT_SUCCESS) goto exit;
	JOUEUR* t_table = table->tete;
	SDL_Delay(500);
	
	//Debut du jeu 
boucle:
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
				    if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) {
				    	liberer_table(table);
				    	return quitter(window, image, renderer);
				    }
				    break;
				case SDL_MOUSEBUTTONDOWN : //Evenement de la souris
					if(event.button.y>40 && event.button.y<200 && event.button.x>40 && event.button.x<190){
						continuer = 0;
					}
				    break;
			}
		}
	}
    statut = demande_mises(window, image, renderer, table);
    if(statut == EXIT_SUCCESS) goto exit;
    SDL_Delay(20);
    reinitialiser_plateau(renderer);

    afficher_nom_capital(renderer, table, nomj_emp1, capital_emp1);
    afficher_mise(renderer, table, mise_emp1);
    SDL_Delay(1000);
    tirage_debut_partie(renderer, table, carte_emp1, carte_croup_dos);
    SDL_Delay(20);
    
    int i = 1;
    int offset = 0;
    int offset_cartes = 0;
    int tirage = 1;
    JOUEUR *j = t_table;
    int a_split = 0;

	while(j!=NULL){
		if(j->en_jeu){
			j->score = comptage_score_joueur(j);
			while(tirage!=4 && tirage!=2 && j->score<21){
				choix(renderer, &choix_emp, i);
				if(j->nb_cartes==2 && j->capital >= j->mise && j->tab_cartes[0].num == j->tab_cartes[1].num && j->split == 0){
					action(renderer, &choix_emp, 2);
					tirage = gestion_action(window, image, renderer, table, offset, 2, j);
					if(tirage == EXIT_SUCCESS) goto exit;
				}
				else {
					action(renderer, &choix_emp, 1);
					tirage = gestion_action(window, image, renderer, table, offset, 1, j);
					if(tirage == EXIT_SUCCESS) goto exit;
				}
				switch(tirage){
					case 4 :
						tirage = 4;
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
					statut = jeu_split(window, image, renderer, table, j, offset, choix_emp, mise_emp1, i);
					if(statut == EXIT_SUCCESS) goto exit;
					SDL_Delay(20);
					choix(renderer, &choix_emp, i);
					SDL_Delay(20);
					tirage = 4;
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
	SDL_Delay(20);
	table->croupier->score = comptage_score_croupier(table->croupier);
	SDL_Delay(500);
	offset = 162;
	while(table->croupier->score<17){
		tirage_carte_croupier_apres_mises(renderer, table, carte_croup_dos, offset);
		SDL_Delay(20);
		table->croupier->score = comptage_score_croupier(table->croupier);
		SDL_Delay(20);
		offset+=81;
		SDL_Delay(20);
	}
	SDL_Delay(20);
	afficher_score_croupier(renderer, table->croupier);
	SDL_Delay(20);
	repartition_gains(renderer, table);
	SDL_Delay(2000);
	statut = reste_sur_table(window, image, renderer, table);
	if(statut == EXIT_SUCCESS) goto exit;
	SDL_Delay(20);
	statut = saisie_joueurs_en_partie(window, image, table, renderer);
	if(statut == EXIT_SUCCESS) goto exit;
    offset = 0;
    choix_emp.x = 33;
	carte_emp2.x = 78;
	carte_emp1.x = 48;
    carte_emp1.y = 410;
	split_emp1.x = 44;
	free(pioche);
    SDL_Delay(1000);
    goto boucle;
    }

exit:
    return 0;
}
	
