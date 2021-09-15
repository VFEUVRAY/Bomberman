#include "../include/game.h"

#ifndef BOMBERMAN_GLOBALS_H
# define BOMBERMAN_GLOBALS_H 1

# include "../include/globals.h"

#endif /* BOMBERMAN_GLOBALS_H */

struct sockaddr_in init_client(int *sock)
{
	struct sockaddr_in server_access;
	int player_number = -1;
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
	recv(*sock, &player_number, sizeof(int), MSG_WAITALL);
	printf("player_number %d\n", player_number);
	//game->playerNumber = player_number;
	return (server_access);
}

void *server_communicating_loop(void *vargs)
{
	game_t *game = (game_t *) vargs;
	game_client_t *serv = (game_client_t*)game->online_component;
	//int read_size = 0;
	int buffer[8];

	if (read_from_server(serv->server_socket, buffer) >= 0) {
		game->pPlayer.positionRect.x = buffer[0];
		game->pPlayer.positionRect.y = buffer[1];
	}
	send_to_server(serv->server_socket, &game->directionKeyHoldMem, game->pPlayer.positionRect);
	return (NULL);
}

int read_from_server(int socket, int *buffer)
{
	int read_size = 0;
	read_size = recv(socket, buffer, sizeof(int) * 8, MSG_WAITALL);
	printf("read %d\n", read_size);
	if (read_size < 0) {
		my_puterr("Major error while reading from server, exiting\n");
		return (-1);
	}
	//buffer--;
	printf("data received 1 %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);
	printf("data received 2 %d %d %d %d\n", buffer[4], buffer[5], buffer[6], buffer[7]);
	return (0);
}

int send_to_server(int sock, bool_t (*directions)[4], SDL_Rect coords)
{
	int write_size = 0;
	int buffer[2];
	buffer[0] = (*directions)[0];
	buffer[0] = coords.x;
	buffer[1] = coords.y;
	write_size = write(sock, buffer, sizeof(int) * 2);
	if (write_size < 0) {
		my_puterr("Major error while sending to server \n");
		return (84);
	}
	return (0);
}