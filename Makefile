CC = gcc
CFLAGS = -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows -lws2_32
SRC = src/
OBJ = obj/
INC = include/
TETRIS = TETRIS/

CFLAGS_SERVER = -Wextra -pedantic -std=c11
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

server: $(OBJ)serverFunctions.o $(OBJ)server.o
	$(CC) -o server $(OBJ)serverFunctions.o $(OBJ)server.o $(LDFLAGS_SERVER)

$(OBJ)serverFunctions.o: $(SRC)serverFunctions.c $(INC)$(TETRIS)serverFunctions.h
	$(CC) -c $(SRC)serverFunctions.c -o $(OBJ)serverFunctions.o $(CFLAGS_SERVER)

$(OBJ)server.o: $(SRC)server.c $(INC)$(TETRIS)serverFunctions.h
	$(CC) -c $(SRC)server.c -o $(OBJ)server.o $(CFLAGS_SERVER)

clean :
	rm -rf $(OBJ)*.o
	rm -rf *.exe
