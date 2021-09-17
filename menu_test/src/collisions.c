/*
** ETNA PROJECT, 13/07/2021 by feuvra_v
** client
** File description:
**      basic client for multiclient server
*/

#include "../include/game.h"

int BOMBERMAN_BASE_WALL_POS[16][2] = {   (int []){90, 90}, (int []){90, 180}, (int []){90, 270}, (int []){90, 360},
                                        (int []){150, 90}, (int []){150, 180}, (int []){150, 270}, (int []){150, 360},
                                        (int []){210, 90}, (int []){210, 180}, (int []){210, 270}, (int []){210, 360},
                                        (int []){270, 90}, (int []){270, 180}, (int []){270, 270}, (int []){270, 360}};
int const BOMBER_WALL_NB = 16;


void    check_collisions(SDL_Rect *coords)
{
    if (coords->x < 30)
        coords->x = 30;
    else if (coords->x > 580)
        coords->x = 580;
    if (coords->y < 30)
        coords->y = 30;
    else if (coords->y > 420)
        coords->y = 420;
}

bool_t check_walls(object_queue_t *walls, SDL_Rect *new_coords)
{
    object_queue_t *current_wall = walls;
    SDL_Rect *wall_coords;

    while (current_wall) {
        wall_coords = &current_wall->object.positionRect;
        if ((new_coords->x > wall_coords->x && new_coords->x < (wall_coords->x + wall_coords->w))
            && (new_coords->y > wall_coords->y && new_coords->y < (wall_coords->y + wall_coords->h))) {
            my_putstr("checking walls \n");
            return (0);
            }
        current_wall = current_wall->next;
    }
    return (1);
}

object_queue_t *create_walls()
{
    object_queue_t *walls = malloc(sizeof(object_queue_t));
    object_queue_t *first = walls;
    int i = 0;
    if (!walls)
        return (NULL);
    while (i < BOMBER_WALL_NB) {
        object_init(&walls->object, BOMBERMAN_BASE_WALL_POS[i][0], BOMBERMAN_BASE_WALL_POS[i][1],
                    30, 30);
        walls->object.spriteRect.x = 0;
        walls->object.spriteRect.y = 0;
        walls->object.spriteRect.h = 30;
        walls->object.spriteRect.w = 30;
        walls->display = 1;
        if (i != BOMBER_WALL_NB - 1) {
            walls->next = malloc(sizeof(object_queue_t));
            walls = walls->next;
        }
        ++i;
    }
    walls->next = NULL;
    return (first);
}



/*
void check_walls_players(object_queue_t *walls, SDL_Rect *old_coords, SDL_Rect *new_coords)
{

}
*/