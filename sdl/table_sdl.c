#include "table_sdl.h"

/* Initialise la structure de la table */
TABLE* init_table(){
    TABLE * table;
    table = (TABLE *) malloc(sizeof(TABLE));
    table->nb_joueurs=0;
    table->tete=NULL;
    table->pioche=NULL;
    return table;
}

int table_est_pleine(TABLE* t){
    if(t->nb_joueurs==MAX_JOUEURS) return 1;
    return 0;
}

int table_est_vide(TABLE* t){
    if(t->nb_joueurs==0) return 1;
    return 0;
}

void assigner_pioche(TABLE *t, PIOCHE *p){
    t->pioche=p;
}


int saisie_joueurs_dans_table(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer, TABLE* table){
    
    /* initialisation des joueurs dans la table */
    JOUEUR* j,*j_suiv;
    table->tete=saisie_joueur_sdl(window, image, renderer, 1, table);
    if(table->tete==NULL) return EXIT_SUCCESS;
    j=table->tete;
    for (int i=2;i<=table->nb_joueurs;i++){
        j_suiv=saisie_joueur_sdl(window, image, renderer, i, table);
        if(j_suiv==NULL) return EXIT_SUCCESS;
        j->suivant=j_suiv;
        j=j_suiv;
    }
    CROUPIER *c;
    c = init_croupier();
    table->croupier = c;
    return 1;
}

/* Fonction permettant de gerer l'affichage de l'ajout des joueurs ainsi que leur mise et l'ajout des informations dans les structures */
JOUEUR* saisie_joueur_sdl(SDL_Window *window, SDL_Texture *image, SDL_Renderer* renderer, int num, TABLE* table){
	JOUEUR * j;
    j=(JOUEUR *) malloc(sizeof(JOUEUR));
	
	char tab_nom[10] = "";
	char tab_capital[6] = "";
	SDL_Rect RectTexte = {360, 325, 0, 0};
	
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
	afficher_vierge(renderer);
	SDL_Event event;
	SDL_Color TextColor = {255,255,255};
		
	SDL_Rect rect = {100, 275, 0, 0};
	SDL_Delay(20);
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "Entrez le nom du joueur ", rect, 0);
		SDL_Delay(20);
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, num, rect, 370);
		SDL_Delay(20);
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "(entrer pour valider) :", rect, 400);

	/* Boucle pour afficher les lettres tap??es au clavier */ 
	while(continuer){
			if ( SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_WINDOWEVENT: // ??v??nement de la fen??tre
						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ){
							liberer_table(table);
							quitter(window, image, renderer);
							return NULL;
						}
						break;
					case SDL_KEYDOWN: // ??v??nement de rel??chement d'une touche clavier
						switch(event.key.keysym.sym){
							case SDLK_RETURN :
								continuer = 0;
							break;
							case SDLK_a :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "a", RectTexte, 0);
								strcat(tab_nom, "a");
								RectTexte.x+=35;
							break;
							case SDLK_b :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "b", RectTexte, 0);
								strcat(tab_nom, "b");
								RectTexte.x+=35;
							break;
							case SDLK_c :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "c", RectTexte, 0);
								strcat(tab_nom, "c");
								RectTexte.x+=35;
							break;
							case SDLK_d :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "d", RectTexte, 0);
								strcat(tab_nom, "d");
								RectTexte.x+=35;
							break;
							case SDLK_e :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "e", RectTexte, 0);
								strcat(tab_nom, "e");
								RectTexte.x+=35;
							break;
							case SDLK_f :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "f", RectTexte, 0);
								strcat(tab_nom, "f");
								RectTexte.x+=30;
							break;
							case SDLK_g :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "g", RectTexte, 0);
								strcat(tab_nom, "g");
								RectTexte.x+=35;
							break;
							case SDLK_h :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "h", RectTexte, 0);
								strcat(tab_nom, "h");
								RectTexte.x+=35;
							break;
							case SDLK_i :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "i", RectTexte, 0);
								strcat(tab_nom, "i");
								RectTexte.x+=25;
							break;
							case SDLK_j :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "j", RectTexte, 0);
								strcat(tab_nom, "j");
								RectTexte.x+=25;
							break;
							case SDLK_k :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "k", RectTexte, 0);
								strcat(tab_nom, "k");
								RectTexte.x+=35;
							break;
							case SDLK_l :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "l", RectTexte, 0);
								strcat(tab_nom, "l");
								RectTexte.x+=25;
							break;
							case SDLK_m :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "m", RectTexte, 0);
								strcat(tab_nom, "m");
								RectTexte.x+=45;
							break;
							case SDLK_n :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "n", RectTexte, 0);
								strcat(tab_nom, "n");
								RectTexte.x+=35;
							break;
							case SDLK_o :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "o", RectTexte, 0);
								strcat(tab_nom, "o");
								RectTexte.x+=35;
							break;
							case SDLK_p :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "p", RectTexte, 0);
								strcat(tab_nom, "p");
								RectTexte.x+=35;
							break;
							case SDLK_q :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "q", RectTexte, 0);
								strcat(tab_nom, "q");
								RectTexte.x+=35;
							break;
							case SDLK_r :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "r", RectTexte, 0);
								strcat(tab_nom, "r");
								RectTexte.x+=30;
							break;
							case SDLK_s :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "s", RectTexte, 0);
								strcat(tab_nom, "s");
								RectTexte.x+=35;
							break;
							case SDLK_t :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "t", RectTexte, 0);
								strcat(tab_nom, "t");
								RectTexte.x+=30;
							break;
							case SDLK_u :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "u", RectTexte, 0);
								strcat(tab_nom, "u");
								RectTexte.x+=35;
							break;
							case SDLK_v :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "v", RectTexte, 0);
								strcat(tab_nom, "v");
								RectTexte.x+=35;
							break;
							case SDLK_w :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "w", RectTexte, 0);
								strcat(tab_nom, "w");
								RectTexte.x+=35;
							break;
							case SDLK_x :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "x", RectTexte, 0);
								strcat(tab_nom, "x");
								RectTexte.x+=35;
							break;
							case SDLK_y :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "y", RectTexte, 0);
								strcat(tab_nom, "y");
								RectTexte.x+=35;
							break;
							case SDLK_z :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "z", RectTexte, 0);
								strcat(tab_nom, "z");
								RectTexte.x+=35;
							break;
						}
						break;
			}
		}
	}
	strcpy(j->nom, tab_nom);
	
	rect.y = 400;
	RectTexte.y = 450;
	RectTexte.x = 360;
	SDL_Delay(20);
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "Entrez le capital du joueur ", rect, 0);
	SDL_Delay(20);
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, num, rect, 405);
	SDL_Delay(20);
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "(entrer pour valider) :", rect, 435);
	SDL_Delay(20);
	
	continuer = 1;

	/* Boucle pour afficher les lettres tap??es au clavier */ 
	while(continuer){
			if ( SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_WINDOWEVENT: // ??v??nement de la fen??tre
						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ){
							liberer_table(table);
							quitter(window, image, renderer);
							return NULL;
						}
						break;
					case SDL_KEYDOWN: // ??v??nement de rel??chement d'une touche clavier
						switch(event.key.keysym.sym){
							case SDLK_RETURN :
								continuer = 0;
							break;
							case SDLK_1 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "1", RectTexte, 0);
								strcat(tab_capital, "1");
								RectTexte.x+=30;
							break;
							case SDLK_2 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "2", RectTexte, 0);
								strcat(tab_capital, "2");
								RectTexte.x+=30;
							break;
							case SDLK_3 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "3", RectTexte, 0);
								strcat(tab_capital, "3");
								RectTexte.x+=30;
							break;
							case SDLK_4 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "4", RectTexte, 0);
								strcat(tab_capital, "4");
								RectTexte.x+=30;
							break;
							case SDLK_5 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "5", RectTexte, 0);
								strcat(tab_capital, "5");
								RectTexte.x+=30;
							break;
							case SDLK_6 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "6", RectTexte, 0);
								strcat(tab_capital, "6");
								RectTexte.x+=30;
							break;
							case SDLK_7 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "7", RectTexte, 0);
								strcat(tab_capital, "7");
								RectTexte.x+=30;
							break;
							case SDLK_8 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "8", RectTexte, 0);
								strcat(tab_capital, "8");
								RectTexte.x+=30;
							break;
							case SDLK_9 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "9", RectTexte, 0);
								strcat(tab_capital, "9");
								RectTexte.x+=30;
							break;
							case SDLK_0 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "0", RectTexte, 0);
								strcat(tab_capital, "0");
								RectTexte.x+=30;
							break;
						}
						break;
			}
		}
	}
	j->capital = atoi(tab_capital);
	return j;
}



/* Fonction permettant de gerer l'affichage de l'ajout des joueurs ainsi que leur mise et l'ajout des informations dans les structures en partie */
int saisie_joueurs_en_partie(SDL_Window *window, SDL_Texture *image, TABLE *table, SDL_Renderer *renderer){
    int nb,i,cpt, continuer = 1, saisie;
    SDL_Rect joueur = {160,340,0,0};
    SDL_Rect RectTexte = {900, 340, 0, 0};
    SDL_Event event;
    SDL_Color TextColor = {255,255,255};
    nb = 5 - table->nb_joueurs;
    char txt[] = "Combien de joueur voulez-vous ajouter ? ";
    char plus[] = { '(', 'm', 'a', 'x', ' ', nb+'0', ')', '\0' };
    strcat(txt, plus);
    saisie = nb;
    
    /* initialisation du nombre de joueurs dans la table */
    
    SDL_Delay(20);
	reste_part(renderer, "sdl/images/Ajout_joueur.png");
	SDL_Delay(20);
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, txt, joueur, 0);
	SDL_Delay(20);
    
   	while(continuer){
			if ( SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_WINDOWEVENT: // ??v??nement de la fen??tre
						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ){
							liberer_table(table);
							quitter(window, image, renderer);
							return EXIT_SUCCESS;
						}
						break;
					case SDL_KEYDOWN: // ??v??nement de rel??chement d'une touche clavier
						switch(event.key.keysym.sym){
							case SDLK_RETURN :
								continuer = 0;
							break;
							case SDLK_1 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "1", RectTexte, 0);
								saisie = 1;
								RectTexte.x+=60;
							break;
							case SDLK_2 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "2", RectTexte, 0);
								saisie = 2;
								RectTexte.x+=60;
							break;
							case SDLK_3 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "3", RectTexte, 0);
								saisie = 3;
								RectTexte.x+=60;
							break;
							case SDLK_4 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "4", RectTexte, 0);
								saisie = 4;
								RectTexte.x+=60;
							break;
							case SDLK_5 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "5", RectTexte, 0);
								saisie = 5;
								RectTexte.x+=60;
							break;
							case SDLK_0 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "0", RectTexte, 0);
								saisie = 0;
								RectTexte.x+=60;
							break;
						}
						break;
				}
			}
			if(saisie>nb) {
				afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "INCORRECT", RectTexte, 0);
				continuer = 1;
				SDL_Delay(500);
				reste_part(renderer, "sdl/images/Ajout_joueur.png");
				SDL_Delay(20);
				afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, txt, joueur, 0);
				SDL_Delay(20);
			}
	}
	SDL_Delay(20);

    /* initialisation des joueurs dans la table */
    JOUEUR* j,*j_suiv;
    i = table->nb_joueurs+1;
    //printf("\n---------- Saisie des joueurs dans la table ----------\n");
    if(table->nb_joueurs == 0){
        j=saisie_joueur_sdl(window, image, renderer, i, table);
        table->tete=j;
        cpt = saisie;
    }
    else{
        j = table->tete;
        while(j->suivant != NULL){
            j = j->suivant;
        }
        cpt = table->nb_joueurs+1;
    }
    for (i=cpt;i<cpt+saisie;i++){
        j_suiv=saisie_joueur_sdl(window, image, renderer, i, table);
        j->suivant=j_suiv;
        j=j_suiv;
    }
    table->nb_joueurs += saisie;
    return 1;
}




void tirage_debut_partie(SDL_Renderer *renderer, TABLE *t, SDL_Rect emp_j, SDL_Rect emp_c){
    JOUEUR *j;
    j=t->tete;
    int offset = 0;
    while(j!=NULL){
        if(j->en_jeu) tirage_carte_joueur_debut(renderer,t->pioche,j, emp_j, offset);
        j=j->suivant;
        offset+=248;
    }
    tirage_carte_croupier_debut(renderer,t->pioche,t->croupier, emp_c);
}

void tirage_carte_joueur_mises(SDL_Renderer *renderer,TABLE *t,JOUEUR *j, SDL_Rect emp, int offset){
    /* permet au joueur de tirer des cartes pendant les mises */
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(t->pioche);
    afficher_carte(StructToChaine(carte_tiree), renderer, &emp, offset, offset);
    SDL_Delay(500);
    j->tab_cartes[j->nb_cartes] = *carte_tiree;
    j->nb_cartes++;
}


void tirage_carte_joueur_split1(SDL_Renderer *renderer,TABLE *t,JOUEUR *j, SDL_Rect emp, int offset){
    /* permet au joueur de tirer des cartes pendant les mises */
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(t->pioche);
    afficher_carte(StructToChaine(carte_tiree), renderer, &emp, 0, offset);
    SDL_Delay(500);
    j->tab_cartes[j->nb_cartes] = *carte_tiree;
    j->nb_cartes++;
}



void tirage_carte_joueur_split2(SDL_Renderer *renderer,TABLE *t,JOUEUR *j, SDL_Rect emp, int offset){
    /* permet au joueur de tirer des cartes pendant les mises */
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(t->pioche);
    afficher_carte(StructToChaine(carte_tiree), renderer, &emp, 0, offset);
    SDL_Delay(500);
    /*tableau carte de split*/
    j->tab_cartes_split[j->nb_cartes_split] = *carte_tiree;
    j->nb_cartes_split++;
}


void tirage_carte_croupier_apres_mises(SDL_Renderer *renderer,TABLE *t, SDL_Rect emp, int offset){
    /* permet au croupier de tirer des cartes jusqu'a avoir un score superieur a 16 */
    CROUPIER *c = t->croupier;
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(t->pioche);
    afficher_carte(StructToChaine(carte_tiree), renderer, &emp, offset, 0);
    SDL_Delay(500);
    c->tab_cartes[c->nb_cartes] = *carte_tiree;
    c->nb_cartes++;
}


int demande_mises(SDL_Window *window, SDL_Texture *image, SDL_Renderer* renderer, TABLE* t){
	JOUEUR *j;
	char tab_mise[6];
	int num=1;
	int mise;
	int continuer;
	SDL_Rect RectTexte = {360, 325, 0, 0};
	SDL_Rect rect = {100, 275, 0, 0};
	SDL_Event event;
	SDL_Color TextColor = {255,255,255};
	if (table_est_vide(t)==1) return 1;
    j=t->tete;
    while(j!=NULL){
    	strcpy(tab_mise, "");
    	continuer = 1;
    	SDL_Delay(20);
    	afficher_vierge(renderer);
    	SDL_Delay(20);
		afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "Entrez la mise du joueur ", rect, 0);
		SDL_Delay(20);
		afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, num, rect, 370);
		SDL_Delay(20);
		afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "(entrer pour valider) :", rect, 400);
		SDL_Delay(20);

        while(continuer){
			if ( SDL_PollEvent(&event) )
			{
				switch(event.type)
				{
					case SDL_WINDOWEVENT: // ??v??nement de la fen??tre
						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ){
							liberer_table(t);
							quitter(window, image, renderer);
							return EXIT_SUCCESS;
						}
						break;
					case SDL_KEYDOWN: // ??v??nement de rel??chement d'une touche clavier
						switch(event.key.keysym.sym){
							case SDLK_RETURN :
								continuer = 0;
							break;
							case SDLK_1 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "1", RectTexte, 0);
								strcat(tab_mise, "1");
								RectTexte.x+=30;
							break;
							case SDLK_2 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "2", RectTexte, 0);
								strcat(tab_mise, "2");
								RectTexte.x+=30;
							break;
							case SDLK_3 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "3", RectTexte, 0);
								strcat(tab_mise, "3");
								RectTexte.x+=30;
							break;
							case SDLK_4 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "4", RectTexte, 0);
								strcat(tab_mise, "4");
								RectTexte.x+=30;
							break;
							case SDLK_5 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "5", RectTexte, 0);
								strcat(tab_mise, "5");
								RectTexte.x+=30;
							break;
							case SDLK_6 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "6", RectTexte, 0);
								strcat(tab_mise, "6");
								RectTexte.x+=30;
							break;
							case SDLK_7 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "7", RectTexte, 0);
								strcat(tab_mise, "7");
								RectTexte.x+=30;
							break;
							case SDLK_8 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "8", RectTexte, 0);
								strcat(tab_mise, "8");
								RectTexte.x+=30;
							break;
							case SDLK_9 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "9", RectTexte, 0);
								strcat(tab_mise, "9");
								RectTexte.x+=30;
							break;
							case SDLK_0 :
								afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "0", RectTexte, 0);
								strcat(tab_mise, "0");
								RectTexte.x+=30;
							break;
						}
						break;
				}
			}
		}
		mise = atoi(tab_mise);
		if(mise>j->capital){
			SDL_Delay(20);
			afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 50, TextColor, "INCORRECT", RectTexte, 100);
			SDL_Delay(500);
		}
		else {
			if(mise == 0) j->en_jeu = 0;
			else j->en_jeu = 1;
			j->mise = mise;
			j->capital -= mise;
			j=j->suivant;
			num++;
		}
		RectTexte.x = 360;
	}
	return 1;
}

/* GEstion des actions des clics des actions des joueurs */
int gestion_action(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer, TABLE *t, int offset, int cas, JOUEUR* joueur){
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	int tirage;
	while(!quit){
		if (SDL_PollEvent(&event)){
			switch(event.type)
			{	
				case SDL_WINDOWEVENT: // ??v??nement de la fen??tre
						if ( event.window.event == SDL_WINDOWEVENT_CLOSE ){
							liberer_table(t);
							quitter(window, image, renderer);
							return EXIT_SUCCESS;
						}
						break;
				case SDL_MOUSEBUTTONDOWN : //Evenement de la souris
					if ((event.button.y>645) && (event.button.y<681) && (event.button.x>33 + offset) && (event.button.x<143 + offset)) {
						tirage = 4;
						quit = SDL_TRUE;
					}
					else
					if ((event.button.y>645) && (event.button.y<681) && (event.button.x>145 + offset) && (event.button.x<256 + offset) && (cas == 2) && (joueur->capital >= 2*joueur->mise)) {
						tirage = 3;
						quit = SDL_TRUE;
					}
					else
					if ((event.button.y>684) && (event.button.y<720) && (event.button.x>33 + offset) && (event.button.x<143 + offset)) {
						tirage = 1;
						quit = SDL_TRUE;
					}
					else
					if ((event.button.y>684) && (event.button.y<720) && (event.button.x>145 + offset) && (event.button.x<256 + offset) && (joueur->capital >= 2*joueur->mise)) {
						tirage = 2;
						quit = SDL_TRUE;
					}
					break;
			}
		}
	}
	return tirage;
}

/* Gere le split des joueurs */
int jeu_split(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer, TABLE *t, JOUEUR *j, int offset, SDL_Rect choix_emp, SDL_Rect mise_emp, int i){
	SDL_Rect carte1 = {48+offset, 425, 71, 96};
	SDL_Rect carte2 = {159+offset, 425, 71, 96};
	int tirage;
	int offset_cartes=0;
	choix(renderer, &choix_emp, i);
	action(renderer, &choix_emp, 1);
	while(tirage!=4 && tirage!=2 && j->score<21){
		tirage = gestion_action(window, image, renderer, t, offset, 1, j);
		if(tirage==EXIT_SUCCESS) return EXIT_SUCCESS;
		switch(tirage){
			case 4 :
				choix(renderer, &choix_emp, i);
				afficher_mise_split(j, renderer, t, mise_emp, offset);
				SDL_Delay(200);
				break;
			case 1 : 
				tirage_carte_joueur_split1(renderer,t,j,carte1,offset_cartes); 
				SDL_Delay(20);
				offset_cartes+=15;
				break;
			case 2 : 
				joueur_double(j,t); 
				tirage_carte_joueur_split1(renderer,t,j,carte1,offset_cartes);
				SDL_Delay(20);
				break;
		}
		j->score = comptage_score_joueur(j);
	}
	offset_cartes = 0;
	tirage = 1;
	SDL_Delay(20);
	choix(renderer, &choix_emp, i);
	SDL_Delay(20);
	action(renderer, &choix_emp, 1);
	SDL_Delay(20);
	while(tirage!=4 && tirage!=2 && j->score_split<21){
		tirage = gestion_action(window, image, renderer, t, offset, 1, j);
		if(tirage==EXIT_SUCCESS) return EXIT_SUCCESS;
		switch(tirage){
			case 4 : 
				choix(renderer, &choix_emp, i);
				afficher_mise_split(j, renderer, t, mise_emp, offset);
				SDL_Delay(200);
				break;
			case 1 : 
				tirage_carte_joueur_split2(renderer,t,j,carte2,offset_cartes); 
				SDL_Delay(20);
				offset_cartes+=15;
				break;
			case 2 : 
				joueur_double(j,t); 
				tirage_carte_joueur_split2(renderer,t,j,carte2,offset_cartes);
				SDL_Delay(20);
				break;
		}
		j->score_split = comptage_score_split_joueur(j);
	}
	return 1;
}



int comptage_score_croupier(CROUPIER *c){
    /*permet de compter le score du croupier */
    int res;
    res = compter_score(c->tab_cartes,c->nb_cartes);
    return res;
}

int comptage_score_joueur(JOUEUR* j){
    /*permet de compter le score d'un joueur */
    int res;
    res = compter_score(j->tab_cartes,j->nb_cartes);
    return res;
}

int comptage_score_split_joueur(JOUEUR* j){
    /*permet de compter le score_split d'un joueur */
    int res;
    res = compter_score(j->tab_cartes_split,j->nb_cartes_split);
    return res;
}

int compter_score(CARTE* tab_cartes, int nb_cartes){
	int score = 0;
	int nb_as = 0;
	for(int i=0; i<nb_cartes; i++){
		if(tab_cartes[i].num>1 && tab_cartes[i].num<=10){
			score += tab_cartes[i].num;
		}
		else{
            if(tab_cartes[i].num>10 && tab_cartes[i].num<=13){
                score += 10;
            }
            else nb_as++;
		}
	}
	for(int j=0; j<nb_as; j++){
		if(score<11) score+=11;
		else score+=1;
	}
	return score;
}

/* Affiche la victoire et les defaites et r??partie les gains */ 
void repartition_gains(SDL_Renderer* renderer, TABLE *t){
    JOUEUR *j;
    SDL_Rect rect_texte = {100, 665, 0, 0};
    SDL_Rect rect_texte_split = {100, 690, 0, 0};
    SDL_Color TextColor = {255, 255, 255};
    j=t->tete;
    while(j!=NULL){
        if(j->en_jeu){
            if(j->score > 21){
            	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "PERDU", rect_texte, 0);
            }
            else if((joueur_a_blackjack(j) && croupier_a_blackjack(t->croupier)) || (j->score == t->croupier->score)){
                j->capital += j->mise;
                afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "EGALITE", rect_texte, 0);
            }
            else if(joueur_a_blackjack(j)){
            	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "BLACKJACK !", rect_texte, 0);
                j->capital += (j->mise*2.5);
            }
            else if(j->score > t->croupier->score || t->croupier->score >21){
                j->capital += (j->mise*2);
                afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "GAGNE", rect_texte, 0);
            }
            else {
            	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "PERDU", rect_texte, 0);
            }
            if(j->split){
                if(j->score_split > 21) afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "PERDU", rect_texte_split, 0);
                else if(j->score_split == t->croupier->score){
                    j->capital += j->mise_split;
                    afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "EGALITE", rect_texte_split, 0);
                }
                else if(j->score_split > t->croupier->score || t->croupier->score >21){
                    j->capital += (j->mise_split*2);
                    afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "GAGNE", rect_texte_split, 0);
                }
                else {
                	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, "PERDU", rect_texte_split, 0);
                }
            }
        }
        j->score = 0;
        j->mise=0;
		j->nb_cartes=0;
		j->split=0;
		j->mise_split=0;
		j->nb_cartes_split=0;
		j->score_split=0;
        j=j->suivant;
        rect_texte.x += 248;
        rect_texte_split.x+=248;
    }

}

/* Gere la possibilit?? d'ajout et de retrait d'un joueur en fin de partie */
int reste_sur_table(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer, TABLE *t){
	JOUEUR *j, *j_suiv;
	int statut;
	//SDL_Rect fond = {140, 235, 1000, 250};
    SDL_Rect joueur = {200,340,0,0};
    SDL_Event event;
	SDL_Color TextColor = {255,255,255};
    char txt[40];
    if (table_est_vide(t)==1) printf("La table est vide");
    else{
        j=t->tete;
        while(j!=NULL){
        	statut = 2;
        	SDL_Delay(20);
        	reste_part(renderer, "sdl/images/Reste_part.png");
        	SDL_Delay(20);
            strcpy(txt,j->nom);
            strcat(txt, " ? ");
            afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 40, TextColor, txt, joueur, 0);
            while(statut == 2){
				if (SDL_PollEvent(&event))
				{
					switch(event.type)
					{
						case SDL_WINDOWEVENT: // ??v??nement de la fen??tre
							if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // Fermeture de la fen??tre
							{
								liberer_table(t);
								return quitter(window, image, renderer);
							}
							break;
						case SDL_MOUSEBUTTONDOWN : //Evenement de la souris
							if(event.button.x>705 && event.button.x<885 && event.button.y>310 && event.button.y<410) statut = 1;
							else if(event.button.x>890 && event.button.x<1070 && event.button.y>310 && event.button.y<410) statut = 0;
							break;
					}
                }
            }
            if(statut){
                j->split=0;
                j->en_jeu = 1;
                j=j->suivant;
            }
            else {
            	j_suiv = j->suivant;
            	sortie_joueur_table(j,t);
            	j = j_suiv;
            }
        }
    }
    return 1;
}

/* Gere la sortie de table d'un joueur */
void sortie_joueur_table(JOUEUR *j,TABLE *t){
    JOUEUR *j_cour,*j_ancien;
    if(j==t->tete){
        t->tete=j->suivant;
        t->nb_joueurs--;
        return;
    }
    j_cour=t->tete;
    j_ancien=j_cour;
    while(j_cour!=NULL && j->nom!=j_cour->nom){
        j_ancien=j_cour;
        j_cour=j_cour->suivant;
    }
    if (j_cour==NULL){
        printf("Impossible de supprimer ce joueur : il n'est pas sur la table\n");
        return;
    }
    j_ancien->suivant=j_cour->suivant;
    t->nb_joueurs--;
    liberer_joueur(j);
}

void joueur_double(JOUEUR *j, TABLE *t){
    j->capital -= j->mise;
    j->mise *= 2;
}


/* Affiche le nom et le capital des joueurs */
void afficher_nom_capital(SDL_Renderer *renderer, TABLE *table, SDL_Rect nomj_emp, SDL_Rect capital_emp){
	JOUEUR * j;
	j=table->tete;
	int offset = 0;
	SDL_Color TextColor = {255,255,255};
	while(j!=NULL){
		SDL_Delay(20);
		afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, j->nom, nomj_emp, offset);
		SDL_Delay(20);
		afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "$", capital_emp, offset);
		SDL_Delay(20);
		afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, j->capital, capital_emp, offset+20);
		SDL_Delay(20);
		j=j->suivant;
		offset+=248;
	}
}

void afficher_mise(SDL_Renderer *renderer, TABLE *table, SDL_Rect mise_emp){
	JOUEUR * j;
	j=table->tete;
	int offset = 0;
	SDL_Color TextColor = {255,255,255};
	while(j!=NULL){
		SDL_Delay(20);
		afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "$", mise_emp, offset);
		SDL_Delay(20);
		afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, j->mise, mise_emp, offset+20);
		SDL_Delay(20);
		j=j->suivant;
		offset+=248;
	}
}

void afficher_cartes_split(SDL_Renderer *renderer, JOUEUR * j, int offset){
	SDL_Rect carte1 = {48+offset, 410, 71, 96};
	SDL_Rect carte2 = {159+offset, 410, 71, 96};
	afficher_carte(StructToChaine(&j->tab_cartes[0]), renderer, &carte1, 0, 0);
	afficher_carte(StructToChaine(&j->tab_cartes[1]), renderer, &carte2, 0, 0);
}

void afficher_score(SDL_Renderer *renderer, JOUEUR * j, int offset){
	SDL_Color TextColor = {255,255,255};
	SDL_Rect score = {220+offset, 360, 71, 96};
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, j->score, score, 0);
}

void afficher_score_split(SDL_Renderer *renderer, JOUEUR * j, int offset){
	SDL_Color TextColor = {255,255,255};
	SDL_Rect score1 = {170+offset, 360, 71, 96};
	SDL_Rect score2 = {220+offset, 360, 71, 96};
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, j->score, score1, 0);
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 20, TextColor, j->score_split, score2, 0);
}

void afficher_score_croupier(SDL_Renderer *renderer, CROUPIER *c){
	SDL_Color TextColor = {255,255,255};
	SDL_Rect score = {340, 140, 71, 96};
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 25, TextColor, c->score, score, 0);
}

void afficher_blackjack(SDL_Renderer *renderer, JOUEUR * j, int offset){
	SDL_Color TextColor = {255,255,255};
	SDL_Rect blackjack = {80+offset, 355, 71, 96};
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "BLACKJACK", blackjack, 0);
}


void afficher_mise_split(JOUEUR *j, SDL_Renderer *renderer, TABLE *table, SDL_Rect mise_emp, int offset){
	SDL_Color TextColor = {255,255,255};
	SDL_Delay(20);
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "$", mise_emp, offset);
	SDL_Delay(20);
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, j->mise, mise_emp, offset+20);
	SDL_Delay(20);
	afficher_texte(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, "$", mise_emp, offset+150);
	SDL_Delay(20);
	afficher_entier(renderer, "sdl/police/BOOKMANL.ttf", 30, TextColor, j->mise, mise_emp, offset+170);
	SDL_Delay(20);
}

void liberer_table(TABLE *t){
	int cpt_j = 0;
	int flag = 0;
	printf("Liberation de ");
	if(t->tete!=NULL){
		JOUEUR *j = t->tete;
		JOUEUR *j_suiv = t->tete->suivant;
		liberer_joueur(j);
		cpt_j++;
		flag = 1;
		while(j_suiv!=NULL){
			j=j_suiv;
			liberer_joueur(j);
			cpt_j++;
			j_suiv = j_suiv->suivant;
		}
		printf("%d joueur(s)", cpt_j);
	}
	if(t->croupier!=NULL){
		liberer_croupier(t->croupier);
		printf(", du croupier");
	}
	if(t->pioche!=NULL){
		liberer_pioche(t->pioche);
		printf(", de la pioche ");
	}
	free(t);
	if(!flag) printf("la table OK !\n");
	else printf("et de la table OK !\n");
}







