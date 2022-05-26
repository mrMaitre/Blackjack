# Makefile jeu BlackJack

CC = gcc
FLAGS = -std=c11 -Wall
OBJS = main.o table.o joueur.o croupier.o pioche.o
OBJS1 = main_sdl.o table.o joueur.o croupier.o pioche.o fonction_sdl.o
EXE = code
EXE1 = sdl

$(EXE) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXE)
	
$(EXE1) : $(OBJS1)
	$(CC) $(FLAGS) $(OBJS1) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o $(EXE1)
	
main.o : table.h main.c
	$(CC) $(FLAGS) -c main.c -o main.o
	
main_sdl.o : table.h main_sdl.c
	$(CC) $(FLAGS) -c main_sdl.c $(sdl2-config --cflags --libs) -o main_sdl.o
	
table.o : fonction_sdl.h croupier.h table.h table.c
	$(CC) $(FLAGS) -c table.c -o table.o
	
fonction_sdl.o : joueur.h fonction_sdl.h fonction_sdl.c
	$(CC) $(FLAGS) -c fonction_sdl.c -o fonction_sdl.o
	
joueur.o : pioche.h joueur.h joueur.c
	$(CC) $(FLAGS) -c joueur.c -o joueur.o
	
croupier.o : pioche.h croupier.h croupier.c
	$(CC) $(FLAGS) -c croupier.c -o croupier.o
	
pioche.o : pioche.h pioche.c
	$(CC) $(FLAGS) -c pioche.c -o pioche.o
	
	
clean :
	rm *.o $(EXE1)
