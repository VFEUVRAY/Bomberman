/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** main
** File description:
**      main for bomberman training ting
*/

#include "../include/game.h"

int INITIALIZING_ERROR_CHECK = 0;

int main()
{
    game_t  *game = game_init();
    if (game){
        my_putstr("SDL Initiated OK\n");
        game_draw(game);
        game_destroy(game);
    }
    return (0);
}
