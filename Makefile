CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows -lws2_32

CFLAGS_SERVER = -Wall -Wextra -pedantic -std=c11
LDFLAGS_SERVER = -lws2_32
all: Menu Jeu

Menu : menu.o
	$(CC) menu.o -o Menu $(LDFLAGS)

menu.o : src/menu.c
	$(CC) $(CFLAGS) -c src/menu.c -o menu.o

Jeu : Jeu.o
	$(CC) Jeu.o -o Jeu $(LDFLAGS)

Jeu.o : src/Jeu.c
	$(CC) $(CFLAGS) -c src/Jeu.c -o Jeu.o

# Serveur
Server : server.o
	$(CC) server.o -o server $(LDFLAGS_SERVER)

server.o : src/server.c
	$(CC) $(CFLAGS_SERVER) -c src/server.c -o server.o

clean :
	rm -rf *.o
	rm -rf *.exe
