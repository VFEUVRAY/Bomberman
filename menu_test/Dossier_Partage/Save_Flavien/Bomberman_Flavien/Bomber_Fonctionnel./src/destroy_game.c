#include "../include/game.h"

void game_destroy(stGame* game){

    printf("/================================/\n/================================/\n");

    if (game) {
        if (game->sBombe.bombeTexture) {
            SDL_DestroyTexture(game->sBombe.bombeTexture);
            printf("On detruit la texture : game->sBombe.bombeTexture\n");
        }

        if (game->sPlayer.playerTexture) {
            SDL_DestroyTexture(game->sPlayer.playerTexture);
            printf("On detruit la texture : game->sPlayer.playerTexture\n");
        }

        if (game->tMapTexture) {
            SDL_DestroyTexture(game->tMapTexture);
            printf("On detruit la texture : game->tMapTexture\n");
        }

        if (game->pRenderer) {
            SDL_DestroyRenderer(game->pRenderer);
            printf("On detruit le Renderer : game->pRenderer\n");
        }

        if (game->pWindow) {
            SDL_DestroyWindow(game->pWindow);
            printf("On detruit la Windows : game->pWindow\n");
        }

        SDL_Quit();
        free(game);
        printf("On quitte le jeu\n");
        printf("/================================/\n/================================/\n");
        
    }
}