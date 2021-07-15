#include "../include/game.h"
#include "../include/globals.h"

struct sockaddr_in init_server(int *sock)
{
	struct sockaddr_in server;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(8001);

	*sock = socket(AF_INET, SOCK_STREAM, 0);
	if (*sock < 0) {
		my_puterr("init_server(): Failed to create socket\n");
		server.sin_port = 0;
	}
	while (bind(*sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		my_puterr("bind(): Failed to bind socket, retrying in 30 seconds\n");
		sleep(30);
	}
	if (listen(*sock, 4) < 0) {
		my_puterr("listen(): failed to set socket in listen mode\n");
		server.sin_port = 0;
	}
	return (server);
}

void *read_input(void *vargs)
{
	serv_game_t *info = (serv_game_t *)vargs;
	int read_size = 0;
	int input = -1;
	printf("preparing to receive input\n");
	while ((read_size = recv(*info->sock, &input, sizeof(int), 0)) > 0) {
		if (read_size > 0) {
			printf("input received %d \n", input);
			info->game->directionKeyHoldMem[input] = 1;
			for (int i = 0 ; i < 4 ; i++) {
				if (i != input)
					info->game->directionKeyHoldMem[i] = 0;
			}
			return (0);
		}
	}
	return (NULL);
}