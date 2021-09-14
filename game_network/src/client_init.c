#include "../include/game.h"

#ifndef BOMBERMAN_GLOBALS_H
# define BOMBERMAN_GLOBALS_H 1

# include "../include/globals.h"

#endif /* BOMBERMAN_GLOBALS_H */

struct sockaddr_in init_client(int *sock)
{
	struct sockaddr_in server_access;
	server_access.sin_addr.s_addr = inet_addr("127.0.1.1");
	server_access.sin_family = AF_INET;
	server_access.sin_port = htons(8001);
	*sock = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(*sock, (struct sockaddr*)&server_access, sizeof(server_access)) < 0) {
		my_puterr("Failed to connect to server (was probably not found)\n");
		server_access.sin_port = 0;
	}
	if (server_access.sin_port)
		my_putstr("connected to server\n");
	return (server_access);
}

void *server_communicating_loop(void *vargs)
{
	game_t *game = (game_t *) vargs;
	game_client_t *serv = (game_client_t*)game->online_component;
	//int read_size = 0;
	int buffer[8];

	printf("client here\n");
	read_from_server(serv->server_socket, &buffer);
	printf("client here\n");
	send_to_server(serv->server_socket, &game->directionKeyHoldMem);
	printf("client here\n");
	return (NULL);
}

int read_from_server(int socket, int (*buffer)[8])
{
	int read_size = 0;
	read_size = read(socket, *buffer, 8);
	if (read_size <  0) {
		my_puterr("Major error while reading from server, exiting\n");
		return (-1);
	}
	printf("%d %d %d %d", (*buffer)[0], (*buffer)[1], (*buffer)[2], (*buffer)[3]);
	return (0);
}

int send_to_server(int sock, bool_t (*directions)[4])
{
	int write_size = 0;
	write_size = write(sock, *directions, 4);
	if (write_size < 0) {
		my_puterr("Major error while sending to server\n");
		return (84);
	}
	return (0);
}