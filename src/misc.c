/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** misc
** File description:
**      random useful functions
*/

#include "game.h"

int     my_strlen(char const *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}

void    my_puterr(char const *str)
{
    write(2, str, my_strlen(str));
}

void    my_putchar(char const c, char const fd)
{
    write(fd, &c, 1);
}