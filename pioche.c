#include "pioche.h"

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
    p->nb_cartes=1;
    for(k=0;k<NB_JEUX_CARTES;k++){
        for(i=0;i<4;i++){
            for(j=1;j<14;j++){
                if(p->nb_cartes==1);
                else{
                    c_prec=c;
                    c=(CARTE*) malloc(sizeof(CARTE));
                    c->num=j;
                    c->couleur=i;
                    c->suivant=NULL;
                    c_prec->suivant=c;
                    p->nb_cartes++;
                }
            }
        }
    }
    return p;
}

CARTE* tirer_carte(PIOCHE *p){
    int alea,i;
    CARTE *c,*c_prec;;
    c=p->tete;
    alea = rand() % (p->nb_cartes+1);
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
        printf("couleur : %d et num : %d\n",c->couleur,c->num);
        c = c->suivant;
    }
    printf("couleur : %d et num : %d\n",c->couleur,c->num);
}
