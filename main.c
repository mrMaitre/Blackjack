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
    int tirage = 1;
    table = init_table();
    saisie_joueurs_croupier_dans_table(table);
    int continuer = 1;
    while(continuer==1){
        j=table->tete;
        while(j!=NULL){
            j->nb_cartes=0;
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
				printf("\n---------- Tour du joueur %d ----------\n",j->num);
				j->score = comptage_score_joueur(j);
				while(tirage!=0 && j->score<21){
					affiche_carte_joueur(j);
					printf("score : %d\n",j->score);
					printf("Voulez-vous tirer une carte ? (0 : Non, 1 : Oui) ");
					scanf("%d",&tirage);
					if(tirage == 1){
						tirage_carte_joueur_mises(table,j);
					}
					j->score = comptage_score_joueur(j);
				}
				affiche_carte_joueur(j);
				printf("score final : %d\n",j->score);
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
		free(pioche);
		
	}

	printf("\n---------- Fin du jeu ----------\n");

    return 0;
}

