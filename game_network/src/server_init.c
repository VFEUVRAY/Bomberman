#include "../include/game.h"

#ifndef BOMBERMAN_GLOBALS_H
# define BOMBERMAN_GLOBALS_H 1

# include "../include/globals.h"

#endif /* BOMBERMAN_GLOBALS_H */

int const BOMBERMAN_MAX_CLIENTS = 3;
int const BOMBERMAN_KEY_ARRAY_LEN = 5;

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
		return (server);
	}
	while (bind(*sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		my_puterr("bind(): Failed to bind socket, retrying in 30 seconds\n");
		sleep(30);
	}
	if (listen(*sock, BOMBERMAN_MAX_CLIENTS) < 0) {
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
	while (i < BOMBERMAN_MAX_CLIENTS) {
		if (clients[i] < 0)
			return (i);
		++i;
	}
	my_puterr("attribute player: Max player number reached\n");
	return (84);
}

/* THIS FUNCTION IS MEANT FOR MULTITHREADING PURPOSES
	vargs contains game_t variable
	game->online_component is ALSO a void * pointer and needs casting to appropriate structure
*/

void *client_reading_loop(void *vargs)
{
	game_t *game = (game_t *)vargs;
	game_server_t *server = (game_server_t *)game->online_component;
	int buffer[8];
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	//fd_set readfs;
	int i = 0;
	//while (1) {
		//printf("waiting %d \n", server->current_client);
		set_fds(server);
		if (server->current_client > 0) {
			select(server->clients[server->current_client - 1] + 1, &server->readfs, NULL, NULL, &server->timeout);
		} else {
			select(server->sock + 1, &server->readfs, NULL, NULL, &server->timeout);
			//printf("this select\n");
		}
		/*
		if (server->current_client == 0) {
			server->clients[0] = accept(server->sock, (struct sockaddr*) &client_addr, &client_addr_len);
			printf("client %d\n", server->clients[0]);
			server->current_client++;
		}
		*/
		//printf("get accepted for fuck's sake\n");
		if (FD_ISSET(server->sock, &server->readfs) && server->current_client < 4) {
			printf("clients incoming\n");
			server->clients[server->current_client] = accept(server->sock, (struct sockaddr*)&client_addr, &client_addr_len);
			server->current_client++;
			my_putstr("Client accepted\n");
		}
		for (i = 0 ; i < BOMBERMAN_MAX_CLIENTS && server->clients[i] > 0 ; i++) {
			if (FD_ISSET(server->clients[i], &server->readfs))
				read_client(game, server->clients, &buffer, &server->readfs);
		}
		send_to_clients(server->clients, buffer);
	//}
	return NULL;
}

/* set file descriptors for reading in selects */

void set_fds(game_server_t *server)
{
	int i = 0;
	FD_ZERO(&server->readfs);
	server->timeout.tv_sec = 0;
	server->timeout.tv_usec = 16;
	if (server->current_client == 0){
		FD_SET(server->sock, &server->readfs);
		//printf("no clients yet\n");
	} else {
		while (i < BOMBERMAN_MAX_CLIENTS && server->clients[i] >= 0) {
			FD_SET(server->clients[i], &server->readfs);
			++i;
		}
	}
}

/* Accept client and send to client which player they are */

int accept_client(int *clients, int sock)
{
	//int client_player_placement = -1;
	int i = 0;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	while (i < 4 && clients[i] > 0)
		i = i + 1;
	if (i == 4)
		return (-1);
	clients[i] = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
	if (clients[i] < 0)
		return (-1);
	if (write (clients[i], &i, 4) < 0)
		return (-1);
	return (0);
}

/* Read incoming inputs from client */

int read_client(game_t *game, int *clients, int (*buffer)[8], fd_set *readfs)
{
	int i = 0;
	int read_size;
	int player_buffer[2];
	int offset = 2;
	while (i < BOMBERMAN_MAX_CLIENTS && clients[i] > 0) {
		if (FD_ISSET(clients[i], readfs)){
			read_size = read(clients[i], player_buffer, (sizeof(int) * 2));
			if (read_size < 0)
				clients[i] = -1;
			else {
				(*buffer)[i + offset] = player_buffer[0];
				(*buffer)[i + offset + 1] = player_buffer[1];
				//printf("received some shit %d %d\n", (*buffer)[i + offset], (*buffer)[i + offset + 1]);
			}
		}
		++i;
		offset += 2;
	}
	(*buffer)[0] = game->pPlayer.positionRect.x;
	(*buffer)[1] = game->pPlayer.positionRect.y;
	return (1);
}

/* send total new positionning information to clients, animation work is up to them */

int send_to_clients(int *clients, int *buffer)
{
	int i = 0;
	printf("data being sent %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);
	while (i < BOMBERMAN_MAX_CLIENTS && clients[i] > 0) {
		if (write(clients[i], buffer, sizeof(int) * 8) < 0)
			printf("Clients %d disconnected", clients[i]);
		++i;
	}
	return (1);
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