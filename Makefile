CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows -lws2_32

CFLAGS_SERVER = -Wall -Wextra -pedantic -std=c11
LDFLAGS_SERVER = -lws2_32

Programme : jeu.o
	$(CC) jeu.o -o Programme $(LDFLAGS)

jeu.o : src/jeu.c
	$(CC) $(CFLAGS) -c src/jeu.c -o jeu.o

# Serveur
Server : server.o
	$(CC) server.o -o server $(LDFLAGS_SERVER)

server.o : src/server.c
	$(CC) $(CFLAGS_SERVER) -c src/server.c -o server.o

#client
Client : client.o
	$(CC) client.o -o client $(LDFLAGS_SERVER)

client.o : src/client.c
	$(CC) $(CFLAGS_SERVER) -c src/client.c -o client.o

clean :
	rm -rf *.o
	rm -rf *.exe
