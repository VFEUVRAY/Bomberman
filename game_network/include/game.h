/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** game
** File description:
**      yo mec
*/

#ifndef GAME_H
# define GAME_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# include <arpa/inet.h>
# include <sys/time.h>
# include <sys/select.h>
# include <netdb.h>
# include <netinet/in.h>
# include <pthread.h>

/*Typdef for string output function pointers.
Is used for convenient multipurpose output function (misc.c)
*/
typedef void (*strfunc_t) (char const *);
/*typedef of char as bool_t, used when we just need small variable for checking purposes*/
typedef char bool_t;

typedef struct game_object_s {
    SDL_Texture*    oTexture;
    SDL_Rect        positionRect;
    SDL_Rect        spriteRect;
} game_object_t;

/*Structure specific to player object
the added spriteRect is meant to be used as source rectangle
in the SDL_RenderCopy function, this will allow to get the precise sprite wanted for current animation
*/
typedef struct player_object_s {
    SDL_Texture*    oTexture;
    SDL_Rect        positionRect;
    SDL_Rect        spriteRect;
    unsigned int    sheetLoopIndex;
} player_object_t;

/* bomb object is different because it doesn't need to hold its own texture
also needs a count which will dictate when the object is to be deleted from linked list
*/
typedef struct bomb_object_s {
    SDL_Rect        positionRect;
    SDL_Rect        spriteRect;
    unsigned int    count;
} bomb_object_t;

/*Queue which will contain bombs*/

typedef struct bomb_queue_s {
    bomb_object_t bomb;
    struct bomb_queue_s *next;
} bomb_queue_t;

/*General game structure, will hold information necessary for each rendering loops
Also data that might affect multiple redundant objects
*/
typedef struct game_s {
    SDL_Point       screenSize; /*coords with x y, will contain screen size*/
    SDL_Window*     pWindow;    /*struct pointer containing window*/
    SDL_Renderer*   pRenderer;  /*struct that will interact with graphical component of pc*/

    SDL_Texture*    pTexPlayer;
    SDL_Texture*    pBombTexture;
    /*game_object_t   pPlayer;*/
    player_object_t pPlayer;
    game_object_t   pMap;
    bomb_queue_t    *pBombs;
    bool_t          directionKeyHoldMem[4];
    bool_t          bombKeyHoldCheck;

	void			*online_component; /*Cast into appropriate structure when using in functions */
} game_t;

/* temporary structure with server and game info */

typedef struct serv_game_s {
	game_t				*game;
	struct sockaddr_in	*server;
	int					*sock;
	fd_set				read_fs;
} serv_game_t;

/* server type structure */

typedef struct game_server_s {
	struct sockaddr_in	server;
	int					sock;
	int					*clients;
} game_server_t;

/* client type structure */

typedef struct game_client_s {
	struct sockaddr_in	server_access;
	int					server_socket;
} game_client_t;

/*game related (game.c)*/
game_t  *game_init();
void    game_destroy(game_t *game);
void    game_draw(game_t *game);
int     game_event(game_t *game);
void    game_movePlayer(game_t *game);

/*general object related (object_initializer.c)*/
void    object_init(game_object_t *object, int const x, int const y, int const w, int const h);
void    player_init(player_object_t *player);

/* bomb queue related (bombs.c)*/
bomb_queue_t    *pop_bomb(bomb_queue_t *queue);
void            add_bomb(bomb_queue_t **queue, SDL_Rect *coords);
void            tick_bombs(bomb_queue_t **queue);
void            free_queue(bomb_queue_t **queue);

/* various debug functions (debug.c)*/
void    debug_display_player_coords(const player_object_t *player);
void    debug_reset_player_pos(player_object_t *player);

/* functions regarding network implementation */
struct sockaddr_in init_server(int *sock);
void *read_input(void *vargs);

/*miscellanious functions (misc.c)*/
int     my_strlen(char const *str);
void    my_putstr(char const *str);
void    my_puterr(char const *str);
void    my_putchar(char const c, char const fd);
void    my_putCharArray(char const **array, char const fd);
void    my_putnbr(int nb);

/* globals used to streamline error checking and temporary animation looping */
#endif /* GAME_H */