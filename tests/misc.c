/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** misc
** File description:
**      random useful functions
*/

#include "game.h"

static strfunc_t strfuncs[2] = {&my_putstr, &my_puterr};

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


/**
 * Convienient func to output string arrays, only use to output on standard output
 * or standard error output, will modify later, PUT NULL AT END OF ARRAY
 * */

void    my_putCharArray(char const **array, char const fd)
{
    size_t i = 0;

    if (fd < 1 || fd > 2) {
        my_puterr("ERROR my_putCharArray: use only to write on standard ouput (fd == 1) or standard error output (fd == 2)");
        return ;
    }
    while (array[i]) {
        strfuncs[fd-1](array[i]);
        i++;
    }
}