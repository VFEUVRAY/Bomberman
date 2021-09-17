#include "../include/game_menu.h"
#include "../../include/game.h"

int menu() {

    //Initialisation de la Window + texture + pRenderer pour afficher le menu
    sMenu* menu = menu_init();
    
    
    int quit = 0;
    while(quit != 1) {

        menu_draw(menu);

        //Gestion des evenements
        quit = menu_event_mouse(menu);
        

        //on attend un peu
        SDL_Delay(20);
    }
    printf("%d\n", quit);
    menu_destroy(menu);
    if (port){
        main_game_loop(menu->user_type, port);
    }
    return (-1);//EXIT_SUCCESS;
}