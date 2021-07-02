/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** main
** File description:
**      main for bomberman training ting
*/

#include "../include/game.h"

int main()
{
    game_t  *game = game_init();
    int quit = 0;
    if (game){
        my_putstr("SDL Initiated OK\n");
    }
    while (quit != 1) {
        game_draw(game);
        quit = game_event(game);
        game_movePlayer(game);
        SDL_Delay(16);
    }
    game_destroy(game);
    return (0);
}
