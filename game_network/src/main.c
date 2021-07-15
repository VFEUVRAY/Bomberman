/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** main
** File description:
**      main for bomberman training ting
*/

#include "../include/game.h"

int main()
{
    game_t  *game = game_init();
	pthread_t server_thread;
	int sock = -1;
	struct sockaddr_in server = init_server(&sock);
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	serv_game_t *game_input_reader = malloc(sizeof(serv_game_t));


	if (server.sin_port == 0) {
		my_puterr("Server initialization failed, exiting\n");
		return (84);
	}
	int client = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
	if (client > 0)
		printf ("Client Accepted successfully: %d\n", client);
    int quit = 0;
    if (game){
        my_putstr("SDL Initiated OK\n");
    }
	game_input_reader->game = game;
	game_input_reader->server = &server;
	game_input_reader->sock = &client;
    while (quit != 1) {
        game_draw(game);
        quit = game_event(game);
		pthread_create(&server_thread, NULL, read_input, game_input_reader);
		pthread_join(server_thread, NULL);
        game_movePlayer(game);
        SDL_Delay(16);
    }
    game_destroy(game);
    return (0);
}
