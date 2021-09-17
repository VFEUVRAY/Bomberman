#include "../include/game.h"

//Affichage du jeu
void game_draw(stGame* game){

    //Nettoyer l'ecran
    SDL_SetRenderDrawColor(game->pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(game->pRenderer);
    printf("on nettoie et on donne la couleur du fond et d'application \n");

    //Afficher la MAP
    SDL_RenderCopy(game->pRenderer, game->tMapTexture, NULL, &game->mapPositionRect);
    printf("on affiche la map\n");

    //Afficher le joueur
    //
    //
    SDL_RenderCopy(game->pRenderer, game->sPlayer.playerTexture, NULL, &game->sPlayer.playerPositionRect);
    printf("on affiche le joueur\n");


    //Une fois sétté on presente le rendu
    SDL_RenderPresent(game->pRenderer);
}