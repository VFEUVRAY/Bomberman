#include "../include/game.h"

sMenu* menu_init(){
    
    //Initailisation des données
    sMenu* menu = NULL;
    menu = malloc(sizeof(sMenu));
    menu->screenSizeMenu.x = 640;
    menu->screenSizeMenu.y = 480;
    menu->pWindowMenu = NULL;
    menu->pRendererMenu = NULL;
    menu->tMenuTexture = NULL;
    //menu->surfaceMenu = NULL;

    menu->MenuPositionRect.x = 70;
    menu->MenuPositionRect.y = 22;
    menu->MenuPositionRect.w = 500;
    menu->MenuPositionRect.h = 444;

    //==============BUTTON_INIT_Button_Play=============//
    menu->sButton_Play.ButtonPositionRect.x = 260 ;//((menu->screenSizeMenu.x)/2) - ((menu->sButton_Play.ButtonPositionRect.w)/2);
    menu->sButton_Play.ButtonPositionRect.y = 50 ;//((menu->screenSizeMenu.y)/2)  - ((menu->sButton_Play.ButtonPositionRect.h)/2);
    menu->sButton_Play.ButtonPositionRect.w = 125;
    menu->sButton_Play.ButtonPositionRect.h = 70;
    //==============BUTTON_INIT_Button_Play=============//

    //==============BUTTON_INIT_Button_Host_Game=============//
    menu->sButton_Host_Game.ButtonPositionRect.x = 260 ;//((menu->screenSizeMenu.x)/2) - ((menu->sButton_Host_Game.ButtonPositionRect.w)/2);
    menu->sButton_Host_Game.ButtonPositionRect.y = 170 ;//((menu->screenSizeMenu.y)/2)  - ((menu->sButton_Host_Game.ButtonPositionRect.h)/2);
    menu->sButton_Host_Game.ButtonPositionRect.w = 125;
    menu->sButton_Host_Game.ButtonPositionRect.h = 70;
    //==============BUTTON_INIT_Button_Host_Game=============//

    //==============BUTTON_INIT_Button_Join_Game=============//
    menu->sButton_Join_Game.ButtonPositionRect.x = 260 ;//((menu->screenSizeMenu.x)/2) - ((menu->sButton_Join_Game.ButtonPositionRect.w)/2);
    menu->sButton_Join_Game.ButtonPositionRect.y = 290 ;//((menu->screenSizeMenu.y)/2)  - ((menu->sButton_Join_Game.ButtonPositionRect.h)/2);
    menu->sButton_Join_Game.ButtonPositionRect.w = 125;
    menu->sButton_Join_Game.ButtonPositionRect.h = 70;
    //==============BUTTON_INIT_Button_Join_Game=============//

    //==============BUTTON_INIT_Button_Quit=============//
    menu->sButton_Quit.ButtonPositionRect.x = 260 ;//((menu->screenSizeMenu.x)/2) - ((menu->sButton_Quit.ButtonPositionRect.w)/2);
    menu->sButton_Quit.ButtonPositionRect.y = 400 ;//((menu->screenSizeMenu.y)/2)  - ((menu->sButton_Quit.ButtonPositionRect.h)/2);
    menu->sButton_Quit.ButtonPositionRect.w = 125;
    menu->sButton_Quit.ButtonPositionRect.h = 70;
    //==============BUTTON_INIT_Button_Quit=============//

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "impossible de lancer la SDL : %s\n", SDL_GetError());
        menu_destroy(menu);
        return NULL;
    }

    //Création de la fenetre
    //====================================================================================//
    menu->pWindowMenu = SDL_CreateWindow("Bomberman",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        menu->screenSizeMenu.x, menu->screenSizeMenu.y, 
        SDL_WINDOW_SHOWN);
        if (!menu->pWindowMenu){
            fprintf(stderr, "Impossible de créer la Window %s\n", SDL_GetError());
            menu_destroy(menu);
            return NULL;
        }

    if (menu->pWindowMenu) {
        //Creer le renderer
        menu->pRendererMenu = SDL_CreateRenderer(menu->pWindowMenu, -1, SDL_RENDERER_ACCELERATED);
        if (!menu->pRendererMenu) {
            fprintf(stderr, "Impossible de créer le Renderer SDL : %s\n", SDL_GetError());
            menu_destroy(menu);
            return NULL;
        }
    } 
    else {
            fprintf(stderr, "Impossible de créer la fenetre SDL : %s\n", SDL_GetError());
            menu_destroy(menu);
            return NULL;
    }

    //Chargement de la Texture du Menu
    //====================================================================================//
    SDL_Surface* surfaceMenu = IMG_Load("./src_image/Menu/Menu_mignon.gif");
        if (!surfaceMenu) {
            fprintf(stderr, "Impossible de créer la Surface du Menu : %s\n", IMG_GetError());
            menu_destroy(menu);
            return NULL;
        }

        menu->tMenuTexture = SDL_CreateTextureFromSurface(menu->pRendererMenu, surfaceMenu);
            if (!menu->tMenuTexture) {
                fprintf(stderr, "Impossible de créer la Surface de la Texture du Menu : %s\n", SDL_GetError());
                menu_destroy(menu);
                return NULL;
            }
            SDL_FreeSurface(surfaceMenu);

    //Chargement de la Texture du Button : sButton_Play
    //====================================================================================//
    SDL_Surface* surfaceButton_Play = IMG_Load("./src_image/Menu/Button/Play.png");
        if (!surfaceButton_Play) {
            fprintf(stderr, "Impossible de créer la Surface du sButton_Play : %s\n", IMG_GetError());
            menu_destroy(menu);
            return NULL;
        }

        menu->sButton_Play.tButtonTexture = SDL_CreateTextureFromSurface(menu->pRendererMenu, surfaceButton_Play);
            if (!menu->sButton_Play.tButtonTexture) {
                fprintf(stderr, "Impossible de créer la Surface de la Texture du sButton_Play : %s\n", SDL_GetError());
                menu_destroy(menu);
                return NULL;
            }
            SDL_FreeSurface(surfaceButton_Play);

    //Chargement de la Texture du Button : sButton_Host_Game
    //====================================================================================//
    SDL_Surface* surfaceButton_Host_Game = IMG_Load("./src_image/Menu/Button/Host_Game.png");
        if (!surfaceButton_Host_Game) {
            fprintf(stderr, "Impossible de créer la Surface du sButton_Host_Game : %s\n", IMG_GetError());
            menu_destroy(menu);
            return NULL;
        }

        menu->sButton_Host_Game.tButtonTexture = SDL_CreateTextureFromSurface(menu->pRendererMenu, surfaceButton_Host_Game);
            if (!menu->sButton_Host_Game.tButtonTexture) {
                fprintf(stderr, "Impossible de créer la Surface de la Texture du sButton_Host_Game : %s\n", SDL_GetError());
                menu_destroy(menu);
                return NULL;
            }
            SDL_FreeSurface(surfaceButton_Host_Game);

    //Chargement de la Texture du Button : sButton_Join_Game
    //====================================================================================//
    SDL_Surface* surfaceButton_Join_Game = IMG_Load("./src_image/Menu/Button/Join_Game.png");
        if (!surfaceButton_Join_Game) {
            fprintf(stderr, "Impossible de créer la Surface du sButton_Join_Game : %s\n", IMG_GetError());
            menu_destroy(menu);
            return NULL;
        }

        menu->sButton_Join_Game.tButtonTexture = SDL_CreateTextureFromSurface(menu->pRendererMenu, surfaceButton_Join_Game);
            if (!menu->sButton_Join_Game.tButtonTexture) {
                fprintf(stderr, "Impossible de créer la Surface de la Texture du sButton_Join_Game : %s\n", SDL_GetError());
                menu_destroy(menu);
                return NULL;
            }
            SDL_FreeSurface(surfaceButton_Join_Game);

    //Chargement de la Texture du Button : sButton_Quit
    //====================================================================================//
    SDL_Surface* surfaceButton_Quit = IMG_Load("./src_image/Menu/Button/Quit.png");
        if (!surfaceButton_Quit) {
            fprintf(stderr, "Impossible de créer la Surface du sButton_Quit : %s\n", IMG_GetError());
            menu_destroy(menu);
            return NULL;
        }

        menu->sButton_Quit.tButtonTexture = SDL_CreateTextureFromSurface(menu->pRendererMenu, surfaceButton_Quit);
            if (!menu->sButton_Quit.tButtonTexture) {
                fprintf(stderr, "Impossible de créer la Surface de la Texture du sButton_Quit : %s\n", SDL_GetError());
                menu_destroy(menu);
                return NULL;
            }
            SDL_FreeSurface(surfaceButton_Quit);

    return menu;
}
