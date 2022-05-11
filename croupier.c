#include "croupier.h"

CROUPIER *init_croupier(){
    /*initialise la structure croupier */
    CROUPIER *c = (CROUPIER*) malloc(sizeof(CROUPIER));
    c->nb_cartes = 0;
    return c;
}

void tirage_carte_croupier_debut(PIOCHE *p,CROUPIER *c){
    /*permet au croupier de tirer ses 2 premieres cartes */
    CARTE *carte_tiree;
    int i;
    for(i=0;i++;i<2){
        carte_tiree = tirer_carte(PIOCHE *p);
        c->tab_cartes[i] = *carte_tiree;
        c->nb_cartes++;
    }
}

void tirage_carte_croupier_apres_mises(PIOCHE *p,CROUPIER *c){
    /* permet au croupier de tirer des cartes jusqu'a avoir un score superieur a 16 */
    CARTE *carte_tiree;
    int i;
    while(comptage_score_croupier(c)<17){
        carte_tiree = tirer_carte(PIOCHE *p);
        c->tab_cartes[i] = *carte_tiree;
        c->nb_cartes++;
    }
}

int comptage_score_croupier(CROUPIER *c){
    /*permet de compter le score du croupier */
    int res;
    res = compter_score(c->tab_cartes,c->nb_cartes);
    return res;
}

void liberer_croupier(CROUPIER *c){
    /* libere l'espace alouee par le croupier */
    free(c);
}
