/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** main
** File description:
**      main for bomberman training ting
*/

#include "../include/game.h"


int prepare_systems(struct sockaddr_in *server, game_t **game, int *sock)
{
	*server = init_server(sock);
	*game = game_init();
	if (server->sin_port == 0) {
		my_puterr("Server initialization failed, exiting\n");
		return (84);
	}
	if (*game)
		my_putstr("SDL Initiated OK\n");
	return (0);
}

int main_game_loop()
{
	/*
	game_t  *game = game_init();
	int sock = -1;
	struct sockaddr_in server = init_server(&sock);
	*/
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	serv_game_t *game_input_reader = malloc(sizeof(serv_game_t));
	pthread_t server_thread;
	struct sockaddr_in server;
	game_t *game = NULL;
	int sock = -1;
	if (prepare_systems(&server, &game, &sock) > 0)
		return (84);
	/*
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
	*/
	int client = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
	if (client > 0)
		printf ("Client Accepted successfully: %d\n", client);
    int quit = 0;
	game_input_reader->game = game;
	game_input_reader->server = &server;
	game_input_reader->sock = &client;
    while (quit != 1) {
		printf("looping\n");
        game_draw(game);
        quit = game_event(game);
		pthread_create(&server_thread, NULL, read_input, game_input_reader);
        SDL_Delay(16);
		pthread_join(server_thread, NULL);
        game_movePlayer(game);
    }
    game_destroy(game);
    return (0);
}


int main(int argc, char **argv)
{
	if (argc > 1 && !strncmp(argv[1], "-s", 2)) {
		printf("serveur\n");
	} else
		printf("client\n");
	if (main_game_loop() > 0)
		return (84);
	return (0);
}
