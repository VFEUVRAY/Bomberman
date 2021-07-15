/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** game
** File description:
**      game specific functions
*/

#include "../include/game.h"

/**
 * will initiate game + SDL
 **/

game_t  *game_init()
{
    game_t  *game = NULL;
    game = malloc(sizeof(game_t));

    /*check if memory was allocated properly*/
    if (!game){
        my_puterr("Error while allocating memory for game structure\n");
        return (NULL);
    }

    /*Initialising game structures*/
    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pRenderer = NULL;
    game->pWindow = NULL;
    game->pTexPlayer = NULL;
    game->pPlayer.oTexture = NULL;
    game->pBombTexture = NULL;
    game->pBombs = NULL;
    player_init(&game->pPlayer);
    object_init(&game->pMap, 0, 0, game->screenSize.x, game->screenSize.y);
    game->directionKeyHoldMem[0] = game->directionKeyHoldMem[1] = game->directionKeyHoldMem[2] = game->directionKeyHoldMem[3] = 0;
    game->bombKeyHoldCheck = 0;
    /*
    game->pPlayer.positionRect.x = ;
    game->pPlayer.positionRect.y = ;
    game->pPlayer.positionRect.w = ;
    game->pPlayer.positionRect.h = 30;
    */

    /*Initialisation des modules nécessaires*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        my_puterr("Could not Initialize SDL VIDEO module:");
        my_puterr(SDL_GetError());
        my_putchar('\n', 2);
        game_destroy(game);
        return (NULL);
    }


    game->pWindow = SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED,
                            game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN); /*(title, size x, size y, pos x, pos y, some flags (ex fullscreen, borderless etc..))*/
    if (!game->pWindow) {
        my_putCharArray((char const *[]){"Could not Initialize SDL Window:", SDL_GetError(), "\n", NULL}, 2);
        game_destroy(game);
        return (NULL);
    }
    game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!game->pRenderer) {
        my_putCharArray((char const *[]){"Could not Initialize SDL Renderer:", SDL_GetError(), "\n", NULL}, 2);
        game_destroy(game);
        return (NULL);
    }

    /*loading a texture*/
    /*IMG_Init(IMG_INIT_PNG);*/
    SDL_Surface* surfacePlayer = IMG_Load("./assets/PlayerDummySheet.png");
    if (!surfacePlayer) {
        my_putCharArray((char const *[]){"Could not open Player Image:", IMG_GetError(), "\n", NULL}, 2);
        game_destroy(game);
        return (NULL);
    }
    game->pPlayer.oTexture = SDL_CreateTextureFromSurface(game->pRenderer, surfacePlayer);
    if (!game->pPlayer.oTexture) {
        my_putCharArray((char const *[]){"Could create texture from image generated surface:", SDL_GetError(), "\n", NULL}, 2);
        game_destroy(game);
        return (NULL);
    }
    SDL_FreeSurface(surfacePlayer);
    surfacePlayer = IMG_Load("./assets/bombermap.jpg");
    if (!surfacePlayer) {
        my_putCharArray((char const *[]){"Could not open Map Image:", IMG_GetError(), "\n", NULL}, 2);
        game_destroy(game);
        return (NULL);
    }
    game->pMap.oTexture = SDL_CreateTextureFromSurface(game->pRenderer, surfacePlayer);
    SDL_FreeSurface(surfacePlayer);
    surfacePlayer = IMG_Load("./assets/BombSheet.png");
    if (!surfacePlayer) {
        my_putCharArray((char const *[]){"Could not open Bomb Image:", IMG_GetError(), "\n", NULL}, 2);
        game_destroy(game);
        return (NULL);
    }
    game->pBombTexture = SDL_CreateTextureFromSurface(game->pRenderer, surfacePlayer);
    SDL_FreeSurface(surfacePlayer);
    return (game);
}

/**
 * All about destroying structure and closing SDL modules
 * */

void    game_destroy(game_t *game)
{
    /*close SDL modules*/
    if (game) {
        if (game->pBombs)
            free_queue(&game->pBombs);
        if (game->pBombTexture)
            SDL_DestroyTexture(game->pBombTexture);
        if (game->pPlayer.oTexture)
            SDL_DestroyTexture(game->pPlayer.oTexture);
        if (game->pMap.oTexture)
            SDL_DestroyTexture(game->pMap.oTexture);
        if (game->pRenderer)
            SDL_DestroyRenderer(game->pRenderer);
        if (game->pWindow)
            SDL_DestroyWindow(game->pWindow);
        free(game);
    }
    SDL_Quit();
}

/**
 * game display funcs
 * */

void    game_draw(game_t *game)
{
    bomb_queue_t *currentBomb = game->pBombs;

    /*cleanup screen by filling with black*/
    SDL_SetRenderDrawColor(game->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(game->pRenderer);

    /*display player*/
    SDL_RenderCopy(game->pRenderer, game->pMap.oTexture, NULL, &game->pMap.positionRect);
    while (currentBomb) {
        SDL_RenderCopy(game->pRenderer, game->pBombTexture, &currentBomb->bomb.spriteRect, &currentBomb->bomb.positionRect);
        currentBomb = currentBomb->next;
    }
    SDL_RenderCopy(game->pRenderer, game->pPlayer.oTexture, &game->pPlayer.spriteRect, &game->pPlayer.positionRect);

    /*preset render*/
    SDL_RenderPresent(game->pRenderer);

    if (game->pBombs)
        tick_bombs(&game->pBombs);
}

/**
 * event handling func, return 1 = quit
 * */
int     game_event(game_t *game)
{
    SDL_Event   event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return (1);
        } else if (event.type == SDL_KEYDOWN) {
            /*input handling*/
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE :
                    return (1);
                    break;
                case SDLK_UP :
                    game->directionKeyHoldMem[0] = 1;
                    /*game_movePlayer(game, SDLK_UP);*/
                    return (0);
                    break;
                case SDLK_DOWN :
                    game->directionKeyHoldMem[1] = 1;
                    /*game_movePlayer(game, SDLK_DOWN);*/
                    return (0);
                    break;
                case SDLK_LEFT :
                    game->directionKeyHoldMem[2] = 1;
                    /*game_movePlayer(game, SDLK_LEFT);*/
                    return (0);
                    break;
                case SDLK_RIGHT :
                    game->directionKeyHoldMem[3] = 1;
                    /*game_movePlayer(game, SDLK_RIGHT);*/
                    return (0);
                    break;
                case SDLK_b :
                    if (!game->bombKeyHoldCheck)
                        add_bomb(&game->pBombs, &game->pPlayer.positionRect);
                    game->bombKeyHoldCheck = 1;
                    return (0);
                    break;
                case SDLK_d :
                    debug_display_player_coords(&game->pPlayer);
                    return (0);
                    break;
		case SDLK_r :
		    debug_reset_player_pos(&game->pPlayer);
		    return (0);
		    break;
                default :
                    my_putCharArray((char const *[]){"Key not recognized: ", SDL_GetKeyName(event.key.keysym.sym) ," \n", NULL}, 2);
                    return (0);
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case (SDLK_UP):
                    game->directionKeyHoldMem[0] = 0;
                    return (0);
                    break;
                case (SDLK_DOWN):
                    game->directionKeyHoldMem[1] = 0;
                    return (0);
                    break;
                case (SDLK_LEFT):
                    game->directionKeyHoldMem[2] = 0;
                    return (0);
                    break;
                case (SDLK_RIGHT):
                    game->directionKeyHoldMem[3] = 0;
                    return (0);
                    break;
                case (SDLK_b):
                    game->bombKeyHoldCheck = 0;
                    return (0);
                    break;
                default :
                    return (0);
            }
        }
    }
    return (0);
}

void    game_movePlayer(game_t *game)
{
    if (game->directionKeyHoldMem[0]) {
        game->pPlayer.positionRect.y = (game->pPlayer.positionRect.y - 10) * (game->pPlayer.positionRect.y > 40)
                                        + (10 * (game->pPlayer.positionRect.y <= 40));
        game->pPlayer.sheetLoopIndex = ((game->pPlayer.sheetLoopIndex + 1) % 3) + 6;
    } if (game->directionKeyHoldMem[1]) {
        game->pPlayer.positionRect.y = (game->pPlayer.positionRect.y + 10) * ((game->pPlayer.positionRect.y) <= 420)
                                        + (420 * ((game->pPlayer.positionRect.y + 10) > 420));
        game->pPlayer.sheetLoopIndex = ((game->pPlayer.sheetLoopIndex + 1) % 3) + 9;
    } if (game->directionKeyHoldMem[2]) {
        game->pPlayer.positionRect.x = (game->pPlayer.positionRect.x - 10) * (game->pPlayer.positionRect.x > 30)
                                        + (30 * ((game->pPlayer.positionRect.x - 10) <= 30));
        game->pPlayer.sheetLoopIndex = ((game->pPlayer.sheetLoopIndex + 1) % 3) + 3;
    } if (game->directionKeyHoldMem[3]) {
        game->pPlayer.positionRect.x = (game->pPlayer.positionRect.x + 10) * ((game->pPlayer.positionRect.x) < 590)
                                        + (590 * (game->pPlayer.positionRect.x >= 590));
        game->pPlayer.sheetLoopIndex = ((game->pPlayer.sheetLoopIndex + 1) % 3);
    }
    game->pPlayer.spriteRect.x = game->pPlayer.sheetLoopIndex * 30;
}
