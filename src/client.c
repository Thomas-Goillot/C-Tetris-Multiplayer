#include <stdio.h>
#include <winsock2.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : client.exe nom score\n");
        return 1;
    }

    const char *name = argv[1];
    int score = atoi(argv[2]);

    // initialiser Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        printf("Erreur : impossible d'initialiser Winsock\n");
        return 1;
    }

    // créer la socket du client
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        printf("Erreur : impossible de creer la socket du client\n");
        WSACleanup();
        return 1;
    }

    // se connecter au serveur
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(1234);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Erreur : impossible de se connecter au serveur\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // envoyer les données au serveur
    char buffer[1024];
    sprintf(buffer, "%s %d", name, score);
    if (send(clientSocket, buffer, strlen(buffer), 0) == SOCKET_ERROR)
    {
        printf("Erreur : impossible d'envoyer les donnees au serveur\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // recevoir la réponse du serveur
    char response[1024];
    int numBytes = recv(clientSocket, response, sizeof(response) - 1, 0);
    if (numBytes == SOCKET_ERROR)
    {
        printf("Erreur : impossible de recevoir la reponse du serveur\n");
    }
    else
    {
        response[numBytes] = '\0';
        printf("Reponse reçue : %s\n", response);
    }

    // fermer la socket du client
    closesocket(clientSocket);

    // fermer Winsock
    WSACleanup();

    return 0;
}
