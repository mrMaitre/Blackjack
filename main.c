#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main(int argc, char **argv){
    printf("\n----------- JEU DU BLACKJACK -----------\n");
    TABLE* table;
    table=init_table();
    saisie_joueurs_croupier_dans_table(table);
    affiche_table(table);
    demande_mises(table);
    reste_sur_table(table);
	
    return 0;
}

