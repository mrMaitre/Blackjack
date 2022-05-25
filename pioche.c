#include "pioche.h"
#include "string.h"

char nom_carte[14];

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

char *StructToChaine(CARTE *c){
    int num;
    strcpy(nom_carte,"cartes/xx.bmp");
    COULEUR color;
    num = c->num;
    color = c->couleur;
    switch(num){
        case 1:
            nom_carte[7] = '1';
            break;

        case 2:
            nom_carte[7] = '2';
            break;

        case 3 :
            nom_carte[7] = '3';
            break;

        case 4 :
            nom_carte[7] = '4';
            break;

        case 5:
            nom_carte[7] = '5';
            break;
        case 6:
            nom_carte[7] = '6';
            break;

        case 7:
            nom_carte[7] = '7';
            break;

        case 8 :
            nom_carte[7] = '8';
            break;

        case 9 :
            nom_carte[7] = '9';
            break;

        case 10:
            nom_carte[7] = 'D';
            break;

        case 11:
            nom_carte[7] = 'J';
            break;

        case 12 :
            nom_carte[7] = 'Q';
            break;

        case 13 :
            nom_carte[7] = 'K';
            break;
    }
    switch(color){

        case CARREAU :
            nom_carte[8] = 'd';
            break;
        case COEUR :
            nom_carte[8] = 'h';
            break;
        case PIC :
            nom_carte[8] = 's';
            break;
        case TREFLE :
            nom_carte[8] = 'c';
            break;
    }
    return nom_carte;
}

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

void afficher_pioche(PIOCHE *p){
    printf("___ affichge pioche ___\n");
    CARTE *c = p->tete;
    while(c->suivant != NULL){
        printf("couleur : %d, num : %d et nom_image : %s\n",c->couleur,c->num,c->nom_image);
        c = c->suivant;
    }
    printf("couleur : %d, num : %d et nom_image : %s\n",c->couleur,c->num,c->nom_image);
}

void liberer_pioche(PIOCHE *p){
    free(p);
}
