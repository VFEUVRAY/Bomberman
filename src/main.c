/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** main
** File description:
**      main for bomberman training ting
*/

#include "../include/game.h"

int INITIALIZING_ERROR_CHECK = 0;
int WALK_LOOP_TICK = 0;
SDL_Rect RECT_LOPP;

int main()
{
    game_t  *game = game_init();
    int quit = 0;
    RECT_LOPP.x = 0;
    RECT_LOPP.y = 0;
    RECT_LOPP.h = 30;
    RECT_LOPP.w = 30;
    if (game){
        my_putstr("SDL Initiated OK\n");
    }
    while (!quit) {
        game_draw(game);
        quit = game_event(game);
        SDL_Delay(16);
    }
    game_destroy(game);
    return (0);
}
