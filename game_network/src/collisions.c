/*
** ETNA PROJECT, 13/07/2021 by feuvra_v
** client
** File description:
**      basic client for multiclient server
*/

#include "../include/game.h"

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
        printf("wall : %d %d %d %d\n", wall_coords->x, wall_coords->x + wall_coords->w, wall_coords->y, wall_coords->y + wall_coords->h);
        printf("char : %d %d\n", new_coords->x, new_coords->y);
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
    if (!walls)
        return (NULL);
    object_init(&walls->object, 150, 100, 400, 400);
    walls->next = NULL;
    return (walls);
}

/*
void check_walls_players(object_queue_t *walls, SDL_Rect *old_coords, SDL_Rect *new_coords)
{

}
*/