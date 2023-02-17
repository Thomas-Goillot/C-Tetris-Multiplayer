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


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

char* name;
// ------------------------------------------------------------------------------
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage : Programme.exe nom\n");
        return 1;
    }
    name = argv[1];            // nom du joueur
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
    window = SDL_CreateWindow("Mon Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    font = TTF_OpenFont("arial.ttf",50);
    if (font == NULL)
    {
        printf("Erreur de chargement de la police: %s\n", TTF_GetError());
        return 1;
    }

    //Boucle principale
    while (running)
    {


        //Dessiner le menu
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Dessiner le bouton jouer
        SDL_Color color = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "Jouer", color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect Play; //create a rect

        if (SDL_QueryTexture(texture, NULL, NULL, &Play.w, &Play.h) != 0)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            printf("erreur texture");
        }

        Play.x = (WINDOW_WIDTH - Play.w) / 2;  //controls the rect's x coordinate
        Play.y = (WINDOW_HEIGHT - Play.h) / 2; // controls the rect's y coordinte
//        SDL_Rect rect = {300, 200, 200, 100};
        SDL_RenderCopy(renderer, texture, NULL, &Play);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        //Dessiner le bouton Quitter
        surface = TTF_RenderText_Solid(font, "Quitter", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect Quitter; //create a rect
        if (SDL_QueryTexture(texture, NULL, NULL, &Quitter.w, &Quitter.h) != 0)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            printf("erreur texture");
        }

        Quitter.x = (WINDOW_WIDTH - Quitter.w) / 2;  //controls the rect's x coordinate
        Quitter.y = (WINDOW_HEIGHT -Quitter.h) / 2+100; // controls the rect's y coordinte
        SDL_RenderCopy(renderer, texture, NULL, &Quitter);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        //Mettre à jour le renderer
        SDL_RenderPresent(renderer);
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
//                            jouer();
                            system("start Jeu.exe");
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Vérifie si l'utilisateur a cliqué sur le bouton jouer
                    if (event.button.x >= Play.x && event.button.x <= Play.x + Play.w && event.button.y >= Play.y && event.button.y <= Play.y + Play.h) {
//                        jouer();

                        //demarre jeu.exe avec name en parametre
                        char command[100];
                        sprintf(command, "start Jeu.exe %s", name);
                        system(command);
                        int data = atoi(argv[1]);
                        printf("Data from client.c: %d\n", data);
                    }
                     //Vérifie si l'utilisateur a cliqué sur le bouton quitter
                    else if (event.button.x >= Quitter.x && event.button.x <= Quitter.x + Quitter.w && event.button.y >= Quitter.y &&event.button.y <=Quitter.y + Quitter.h) {
                     running = 0;
                     break;
                    }

            }
        }
    }

    //Libérer les ressources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
