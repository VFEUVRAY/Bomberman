#include "../include/game.h"


void player_init(player_t* sPlayer) {

    //Position sur l'axe x et y,
    //Largeur et Hauteur de la Texture
    sPlayer->playerPositionRect.x = 20;
    sPlayer->playerPositionRect.y = 64;
    sPlayer->playerPositionRect.w = 30;
    sPlayer->playerPositionRect.h = 30;
    printf("On initialise les parametres de position et de taille du player\n");
}

