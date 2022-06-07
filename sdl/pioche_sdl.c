#include "pioche_sdl.h"

char nom_carte[18];

/* Initialise la structure de la pioche */
PIOCHE* init_pioche(){
    int i,j,k;
    PIOCHE * p;
    p=(PIOCHE*) malloc(sizeof(PIOCHE));
    CARTE * c, *c_prec;
    c=(CARTE*) malloc(sizeof(CARTE));
    c->couleur=CARREAU;
    c->num=1;
    c->suivant=NULL;
    p->tete=c;
    strcpy(c->nom_image,StructToChaine(c));
    p->nb_cartes=1;
    for(k=0;k<NB_JEUX_CARTES;k++){
        for(i=0;i<4;i++){
            for(j=1;j<14;j++){
                if((k==0)&&(i==0)&&(j==1));
                else{
                    c_prec=c;
                    c=(CARTE*) malloc(sizeof(CARTE));
                    c->num=j;
                    c->couleur=i;
                    c->suivant=NULL;
                    c_prec->suivant=c;
                    strcpy(c->nom_image,StructToChaine(c));
                    p->nb_cartes++;
                }
            }
        }
    }
    return p;
}

/* Permet de passer d'une structure de carte à une chaine de caracteres*/
char *StructToChaine(CARTE *c){
    int num;
    strcpy(nom_carte,"sdl/cartes/xx.bmp");
    COULEUR color;
    num = c->num;
    color = c->couleur;
    switch(num){
        case 1:
            nom_carte[11] = 'A';
            break;

        case 2:
            nom_carte[11] = '2';
            break;

        case 3 :
            nom_carte[11] = '3';
            break;

        case 4 :
            nom_carte[11] = '4';
            break;

        case 5:
            nom_carte[11] = '5';
            break;
        case 6:
            nom_carte[11] = '6';
            break;

        case 7:
            nom_carte[11] = '7';
            break;

        case 8 :
            nom_carte[11] = '8';
            break;

        case 9 :
            nom_carte[11] = '9';
            break;

        case 10:
            nom_carte[11] = 'D';
            break;

        case 11:
            nom_carte[11] = 'J';
            break;

        case 12 :
            nom_carte[11] = 'Q';
            break;

        case 13 :
            nom_carte[11] = 'K';
            break;
    }
    switch(color){

        case CARREAU :
            nom_carte[12] = 'd';
            break;
        case COEUR :
            nom_carte[12] = 'h';
            break;
        case PIC :
            nom_carte[12] = 's';
            break;
        case TREFLE :
            nom_carte[12] = 'c';
            break;
    }
    return nom_carte;
}

/* Permet de tirer une carte de la pioche */
CARTE* tirer_carte(PIOCHE *p){
    int alea,i;
    CARTE *c,*c_prec;;
    c=p->tete;
    alea = rand()% (p->nb_cartes);
    for(i=0;i<=alea;i++){
        c_prec=c;
        c=c->suivant;
    }
    c_prec->suivant=c->suivant;
    p->nb_cartes--;
    return c;
}

void liberer_pioche(PIOCHE *p){
    free(p);
}
