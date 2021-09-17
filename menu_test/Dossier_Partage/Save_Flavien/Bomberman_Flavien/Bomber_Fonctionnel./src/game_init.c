#include "../include/game.h"

//Initialisation du Jeu et SDL
stGame* game_init(){
    
    //Initailisation des données
    stGame* game = NULL;
    game = malloc(sizeof(stGame));
    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->tMapTexture = NULL;
    game->sPlayer.playerTexture = NULL;

    player_init(&game->sPlayer);

    //bombe_init(bombe_t *sBombe);
    //game->sBombe.bombeTexture = NULL;

    game->mapPositionRect.x = 0;
    game->mapPositionRect.y = 0;
    game->mapPositionRect.w = 540;
    game->mapPositionRect.h = 400;
    printf("Initialisation SDL\n");

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "impossible de lancer la SDL : %s\n", SDL_GetError());
        game_destroy(game);
        return NULL;
    }

    //Création de la fenetre
    //====================================================================================//
    game->pWindow = SDL_CreateWindow("Bomberman",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        game->screenSize.x, game->screenSize.y, 
        SDL_WINDOW_SHOWN);
        if (!game->pWindow){
            fprintf(stderr, "Impossible de créer la Window %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }

    if (game->pWindow) {
        //Creer le renderer
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
        printf("pRenderer est créé\n");
        if (!game->pRenderer) {
            fprintf(stderr, "Impossible de créer le Renderer SDL : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
    } 
    else {
            fprintf(stderr, "Impossible de créer la fenetre SDL : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
    }

    //Chargement de la Texture de la Map
    //====================================================================================//
    SDL_Surface* surfaceMap = IMG_Load("./src_image/MAP/MAP_01.png");
    printf("Création de la Texture de la Map\n");
        if (!surfaceMap) {
            fprintf(stderr, "Impossible de créer la Surface de la Map : %s\n", IMG_GetError());
            game_destroy(game);
            return NULL;
        }

        game->tMapTexture = SDL_CreateTextureFromSurface(game->pRenderer, surfaceMap);
            if (!game->tMapTexture) {
                fprintf(stderr, "Impossible de créer la Surface par rapport a la Texture pour le Personnage : %s\n", SDL_GetError());
                game_destroy(game);
                return NULL;
            }
            SDL_FreeSurface(surfaceMap);

    //On charge la texture du personnage
    //====================================================================================//
    SDL_Surface* surfacePerso = IMG_Load("./src_image/Charactere/perso.jpeg");
        printf("Création de la Texture Personnage\n");
    if (!surfacePerso) {
        fprintf(stderr, "Impossible de créer la Surface pour le Personnage : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    }

    game->sPlayer.playerTexture = SDL_CreateTextureFromSurface(game->pRenderer, surfacePerso);
        if (!game->sPlayer.playerTexture) {
            fprintf(stderr, "Impossible de créer la Surface par rapport a la Texture pour le Personnage : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surfacePerso);

    //On charge la texture de la bombe
    //====================================================================================//
    SDL_Surface* surfaceBombe = IMG_Load("./src_image/Charactere/perso.jpeg");
        printf("Création de la Texture de la bombe\n");
    if (!surfaceBombe) {
        fprintf(stderr, "Impossible de créer la Surface pour la bombe : %s\n", IMG_GetError());
        game_destroy(game);
        return NULL;
    }

    game->sBombe.bombeTexture = SDL_CreateTextureFromSurface(game->pRenderer, surfaceBombe);
        if (!game->sBombe.bombeTexture) {
            fprintf(stderr, "Impossible de créer la Surface par rapport a la Texture pour le Personnage : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surfaceBombe);

    return game;
}
