#include "../include/game.h"

//Affichage du jeu
void button_draw(sMenu* menu){

    //Nettoyer l'ecran
    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 0, 0, 0);
    SDL_RenderClear(menu->pRendererMenu);
    printf("on nettoie et on donne la couleur du fond et d'application \n");

    //Afficher le button sButton_Play
    SDL_RenderCopy(menu->pRendererMenu, menu->sButton_Play.tButtonTexture, NULL, &menu->sButton_Play.ButtonPositionRect);
    printf("on affiche le button\n");

    //Afficher le button sButton_Host_Game
    SDL_RenderCopy(menu->pRendererMenu, menu->sButton_Host_Game.tButtonTexture, NULL, &menu->sButton_Host_Game.ButtonPositionRect);
    printf("on affiche le button\n");

    //Une fois sétté on presente le rendu
    SDL_RenderPresent(menu->pRendererMenu);
}