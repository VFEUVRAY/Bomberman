#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

// variable globale utilisée coté serveur et client.
int port;

//Structure du Player
typedef struct {
    SDL_Texture*    playerTexture;
    SDL_Rect        playerPositionRect;
} player_t;

//Structure de la bombe
typedef struct {
    SDL_Texture*    bombeTexture;
    SDL_Rect        bombePositionRect;
} bombe_t;

//Structure du menu
typedef struct {
    //taille de la window, renderer + screenSize obligatoire 
    SDL_Point       screenSizeMenu;
    SDL_Window*     pWindowMenu;
    SDL_Renderer*   pRendererMenu;
    SDL_Renderer*   pBoutonRendererMenu;
    //Pour pouvoir afficher une image sur le menu et indiquer sa position
    //SDL_Surface*    surfaceMenu;
    SDL_Texture*    tMenuTexture;
    SDL_Rect        MenuPositionRect;
} sMenu;

//Structure du jeu de base
typedef struct {
    //Variable classique de la SDL
    SDL_Point       screenSize;
    SDL_Window*     pWindow;
    SDL_Renderer*   pRenderer;
    //Texture Map
    SDL_Texture*    tMapTexture;
    SDL_Rect        mapPositionRect;
    //Objet a initialiser
    player_t sPlayer;
    bombe_t sBombe;
} stGame;

sMenu* menu_init();
stGame* game_init();
//void bombe_init(bombe_t *sBombe);
void player_init(player_t *sPlayer);
bombe_t* bombe_init();
void menu_draw(sMenu* menu);
int menu_event(sMenu* menu);
void menu_destroy(sMenu* menu);
void game_destroy(stGame* game);
void game_draw(stGame* game);
int game_event(stGame* game);
void menu_selector(SDL_Keycode direction, sMenu* menu);
void game_movePlayer(stGame* game, SDL_Keycode direction);
char enter_port(sMenu* menu);
int client_init(int port);
int server_init(int port);
int host_game(int port);

#endif /* GAME_H */