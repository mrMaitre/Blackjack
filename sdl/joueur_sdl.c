#include "joueur_sdl.h"



void tirage_carte_joueur_debut(SDL_Renderer *renderer, PIOCHE *p,JOUEUR *j, SDL_Rect emp, int offset){
    /*permet au joueur de tirer ses 2 premieres cartes */
    CARTE *carte_tiree;
    int i;
    int offset2 = 0;
    for(i=0;i<2;i++){
        carte_tiree = tirer_carte(p);
        afficher_carte(StructToChaine(carte_tiree), renderer, &emp, offset+offset2, offset2);
        SDL_Delay(500);
        j->tab_cartes[i] = *carte_tiree;
        j->nb_cartes++;
        offset2+=15;
        emp.x-=offset;
    }
}


void liberer_joueur(JOUEUR *j){
    free(j);
}

int joueur_a_blackjack(JOUEUR *j){
    if(j->score == 21 && j->nb_cartes == 2) return 1;
    return 0;
}

void joueur_split(JOUEUR *j){
    j->split=1;
    j->mise_split=j->mise;
    j->capital -= j->mise;
    j->tab_cartes_split[0]=j->tab_cartes[1];
    j->nb_cartes--;
    j->nb_cartes_split++;
    j->score = j->tab_cartes_split[0].num;
    j->score_split = j->tab_cartes_split[0].num;
}







