#include "../include/game.h"

//Type d'event du menu avec fonction retourner
// menu_play();
// host_game();
// join_game();
// enter_port();

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
                    menu_selector(event.key.keysym.sym, menu);
                    return (1);
                    //break;

                /*
                //host_game
                case SDLK_h:
                    menu_selector(event.key.keysym.sym);
                    return (1);
                    break;

                //Join game
                case SDLK_j:
                    menu_selector(event.key.keysym.sym);
                    return (1);
                    break;
                */


                //TTF pour ecrire IP Host
                case SDLK_RETURN:
                    menu_selector(event.key.keysym.sym, menu);
                    return (0);
                    //break;
                

                default :
                    fprintf(stderr , "Touche inconnue : %d\n", event.key.keysym.sym);
                    return (0);
            }
        }
    }
}


//Event pour le choix du Menu
void menu_selector(SDL_Keycode direction, sMenu* menu){

    if (direction == SDLK_p) {
        (void)menu;
        play_solo();
    } else if (direction == SDLK_RETURN) {
        enter_port(menu);
        //host_game(port);
    }
    /*
    else if (direction == SDLK_h) {
        host_game(port);
    } else if (direction == SDLK_j) {
        join_game();
    }
    */
    else {
        fprintf(stderr , "Touche inconnue \n");
    }

}

char enter_port(sMenu* menu) {

    
    //int WIDTHSCREEN = 800;
    //int HEIGHTSCREEN = 600;

    //Initialisation de TTF (pour ecrire du texte dans un champ)
    if (TTF_Init() < 0) {
        fprintf(stderr, "Impossible d'initialiser TTF : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    } else {
        printf("Initialisation de la TTF_Init réussi\n");
    }

    //On donne une police/font a notre futur texte
    TTF_Font* police = TTF_OpenFont("./FONT/OriginTech_personal_use.ttf", 24);
    if (!police) {
        fprintf(stderr, "Impossible d'initialiser la FONT : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    } else {
        printf("Initialisation de la FONT réussi\n");
    }

    /*if (menu->pWindowMenu) {
        //Creer le renderer
        menu->pBoutonRendererMenu = SDL_CreateRenderer(menu->pWindowMenu, -1, SDL_RENDERER_ACCELERATED);
        if (!menu->pBoutonRendererMenu) {
            fprintf(stderr, "Impossible de créer le Renderer SDL : %s\n", SDL_GetError());
            //menu_destroy(menu);
            return NULL;
        }
        printf("BOUTON pRenderer est créé\n");
    } 
    else {
            fprintf(stderr, "Impossible de créer la fenetre SDL : %s\n", SDL_GetError());
            menu_destroy(menu);
            return NULL;
    }*/


    SDL_Color couleur_texte = {0, 255, 0, 255};
    //On créer une surface qui contiendras notre futur texte
    SDL_Surface* texte = TTF_RenderText_Blended(police, "Heberger une partie, port a 4 chiffres", couleur_texte);
    if (!texte) {
        fprintf(stderr, "Impossible d'initialiser le texte : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    } else {
        printf("Initialisation de la SDL_SURFACE texte réussi\n");
    }


    //SDL_Window *fenetreTexte = NULL;
    //SDL_Renderer *RendererTexte = NULL;
    //int posX = 100, posY = 100, width = 320, height = 240;

    //fenetreTexte = SDL_CreateWindow("TEST", posX, posY, width, height, 0);
    //RendererTexte = SDL_CreateRenderer(menu->pWindowMenu, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* texture_texte = SDL_CreateTextureFromSurface(menu->pRendererMenu, texte);
    if (!texture_texte) {
        fprintf(stderr, "Impossible d'initialiser la texture_texte : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    } else {
        printf("Initialisation de la SDL_Texture texture_texte réussi\n");
    }
    
    //SDL_Rect position_texte;
    SDL_QueryTexture(texture_texte, NULL, NULL, &menu->MenuPositionRect.w, &menu->MenuPositionRect.h);
    //position_texte.x = (WIDTHSCREEN / 2) - position_texte.w / 2 ; 
    //position_texte.y = (HEIGHTSCREEN / 2) - position_texte.h / 2;

    printf("On est avant le freesurface\n");
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);

    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 0, 0, 255);
    SDL_RenderClear(menu->pRendererMenu);

    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 255, 0, 255);
    SDL_RenderCopy(menu->pRendererMenu, texture_texte, NULL, &menu->MenuPositionRect);

    SDL_RenderPresent(menu->pRendererMenu);
    printf("On fait le RenderPresent\n");

    printf("On est avant le l\'event\n");
    char text_port[4];
    int int_port[4];
    int nb_port;
    nb_port = 0;
    SDL_Event events;
    while (nb_port < 4) {
        if (SDL_PollEvent(&events)) {
            printf("00000000000000bouton000000000000000\n");
            if (events.type == SDL_QUIT) {
                return (1);
            } else if (events.type == SDL_KEYDOWN) {
            //Gerer les touches du clavier
                switch(events.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        //quitter l'application
                        printf("on appuie sur escape\n");
                        //SDL_Quit();
                        return (1);
                    
                    case SDLK_a:
                        text_port[nb_port] = '1';
                        int_port[nb_port] = 1;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        //return (0);
                        break;
                    
                    case SDLK_z:
                        text_port[nb_port] = '2';
                        int_port[nb_port] = 2;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        //return (0);
                        break;

                    /*case SDLK_e:
                        text_port[nb_port] = '3';
                        int_port[nb_port] = 3;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);
                    
                    case SDLK_r:
                        text_port[nb_port] = '4';
                        int_port[nb_port] = 4;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);

                    case SDLK_t:
                        text_port[nb_port] = '5';
                        int_port[nb_port] = 5;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);
                    
                    case SDLK_y:
                        text_port[nb_port] = '6';
                        int_port[nb_port] = 6;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);
                    
                    case SDLK_u:
                        text_port[nb_port] = '7';
                        int_port[nb_port] = 7;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);
                    
                    case SDLK_i:
                        text_port[nb_port] = '8';
                        int_port[nb_port] = 8;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);
                    
                    case SDLK_o:
                        text_port[nb_port] = '9';
                        int_port[nb_port] = 9;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);

                    case SDLK_p:
                        text_port[nb_port] = '0';
                        int_port[nb_port] = 0;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        return (0);

                    default :
                        fprintf(stderr , "Touche inconnue : %d\n", events.key.keysym.sym);
                        return (0);
                    */
                }
            }
        }
    }
    SDL_DestroyTexture(texture_texte);
    SDL_DestroyRenderer(menu->pRendererMenu);
    TTF_Quit();

    port = int_port[0]*1000;
    port = port + (int_port[1]*100);
    port = port + (int_port[2]*10);
    port = port + int_port[3];


    int i = 0;
    printf("le tableau de char est égal à : ");
    for ( i = 0 ; i < 4 ; i++) {
         printf("%c", text_port[i]);
    //     port = atoi( text_port[i]);
    }
    printf("\n");

    //port = sscanf("%d", text_port);
    //strcpy(port, text_port);

    printf("le port (tableau d'int) est égal à : %d \n", port);
    //menu_destroy(menu);
    host_game(port);
    return (1);
}

void maj_ttf(sMenu* menu, char* text_port){
    TTF_Font* police = TTF_OpenFont("./FONT/OriginTech_personal_use.ttf", 24);
    SDL_Color couleur_texte = {0, 255, 0, 255};
    SDL_Surface* texte = TTF_RenderText_Blended(police, text_port, couleur_texte);
    SDL_Texture* texture_texte = SDL_CreateTextureFromSurface(menu->pRendererMenu, texte);
    SDL_QueryTexture(texture_texte, NULL, NULL, &menu->MenuPositionRect.w, &menu->MenuPositionRect.h);
    
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);

    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 0, 0, 255);
    SDL_RenderClear(menu->pRendererMenu);

    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 255, 0, 255);
    SDL_RenderCopy(menu->pRendererMenu, texture_texte, NULL, &menu->MenuPositionRect);

    SDL_RenderPresent(menu->pRendererMenu);
    printf("On fait le RenderPresent\n");
}