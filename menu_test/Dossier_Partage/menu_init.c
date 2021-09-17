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

    menu->MenuPositionRect.x = 0;
    menu->MenuPositionRect.y = 0;
    menu->MenuPositionRect.w = 500;
    menu->MenuPositionRect.h = 444;
    printf("Initialisation SDL menu\n");

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
        printf("pRenderer est créé\n");
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
    printf("Création de la Texture du Menu\n");
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

    return menu;
}
