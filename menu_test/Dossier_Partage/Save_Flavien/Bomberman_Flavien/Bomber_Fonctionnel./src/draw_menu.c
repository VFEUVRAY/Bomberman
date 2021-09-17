#include "../include/game.h"

//Affichage du jeu
void menu_draw(sMenu* menu){

    //Nettoyer l'ecran
    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 0, 0, 0);
    SDL_RenderClear(menu->pRendererMenu);
    printf("On nettoie l'ecran du Menu\n");

    //Afficher du Menu
    SDL_RenderCopy(menu->pRendererMenu, menu->tMenuTexture, NULL, &menu->MenuPositionRect);
    printf("On affiche le Menu\n");

    //Une fois sétté on presente le rendu
    SDL_RenderPresent(menu->pRendererMenu);
    printf("On set l'ecran\n");
}