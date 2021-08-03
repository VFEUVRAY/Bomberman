/*
** ETNA PROJECT, 20/06/2021 by feuvra_v
** object_initializer
** File description:
**      some convenience to initialize game objects with images
*/

#include "../include/game.h"

int BOMBERMAN_BASE_PLAYERS_POS[8] = {30, 30, 610, 30, 30, 450, 610, 450};

void object_init(game_object_t *object, int const x, int const y, int const w, int const h)
{
    object->positionRect.x = x;
    object->positionRect.y = y;
    object->positionRect.w = w;
    object->positionRect.h = h;
}

/*initialize with default position, then coordinaites of standard idle sprite in PlayerSheet*/
void player_init(player_object_t *player, int player_number)
{
    player->positionRect.x = BOMBERMAN_BASE_PLAYERS_POS[player_number - 1];
    player->positionRect.y = BOMBERMAN_BASE_PLAYERS_POS[player_number];
    player->positionRect.w = 30;
    player->positionRect.h = 30;

    player->spriteRect.x = 270;
    player->spriteRect.y = 0;
    player->spriteRect.w = 30;
    player->spriteRect.h = 30;

    player->sheetLoopIndex = 0;
}
