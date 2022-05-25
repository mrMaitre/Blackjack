#ifndef PIOCHE_H_INCLUDED
#define PIOCHE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define NB_JEUX_CARTES 3

typedef enum couleur {CARREAU,COEUR,PIC,TREFLE} COULEUR;

typedef struct carte{
    int num;
    COULEUR couleur;
    struct carte * suivant;
    char nom_image[14];
}CARTE;

typedef struct pioche{
    int nb_cartes;
    CARTE * tete;
}PIOCHE;

PIOCHE* init_pioche();
CARTE* tirer_carte(PIOCHE *p);
void afficher_pioche(PIOCHE *p);
void liberer_pioche(PIOCHE *p);
char *StructToChaine(CARTE *c);

#endif // PIOCHE_H_INCLUDED
