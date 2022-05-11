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
