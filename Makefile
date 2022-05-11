# Makefile jeu BlackJack

CC = gcc
FLAGS = -std=c11 -Wall
OBJS = main.o joueur.o table.o
EXE = code

$(EXE) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXE)
	
main.o : table.h main.c
	$(CC) $(FLAGS) -c main.c -o main.o
	
table.o : joueur.h croupier.h table.h table.c
	$(CC) $(FLAGS) -c table.c -o table.o
	
joueur.o : pioche.h joueur.h joueur.c
	$(CC) $(FLAGS) -c joueur.c -o joueur.o
	
croupier.o : pioche.h croupier.h croupier.c
	$(CC) $(FLAGS) -c croupier.c -o croupier.o
	
pioche.o : pioche.h pioche.c
	$(CC) $(FLAGS) -c pioche.c -o pioche.o
	
clean :
	rm *.o $(EXE)
