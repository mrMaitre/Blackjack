#include <stdio.h>
#include <stdlib.h>

typedef struct joueur{
    int num;
    char nom[25];
    int en_jeu;
    int capital;
    int mise;
    struct joueur * suivant;
} JOUEUR;


JOUEUR* saisie_joueur(int num);
void affiche_joueur(JOUEUR* j);