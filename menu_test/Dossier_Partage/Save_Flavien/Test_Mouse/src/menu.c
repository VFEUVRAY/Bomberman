#include "../include/game.h"

int menu() {

    //Initialisation de la Window + texture + pRenderer pour afficher le menu
    sMenu* menu = menu_init();
    
    
    int quit = 0;
    while(quit != 1) {

        menu_draw(menu);

        //Gestion des evenements
        quit = menu_event_mouse(menu);
        if (port){
            lance la game
        }

        //on attend un peu
        SDL_Delay(20);

    }

    menu_destroy(menu);

    return (1);//EXIT_SUCCESS;
}