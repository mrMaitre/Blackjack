#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main(int argc, char **argv){
    printf("\n----------- JEU DU BLACKJACK -----------\n");
    TABLE* table;
    PIOCHE* pioche;
    JOUEUR *j;
    int tirage = 1;
    table = init_table();
    saisie_joueurs_croupier_dans_table(table);
    affiche_table(table);
    int continuer = 1;
    while(continuer==1){
    	pioche = init_pioche();
		demande_mises(table);
		tirage_debut_partie(pioche,table);
		j=table->tete;
		while(j!=NULL){
			j->score = comptage_score_joueur(j);
			while(tirage!=0 && j->score<21){
				affiche_carte_joueur(j);
				printf("Voulez-vous tirer une carte ? (0 : Non, 1 : Oui) ");
				scanf("%d",&tirage);
				if(tirage == 1){
					tirage_carte_joueur_mises(pioche,j);
				}
				j->score = comptage_score_joueur(j);
			}
			tirage = 1;
			j=j->suivant;
		}
		table->croupier->score = comptage_score_croupier(table->croupier);
		while(table->croupier->score<16){
			tirage_carte_croupier_apres_mises(pioche,table->croupier);
			table->croupier->score = comptage_score_croupier(table->croupier);
		}
		affiche_carte_croupier(table->croupier);
		repartition_gains(table);
		reste_sur_table(table);
		free(pioche);
		printf("Voulez-vous refaire une partie ? (Oui : 1, Non : 0) ");
		scanf("%d",&continuer);
	}
	
    return 0;
}

