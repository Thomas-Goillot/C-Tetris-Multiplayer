CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows

Programme : main.o
	$(CC) main.o -o Programme $(LDFLAGS)

main.o : src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o


clean :
	rm -rf $(OBJ)*.o
	rm -rf $(EXE)
