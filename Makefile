CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows -lws2_32
SRC = src/
OBJ = obj/

CFLAGS_SERVER = -Wall -Wextra -pedantic -std=c11
LDFLAGS_SERVER = -lws2_32
all: Menu Jeu Server

# Menu
Menu : menu.o
	$(CC) $(OBJ)menu.o -o Menu $(LDFLAGS)

menu.o : $(SRC)menu.c
	$(CC) $(CFLAGS) -c $(SRC)menu.c -o $(OBJ)menu.o

# Jeu
Jeu : Jeu.o
	$(CC) $(OBJ)Jeu.o -o Jeu $(LDFLAGS)

Jeu.o : $(SRC)Jeu.c
	$(CC) $(CFLAGS) -c $(SRC)Jeu.c -o $(OBJ)Jeu.o

# Serveur
Server : server.o
	$(CC) $(OBJ)server.o -o server $(LDFLAGS_SERVER)

server.o : $(SRC)server.c
	$(CC) $(CFLAGS_SERVER) -c $(SRC)server.c -o $(OBJ)server.o

clean :
	rm -rf *.o
	rm -rf *.exe
