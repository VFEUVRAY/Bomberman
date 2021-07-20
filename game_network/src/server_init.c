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

int attribute_player(int *clients)
{
	int i = 0;
	if (!clients) {
		my_puterr("attribute player: Major error, exiting\n");
		return (-1);
	}
	while (i < 4) {
		if (clients[i] < 0)
			return (i);
		++i;
	}
	my_puterr("attribute player: Max player number reached\n");
	return (84);
}

void *read_input(void *vargs)
{
	struct timeval timeout;
	serv_game_t *info = (serv_game_t *)vargs;
	int read_size = 0;
	int input = -1;
	printf("preparing to receive input\n");
	FD_ZERO(&info->read_fs);
	FD_SET(*info->sock, &info->read_fs);
	timeout.tv_sec = 0;
	timeout.tv_usec = 16000;
	select(*info->sock + 1, &info->read_fs, NULL, NULL, &timeout);
	//while ((read_size = recv(*info->sock, &input, sizeof(int), 0)) > 0) {
	if (FD_ISSET(*info->sock, &info->read_fs)){
		read_size = recv(*info->sock, &input, sizeof(int), 0);
		if (read_size > 0) {
			printf("input received %d \n", input);
			if (input >= 0 && input <= 3) {
				info->game->directionKeyHoldMem[input] = 1;
				for (int i = 0 ; i < 4 ; i++) {
					if (i != input)
						info->game->directionKeyHoldMem[i] = 0;
				}
			} else if (input == 4) {
				add_bomb(&info->game->pBombs, &info->game->pPlayer.positionRect);
			}
			return (NULL);
		}
	}
	return (NULL);
}