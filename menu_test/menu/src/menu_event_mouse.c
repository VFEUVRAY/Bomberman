#include "../include/game_menu.h"

//Gestion des evenements
//return 1 pour quitter
int menu_event_mouse(sMenu* menu) {

    int recup_souris_x, recup_souris_y = 0;

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
                    return (1);

                case SDLK_p:
                    menu_selector(event.key.keysym.sym, menu);
                    return (1);

                //TTF pour ecrire IP Host
                case SDLK_RETURN:
                    menu->user_type = 0;
                    menu_selector(event.key.keysym.sym, menu);
                    return (0);
                
                case SDLK_j:
                    menu->user_type = 1;
                    menu_selector(event.key.keysym.sym, menu);
                    return (0);

                default :
                    fprintf(stderr , "Touche inconnue : %d\n", event.key.keysym.sym);
                    return (0);
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
            SDL_GetMouseState(&recup_souris_x, &recup_souris_y);
            if ( recup_souris_x >= menu->sButton_Play.ButtonPositionRect.x && recup_souris_x < (menu->sButton_Play.ButtonPositionRect.x + menu->sButton_Play.ButtonPositionRect.w) 
            && recup_souris_y >= menu->sButton_Play.ButtonPositionRect.y && recup_souris_y < (menu->sButton_Play.ButtonPositionRect.y + menu->sButton_Play.ButtonPositionRect.h) ) {
                //play_solo();
                return (1);
            } else if ( recup_souris_x >= menu->sButton_Host_Game.ButtonPositionRect.x && recup_souris_x < (menu->sButton_Host_Game.ButtonPositionRect.x + menu->sButton_Host_Game.ButtonPositionRect.w) 
                && recup_souris_y >= menu->sButton_Host_Game.ButtonPositionRect.y && recup_souris_y < (menu->sButton_Host_Game.ButtonPositionRect.y + menu->sButton_Host_Game.ButtonPositionRect.h) ) {
                menu->user_type = 0;
                enter_port(menu);
                return (1);
            }else if ( recup_souris_x >= menu->sButton_Join_Game.ButtonPositionRect.x && recup_souris_x < (menu->sButton_Join_Game.ButtonPositionRect.x + menu->sButton_Join_Game.ButtonPositionRect.w) 
                && recup_souris_y >= menu->sButton_Join_Game.ButtonPositionRect.y && recup_souris_y < (menu->sButton_Join_Game.ButtonPositionRect.y + menu->sButton_Join_Game.ButtonPositionRect.h) ) {
                menu->user_type = 1;
                enter_port(menu);
                return (1);
            } else if ( recup_souris_x >= menu->sButton_Quit.ButtonPositionRect.x && recup_souris_x < (menu->sButton_Quit.ButtonPositionRect.x + menu->sButton_Quit.ButtonPositionRect.w) 
                && recup_souris_y >= menu->sButton_Quit.ButtonPositionRect.y && recup_souris_y < (menu->sButton_Quit.ButtonPositionRect.y + menu->sButton_Quit.ButtonPositionRect.h) ) {
                return (1);
            }

        }
    }
    return (0);
}

//Event pour le choix du Menu
void menu_selector(SDL_Keycode direction, sMenu* menu){

    if (direction == SDLK_p) {
        (void)menu;
        //play_solo();
    } else if (direction == SDLK_RETURN || direction == SDLK_j) {
        enter_port(menu);
    }
    else {
        fprintf(stderr , "Touche inconnue \n");
    }
}

char enter_port(sMenu* menu) {

    //Initialisation de TTF (pour ecrire du texte dans un champ)
    if (TTF_Init() < 0) {
        fprintf(stderr, "Impossible d'initialiser TTF : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    }

    //On donne une police/font a notre futur texte
    TTF_Font* police = TTF_OpenFont("./FONT/OriginTech_personal_use.ttf", 24);
    if (!police) {
        fprintf(stderr, "Impossible d'initialiser la FONT : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    }

    SDL_Color couleur_texte = {0, 255, 0, 255};
    //On créer une surface qui contiendras notre futur texte
    SDL_Surface* texte = TTF_RenderText_Blended(police, "Heberger une partie, port a 4 chiffres", couleur_texte);
    if (!texte) {
        fprintf(stderr, "Impossible d'initialiser le texte : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    }


    SDL_Texture* texture_texte = SDL_CreateTextureFromSurface(menu->pRendererMenu, texte);
    if (!texture_texte) {
        fprintf(stderr, "Impossible d'initialiser la texture_texte : %s\n", TTF_GetError());
        return (EXIT_FAILURE);
    }
    
    //SDL_Rect position_texte;
    SDL_QueryTexture(texture_texte, NULL, NULL, &menu->MenuPositionRect.w, &menu->MenuPositionRect.h);

    SDL_FreeSurface(texte);
    TTF_CloseFont(police);

    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 0, 0, 255);
    SDL_RenderClear(menu->pRendererMenu);

    SDL_SetRenderDrawColor(menu->pRendererMenu, 0, 255, 0, 255);
    SDL_RenderCopy(menu->pRendererMenu, texture_texte, NULL, &menu->MenuPositionRect);

    SDL_RenderPresent(menu->pRendererMenu);
    char text_port[4];
    int int_port[4];
    int nb_port;
    nb_port = 0;
    SDL_Event events;
    while (nb_port < 4) {
        if (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT) {
                return (1);
            } else if (events.type == SDL_KEYDOWN) {
            //Gerer les touches du clavier
                switch(events.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return (1);
                    
                    case SDLK_a:
                        text_port[nb_port] = '1';
                        int_port[nb_port] = 1;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;
                    
                    case SDLK_z:
                        text_port[nb_port] = '2';
                        int_port[nb_port] = 2;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;

                    case SDLK_e:
                        text_port[nb_port] = '3';
                        int_port[nb_port] = 3;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;

                    case SDLK_r:
                        text_port[nb_port] = '4';
                        int_port[nb_port] = 4;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;

                    case SDLK_t:
                        text_port[nb_port] = '5';
                        int_port[nb_port] = 5;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;
                    
                    case SDLK_y:
                        text_port[nb_port] = '6';
                        int_port[nb_port] = 6;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;
                    
                    case SDLK_u:
                        text_port[nb_port] = '7';
                        int_port[nb_port] = 7;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;
                    
                    case SDLK_i:
                        text_port[nb_port] = '8';
                        int_port[nb_port] = 8;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;
                    
                    case SDLK_o:
                        text_port[nb_port] = '9';
                        int_port[nb_port] = 9;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;

                    case SDLK_p:
                        text_port[nb_port] = '0';
                        int_port[nb_port] = 0;
                        maj_ttf(menu, text_port);
                        nb_port += 1;
                        break;

                    default :
                        fprintf(stderr , "Touche inconnue : %d\n", events.key.keysym.sym);
                        return (0);
                    
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

    //menu_destroy(menu);
    memset(text_port, '\0', 4);
    //host_game(port);
    return (port);
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
}