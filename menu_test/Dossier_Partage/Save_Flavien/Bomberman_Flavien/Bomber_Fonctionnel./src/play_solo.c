#include "../include/game.h"

int play_solo() {

    stGame* game = game_init();
    printf("Initialisation fini\n");
    

    /*

    On initialise le serveur ici et on fait passer dans la boucle game_event l'envoi et reception des fichiers.
    Tant que tous les joueurs ne sont pas mort ou ont quittés = 0 si tous morts/quittés =1.

    */

    int quit = 0;
    while(quit != 1) {

        
        //Dessiner le jeu
        game_draw(game);

        //Gestion des evenements
        quit = game_event(game);

        //on attend un peu
        SDL_Delay(20);
        printf("QUIT dans le game_init = %d\n", quit);
    }

    game_destroy(game);
    menu();
    return 1;
    //return EXIT_SUCCESS;
}