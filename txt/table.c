#include "table.h"

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
	float mise;
	printf("\n---------- Demande des mises ----------\n");
	if (table_est_vide(t)==1) printf("La table est vide");
    else{
        j=t->tete;
        while(j!=NULL){
            do {
            printf("Mise de %s (mise minimum = 2, 0 si passer son tour) : ",j->nom);
            scanf("%f",&mise);
            } while((mise<2 && mise !=0 )|| mise>j->capital);
            if(mise==0) j->en_jeu=0;
            else {
                j->en_jeu=1;
                j->mise = mise;
                j->capital -= mise;
            }
            j=j->suivant;

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









