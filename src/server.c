#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define MAX_PLAYERS 100

typedef struct
{
    char name[50];
    int score;
} Player;

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

int main()
{
    const char *filename = "scores.txt";

    // initialiser Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        printf("Erreur : impossible d'initialiser Winsock\n");
        return 1;
    }

    // créer la socket du serveur
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("Erreur : impossible de créer la socket du serveur\n");
        WSACleanup();
        return 1;
    }

    // lier la socket à l'adresse IP locale et au port 1234
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(1234);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Erreur : impossible de lier la socket du serveur à l'adresse IP et au port spécifiés\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // écouter les connexions entrantes
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Erreur : impossible d'écouter les connexions entrantes\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("En attente de connexions...\n");

    // initialiser le tableau de joueurs
    Player players[MAX_PLAYERS];
    int numPlayers = read_scores_from_file(filename, players);

    // boucle principale du serveur
    while (1)
    {
        // accepter une nouvelle connexion
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            printf("Erreur : impossible d'accepter une nouvelle connexion\n");
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        printf("Nouvelle connexion acceptée.\n");

        // recevoir le nom et le score du joueur
        char playerName[50];
        int playerScore = 0;
        int bytesReceived = recv(clientSocket, playerName, sizeof(playerName), 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            printf("Erreur : impossible de recevoir les données du joueur\n");
            closesocket(clientSocket);
            continue;
        }

        // ajouter le joueur au tableau
        playerName[bytesReceived] = '\0';
        Player newPlayer;
        strncpy(newPlayer.name, playerName, sizeof(newPlayer.name));
        newPlayer.score = playerScore;
        players[numPlayers] = newPlayer;
        numPlayers++;

        // trier le tableau de joueurs par score décroissant
        qsort(players, numPlayers, sizeof(Player), compare_players);

        // limiter le nombre de joueurs à MAX_PLAYERS
        if (numPlayers > MAX_PLAYERS)
        {
            numPlayers = MAX_PLAYERS;
        }

        // écrire les scores dans le fichier
        write_scores_to_file(filename, players, numPlayers);

        // renvoyer les 5 meilleurs scores au client
        char scoresMessage[500] = "";
        for (int i = 0; i < 5 && i < numPlayers; i++)
        {
            char scoreLine[50];
            sprintf(scoreLine, "%s-%d-", players[i].name, players[i].score);
            strncat(scoresMessage, scoreLine, sizeof(scoresMessage) - strlen(scoresMessage) - 1);
        }
        scoresMessage[strlen(scoresMessage) - 1] = '\0';

        //printf("%s", scoresMessage);
        if (send(clientSocket, scoresMessage, strlen(scoresMessage), 0) == SOCKET_ERROR)
        {
            printf("Erreur : impossible d'envoyer les scores au client\n");
            closesocket(clientSocket);
            continue;
        }

        // fermer la connexion avec le client
        closesocket(clientSocket);
    }

    // fermer la socket du serveur
    closesocket(serverSocket);

    // libérer Winsock
    WSACleanup();

    return 0;
}
