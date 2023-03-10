#include "croupier_sdl.h"

CROUPIER *init_croupier(){
    /*initialise la structure croupier */
    CROUPIER *c = (CROUPIER*) malloc(sizeof(CROUPIER));
    c->nb_cartes = 0;
    c->score = 0;
    return c;
}


void tirage_carte_croupier_debut(SDL_Renderer *renderer, PIOCHE *p, CROUPIER *c, SDL_Rect emp){
    /*permet au croupier de tirer ses 2 premieres cartes */
    CARTE *carte_tiree;
    int offset2 = 0;
    carte_tiree = tirer_carte(p);
    afficher_carte("sdl/cartes/Dos.bmp", renderer, &emp, offset2, 0);
    SDL_Delay(500);
    c->tab_cartes[0] = *carte_tiree;
    c->nb_cartes++;
    carte_tiree = tirer_carte(p);
    offset2+=81;
    carte_tiree = tirer_carte(p);
    afficher_carte(StructToChaine(carte_tiree), renderer, &emp, offset2, 0);
    SDL_Delay(500);
    c->tab_cartes[1] = *carte_tiree;
    c->nb_cartes++;
    carte_tiree = tirer_carte(p);
    offset2+=81;
}


void liberer_croupier(CROUPIER *c){
    /* libere l'espace alouee par le croupier */
    free(c);
}

int croupier_a_blackjack(CROUPIER *c){
    if(c->score == 21 && c->nb_cartes == 2) return 1;
    return 0;
}
