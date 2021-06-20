/*
** ETNA PROJECT, 20/06/2021 by feuvra_v
** main
** File description:
**      testing some things outside of game format
*/

#include "game.h"

int main()
{
    my_putCharArray((char const *[]){"this ", "is ", "a test\n", NULL}, 1);
    my_putCharArray((char const *[]){"this is", "an error", " test\n", NULL}, 2);
    return (0);
}