#include "../include/game.h"

//Affichage du jeu
void menu_draw(sMenu* menu){

    //Nettoyer l'ecran
    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 0, 0, 0);
    SDL_RenderClear(menu->pRendererMenu);

    //Afficher du Menu
    SDL_RenderCopy(menu->pRendererMenu, menu->tMenuTexture, NULL, &menu->MenuPositionRect);

    //Afficher le button sButton_Play
    SDL_RenderCopy(menu->pRendererMenu, menu->sButton_Play.tButtonTexture, NULL, &menu->sButton_Play.ButtonPositionRect);

    //Afficher le button sButton_Host_Game
    SDL_RenderCopy(menu->pRendererMenu, menu->sButton_Host_Game.tButtonTexture, NULL, &menu->sButton_Host_Game.ButtonPositionRect);

    //Afficher le button sButton_Join_Game
    SDL_RenderCopy(menu->pRendererMenu, menu->sButton_Join_Game.tButtonTexture, NULL, &menu->sButton_Join_Game.ButtonPositionRect);

    //Afficher le button sButton_Quit
    SDL_RenderCopy(menu->pRendererMenu, menu->sButton_Quit.tButtonTexture, NULL, &menu->sButton_Quit.ButtonPositionRect);

    //Une fois sétté on presente le rendu
    SDL_RenderPresent(menu->pRendererMenu);
}