#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define MAX_PLAYERS 100    // nombre maximum de joueurs
#define MAX_NAME_LENGTH 50 // longueur maximale du nom du joueur

// structure représentant un joueur
struct Player
{
    char name[MAX_NAME_LENGTH];
    int score;
};

// fonction de comparaison pour le tri des joueurs par score décroissant
int comparePlayers(const void *a, const void *b)
{
    struct Player *playerA = (struct Player *)a;
    struct Player *playerB = (struct Player *)b;
    return (playerB->score - playerA->score);
}

int main()
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    char buffer[1024];
    struct Player players[MAX_PLAYERS]; // tableau de joueurs
    int numPlayers = 0;                 // nombre de joueurs enregistrés

    // initialiser Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Erreur : impossible d'initialiser Winsock\n");
        return 1;
    }

    // créer la socket du serveur
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("Erreur : impossible de créer la socket du serveur\n");
        return 1;
    }

    // lier la socket du serveur à l'adresse IP et au port spécifiés
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(1234);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        printf("Erreur : impossible de lier la socket du serveur à l'adresse IP et au port spécifiés\n");
        return 1;
    }

    // mettre le serveur en écoute
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Erreur : impossible de mettre le serveur en écoute\n");
        return 1;
    }

    // boucle principale du serveur
    while (1)
    {
        printf("En attente de connexion...\n");

        // accepter une connexion entrante
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
        if (clientSocket == INVALID_SOCKET)
        {
            printf("Erreur : impossible d'accepter une connexion entrante\n");
            return 1;
        }

        printf("Connexion acceptée : %s\n", inet_ntoa(clientAddress.sin_addr));

        // recevoir les données du client
        int received = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (received == SOCKET_ERROR)
        {
            printf("Erreur : impossible de recevoir les données du client\n");
            closesocket(clientSocket);
            continue;
        }

        // extraire le nom et le score du buffer
        char name[MAX_NAME_LENGTH];

        int score = 0;
        sscanf(buffer, "%s %d", name, &score);
        printf("Données reçues : %s %d\n", name, score);

        // ajouter le joueur au tableau de joueurs
        if (numPlayers < MAX_PLAYERS)
        {
            struct Player player;
            strcpy(player.name, name);
            player.score = score;
            players[numPlayers] = player;
            numPlayers++;
        }

        // trier le tableau de joueurs par score décroissant
        qsort(players, numPlayers, sizeof(struct Player), comparePlayers);

        // enregistrer les 5 meilleurs scores dans un fichier texte
        FILE *file = fopen("scores.txt", "w");
        if (file == NULL)
        {
            printf("Erreur : impossible d'ouvrir le fichier scores.txt\n");
            closesocket(clientSocket);
            continue;
        }

        fprintf(file, "Meilleurs scores :\n");
        for (int i = 0; i < numPlayers && i < 5; i++)
        {
            fprintf(file, "%s : %d\n", players[i].name, players[i].score);
        }

        fclose(file);

        // envoyer la réponse au client
        const char *response = "Score enregistré.";


        if (send(clientSocket, response, strlen(response), 0) == SOCKET_ERROR)
        {
            printf("Erreur : impossible d'envoyer la réponse au client\n");
        }

        // fermer la socket du client
        closesocket(clientSocket);
    }

    // fermer la socket du serveur
    closesocket(serverSocket);

    // fermer Winsock
    WSACleanup();

    return 0;
}
