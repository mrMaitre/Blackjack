#include <stdio.h>
#include <stdlib.h>
#include <pioche.h>


typedef struct joueur{
    int num;
    char nom[25];
    int en_jeu;
    float capital;
    float mise;
    CARTE tab_cartes[10];
    int nb_cartes;
    struct joueur * suivant;
} JOUEUR;


JOUEUR* saisie_joueur(int num);
void affiche_joueur(JOUEUR* j);
void tirer_carte_joueur_debut(JOUEUR *j);
void tirage_carte_croupier_mises(PIOCHE *p,JOUEUR *j);
void liberer_joueur(JOUEUR *j);
