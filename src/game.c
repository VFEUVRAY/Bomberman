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

    //check if memory was allocated properly
    if (!game){
        my_puterr("Error while allocating memory for game structure");
        return (NULL);
    }

    //Initialisation des modules nécessaires
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        my_puterr("Could not Initialize SDL VIDEO module:");
        my_puterr(SDL_GetError());
        my_putchar('\n', 2);
        game_destroy(game);
        return (NULL);
    }

    game->screenSize.x = 640;
    game->screenSize.y = 480;
    return (game);
}

/**
 * All about destroying structure and closing SDL modules
 * */

void    game_destroy(game_t *game)
{
    //close SDL modules
    SDL_Quit();
    free(game);
}

