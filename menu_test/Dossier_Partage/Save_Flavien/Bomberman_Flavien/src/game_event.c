#include "../include/game.h"

//Gestion des evenements
//return 1 pour quitter
int game_event(stGame* game) {
    printf("on rentre dans le game_event\n");

    SDL_Event event;
    //Recuperer un evenement
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            //quitter l'application
            return (1);
        } else if (event.type == SDL_KEYDOWN) {
            //Gerer les touches du clavier
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    //quitter l'application
                    printf("GAME_EVENT : on appuie sur escape\n");
                    //message = "SDLK_ESCAPE";
                    //recv(sock, message, 128, MSG_DONTWAIT);
                    //close(sock);
                    return (1);
                    break;

                case SDLK_UP:
                    game_movePlayer(game, event.key.keysym.sym);
                    //message = "SDLK_UP";
                    //recv(sock, message, 128, MSG_DONTWAIT);
                    return (0);
                    break;

                case SDLK_DOWN:
                    game_movePlayer(game, event.key.keysym.sym);
                    //message = "SDLK_DOWN";
                    //recv(sock, message, 128, MSG_DONTWAIT);
                    return (0);
                    break;

                case SDLK_LEFT:
                    game_movePlayer(game, event.key.keysym.sym);
                    //message = "SDLK_LEFT";
                    //recv(sock, message, 128, MSG_DONTWAIT);
                    return (0);
                    break;

                case SDLK_RIGHT:
                    game_movePlayer(game, event.key.keysym.sym);
                    //message = "SDLK_RIGHT";
                    //recv(sock, message, 128, MSG_DONTWAIT);
                    return (0);
                    break;

                //case SDLK_b

                default :
                    fprintf(stderr , "Touche inconnue : %d\n", event.key.keysym.sym);
                    return (0);
            }
        }
    }
    printf("/================================/\n/================================/\n");
    printf("apres l'evenement :\n");
    printf("la valeur de sPlayer.playerPositionRect.x = %d\n", game->sPlayer.playerPositionRect.x);
    printf("la valeur de sPlayer.playerPositionRect.y = %d\n", game->sPlayer.playerPositionRect.y);
    printf("la TAILLE de sPlayer.playerPositionRect.h = %d\n", game->sPlayer.playerPositionRect.h);
    printf("la TAILLE de sPlayer.playerPositionRect.w = %d\n", game->sPlayer.playerPositionRect.w);
    printf("/================================/\n/================================/\n");
    return (0);
}

//Event pour le deplacement du personnage
void game_movePlayer(stGame* game, SDL_Keycode direction){

    if (direction == SDLK_UP) {
        if (game->sPlayer.playerPositionRect.y > + 30 ) {
            game->sPlayer.playerPositionRect.y -= 34;
        }
    } else if (direction == SDLK_DOWN) {
        if (game->sPlayer.playerPositionRect.y < ((game->screenSize.y) - (game->sPlayer.playerPositionRect.h)) - 30 ) {
            game->sPlayer.playerPositionRect.y += 34;
        }
    } else if (direction == SDLK_LEFT) {
        if (game->sPlayer.playerPositionRect.x > 30 ) {
            game->sPlayer.playerPositionRect.x -= 34;
        }
    } else if (direction == SDLK_RIGHT) {
        if (game->sPlayer.playerPositionRect.x < ((game->screenSize.x) - (game->sPlayer.playerPositionRect.w)) - 30 ) {
            game->sPlayer.playerPositionRect.x += 34;
        }
    } else {
        fprintf(stderr , "Touche inconnue \n");
    }

}