/*
Server functions for Tetris
Author: Ibrahim OUBIHI / Thomas Goillot / Johua TANG TONG HI
Date  : 18/02/2023
*/


#ifndef DEF_HEADER_SERVER_FUNCTIONS
#define DEF_HEADER_SERVER_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player Player;
struct Player
{
    char name[50];
    int score;
};

void write_scores_to_file(const char *filename, Player players[], int numPlayers);

int read_scores_from_file(const char *filename, Player players[]);

int compare_players(const void *a, const void *b);

#endif
