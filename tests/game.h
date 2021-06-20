/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** game
** File description:
**      yo mec
*/

#ifndef GAME_H
# define GAME_H

//# include <SDL2/SDL.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef void (*strfunc_t) (char const *);

/*misc*/
int     my_strlen(char const *str);
void    my_putstr(char const *str);
void    my_puterr(char const *str);
void    my_putchar(char const c, char const fd);
void    my_putCharArray(char const **array, char const fd);

#endif /* GAME_H */