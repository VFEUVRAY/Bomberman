/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** main
** File description:
**      main for bomberman training ting
*/
#ifndef GAME_H
# define GAME_H
# include "../include/game.h"
#endif

int main()
{
    game_t  *game = game_init();
    int quit = 0;
    if (!game){
        my_puterr("Game initialization fail, exiting with code 84\n");
        return (84);
    }
    my_putstr("SDL Initiated OK\n");
    while (quit != 1) {
        game_draw(game);
        quit = game_event(game);
        game_movePlayer(game);
        SDL_Delay(16);
    }
    game_destroy(game);
    return (0);
}
