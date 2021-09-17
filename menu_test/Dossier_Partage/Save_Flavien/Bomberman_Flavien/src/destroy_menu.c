#include "../include/game.h"

void menu_destroy(sMenu* menu){

    printf("/================================/\n/================================/\n");

    if (menu) {
        if (menu->tMenuTexture) {
            SDL_DestroyTexture(menu->tMenuTexture);
            printf("On detruit la texture : menu->tMenuTexture\n");
        }

        if (menu->pRendererMenu) {
            SDL_DestroyRenderer(menu->pRendererMenu);
            printf("On detruit le Renderer : menu->pRendererMenu\n");
        }

        if (menu->pWindowMenu) {
            SDL_DestroyWindow(menu->pWindowMenu);
            printf("On detruit la Windows : menu->pWindowMenu\n");
        }
            SDL_Quit();
        free(menu);
        printf("On quitte le jeu\n");
        printf("/================================/\n/================================/\n");
    }
}