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

typedef void (*strfunc_t) (char const *);

typedef struct game_object_s {
    SDL_Texture*    oTexture;
    SDL_Rect        positionRect;
} game_object_t;

typedef struct game_s {
    SDL_Point       screenSize; /*coords with x y, will contain screen size*/
    SDL_Window*     pWindow;    /*struct pointer containing window*/
    SDL_Renderer*   pRenderer;  /*struct that will interact with graphical component of pc*/

    SDL_Texture* pTexPlayer;
    game_object_t   pPlayer;
    game_object_t   pMap;
} game_t;


/*game related*/
game_t  *game_init();
void    game_destroy(game_t *game);
void    game_draw(game_t *game);
void    object_init(game_object_t *object, int const x, int const y, int const w, int const h);

/*misc*/
int     my_strlen(char const *str);
void    my_putstr(char const *str);
void    my_puterr(char const *str);
void    my_putchar(char const c, char const fd);
void    my_putCharArray(char const **array, char const fd);

/* globals used to streamline error checking */
int INITIALIZING_ERROR_CHECK;

#endif /* GAME_H */