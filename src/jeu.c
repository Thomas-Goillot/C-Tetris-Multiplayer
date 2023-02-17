#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_audio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <winsock2.h>
const int8_t bi[4][4][2] =
        {
                {{-2, 0}, {1,  0}, {-2, -1}, {1,  2}},
                {{-1, 0}, {2,  0}, {-1, 2},  {2,  -1}},
                {{2,  0}, {-1, 0}, {2,  1},  {-1, -2}},
                {{1,  0}, {-2, 0}, {1,  -2}, {-2, 1}}};

const int8_t br[4][4][2] =
        {
                {{-1, 0}, {-1, 1},  {0, -2}, {-1, -2}},
                {{1,  0}, {1,  -1}, {0, 2},  {1,  2}},
                {{1,  0}, {1,  1},  {0, -2}, {1,  -2}},
                {{-1, 0}, {-1, -1}, {0, 2},  {-1, 2}}};

// initialisation de la taille du tableau en hauteur et largeur, ainsi que la taille de chaque cellules
const uint8_t ri[4][4] =
        {
                {0, 3, 15, 12},
                {1, 7, 14, 8},
                {4, 2, 11, 13},
                {5, 6, 10, 9}};

const uint8_t rr[2][4] =
        {
                {0, 2, 10, 8},
                {1, 6, 9,  4}};

const uint8_t height = 40;
const uint8_t width = 10;
const uint8_t cellwidth = 20;

enum TETROMINOS {
    E, // vide
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

const SDL_Colour cmap[L + 1] =
        {
                {40,  40,  40,  255},
                {0,   255, 255, 255},
                {255, 255, 0,   255},
                {255, 0,   255, 255},
                {0,   255, 0,   255},
                {255, 0,   0,   255},
                {0,   0,   255, 255},
                {255, 200, 0,   255}};

// initialisation des formes a l'aide de la fonction enum TETROMINOS et chaque lettre correspond a une forme

const uint8_t starts[L][16] =
        {
                {E, E, E, E,
                        I, I, I, I,
                        E, E, E, E,
                        E, E, E, E},
                {E, O, O, E,
                        E, O, O, E,
                        E, E, E, E,
                        E, E, E, E},
                {E, T, E, E,
                        T, T, T, E,
                        E, E, E, E,
                        E, E, E, E},
                {E, S, S, E,
                        S, S, E, E,
                        E, E, E, E,
                        E, E, E, E},
                {Z, Z, E, E,
                        E, Z, Z, E,
                        E, E, E, E,
                        E, E, E, E},
                {J, E, E, E,
                        J, J, J, E,
                        E, E, E, E,
                        E, E, E, E},
                {E, E, L, E,
                        L, L, L, E,
                        E, E, E, E,
                        E, E, E, E}};

uint8_t field[400];

int8_t x, y;
uint8_t piecebox[16];
uint8_t falltype;
uint8_t rstate = 0;
uint8_t droptimer = 0;

// chargement des formes suivantes de manières aleatoires

uint8_t formecur = 7;
uint8_t forme[7];

char* name;
int score = 0; // affichage du score

void nouvelle_forme() {
    for (uint8_t i = 0; i < 7; i++)
        forme[i] = i + 1;

    for (uint8_t i = 6; i > 0; i--) {
        uint8_t t;
        uint8_t num = rand() % (i + 1);

        t = forme[i];
        forme[i] = forme[num];
        forme[num] = t;
    }

    formecur = 0;
}

// apparition de la prochaine forme

void spawn() {
    if (formecur >= 7)
        nouvelle_forme();

    falltype = forme[formecur++];

    x = 3;
    y = 0;
    rstate = 0;
    droptimer = 0;
    memcpy(piecebox, starts[falltype - 1], 16);
}

void place() {
    for (uint8_t i = 0; i < 4; i++)
        for (uint8_t j = 0; j < 4; j++) {
            if (y >= height - j)
                continue;
            if (piecebox[i + 4 * j] == E)
                continue;

            field[x + i + (y + j) * width] = piecebox[i + 4 * j];
        }
}

// Verification fin de partie

bool loss() {
    for (uint8_t i = 0; i < width; i++)
        if (field[i] != E)
            return true;

    return false;
}

// Nettoyer la ligne en cas de ligne complete

void clearline() {
    uint8_t l;
    uint8_t lines = 0;

    for (l = 0; l < height; l++) {
        bool line = true;
        for (uint8_t i = 0; i < width; i++) {
            if (field[i + width * l] != E)
                continue;
            line = false;
            break;
        }
        if (line)
            lines++;

        if (lines && !line)
            break;
    }

    for (l; l > lines; l--) {
        for (uint8_t i = 0; i < width; i++) {
            field[i + (l - 1) * width] = field[i + (l - 1 - lines) * width];
        }
    }
    score++;
}

bool intersect(uint8_t temp[], int8_t xoff, int8_t yoff) {
    for (int8_t i = 0; i < 4; i++)
        for (int8_t j = 0; j < 4; j++) {
            if (temp[i + 4 * j] == E)
                continue;
            if (i + x + xoff < 0)
                return true;
            if (i + x + xoff >= width)
                return true;
            if (y + yoff + j >= height)
                return true;
            if (field[x + xoff + i + (y + yoff + j) * width] != E)
                return true;
        }
    return false;
}

bool bottom() {
    return intersect(piecebox, 0, 1);

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            if (piecebox[i + 4 * j] == E)
                continue;
            if (j + y + 1 == height)
                return true;
            if (field[x + i + width * (y + j + 1)] != E)
                return true;
        }
        return false;
    }
    // ----------------------------------------------------------------
}

void droptick() {
    if (bottom()) {
        if (droptimer++ < 4)
            return;
        droptimer = 0;
        place();
        clearline();
        spawn();
        return;
    }

    droptimer = 0;

    y++;
}


void rotater(uint8_t temp[]) {
    switch (falltype) {
        case I:
            for (uint8_t i = 0; i < 4; i++)
                for (uint8_t j = 0; j < 4; j++)
                    temp[ri[i][(j + 1) % 4]] = piecebox[ri[i][j]];
            break;
        default:
            for (uint8_t i = 0; i < 2; i++)
                for (uint8_t j = 0; j < 4; j++)
                    temp[rr[i][(j + 1) % 4]] = piecebox[rr[i][j]];

            temp[5] = piecebox[5];
    };
}

void rotatel(uint8_t temp[]) {
    switch (falltype) {
        case I:
            for (uint8_t i = 0; i < 4; i++)
                for (uint8_t j = 0; j < 4; j++)
                    temp[ri[i][j]] = piecebox[ri[i][(j + 1) % 4]];
            break;
        default:
            for (uint8_t i = 0; i < 2; i++)
                for (uint8_t j = 0; j < 4; j++)
                    temp[rr[i][j]] = piecebox[rr[i][(j + 1) % 4]];

            temp[5] = piecebox[5];
    };
}


void rotate(bool right) {
    if (falltype == E || falltype == O)
        return;
    uint8_t temp[16];

    memset(temp, E, 16);

    if (right)
        rotater(temp);
    else
        rotatel(temp);

    uint8_t count = 0;
    uint8_t rindex = (4 + rstate - !right) % 4;
    int8_t rdir = !!right - !right;

    int8_t *b;

    if (falltype == I)
        b = (int8_t *) bi;
    else
        b = (int8_t *) br;

    if (intersect(temp, 0, 0)) {
        while (intersect(temp, b[rindex * 8 + count * 2] * rdir, b[rindex * 8 + count * 2 + 1] * rdir) && count < 4)
            count++;

        if (count >= 4)
            return;

        x += b[rindex * 8 + count * 2] * rdir;
        y += b[rindex * 8 + count * 2 + 1] * rdir;
    }

    memcpy(piecebox, temp, 16);
    rstate = (rstate + rdir + 4) % 4;
}

void move(int8_t direction) {
    if (intersect(piecebox, direction, 0))
        return;

    droptimer = 0;
    x += direction;
}

int sendDataToServer(char *name, int score)
{
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

int main(int argc, char *argv[]) {

    if (argc != 2)
    {
        printf("Usage : Programme.exe nom\n");
        return 1;
    }
    name = argv[1]; //nom du joueur
    SDL_Window *win;
    SDL_Renderer *ren;
    bool running = true;
    SDL_Event event;

    uint32_t target = SDL_GetTicks();
    srand(time(0));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("%s", SDL_GetError());
        return 1;
    }

    SDL_CreateWindowAndRenderer(cellwidth * width, cellwidth * height, 0, &win, &ren);

    spawn();
    while (running) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
//Si l'utilisateur a cliqué sur la croix de fermeture
                    running = 0;
                    break;

                    //Si l'utilisateur appuie sur une touche
                
                    //Si l'utilisateur appuie sur la touche échap

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_LEFT)
                        move(-1);
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        move(1);
                    if (event.key.keysym.sym == SDLK_UP)
                        rotate(true);
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        if (bottom())
                            droptimer = 4;
                        else
                            while (!bottom())
                                droptick();

                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = 0;
                    break;
            }
        }

        SDL_SetRenderDrawColor(ren, cmap[0].r, cmap[0].g, cmap[0].b, cmap[0].a);
        SDL_RenderClear(ren);

        for (uint8_t i = 0; i < width; i++) {
            SDL_Rect r = {cellwidth * i, 0, cellwidth, cellwidth};
            for (uint8_t j = 0; j < height; j++) {
                SDL_Colour c = cmap[field[i + j * width]];
                SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
                SDL_RenderFillRect(ren, &r);
                r.y += cellwidth;
            }
        }

        for (uint8_t i = 0; i < 4; i++) {
            if (i < -x || x + i >= width)
                continue;
            SDL_Rect r = {cellwidth * (i + x), y * cellwidth, cellwidth, cellwidth};
            for (uint8_t j = 0; j < 4; j++, r.y += cellwidth) {
                if (y + j >= height)
                    continue;
                if (piecebox[i + 4 * j] == E)
                    continue;
                SDL_Colour c = cmap[piecebox[i + 4 * j]];
                SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, 200);
                SDL_RenderFillRect(ren, &r);
            }
        }

        SDL_SetRenderDrawColor(ren, cmap[0].r, cmap[0].g, cmap[0].b, cmap[0].a);

        for (uint8_t i = 0; i < width - 1; i++)
            SDL_RenderDrawLine(ren, (i + 1) * cellwidth, 0, (i + 1) * cellwidth, height * cellwidth);
        for (uint8_t j = 0; j < height - 1; j++)
            SDL_RenderDrawLine(ren, 0, (j + 1) * cellwidth, width * cellwidth, (j + 1) * cellwidth);

        int8_t offset = 0;

        while (!intersect(piecebox, 0, offset++));
        offset -= 2;

        for (uint8_t i = 0; i < 4; i++) {
            if (i < -x || x + i >= width)
                continue;
            SDL_Rect r = {cellwidth * (i + x), (y + offset) * cellwidth, cellwidth, cellwidth};
            for (uint8_t j = 0; j < 4; j++, r.y += cellwidth) {
                if (y + offset + j >= height)
                    continue;
                if (piecebox[i + 4 * j] == E)
                    continue;
                SDL_Colour c = cmap[piecebox[i + 4 * j]];
                SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, 200);
                SDL_RenderDrawRect(ren, &r);
            }
        }

        SDL_RenderPresent(ren);

        if (SDL_GetTicks() > target) {
            droptick();
            target = SDL_GetTicks() + 100;
            if (loss()) {
                if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Vous avez perdu HAHAHAHAHA",
                                             "GAME OVER\nRetente ta chance ;) !", win) != 0)
                    SDL_Log("%s", SDL_GetError());

                sendDataToServer(name , score);


                char* data = "test98765-test2456"; // variable à envoyer à Menu.exe
                char command[500];
                sprintf(command, "start menu2.exe %s %s", name, data);
                system(command);

                running = false;

            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);


}