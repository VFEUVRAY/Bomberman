#include "../include/game.h"

#ifndef BOMBERMAN_GLOBALS_H
# define BOMBERMAN_GLOBALS_H 1

# include "../include/globals.h"

#endif /* BOMBERMAN_GLOBALS_H */

struct sockaddr_in init_client(int *sock, int *player_number)
{
	struct sockaddr_in server_access;
	server_access.sin_addr.s_addr = inet_addr("127.0.1.1");
	server_access.sin_family = AF_INET;
	server_access.sin_port = htons(8001);
	*sock = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(*sock, (struct sockaddr*)&server_access, sizeof(server_access)) < 0) {
		my_puterr("Failed to connect to server (was probably not found)\n");
		server_access.sin_port = 0;
		return (server_access);
	}
	my_putstr("connected to server\n");
	recv(*sock, player_number, sizeof(int), MSG_WAITALL);
	printf("player_number %d\n", *player_number);
	//game->playerNumber = player_number;
	return (server_access);
}

void *server_communicating_loop(void *vargs)
{
	game_t *game = (game_t *) vargs;
	game_client_t *serv = (game_client_t*)game->online_component;
	//int read_size = 0;
	game_packet_t buffer[4];
	bool_t player_lives[4];
	bool_t packet_for_serv[5];

	for (int i = 0 ; i < 4 ; i++)
		player_lives[i] = game->pPlayers[i].alive;
	if (read_from_server(serv->server_socket, buffer) >= 0) {
		//game->pPlayer.positionRect.x = buffer[0].x;
		//game->pPlayer.positionRect.y = buffer[0].y;
		handle_packet(buffer, game, player_lives);
	}
	prepare_packet_for_serv(game->pPlayers[game->playerNumber].directionKeyHoldMem, game->bombKeyHoldCheck, packet_for_serv);
	send_to_server(serv->server_socket, &packet_for_serv, game->pPlayers[game->playerNumber].positionRect);
	return (NULL);
}

int read_from_server(int sock, game_packet_t *buffer)
{
	int read_size = 0;
	read_size = recv(sock, buffer, sizeof(game_packet_t) * 4, MSG_WAITALL);
	//printf("read %d\n", read_size);
	if (read_size < 0) {
		my_puterr("Major error while reading from server, exiting\n");
		return (-1);
	}
	//buffer--;
	//printf("data received 1 %d %d %d %d\n", buffer[0].x, buffer[0].y, buffer[1].x, buffer[1].y);
	//printf("data received 2 %d %d %d %d\n", buffer[2].x, buffer[2].y, buffer[3].x, buffer[3].y);
	return (0);
}
/*
int send_to_server(int sock, bool_t (*directions)[4], SDL_Rect coords)
{
	int write_size = 0;
	game_packet_t player_buffer;
	player_buffer.x = (*directions)[0];
	player_buffer.x = coords.x;
	player_buffer.y = coords.y;
	player_buffer.bomb = 0;
	write_size = player_buffer.x;
	printf("%d %d \n", player_buffer.x, player_buffer.y);
	//write_size = write(sock, &player_buffer, sizeof(game_packet_t));
	write_size = write(sock, *directions, sizeof(bool_t) * 4);
	if (write_size < 0) {
		my_puterr("Major error while sending to server \n");
		return (84);
	}
	return (0);
}
*/
int send_to_server(int sock, bool_t (*directions)[5], SDL_Rect coords)
{
	int write_size = 0;
	game_packet_t player_buffer;
	player_buffer.x = (*directions)[0];
	player_buffer.x = coords.x;
	player_buffer.y = coords.y;
	player_buffer.bomb = 0;
	write_size = player_buffer.x;
	//printf("%d %d \n", player_buffer.x, player_buffer.y);
	//write_size = write(sock, &player_buffer, sizeof(game_packet_t));
	write_size = write(sock, *directions, sizeof(bool_t) * 5);
	if (write_size < 0) {
		my_puterr("Major error while sending to server \n");
		return (84);
	}
	return (0);
}


int handle_packet(game_packet_t *buffer, game_t *game, bool_t *player_lives)
{
	int i = 0;

	while (i < 4) {
		if (game->pPlayers[i].alive){
			game->pPlayers[i].positionRect.x = buffer[i].x;
			game->pPlayers[i].positionRect.y = buffer[i].y;
		} else if (player_lives[i] == 0 && buffer[i].alive == 1)
			add_player(game);
		++i;
	}
	/*
	game->pPlayers[0].positionRect.x = buffer[0].x;
	game->pPlayers[0].positionRect.y = buffer[0].y;
	if (buffer[0].bomb)
		add_bomb(&game->pBombs, &game->pPlayer.positionRect);

	while (i < 4) {
		if (player_lives[i] == 0 && buffer[i].alive == 1)
			add_player(game);
		i++;
	}*/
	return (0);

}

int prepare_packet_for_serv(bool_t *directions, bool_t bomb, bool_t *packet_for_serv)
{
	int i = 0;
	while (i < 4) {
		packet_for_serv[i] = directions[i];
		++i;
	}
	packet_for_serv[4] = bomb;
	return (1);
}