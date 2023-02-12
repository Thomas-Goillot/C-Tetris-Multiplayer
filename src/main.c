/* Déclaration des fonctions */
void jouer(); // Fonction qui lance le jeu
//Le point d'entrée du programme
/*
Auteur: Ibrahim OUBIHI / Thomas Goillot / Joshua TANG TONG HI
Date : rendu du 01/02/2023
Sujet : Réaliser un Tetris en langage C a l'aide de la bibliotheque graphique SDL
*/

/*
TODO :
- ajouter comptage de points
- ajouter une musique d'ambiance
- ajouter une interface d'accueil
- ajouter un systeme de sauvgarde de points en reseau
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_audio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

const int8_t bi[4][4][2] =
        {
                {{-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
                {{-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
                {{2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
                {{1, 0}, {-2, 0}, {1, -2}, {-2, 1}}};

const int8_t br[4][4][2] =
        {
                {{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
                {{1, 0}, {1, -1}, {0, 2}, {1, 2}},
                {{1, 0}, {1, 1}, {0, -2}, {1, -2}},
                {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}};

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
                {1, 6, 9, 4}};

const uint8_t height = 40;
const uint8_t width = 10;
const uint8_t cellwidth = 20;

enum TETROMINOS
{
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
                {40, 40, 40, 255},
                {0, 255, 255, 255},
                {255, 255, 0, 255},
                {255, 0, 255, 255},
                {0, 255, 0, 255},
                {255, 0, 0, 255},
                {0, 0, 255, 255},
                {255, 200, 0, 255}};

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

void nouvelle_forme()
{
    for (uint8_t i = 0; i < 7; i++)
        forme[i] = i + 1;

    for (uint8_t i = 6; i > 0; i--)
    {
        uint8_t t;
        uint8_t num = rand() % (i + 1);

        t = forme[i];
        forme[i] = forme[num];
        forme[num] = t;
    }

    formecur = 0;
}

// apparition de la prochaine forme

void spawn()
{
    if (formecur >= 7)
        nouvelle_forme();

    falltype = forme[formecur++];

    x = 3;
    y = 0;
    rstate = 0;
    droptimer = 0;
    memcpy(piecebox, starts[falltype - 1], 16);
}

void place()
{
    for (uint8_t i = 0; i < 4; i++)
        for (uint8_t j = 0; j < 4; j++)
        {
            if (y >= height - j)
                continue;
            if (piecebox[i + 4 * j] == E)
                continue;

            field[x + i + (y + j) * width] = piecebox[i + 4 * j];
        }
}

// Verification fin de partie

bool loss()
{
    for (uint8_t i = 0; i < width; i++)
        if (field[i] != E)
            return true;

    return false;
}

// Nettoyer la ligne en cas de ligne complete

void clearline()
{
    uint8_t l;
    uint8_t lines = 0;
    // uint64_t score = 0;    //affichage du score

    for (l = 0; l < height; l++)
    {
        bool line = true;
        for (uint8_t i = 0; i < width; i++)
        {
            if (field[i + width * l] != E)
                continue;
            line = false;
            break;
        }
        if (line)
            lines++;

        if (lines && !line)
            break;
        // score++,
    }

    for (l; l > lines; l--)
    {
        for (uint8_t i = 0; i < width; i++)
        {
            field[i + (l - 1) * width] = field[i + (l - 1 - lines) * width];
        }
    }
}

bool intersect(uint8_t temp[], int8_t xoff, int8_t yoff)
{
    for (int8_t i = 0; i < 4; i++)
        for (int8_t j = 0; j < 4; j++)
        {
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

bool bottom()
{
    return intersect(piecebox, 0, 1);

    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
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

void droptick()
{
    if (bottom())
    {
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


void rotater(uint8_t temp[])
{
    switch (falltype)
    {
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

void rotatel(uint8_t temp[])
{
    switch (falltype)
    {
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


void rotate(bool right)
{
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
        b = (int8_t *)bi;
    else
        b = (int8_t *)br;

    if (intersect(temp, 0, 0))
    {
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

void move(int8_t direction)
{
    if (intersect(piecebox, direction, 0))
        return;

    droptimer = 0;
    x += direction;
}

// ------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //La fenêtre que nous allons utiliser
    SDL_Renderer *renderer = NULL; //Le rendu que nous allons utiliser
    TTF_Font *font = NULL; //La police que nous allons utiliser
    SDL_Event event; //Gestion des événements
    int running = 1; //variable pour boucle principale

    //initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }

    //initialisation de la TTF
    if (TTF_Init() < 0)
    {
        printf("Erreur d'initialisation de la TTF: %s\n", TTF_GetError());
        return 1;
    }

    //création de la fenêtre
    window = SDL_CreateWindow("Mon Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        return 1;
    }

    //création du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Erreur de création du rendu: %s\n", SDL_GetError());
        return 1;
    }

    //chargement de la police
    font = TTF_OpenFont("arial.ttf", 24);
    if (font == NULL)
    {
        printf("Erreur de chargement de la police: %s\n", TTF_GetError());
        return 1;
    }

    //Boucle principale
    while (running)
    {
        //Traiter les événements
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    //Si l'utilisateur a cliqué sur la croix de fermeture
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    //Si l'utilisateur appuie sur une touche
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            //Si l'utilisateur appuie sur la touche échap
                            running = 0;
                            break;
                        case SDLK_RETURN:
                            //Si l'utilisateur appuie sur la touche entrée
                            jouer();
                            break;
                    }
                    break;
            }
        }

        //Dessiner le menu
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Dessiner le bouton jouer
        SDL_Color color = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "Jouer", color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = {300, 200, 200, 100};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        //Dessiner le bouton Quitter
        surface = TTF_RenderText_Solid(font, "Quitter", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.x = 300;
        rect.y = 350;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        //Mettre à jour le renderer
        SDL_RenderPresent(renderer);
    }

    //Libérer les ressources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
void jouer()
{
    SDL_Window *win;
    SDL_Renderer *ren;
    bool running = true;

    uint32_t target = SDL_GetTicks();
    srand(time(0));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("%s", SDL_GetError());
        return 1;
    }

    SDL_CreateWindowAndRenderer(cellwidth * width, cellwidth * height, 0, &win, &ren);

    spawn();
    while (running)
    {

        // musique

        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8 *wavBuffer;
        SDL_LoadWAV("../music/Brulux-Benzema-_Clip-Officiel_.wav", &wavSpec, &wavBuffer, &wavLength);
        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
        SDL_PauseAudioDevice(deviceId, 0);

        // musique

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_LEFT)
                        move(-1);
                    if (e.key.keysym.sym == SDLK_RIGHT)
                        move(1);
                    if (e.key.keysym.sym == SDLK_UP)
                        rotate(true);
                    if (e.key.keysym.sym == SDLK_DOWN)
                    {
                        if (bottom())
                            droptimer = 4;
                        else
                            while (!bottom())
                                droptick();
                    }
            }
        }

        SDL_SetRenderDrawColor(ren, cmap[0].r, cmap[0].g, cmap[0].b, cmap[0].a);
        SDL_RenderClear(ren);

        for (uint8_t i = 0; i < width; i++)
        {
            SDL_Rect r = {cellwidth * i, 0, cellwidth, cellwidth};
            for (uint8_t j = 0; j < height; j++)
            {
                SDL_Colour c = cmap[field[i + j * width]];
                SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
                SDL_RenderFillRect(ren, &r);
                r.y += cellwidth;
            }
        }

        for (uint8_t i = 0; i < 4; i++)
        {
            if (i < -x || x + i >= width)
                continue;
            SDL_Rect r = {cellwidth * (i + x), y * cellwidth, cellwidth, cellwidth};
            for (uint8_t j = 0; j < 4; j++, r.y += cellwidth)
            {
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

        while (!intersect(piecebox, 0, offset++))
            ;
        offset -= 2;

        for (uint8_t i = 0; i < 4; i++)
        {
            if (i < -x || x + i >= width)
                continue;
            SDL_Rect r = {cellwidth * (i + x), (y + offset) * cellwidth, cellwidth, cellwidth};
            for (uint8_t j = 0; j < 4; j++, r.y += cellwidth)
            {
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

        if (SDL_GetTicks() > target)
        {
            droptick();
            target = SDL_GetTicks() + 100;
            if (loss())
            {
                if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Vous avez perdu HAHAHAHAHA", "GAME OVER\nRetente ta chance ;) !", win) != 0)
                    SDL_Log("%s", SDL_GetError());
                running = false;
            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
  


}