/*
** ETNA PROJECT, 20/06/2021 by feuvra_v
** object_initializer
** File description:
**      some convenience to initialize game objects with images
*/

#include "../include/game.h"

int *BOMBERMAN_BASE_PLAYERS_POS[8] = {(int []){30, 30}, (int []){580, 30}, (int []){30, 420}, (int []){580, 420}};

char const **BOMBERMAN_PLAYER_SHEET_PATHS =  (char const *[]){"./assets/PlayerDummySheet.png",
                                     "./assets/PlayerDummySheet2.png",
                                     "./assets/PlayerDummySheet3.png",
                                     "./assets/PlayerDummySheet4.png"};

SDL_Texture *create_texture(SDL_Renderer *renderer, char const *path)
{
    SDL_Texture *texture = NULL;
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        my_putCharArray((char const *[]){"Could not open Player Image:", IMG_GetError(), "\n", NULL}, 2);
        return (NULL);
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        my_putCharArray((char const *[]){"Could create texture from image generated surface:", SDL_GetError(), "\n", NULL}, 2);
        return (NULL);
    }
    SDL_FreeSurface(surface);
    return (texture);
}

void object_init(game_object_t *object, int const x, int const y, int const w, int const h)
{
    object->positionRect.x = x;
    object->positionRect.y = y;
    object->positionRect.w = w;
    object->positionRect.h = h;
}

/*initialize with default position, then coordinaites of standard idle sprite in PlayerSheet*/
int player_init(player_object_t *player, int player_number, SDL_Renderer *renderer)
{
    if (player_number > 4) {
        player->alive = 0;
        return 0;
    }
    player->oTexture = create_texture(renderer, BOMBERMAN_PLAYER_SHEET_PATHS[player_number]);
    if (!player->oTexture)
        return (0);
    player->positionRect.x = BOMBERMAN_BASE_PLAYERS_POS[player_number][0];
    player->positionRect.y = BOMBERMAN_BASE_PLAYERS_POS[player_number][1];
    player->positionRect.w = 30;
    player->positionRect.h = 30;

    player->spriteRect.x = 270;
    player->spriteRect.y = 0;
    player->spriteRect.w = 30;
    player->spriteRect.h = 30;

    player->sheetLoopIndex = 0;
    player->alive = 1;

    player->directionKeyHoldMem[0] = player->directionKeyHoldMem[1] = player->directionKeyHoldMem[2] = player->directionKeyHoldMem[3] = 0;
    return (1);
}
