# Makefile jeu BlackJack

CC = gcc
FLAGS = -std=c11 -Wall
OBJS = main.o joueur.o table.o
EXE = code

$(EXE) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXE)
	
main.o : joueur.h table.h pioche.h main.c
	$(CC) $(FLAGS) -c main.c -o main.o
	
ensemble.o : joueur.h joueur.c table.h table.c
	$(CC) $(FLAGS) -c joueur.c table.c -o joueur.o
	
clean :
	rm *.o $(EXE)
