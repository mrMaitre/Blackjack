#include "table.h"


TABLE* init_table(){
    TABLE * table;
    table = (TABLE *) malloc(sizeof(TABLE));
    table->nb_joueurs=0;
    table->tete=NULL;
    table->pioche=NULL;
    return table;
}

JOUEUR* saisie_joueur_sdl(SDL_Renderer* renderer){
	JOUEUR * j;
    j=(JOUEUR *) malloc(sizeof(JOUEUR));
	
	char tab_nom[10] = "";
	SDL_Rect RectTexte = {360, 425, 0, 0};
	
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
	SDL_Delay(20);
	afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "Entrez le nom du joueur(entrez pour valider)", rect, 0);

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
						switch(event.key.keysym.sym){
							case SDLK_RETURN :
								continuer = 0;
							break;
							case SDLK_a :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "a", RectTexte, 0);
								strcat(tab_nom, "a");
								RectTexte.x+=35;
							break;
							case SDLK_b :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "b", RectTexte, 0);
								strcat(tab_nom, "b");
								RectTexte.x+=35;
							break;
							case SDLK_c :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "c", RectTexte, 0);
								strcat(tab_nom, "c");
								RectTexte.x+=35;
							break;
							case SDLK_d :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "d", RectTexte, 0);
								strcat(tab_nom, "d");
								RectTexte.x+=35;
							break;
							case SDLK_e :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "e", RectTexte, 0);
								strcat(tab_nom, "e");
								RectTexte.x+=35;
							break;
							case SDLK_f :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "f", RectTexte, 0);
								strcat(tab_nom, "f");
								RectTexte.x+=30;
							break;
							case SDLK_g :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "g", RectTexte, 0);
								strcat(tab_nom, "g");
								RectTexte.x+=35;
							break;
							case SDLK_h :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "h", RectTexte, 0);
								strcat(tab_nom, "h");
								RectTexte.x+=35;
							break;
							case SDLK_i :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "i", RectTexte, 0);
								strcat(tab_nom, "i");
								RectTexte.x+=25;
							break;
							case SDLK_j :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "j", RectTexte, 0);
								strcat(tab_nom, "j");
								RectTexte.x+=25;
							break;
							case SDLK_k :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "k", RectTexte, 0);
								strcat(tab_nom, "k");
								RectTexte.x+=35;
							break;
							case SDLK_l :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "l", RectTexte, 0);
								strcat(tab_nom, "l");
								RectTexte.x+=25;
							break;
							case SDLK_m :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "m", RectTexte, 0);
								strcat(tab_nom, "m");
								RectTexte.x+=35;
							break;
							case SDLK_n :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "n", RectTexte, 0);
								strcat(tab_nom, "n");
								RectTexte.x+=35;
							break;
							case SDLK_o :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "o", RectTexte, 0);
								strcat(tab_nom, "o");
								RectTexte.x+=35;
							break;
							case SDLK_p :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "p", RectTexte, 0);
								strcat(tab_nom, "p");
								RectTexte.x+=35;
							break;
							case SDLK_q :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "q", RectTexte, 0);
								strcat(tab_nom, "q");
								RectTexte.x+=35;
							break;
							case SDLK_r :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "r", RectTexte, 0);
								strcat(tab_nom, "r");
								RectTexte.x+=30;
							break;
							case SDLK_s :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "s", RectTexte, 0);
								strcat(tab_nom, "s");
								RectTexte.x+=35;
							break;
							case SDLK_t :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "t", RectTexte, 0);
								strcat(tab_nom, "t");
								RectTexte.x+=30;
							break;
							case SDLK_u :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "u", RectTexte, 0);
								strcat(tab_nom, "u");
								RectTexte.x+=35;
							break;
							case SDLK_v :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "v", RectTexte, 0);
								strcat(tab_nom, "v");
								RectTexte.x+=35;
							break;
							case SDLK_w :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "w", RectTexte, 0);
								strcat(tab_nom, "w");
								RectTexte.x+=35;
							break;
							case SDLK_x :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "x", RectTexte, 0);
								strcat(tab_nom, "x");
								RectTexte.x+=35;
							break;
							case SDLK_y :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "y", RectTexte, 0);
								strcat(tab_nom, "y");
								RectTexte.x+=35;
							break;
							case SDLK_z :
								afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "z", RectTexte, 0);
								strcat(tab_nom, "z");
								RectTexte.x+=35;
							break;
						}
						break;
			}
		}
	}
	strcpy(j->nom, tab_nom);
	return j;
}

void saisie_joueurs_dans_table(TABLE* table){
    
    /* initialisation des joueurs dans la table */
    JOUEUR* j,*j_suiv;
    j=saisie_joueur_sdl(renderer);
    table->tete=j;
    for (int i=2;i<=table->nb_joueurs;i++){
        j_suiv=saisie_joueur_sdl(renderer);
        j->suivant=j_suiv;
        j=j_suiv;
    }
}

void saisie_joueurs_en_partie(TABLE *table){
    int nb,i,cpt;
    /* initialisation du nombre de joueurs dans la table */
    do {
        printf("\nCombien y a t-il de joueurs en plus sur la table (max %d) ? ",MAX_JOUEURS);
        scanf("%d",&nb);
    } while (nb<0 || (nb+ table->nb_joueurs)>5);

    /* initialisation des joueurs dans la table */
    JOUEUR* j,*j_suiv;
    printf("\n---------- Saisie des joueurs dans la table ----------\n");
    if(table->nb_joueurs == 0){
        j=saisie_joueur();
        table->tete=j;
        cpt = nb;
    }
    else{
        j = table->tete;
        while(j->suivant != NULL){
            j = j->suivant;
        }
        cpt = nb+1;
    }
    for (i=2;i<=cpt;i++){
        j_suiv=saisie_joueur();
        j->suivant=j_suiv;
        j=j_suiv;
    }
    table->nb_joueurs += nb;
}

int table_est_pleine(TABLE* t){
    if(t->nb_joueurs==MAX_JOUEURS) return 1;
    return 0;
}

int table_est_vide(TABLE* t){
    if(t->nb_joueurs==0) return 1;
    return 0;
}

void affiche_table(TABLE* t){
    JOUEUR *j;
    printf("\n---------- Affichage de la table ----------\n");
    if (table_est_vide(t)==1) printf("La table est vide");
    else{
        j=t->tete;
        while(j!=NULL){
            if(j->en_jeu) affiche_joueur(j);
            j=j->suivant;
        }
    }
}

void demande_mises(TABLE* t){
	JOUEUR *j;
	int joueur = 1;
	int mise = 0;
	char tab[5];
	int i=0;
	if (table_est_vide(t)==1) return;
	
        j=t->tete;
        while(j!=NULL){
        	afficher_vierge(renderer);
        	afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, "Mise Joueur 1 : ", mise_emp1, 0);
            while(event.key.keysym.sym == SDLK_RETURN){
				if (SDL_PollEvent(&event))
				{
					switch(event.type)
					{
						case SDL_WINDOWEVENT: // Événement de la fenêtre
							if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // Fermeture de la fenêtre
							{
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
							break;
						case SDL_KEYDOWN	: // Événement de relâchement d'une touche clavier
							switch(event.key.keysym.sym){
								case SDLK_1: //Touche Échap
								{
									tab[i] = '1';
									i++;
								}
								break;
								case SDLK_2: //Touche Échap
								{
									tab[i] = '2';
									i++;
								}
								break;
								case SDLK_3: //Touche Échap
								{
									tab[i] = '3';
									i++;
								}
								break;
								case SDLK_4: //Touche Échap
								{
									tab[i] = '4';
									i++;
								}
								break;
								case SDLK_5: //Touche Échap
								{
									tab[i] = '5';
									i++;
								}
								break;
								case SDLK_6: //Touche Échap
								{
									tab[i] = '6';
									i++;
								}
								break;
								case SDLK_7: //Touche Échap
								{
									tab[i] = '7';
									i++;
								}
								break;
								case SDLK_8: //Touche Échap
								{
									tab[i] = '8';
									i++;
								}
								break;
								case SDLK_9: //Touche Échap
								{
									tab[i] = '9';
									i++;
								}
								break;
								case SDLK_0: //Touche Échap
								{
									tab[i] = '0';
									i++;
								}
								break;
							}
						}
					}
				}
				
				afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, tab[0], nomj_emp1, 100);
				for(int j=1; j<i; j++){
					afficher_texte(renderer, "BOOKMANL.ttf", 30, TextColor, tab[0], nomj_emp1, 25);
				}
				for(int j=i; j>0; j--){
					mise += tab[i]-'0';
				}
					
							
           

        }
    }


void tirage_debut_partie(TABLE *t){
    JOUEUR *j;
    j=t->tete;
    while(j!=NULL){
        if(j->en_jeu) tirage_carte_joueur_debut(t->pioche,j);
        j=j->suivant;
    }
    tirage_carte_croupier_debut(t->pioche,t->croupier);
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


void repartition_gains(TABLE *t){
    JOUEUR *j;
    j=t->tete;
    while(j!=NULL){
        if(j->en_jeu){
            if(j->score > 21) printf("%s : vous avez perdu (score trop eleve!)\n",j->nom);
            else if((joueur_a_blackjack(j) && croupier_a_blackjack(t->croupier)) || (j->score == t->croupier->score)){
                j->capital+=j->mise;
                printf("%s : egalite, vous recuperez la mise!\n",j->nom);
            }
            else if(joueur_a_blackjack(j)){
                printf("%s : Bravo vous gangnez 2.5x votre mise (Blackjack)!\n",j->nom);
                j->capital+=(j->mise*2.5);
            }
            else if(j->score > t->croupier->score || t->croupier->score >21){
                j->capital+=(j->mise*2);
                printf("%s : Bravo vous doublez votre mise (score plus eleve que celui du croupier/croupier out)!\n",j->nom);
            }
            else printf("%s : Dommage, vous avez perdu (score plus faible que celui du croupier)\n",j->nom);
            if(j->split){
                if(j->score_split > 21) printf("%s : vous avez perdu (score trop eleve!)\n",j->nom);
                else if(j->score_split == t->croupier->score){
                    j->capital+=j->mise_split;
                    printf("%s : egalite, vous recuperez la mise!\n",j->nom);
                }
                else if(j->score_split > t->croupier->score || t->croupier->score >21){
                    j->capital+=(j->mise_split*2);
                    printf("%s : Bravo vous doublez votre mise (score plus eleve que celui du croupier/croupier out)!\n",j->nom);
                }
                else printf("%s : Dommage, vous avez perdu (score plus faible que celui du croupier)\n",j->nom);
            }
        }
        j=j->suivant;
    }

}


void reste_sur_table(TABLE *t){
	JOUEUR *j;
	int statut;
    SDL_Rect phrase = {500,200,0,0};
    SDL_Rect phrase2 = {600,200,0,0};
    SDL_Rect joueur = {700,200,0,0};
    char txt[40];
    /*printf("\n---------- Qui reste dans la partie ? ----------\n");*/
    afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "Qui reste dans la partie ?", phrase, 0);
    afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, "(pour rester tapper 1, pour quitter tapper 0)", phrase2, 0);
    if (table_est_vide(t)==1) printf("La table est vide");
    else{
        j=t->tete;
        while(j!=NULL){
            strcpy(txt,j->nom);
            strcat(txt, " ? ");
            afficher_texte(renderer, "BOOKMANL.ttf", 50, TextColor, txt, joueur, 0);
            while(event.key.keysym.sym == SDLK_RETURN){
				if (SDL_PollEvent(&event))
				{
					switch(event.type)
					{
						case SDL_WINDOWEVENT: // Événement de la fenêtre
							if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) // Fermeture de la fenêtre
							{
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
							break;
						case SDL_KEYDOWN	: // Événement de relâchement d'une touche clavier
							if ( event.key.keysym.sym == SDLK_1 ) //Touche 1
							{
								statut=1;
							}if ( event.key.keysym.sym == SDLK_0 ) //Touche 1
							{
								statut=0;
							}
                    }
                }
            }
            if(statut){
                j->split=0;
                j->en_jeu = 1;
            }
            else sortie_joueur_table(j,t);
            j=j->suivant;
        }
    }
}

void assigner_pioche(TABLE *t, PIOCHE *p){
    t->pioche=p;
}

void tirage_carte_joueur_mises(TABLE *t,JOUEUR *j){
    /* permet au joueur de tirer des cartes pendant les mises */
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(t->pioche);
    j->tab_cartes[j->nb_cartes] = *carte_tiree;
    j->nb_cartes++;
}

void tirage_carte_joueur_split(TABLE *t,JOUEUR *j){
    /* permet au joueur de tirer des cartes pendant les mises */
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(t->pioche);
    /*tableau carte de split*/
    j->tab_cartes_split[j->nb_cartes_split] = *carte_tiree;
    j->nb_cartes_split++;
}

void tirage_carte_croupier_apres_mises(TABLE *t){
    /* permet au croupier de tirer des cartes jusqu'a avoir un score superieur a 16 */
    CROUPIER *c = t->croupier;
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(t->pioche);
    c->tab_cartes[c->nb_cartes] = *carte_tiree;
    c->nb_cartes++;
}

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
    j->capital-=j->mise;
    j->mise*=2;
    j->tab_cartes[j->nb_cartes]=*tirer_carte(t->pioche);
    j->nb_cartes++;
}









