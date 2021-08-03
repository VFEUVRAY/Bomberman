#include "../include/game.h"
#include "../include/globals.h"

struct sockaddr_in client_init(int *sock)
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
	return (server_access);
}

void *server_communicating_loop(void *vargs)
{
	game_t *game = (game_t *) vargs;
	game_client_t *serv = (game_client_t*)game->online_component;
	int read_size = 0;
	int buffer[8];

	read_from_server(serv->server_socket, &buffer);
	send_to_server(serv->server_socket, &game->directionKeyHoldMem);
}

int read_from_server(int socket, int **buffer)
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

int send_to_server(int sock, int **directions)
{
	int write_size = 0;
	write_size = write(sock, *directions, 4);
	if (write_size < 0) {
		my_puterr("Major error while sending to server\n");
		return (84);
	}
	return (0);
}