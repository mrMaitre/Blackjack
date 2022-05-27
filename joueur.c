#include "joueur.h"

JOUEUR* saisie_joueur(){
	JOUEUR * j;
    j=(JOUEUR *) malloc(sizeof(JOUEUR));
    printf("Saisie du joueur\n");
    printf("\tEntrez le nom du joueur : ");
    scanf("%s",j->nom);
    printf("\tEntrez le capital du joueur : ");
    scanf("%d",&j->capital);
    j->mise=0;
    j->score = 0;
    j->en_jeu=1;
    j->nb_cartes=0;
    j->split=0;
    j->mise_split=0;
    j->nb_cartes_split=0;
    j->score_split=0;
    j->suivant=NULL;
    return j;
}


void affiche_joueur(JOUEUR* j){
    printf("Joueur enregistre !:\n\tnom : %s\n\tcapital : %ds\n",j->nom,j->capital);
}

void affiche_carte_joueur(JOUEUR* j){
    int i;
	printf("%s :\n",j->nom);
	for(i = 0; i<j->nb_cartes; i++){
    	printf("\tCarte %d : %d\n",i+1,j->tab_cartes[i].num);
	}
    if(j->split){
        printf("Jeu split :\n");
        for(i=0;i<j->nb_cartes_split;i++){
            printf("\tCarte %d : %d\n",i+1,j->tab_cartes_split[i].num);
        }
    }
}

void tirage_carte_joueur_debut(SDL_Renderer *renderer, PIOCHE *p,JOUEUR *j, SDL_Rect emp, int offset){
    /*permet au joueur de tirer ses 2 premieres cartes */
    CARTE *carte_tiree;
    int i;
    int offset2 = 0;
    for(i=0;i<2;i++){
        carte_tiree = tirer_carte(p);
        afficher_carte(StructToChaine(carte_tiree), renderer, &emp, offset+offset2, offset2);
        SDL_Delay(200);
        printf("%d\n", offset+offset2);
        j->tab_cartes[i] = *carte_tiree;
        j->nb_cartes++;
        offset2+=15;
        emp.x-=offset;
    }
    affiche_carte_joueur(j);
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

