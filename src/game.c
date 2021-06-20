/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** game
** File description:
**      game specific functions
*/

#include "../include/game.h"

/**
 * will initiate game + SDL
 **/

game_t  *game_init()
{
    game_t  *game = NULL;
    game = malloc(sizeof(game_t));

    /*check if memory was allocated properly*/
    if (!game){
        my_puterr("Error while allocating memory for game structure\n");
        return (NULL);
    }

    /*Initialising game structures*/
    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pRenderer = NULL;
    game->pWindow = NULL;
    game->pTexPlayer = NULL;
    game->pPlayer.oTexture = NULL;
    object_init(&game->pPlayer, game->screenSize.x / 2, game->screenSize.y / 2, 40, 30);
    /*
    game->pPlayer.positionRect.x = ;
    game->pPlayer.positionRect.y = ;
    game->pPlayer.positionRect.w = ;
    game->pPlayer.positionRect.h = 30;
    */

    /*Initialisation des modules nécessaires*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        my_puterr("Could not Initialize SDL VIDEO module:");
        my_puterr(SDL_GetError());
        my_putchar('\n', 2);
        game_destroy(game);
        return (NULL);
    }


    game->pWindow = SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED,
                            game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN); /*(title, size x, size y, pos x, pos y, some flags (ex fullscreen, borderless etc..))*/
    if (!game->pWindow) {
        my_putCharArray((char const *[]){"Could not Initialize SDL Window:", SDL_GetError(), "\n"}, 2);
        game_destroy(game);
        return (NULL);
    }
    game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!game->pRenderer) {
        my_putCharArray((char const *[]){"Could not Initialize SDL Renderer:", SDL_GetError(), "\n"}, 2);
        game_destroy(game);
        return (NULL);
    }

    /*loading a texture*/
    /*IMG_Init(IMG_INIT_PNG);*/
    SDL_Surface* surfacePlayer = IMG_Load("./assets/player.png");
    if (!surfacePlayer) {
        my_putCharArray((char const *[]){"Could not open Player Image:", IMG_GetError(), "\n"}, 2);
        game_destroy(game);
        return (NULL);
    }
    game->pPlayer.oTexture = SDL_CreateTextureFromSurface(game->pRenderer, surfacePlayer);
    if (!game->pPlayer.oTexture) {
        my_putCharArray((char const *[]){"Could create texture from image generated surface:", SDL_GetError(), "\n"}, 2);
        game_destroy(game);
        return (NULL);
    }
    SDL_FreeSurface(surfacePlayer);
    return (game);
}

/**
 * All about destroying structure and closing SDL modules
 * */

void    game_destroy(game_t *game)
{
    /*close SDL modules*/
    if (game) {
        if (game->pTexPlayer)
            SDL_DestroyTexture(game->pTexPlayer);
        if (game->pRenderer)
            SDL_DestroyRenderer(game->pRenderer);
        if (game->pWindow)
            SDL_DestroyWindow(game->pWindow);
        free(game);
    }
    SDL_Quit();
}

/**
 * game display funcs
 * */

void    game_draw(game_t *game)
{
    /*cleanup screen by filling with black*/
    SDL_SetRenderDrawColor(game->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(game->pRenderer);

    /*display player*/
    SDL_RenderCopy(game->pRenderer, game->pPlayer.oTexture, NULL, &game->pPlayer.positionRect);

    /*preset render*/
    SDL_RenderPresent(game->pRenderer);

    SDL_Delay(2000);
    
    game->pPlayer.positionRect.h = 80;

    SDL_RenderCopy(game->pRenderer, game->pPlayer.oTexture, NULL, &game->pPlayer.positionRect);

    SDL_RenderPresent(game->pRenderer);

    SDL_Delay(2000);

}