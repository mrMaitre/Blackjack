# Makefile jeu BlackJack

CC = gcc
FLAGS = -std=c11 -Wall
OBJS = main.o joueur.o
EXE = code

$(EXE) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXE)
	
main.o : joueur.h main.c
	$(CC) $(FLAGS) -c main.c -o main.o
	
ensemble.o : joueur.h joueur.c
	$(CC) $(FLAGS) -c joueur.c -o joueur.o
	
clean :
	rm *.o $(EXE)
