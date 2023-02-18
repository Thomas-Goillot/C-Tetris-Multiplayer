/*
Server functions for Tetris
Author: Ibrahim OUBIHI / Thomas Goillot / Johua TANG TONG HI
Date  : 18/02/2023
*/

#include "../include/TETRIS/serverFunctions.h"


void write_scores_to_file(const char *filename, Player players[], int numPlayers)
{

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return;
    }

    for (int i = 0; i < numPlayers; i++)
    {
        fprintf(fp, "%s %d\n", players[i].name, players[i].score);
    }

    fclose(fp);
}

int read_scores_from_file(const char *filename, Player players[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Le fichier %s n'existe pas, il sera créé.\n", filename);
        return 0;
    }

    int i = 0;
    while (fscanf(fp, "%s %d", players[i].name, &players[i].score) == 2)
    {
        i++;
    }

    fclose(fp);
    return i;
}

int compare_players(const void *a, const void *b)
{
    const Player *playerA = (const Player *)a;
    const Player *playerB = (const Player *)b;

    return playerB->score - playerA->score;
}
