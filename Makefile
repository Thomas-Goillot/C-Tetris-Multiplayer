CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows -lws2_32
SRC = src/
OBJ = obj/

CFLAGS_SERVER = -Wall -Wextra -pedantic -std=c11
LDFLAGS_SERVER = -lws2_32

all: clean menu score jeu server

# Menu
menu : menu.o
	$(CC) $(OBJ)menu.o -o menu $(LDFLAGS)

menu.o : $(SRC)menu.c
	$(CC) $(CFLAGS) -c $(SRC)menu.c -o $(OBJ)menu.o

score : score.o
	$(CC) $(OBJ)score.o -o score $(LDFLAGS)

score.o : $(SRC)score.c
	$(CC) $(CFLAGS) -c $(SRC)score.c -o $(OBJ)score.o

# Jeu
jeu : jeu.o
	$(CC) $(OBJ)jeu.o -o jeu $(LDFLAGS)

jeu.o : $(SRC)jeu.c
	$(CC) $(CFLAGS) -c $(SRC)jeu.c -o $(OBJ)jeu.o

# Serveur
server : server.o
	$(CC) $(OBJ)server.o -o server $(LDFLAGS_SERVER)

server.o : $(SRC)server.c
	$(CC) $(CFLAGS_SERVER) -c $(SRC)server.c -o $(OBJ)server.o

clean :
	rm -rf *.o
	rm -rf *.exe
