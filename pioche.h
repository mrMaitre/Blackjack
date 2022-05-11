#include <stdio.h>
#include <stdlib.h>

#define NB_JEUX_CARTES 3

typedef enum couleur {CARREAU,COEUR,PIC,TREFLE} COULEUR;

typedef struct carte{
    int num;
    COULEUR couleur;
    struct carte * suivant;
}CARTE;

typedef struct pioche{
    int nb_cartes;
    CARTE * tete;
}PIOCHE;