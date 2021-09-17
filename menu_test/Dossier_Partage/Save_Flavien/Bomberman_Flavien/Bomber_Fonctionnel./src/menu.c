#include "../include/game.h"

int menu() {

    //Initialisation de la Window + texture + pRenderer pour afficher le menu
    sMenu* menu = menu_init();
    
    printf("Initialisation du menu fini\n");
    
    int quit = 0;
    while(quit != 1) {

        
        //Dessiner le jeu
        menu_draw(menu);

        //Gestion des evenements
        quit = menu_event(menu);

        //on attend un peu
        SDL_Delay(20);
        printf("QUIT dans le menu = %d\n", quit);
    }

    menu_destroy(menu);

    return EXIT_SUCCESS;
}