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
int port_client;

typedef char bool_t;

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

//Structure du Button
typedef struct {
    SDL_Point       screenSizeButton;
    SDL_Renderer*   pRendererButton;
    SDL_Texture*    tButtonTexture;
    SDL_Rect        ButtonPositionRect;
} sButton;

//Structure du menu
typedef struct {
    //taille de la window, renderer + screenSize obligatoire 
    SDL_Point       screenSizeMenu;
    SDL_Window*     pWindowMenu;
    SDL_Renderer*   pRendererMenu;
    sButton         sButton_Play;
    sButton         sButton_Host_Game;
    sButton         sButton_Join_Game;
    sButton         sButton_Quit;
    //SDL_Surface*    surfaceMenu;
    SDL_Texture*    tMenuTexture;
    SDL_Rect        MenuPositionRect;
    bool_t          user_type;
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
void button_init(sMenu* menu);
stGame* game_init();
//void bombe_init(bombe_t *sBombe);
void player_init(player_t *sPlayer);
bombe_t* bombe_init();
void menu_draw(sMenu* menu);
void button_draw(sMenu* menu);
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
void maj_ttf(sMenu* menu, char* text_port);
int menu_event_mouse(sMenu* menu);
int main_game_loop(int player_type, int chosen_port);

#endif /* GAME_H */