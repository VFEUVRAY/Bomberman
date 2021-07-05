/*
** ETNA PROJECT, 30/06/2021 by feuvra_v
** debug
** File description:
**      some debug functions
*/

#include "../include/game.h"

void debug_display_player_coords(const player_object_t *player) {
    my_putstr("DEBUG: player_cords: (");
    my_putnbr(player->positionRect.x);
    my_putchar(';', 1);
    my_putnbr(player->positionRect.y);
    my_putstr(")\n");
}

void debug_reset_player_pos(player_object_t *player) {
	player->positionRect.x = 30;
	player->positionRect.y = 30;
}