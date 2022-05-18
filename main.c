#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "table.h"

int main(int argc, char **argv){
    printf("\n----------- JEU DU BLACKJACK -----------\n");
    time_t heure;
    srand((unsigned int) time(&heure));
    TABLE* table;
    PIOCHE* pioche;
    JOUEUR *j;
    int tirage = 1,choix;
    table = init_table();
    saisie_joueurs_croupier_dans_table(table);
    int continuer = 1;
    while(continuer==1){
        j=table->tete;
        while(j!=NULL){
            j->nb_cartes=0;
            j->nb_cartes_split = 0;
            j=j->suivant;
        }
        table->croupier->nb_cartes = 0;
        affiche_table(table);
    	pioche = init_pioche();
    	assigner_pioche(table,pioche);
		demande_mises(table);
		tirage_debut_partie(table);
		j=table->tete;
		printf("\n---------- Debut du jeu ----------\n");
		printf("Croupier :\n\tCarte 1 : %d\n",table->croupier->tab_cartes[0].num);
		while(j!=NULL){
			if(j->en_jeu){
				printf("\n---------- Tour de %s ----------\n",j->nom);
				j->score = comptage_score_joueur(j);
				while(tirage!=0 && tirage!=2 && j->score<21){
					affiche_carte_joueur(j);
					printf("score : %d\n",j->score);
					if(j->nb_cartes==2 && j->capital >= j->mise && j->tab_cartes[0].num== j->tab_cartes[1].num && j->split == 0) printf("Voulez-vous tirer une carte ? (0 : Non, 1 : Oui, 2 : Doubler, 3 : Split) ");
					else if(j->nb_cartes==2 && j->capital >= j->mise && j->split == 0) printf("Voulez-vous tirer une carte ? (0 : Non, 1 : Oui, 2 : Doubler) ");
					else printf("Voulez-vous tirer une carte ? (0 : Non, 1 : Oui)");
					scanf("%d",&tirage);
					if(tirage == 1){
						tirage_carte_joueur_mises(table,j);
					}else if(tirage==2 && j->nb_cartes==2 && j->capital >= j->mise){
						joueur_double(j,table);
					}
					else if(tirage == 3 && j->nb_cartes==2 && j->capital >= j->mise && j->tab_cartes[0].num== j->tab_cartes[1].num){
                        joueur_split(j);
					}
					j->score = comptage_score_joueur(j);
				}
                tirage = 1;
				if(j->split){
                   while(tirage != 0 && j->score_split<21){
                        affiche_carte_joueur(j);
                        printf("score split : %d\n",j->score_split);
                        printf("Voulez-vous tirer une carte ? (0 : Non, 1 : Oui)");
                        scanf("%d",&tirage);
                        if(tirage == 1) tirage_carte_joueur_split(table,j);
                        j->score_split = comptage_score_split_joueur(j);
                   }
				}
				affiche_carte_joueur(j);
				printf("score final : %d\n",j->score);
				if(j->split) printf("score final split : %d\n",j->score_split);
				tirage = 1;
			}
			j=j->suivant;
		}
		printf("\n---------- Tour du croupier ----------\n");
		table->croupier->score = comptage_score_croupier(table->croupier);
		while(table->croupier->score<17){
			tirage_carte_croupier_apres_mises(table);
			table->croupier->score = comptage_score_croupier(table->croupier);
		}
		affiche_carte_croupier(table->croupier);
		printf("score : %d\n",table->croupier->score);
		printf("\n---------- Resultats ----------\n");
		repartition_gains(table);
		affiche_table(table);
		printf("\nVoulez-vous refaire une partie ? (Oui : 1, Non : 0) ");
		scanf("%d",&continuer);
		if(continuer) reste_sur_table(table);
		if(continuer){
            printf("voulez vous ajouter des joueurs ? (Oui : 1, Non : 0)\n");
            scanf("%d",&choix);
            if(choix == 1) saisie_joueurs_en_partie(table);
		}
		free(pioche);

	}

	printf("\n---------- Fin du jeu ----------\n");

    return 0;
}

