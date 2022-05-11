#include "joueur.h"

JOUEUR* saisie_joueur(int num){
	JOUEUR * j;
    j=(JOUEUR *) malloc(sizeof(JOUEUR));
    j->num=num;
    printf("Saisie du joueur n%d\n",num);
    printf("\tEntrez le nom du joueur : ");
    scanf("%s",j->nom);
    printf("\tEntrez le capital du joueur : ");
    scanf("%f",&j->capital);
    j->mise=0;
    j->en_jeu=1;
    j->nb_cartes=0;
    j->suivant=NULL;
    return j; 
}


void affiche_joueur(JOUEUR* j){
    printf("Joueur n%d :\n\tnom : %s\n\tcapital : %f\n",j->num,j->nom,j->capital);
}

void tirer_carte_joueur_debut(PIOCHE *p,JOUEUR *j){
    /*permet au joueur de tirer ses 2 premieres cartes */
    CARTE *carte_tiree;
    int i;
    for(i=0;i++;i<2){
        carte_tiree = tirer_carte(PIOCHE *p);
        j->tab_cartes[i] = *carte_tiree;
        j->nb_cartes++;
    }
}

void tirage_carte_croupier_mises(PIOCHE *p,JOUEUR *j){
    /* permet au joueur de tirer des cartes pendant les mises */
    CARTE *carte_tiree;
    carte_tiree = tirer_carte(PIOCHE *p);
    j->tab_cartes[i] = *carte_tiree;
    j->nb_cartes++;
}

void liberer_joueur(JOUEUR *j){
    free(j);
}
