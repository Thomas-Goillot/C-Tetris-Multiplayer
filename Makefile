CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows

all: Menu Jeu

Menu : menu.o
	$(CC) menu.o -o Menu $(LDFLAGS)

menu.o : src/menu.c
	$(CC) $(CFLAGS) -c src/menu.c -o menu.o

Jeu : Jeu.o
	$(CC) Jeu.o -o Jeu $(LDFLAGS)

Jeu.o : src/Jeu.c
	$(CC) $(CFLAGS) -c src/Jeu.c -o Jeu.o

clean :
	rm -rf *.o
	rm -rf *.exe
