#include "../include/game.h"

//Type d'event du menu avec fonction retourner
// menu_play();
// host_game();
// join_game();
// enter_IP();

//Gestion des evenements
//return 1 pour quitter
int menu_event(sMenu* menu) {
    printf("on rentre dans le menu_event\n");

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
                    printf("on appuie sur escape\n");
                    //SDL_Quit();
                    return (1);
                

                case SDLK_p:
                    menu_selector(event.key.keysym.sym);
                    return (1);
                    break;

                /*
                //Host_game
                case SDLK_h:
                    menu_selector(event.key.keysym.sym);
                    return (1);
                    break;

                //Join game
                case SDLK_j:
                    menu_selector(event.key.keysym.sym);
                    return (1);
                    break;

                //TTF pour ecrire IP Host
                case SDLK_ENTER:
                    menu_selector(event.key.keysym.sym);
                    return (0);
                    break;
                */

                default :
                    fprintf(stderr , "Touche inconnue : %d\n", event.key.keysym.sym);
                    return (0);
            }
        }
    }
}


//Event pour le choix du Menu
void menu_selector(SDL_Keycode direction){

    if (direction == SDLK_p) {
        play_solo();
    }
    /*
    else if (direction == SDLK_h) {
        host_game();
    } else if (direction == SDLK_j) {
        join_game();
    } else if (direction == SDLK_ENTER) {
        enter_IP();
    }
    */
    else {
        fprintf(stderr , "Touche inconnue \n");
    }

}