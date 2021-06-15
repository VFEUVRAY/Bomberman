/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** game
** File description:
**      yo mec
*/

#ifndef GAME_H
# define GAME_H

# include <SDL2/SDL.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct game_s {
    SDL_Point       screenSize; //coords with x y, will contain screen size
    SDL_Window*     pWindow;    //struct pointer containing window
    SDL_Renderer*   pRenderer;  //struct that will interact with graphical component of pc
} game_t;


//game related
game_t  *game_init();
void    game_destroy(game_t *game);

//misc
int     my_strlen(char const *str);
void    my_putstr(char const *str);
void    my_puterr(char const *str);
void    my_putchar(char const c, char const fd);


#endif /* GAME_H */