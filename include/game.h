/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** game
** File description:
**      yo mec
*/

#ifndef GAME_H
# define GAME_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/*Typdef for string output function pointers.
Is used for convenient multipurpose output function*
*/
typedef void (*strfunc_t) (char const *);
typedef char* const string_array_t;

typedef struct game_object_s {
    SDL_Texture*    oTexture;
    SDL_Rect        positionRect;
} game_object_t;


/* bomb object is different because it doesn't need to hold its own texture
also needs a count which will dictate when the object is to be deleted from linked list
*/
typedef struct bomb_object_s {
    SDL_Rect        positionRect;
    unsigned int    count;
} bomb_object_t;

/*Queue which will contain bombs*/

typedef struct bomb_queue_s {
    bomb_object_t bomb;
    struct bomb_object_s *next;
} bomb_queue_t;

/*General game structure, will hold information necessary for each rendering loops
Also data that might affect multiple redundant objects
*/
typedef struct game_s {
    SDL_Point       screenSize; /*coords with x y, will contain screen size*/
    SDL_Window*     pWindow;    /*struct pointer containing window*/
    SDL_Renderer*   pRenderer;  /*struct that will interact with graphical component of pc*/

    SDL_Texture*    pTexPlayer;
    SDL_Texture*    pBombTexture;
    game_object_t   pPlayer;
    game_object_t   pMap;
} game_t;


/*game related*/
game_t  *game_init();
void    game_destroy(game_t *game);
void    game_draw(game_t *game);
void    object_init(game_object_t *object, int const x, int const y, int const w, int const h);
int     game_event(game_t *game);
void    game_movePlayer(game_t *game, SDL_Keycode direction);

/*queue related*/
bomb_queue_t *pop_bomb(bomb_queue_t *queue);
void add_bomb(bomb_queue_t *queue, SDL_Rect *coords);

/*misc*/
int     my_strlen(char const *str);
void    my_putstr(char const *str);
void    my_puterr(char const *str);
void    my_putchar(char const c, char const fd);
void    my_putCharArray(char const **array, char const fd);

/* globals used to streamline error checking */
int WALK_LOOP_TICK;
SDL_Rect RECT_LOPP;
#endif /* GAME_H */