#include "table.h"

#include <math.h>


TABLE* init_table(){
    TABLE * table;
    table = (TABLE *) malloc(sizeof(TABLE));
    table->nb_joueurs=0;
    table->tete=NULL;
    table->pioche=NULL;
    return table;
}

void saisie_joueurs_croupier_dans_table(TABLE* table){
    int nb,i;
    /* initialisation du nombre de joueurs dans la table */
    do {
        printf("\nCombien y a t-il de joueurs sur la table (max %d) ? ",MAX_JOUEURS);
        scanf("%d",&nb);
    } while (nb<0 || nb>5);
    table->nb_joueurs=nb;

    /* initialisation des joueurs dans la table */
    JOUEUR* j,*j_suiv;
    printf("\n---------- Saisie des joueurs dans la table ----------\n");
    j=saisie_joueur();
    table->tete=j;
    for (i=2;i<=nb;i++){
        j_suiv=saisie_joueur();
        j->suivant=j_suiv;
        j=j_suiv;
    }
    CROUPIER *c;
    c = init_croupier();
    table->croupier = c;
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
    printf("\n---------- Qui reste dans la partie ? ----------\n");
    if (table_est_vide(t)==1) printf("La table est vide");
    else{
        j=t->tete;
        while(j!=NULL){
            printf("%s : (pour rester tapper 1, pour quitter tapper 0) : ",j->nom);
            scanf("%d",&statut);
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









