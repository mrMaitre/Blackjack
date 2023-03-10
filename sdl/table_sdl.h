#ifndef __TABLE_H__
#define __TABLE_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "croupier_sdl.h"
#include "joueur_sdl.h"
#define MAX_JOUEURS 5

typedef struct table{
    int nb_joueurs;
    JOUEUR * tete;
    CROUPIER * croupier;
    PIOCHE * pioche;
} TABLE;



TABLE* init_table();
int table_est_pleine(TABLE* p);
int table_est_vide(TABLE* p);
int saisie_joueurs_dans_table(SDL_Window *window, SDL_Texture *image, SDL_Renderer* renderer, TABLE* table);
JOUEUR* saisie_joueur_sdl(SDL_Window *window, SDL_Texture *image, SDL_Renderer* renderer, int num, TABLE *table);
int demande_mises(SDL_Window *window, SDL_Texture *image, SDL_Renderer* renderer, TABLE* t);
int comptage_score_croupier(CROUPIER *c);
int comptage_score_joueur(JOUEUR *j);
int compter_score(CARTE* tab_cartes, int nb_cartes);
void repartition_gains(SDL_Renderer* renderer, TABLE *t);
void tirage_debut_partie(SDL_Renderer *renderer, TABLE *t, SDL_Rect emp_j, SDL_Rect emp_c);
int reste_sur_table(SDL_Window *window, SDL_Texture *image, SDL_Renderer* renderer, TABLE *t);
void assigner_pioche(TABLE *t, PIOCHE *p);
void tirage_carte_croupier_apres_mises(SDL_Renderer *renderer,TABLE *t, SDL_Rect emp, int offset);
void tirage_carte_joueur_mises(SDL_Renderer *renderer,TABLE *t,JOUEUR *j, SDL_Rect emp, int offset);
void sortie_joueur_table(JOUEUR *j,TABLE *t);
void joueur_double(JOUEUR *j, TABLE *t);
int comptage_score_split_joueur(JOUEUR* j);
void tirage_carte_joueur_split1(SDL_Renderer *renderer,TABLE *t,JOUEUR *j, SDL_Rect emp, int offset);
void tirage_carte_joueur_split2(SDL_Renderer *renderer,TABLE *t,JOUEUR *j, SDL_Rect emp, int offset);
int saisie_joueurs_en_partie(SDL_Window *window, SDL_Texture *image, TABLE *table, SDL_Renderer *renderer);
void afficher_nom_capital(SDL_Renderer* renderer, TABLE *t, SDL_Rect nomj_emp, SDL_Rect capital_emp);
void afficher_mise(SDL_Renderer *renderer, TABLE *table, SDL_Rect mise_emp);
void liberer_table(TABLE *t);
int gestion_action(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer, TABLE *t, int offset, int cas, JOUEUR* joueur);
void afficher_cartes_split(SDL_Renderer *renderer, JOUEUR * j, int offset);
void afficher_score(SDL_Renderer *renderer, JOUEUR * j, int offset);
void afficher_score_split(SDL_Renderer *renderer, JOUEUR * j, int offset);
void afficher_score_croupier(SDL_Renderer *renderer, CROUPIER *c);
void afficher_blackjack(SDL_Renderer *renderer, JOUEUR * j, int offset);
void afficher_mise_split(JOUEUR *j, SDL_Renderer *renderer, TABLE *table, SDL_Rect mise_emp, int offset);
int jeu_split(SDL_Window *window, SDL_Texture *image, SDL_Renderer *renderer, TABLE *t, JOUEUR *j, int offset, SDL_Rect choix_emp, SDL_Rect mise_emp, int i);
	

#endif //TABLE_H_INCLUDED
