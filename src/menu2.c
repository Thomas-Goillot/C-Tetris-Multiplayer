
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_audio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_PLAYERS 5
#define MAX_NAME_LENGTH 50

void splitPlayers(char *str, char players[MAX_PLAYERS][2][MAX_NAME_LENGTH])
{
    int i = 0, j = 0, k = 0, l = 0;
    char name[MAX_NAME_LENGTH];

    while (str[i] != '\0' && k < MAX_PLAYERS)
    {
        if (str[i] != '-')
        {
            name[j] = str[i];
            j++;
        }
        else
        {
            name[j] = '\0';
            j = 0;
            strncpy(players[k][l], name, MAX_NAME_LENGTH);
            l++;
            if (l >= 2)
            {
                k++;
                l = 0;
            }
        }
        i++;
    }

    // Ajouter le dernier joueur
    name[j] = '\0';
    strncpy(players[k][l], name, MAX_NAME_LENGTH);
}

char *name;
char players[MAX_PLAYERS][2][MAX_NAME_LENGTH];
// ------------------------------------------------------------------------------
int main(int argc, char *argv[])
{

    name = argv[1];                // nom du joueur
    splitPlayers(argv[2], players);   // tableau de string contenant le nom et le score des joueurs
    SDL_Window *window = NULL;     // La fenêtre que nous allons utiliser
    SDL_Renderer *renderer = NULL; // Le rendu que nous allons utiliser
    TTF_Font *font = NULL;         // La police que nous allons utiliser
    SDL_Event event;               // Gestion des événements
    int running = 1;               // variable pour boucle principale

    // initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        return 1;
    }

    // initialisation de la TTF
    if (TTF_Init() < 0)
    {
        printf("Erreur d'initialisation de la TTF: %s\n", TTF_GetError());
        return 1;
    }

    // création de la fenêtre
    window = SDL_CreateWindow("Mon Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        return 1;
    }

    // création du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Erreur de création du rendu: %s\n", SDL_GetError());
        return 1;
    }

    // chargement de la police
    font = TTF_OpenFont("arial.ttf", 50);
    if (font == NULL)
    {
        printf("Erreur de chargement de la police: %s\n", TTF_GetError());
        return 1;
    }

    // Boucle principale
    while (running)
    {

        // Dessiner le menu
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set the text color
        SDL_Color color = {255, 255, 255, 255};

        char *text_array[] = {0};
            // Define the array of text to be displayed
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i][0][0] != '\0')
            {
                char *text = malloc(100);
                sprintf(text, "%s - %s", players[i][0], players[i][1]);
                text_array[i] = text;
            }
        }


        // Create a surface for the text
        SDL_Surface *surface = NULL;

        // Create a texture for the text
        SDL_Texture *texture = NULL;

        // Define the text position
        SDL_Rect Play;
        Play.x;
        Play.y = 10;

        // Loop through the array of text and display each line
        for (int i = 0; i < 5; i++) {

            // Render the text to a surface
            surface = TTF_RenderText_Solid(font, text_array[i], color);
            if (surface == NULL) {
                SDL_Log("Unable to render text: %s", TTF_GetError());
                return 1;
            }

            // Create a texture from the surface
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == NULL) {
                SDL_Log("Unable to create texture: %s", SDL_GetError());
                return 1;
            }

            // Get the size of the text texture
            int text_width = 0;
            int text_height = 0;
            SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

            // Set the text position
            Play.w = text_width;
            Play.h = text_height;

            // Copy the texture to the renderer
            SDL_RenderCopy(renderer, texture, NULL, &Play);

            // Free the surface and texture
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

            // Increment the text position for the next line
            Play.x = ((WINDOW_WIDTH - Play.w) / 2);
            Play.y += text_height + 10;
        }




        // Dessiner le bouton Quitter
        surface = TTF_RenderText_Solid(font, "Retour", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect Quitter; // create a rect
        if (SDL_QueryTexture(texture, NULL, NULL, &Quitter.w, &Quitter.h) != 0)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            printf("erreur texture");
        }

        Quitter.x = (WINDOW_WIDTH - Quitter.w) / 2;        // controls the rect's x coordinate
        Quitter.y = (WINDOW_HEIGHT - Quitter.h) / 2 + 100; // controls the rect's y coordinte
        SDL_RenderCopy(renderer, texture, NULL, &Quitter);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        // Mettre à jour le renderer
        SDL_RenderPresent(renderer);
        // Traiter les événements
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                // Si l'utilisateur a cliqué sur la croix de fermeture
                running = 0;
                break;
            case SDL_KEYDOWN:
                // Si l'utilisateur appuie sur une touche
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    // Si l'utilisateur appuie sur la touche échap
                    running = 0;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Vérifie si l'utilisateur a cliqué sur le bouton quitter
                if (event.button.x >= Quitter.x && event.button.x <= Quitter.x + Quitter.w && event.button.y >= Quitter.y && event.button.y <= Quitter.y + Quitter.h)
                {
                    char command[500];
                    sprintf(command, "start menu.exe %s", name);
                    system(command);
                    running = 0;
                    break;
                }
            }
        }
    }

    // Libérer les ressources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
