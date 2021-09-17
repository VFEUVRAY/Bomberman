// #include "../include/game.h"

// void button_init(menu){
    
//     //==============BUTTON_INIT_Button_Play=============//
//     //sButton_Play = NULL;
//     //sButton_Play = malloc(sizeof(sButton));
//     //sButton_Play->pRendererButton = NULL;
//     //sButton_Play.tButtonTexture = NULL;

//     menu->sButton_Play.ButtonPositionRect.x = 0;
//     menu->sButton_Play.ButtonPositionRect.y = 0;
//     menu->sButton_Play.ButtonPositionRect.w = 63;
//     menu->sButton_Play.ButtonPositionRect.h = 35;
//     //==============BUTTON_INIT_Button_Play=============//

//     //Chargement de la Texture du Button : sButton_Play
//     //====================================================================================//
//     SDL_Surface* surfaceButton_Play = IMG_Load("./src_image/Menu/Play.png");
//     printf("Création de la Texture du sButton_Play\n");
//         if (!surfaceButton_Play) {
//             fprintf(stderr, "Impossible de créer la Surface du sButton_Play : %s\n", IMG_GetError());
//             menu_destroy(menu);
//             return NULL;
//         }

//         menu->sButton_Play.tButtonTexture = SDL_CreateTextureFromSurface(menu->sButton_Play.pRendererButton, surfaceButton_Play);
//             if (!menu->sButton_Play.tButtonTexture) {
//                 fprintf(stderr, "Impossible de créer la Surface de la Texture du sButton_Play : %s\n", SDL_GetError());
//                 menu_destroy(menu);
//                 return NULL;
//             }
//             SDL_FreeSurface(surfaceButton_Play);

// }
