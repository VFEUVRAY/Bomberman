/*
** ETNA PROJECT, 20/06/2021 by feuvra_v
** object_initializer
** File description:
**      some convenience to initialize game objects with images
*/

#include "../include/game.h"



void object_init(game_object_t *object, int const x, int const y, int const w, int const h)
{
    object->positionRect.x = x;
    object->positionRect.y = y;
    object->positionRect.w = w;
    object->positionRect.h = h;
}