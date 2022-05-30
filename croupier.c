#include "croupier.h"

CROUPIER *init_croupier(){
    /*initialise la structure croupier */
    CROUPIER *c = (CROUPIER*) malloc(sizeof(CROUPIER));
    c->nb_cartes = 0;
    c->score = 0;
    return c;
}

void affiche_carte_croupier(CROUPIER *c){
	for(int i = 0; i<c->nb_cartes; i++){
    	printf("Carte %d : %d\n",i+1,c->tab_cartes[i].num);
	}
}

void tirage_carte_croupier_debut(SDL_Renderer *renderer, PIOCHE *p, CROUPIER *c, SDL_Rect emp){
    /*permet au croupier de tirer ses 2 premieres cartes */
    CARTE *carte_tiree;
    int i;
    int offset2 = 0;
    for(i=0;i<2;i++){
        carte_tiree = tirer_carte(p);
        afficher_carte(StructToChaine(carte_tiree), renderer, &emp, offset2, 0);
        SDL_Delay(500);
        c->tab_cartes[i] = *carte_tiree;
        c->nb_cartes++;
        carte_tiree = tirer_carte(p);
        offset2+=81;
    }
}


void liberer_croupier(CROUPIER *c){
    /* libere l'espace alouee par le croupier */
    free(c);
}

int croupier_a_blackjack(CROUPIER *c){
    if(c->score == 21 && c->nb_cartes == 2) return 1;
    return 0;
}
