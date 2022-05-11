#include "table.h"

TABLE* init_table(){
    TABLE * table;
    table = (TABLE *) malloc(sizeof(TABLE));
    table->nb_joueurs=0;
    table->tete=NULL;
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
    j=saisie_joueur(1);
    table->tete=j;
    for (i=2;i<=nb;i++){
        j_suiv=saisie_joueur(i);
        j->suivant=j_suiv;
        j=j_suiv;
    }
    CROUPIER *c;
    c = init_croupier();
    table->croupier = c;
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
            affiche_joueur(j);
            j=j->suivant;
        }
    }
}

void demande_mises(TABLE* t){
	JOUEUR *j;
	float mise;
	printf("\n---------- Demande des mises ----------\n");
	if (table_est_vide(t)==1) printf("La table est vide");
    else{
        j=t->tete;
        while(j!=NULL){
        	do {
		        printf("Mise du joueur %d (mise mini = 2) :",j->num);
		        scanf("%f",&mise);
		    }
		    while((mise<2) || (mise>j->capital));
		    j->mise = mise;
		    j->capital -= mise;
            j=j->suivant;
        }
    }
}

void tirage_debut_partie(PIOCHE *p,TABLE *t){
    j=t->tete;
        while(j!=NULL){
            tirage_carte_joueur_debut()
            j=j->suivant;

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

int compter_score(CARTE* tab_cartes, int nb_cartes){
	int score = 0;
	int nb_as = 0;
	for(int i=0; i<nb_cartes; i++){
		if(tab_cartes[i].num>1 && tab_cartes[i].num<=10){
			score += tab_cartes[i].num;
		}
		if(tab_cartes[i].num>10 && tab_cartes[i].num<=13){
			score += 10;
		}
		else nb_as++;
	}
	for(int j=0; j<nb_as; j++){
		if(score<11) score+=11;
		else score+=1;
	}
	return score;
}


void repartition_gains(TABLE *t){
    int i;
    JOUEUR *j;
    j=t->tete;
    for(i=0;i<t->nb_joueurs;i++){
        if(j->score > 21);
        else if((joueur_a_blackjack(j) && croupier_a_blackjack(t->croupier)) || (j->score == t->croupier->score)) j->capital+=j->mise;
        else if(joueur_a_blackjack(j)) j->capital+=(j->mise*2.5);
        else if(j->score > t->croupier->score || t->croupier->score >21) j->capital+=(j->mise*2);
        j=j->suivant;
    }
    
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	


