/*
** ETNA PROJECT, 15/06/2021 by feuvra_v
** main
** File description:
**      main for bomberman training ting
*/

#include "../include/game.h"

game_server_t *make_server_online_component()
{
	game_server_t *serv = malloc(sizeof(game_server_t));
	if (!serv)
		return (NULL);
	serv->addr = init_server(&serv->sock);
	if (serv->addr.sin_port == 0) {
		free(serv);
		return (NULL);
	}
	serv->clients[0] = serv->clients[1] = serv->clients[2] = -1;
	serv->current_client = 0;
	serv->timeout.tv_sec = 0;
	serv->timeout.tv_usec = 16;
	return (serv);
}

game_client_t *make_client_online_component(int *player_number)
{
	game_client_t *serv_access = malloc(sizeof(game_client_t));
	if (!serv_access)
		return (NULL);
	serv_access->server_access = init_client(&serv_access->server_socket, player_number);
	if (serv_access->server_access.sin_port == 0) {
		free(serv_access);
		return (NULL);
	}
	return (serv_access);
}

int prepare_systems(game_t **game, int player_type)
{
	void *online_component = NULL;
	int	player_number = -1;

	if (player_type == 0) {
		online_component = (void *)make_server_online_component();
		player_number = 0;
	} else
		online_component = (void *)make_client_online_component(&player_number);
	if (!online_component){
		my_puterr("Failed to initialize online connection, exiting\n");
		return (84);
	}
	*game = game_init(player_number);
	if (!game) {
		my_puterr("There was an error while initializing SDL, exiting\n");
		return (84);
	}
	(*game)->online_component = online_component;
	//(*game)->playerNumber = player_number;
	(*game)->playerType = player_type;
	my_putstr("SDL Initiated OK\n");
	return (0);
}

int main_game_loop(int player_type)
{
	game_t *game = NULL;
	pthread_t server_thread;

	if (prepare_systems(&game, player_type) > 0)
		return (84);

	int quit = 0;
    while (quit != 1) {
		//printf("looping\n");
        game_draw(game);
        quit = game_event(game);
		if (player_type) {
			pthread_create(&server_thread, NULL, server_communicating_loop, game);
		} else
			pthread_create(&server_thread, NULL, client_reading_loop, game);
        SDL_Delay(16);
		pthread_join(server_thread, NULL);
        multi_game_move_player(&game->pPlayers[game->playerNumber]);
        //multi_game_move_player(&game->pPlayer);
    }
    game_destroy(game);
    return (0);
}


int main(int argc, char **argv)
{
	int player_type = -1;
	if (argc > 1 && !strncmp(argv[1], "-s", 2)) {
		player_type = 0;
		printf("serveur\n");
	} else {
		player_type = 1;
		printf("client\n");
	}
	if (main_game_loop(player_type) > 0) {
		my_puterr("Exiting with error\n");
		return (84);
	}
	my_putstr("Closing game\n");
	return (0);
}
