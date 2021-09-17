/*
** ETNA PROJECT, 21/06/2021 by feuvra_v
** bombs
** File description:
**      bomb queue related functions
*/

#ifndef GAME_H
# define GAME_H
# include "../include/game.h"
#endif

void            init_bombs(bomb_queue_t **queue, SDL_Rect *coords)
{
    (*queue) = malloc(sizeof(bomb_queue_t));
    (*queue)->bomb.count = 60;
    (*queue)->bomb.positionRect = *coords;
    (*queue)->bomb.spriteRect.x = 0;
    (*queue)->bomb.spriteRect.y = 0;
    (*queue)->bomb.spriteRect.w = 30;
    (*queue)->bomb.spriteRect.h = 30;
    (*queue)->next = NULL;
}

void            add_bomb(bomb_queue_t **queue, SDL_Rect *coords)
{
    if (!(*queue)) {
        init_bombs(queue, coords);
        return ;
    }
    bomb_queue_t *first = *queue;
    while ((*queue)->next)
        *queue = (*queue)->next;
    (*queue)->next = malloc(sizeof(bomb_queue_t));
    *queue = (*queue)->next;
    (*queue)->bomb.count = 60;
    (*queue)->bomb.positionRect = *coords;
    (*queue)->bomb.spriteRect.x = 0;
    (*queue)->bomb.spriteRect.y = 0;
    (*queue)->bomb.spriteRect.w = 30;
    (*queue)->bomb.spriteRect.h = 30;
    (*queue)->next = NULL;
    *queue = first;
}

bomb_queue_t    *pop_bomb(bomb_queue_t *queue)
{
    if (queue) {
        bomb_queue_t *prev = queue;
        queue = queue->next;
        free(prev);
    }

    return (queue);
}

void            tick_bombs(bomb_queue_t **queue)
{
    bomb_queue_t    *first = *queue;
    while (*queue) {
        (*queue)->bomb.count -= 1;
        if (((*queue)->bomb.count % 3) == 0)
            (*queue)->bomb.spriteRect.x = ((*queue)->bomb.spriteRect.x + 30)  % 150;
        if (!(*queue)->bomb.count){
            first = (*queue)->next;
            *queue = pop_bomb(*queue);
        }
        if (*queue)
            *queue = (*queue)->next;
    }
    *queue = first;
}

void    free_queue(bomb_queue_t **queue)
{
    bomb_queue_t *temp;
    while (*queue) {
        temp = *queue;
        *queue = (*queue)->next;
        free(temp);
    }
}