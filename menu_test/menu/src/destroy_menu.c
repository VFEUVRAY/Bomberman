#include "../include/game_menu.h"

void menu_destroy(sMenu* menu){


    if (menu) {

        if (menu->sButton_Quit.tButtonTexture) {
            SDL_DestroyTexture(menu->sButton_Quit.tButtonTexture);
        }

        if (menu->sButton_Join_Game.tButtonTexture) {
            SDL_DestroyTexture(menu->sButton_Join_Game.tButtonTexture);
        }

        if (menu->sButton_Host_Game.tButtonTexture) {
            SDL_DestroyTexture(menu->sButton_Host_Game.tButtonTexture);
        }

        if (menu->sButton_Play.tButtonTexture) {
            SDL_DestroyTexture(menu->sButton_Play.tButtonTexture);
        }

        if (menu->tMenuTexture) {
            SDL_DestroyTexture(menu->tMenuTexture);
        }

        if (menu->pRendererMenu) {
            SDL_DestroyRenderer(menu->pRendererMenu);
        }

        if (menu->pWindowMenu) {
            SDL_DestroyWindow(menu->pWindowMenu);
        }
        
        SDL_Quit();
        free(menu);
    }
}