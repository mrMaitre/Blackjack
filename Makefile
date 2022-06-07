# Makefile jeu BlackJack

CC = gcc
FLAGS = -std=c11 -Wall
OBJS = txt/main.o txt/table.o txt/joueur.o txt/croupier.o txt/pioche.o
OBJS1 = sdl/main_sdl.o sdl/table_sdl.o sdl/joueur_sdl.o sdl/croupier_sdl.o sdl/pioche_sdl.o sdl/fonction_sdl.o


# Executables

texte : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o texte
	
sdl2 : $(OBJS1)
	$(CC) $(FLAGS) $(OBJS1) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o sdl2
	
	
# Cibles txt
	
txt/main.o : txt/table.h txt/main.c
	$(CC) $(FLAGS) -c txt/main.c -o txt/main.o
	
txt/table.o : txt/croupier.h txt/joueur.h txt/table.h txt/table.c
	$(CC) $(FLAGS) -c txt/table.c -o txt/table.o
	
txt/joueur.o : txt/pioche.h txt/joueur.h txt/joueur.c
	$(CC) $(FLAGS) -c txt/joueur.c -o txt/joueur.o
	
txt/croupier.o : txt/pioche.h txt/croupier.h txt/croupier.c
	$(CC) $(FLAGS) -c txt/croupier.c -o txt/croupier.o
	
txt/pioche.o : txt/pioche.h txt/pioche.c
	$(CC) $(FLAGS) -c txt/pioche.c -o txt/pioche.o
	
	
# Cibles sdl
	
sdl/main_sdl.o : sdl/table_sdl.h sdl/main_sdl.c
	$(CC) $(FLAGS) -c sdl/main_sdl.c $(sdl2-config --cflags --libs) -o sdl/main_sdl.o
	
sdl/table_sdl.o : sdl/croupier_sdl.h sdl/joueur_sdl.h sdl/table_sdl.h sdl/table_sdl.c
	$(CC) $(FLAGS) -c sdl/table_sdl.c -o sdl/table_sdl.o
	
sdl/joueur_sdl.o : sdl/pioche_sdl.h sdl/joueur_sdl.h sdl/joueur_sdl.c
	$(CC) $(FLAGS) -c sdl/joueur_sdl.c -o sdl/joueur_sdl.o
	
sdl/croupier_sdl.o : sdl/pioche_sdl.h sdl/croupier_sdl.h sdl/croupier_sdl.c
	$(CC) $(FLAGS) -c sdl/croupier_sdl.c -o sdl/croupier_sdl.o
	
sdl/pioche_sdl.o : sdl/fonction_sdl.h sdl/pioche_sdl.h sdl/pioche_sdl.c
	$(CC) $(FLAGS) -c sdl/pioche_sdl.c -o sdl/pioche_sdl.o
	
sdl/fonction_sdl.o : sdl/fonction_sdl.h sdl/fonction_sdl.c
	$(CC) $(FLAGS) -c sdl/fonction_sdl.c -o sdl/fonction_sdl.o
	
	
# Clean

clean_texte :
	rm txt/*.o texte
	
clean_sdl2 :
	rm sdl/*.o sdl2
	
clean :
	rm txt/*.o sdl/*.o texte sdl2
