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
	int enable = 1;

	*sock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(*sock, IPPROTO_TCP, TCP_CORK, &enable, sizeof(enable));
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
	game_packet_t buffer[4];
	bool_t direction_buffer[4][5];

		set_fds(server);
		if (server->current_client > 0) {
			select(server->clients[server->current_client - 1] + 1, &server->readfs, NULL, NULL, &server->timeout);
		} else {
			select(server->sock + 1, &server->readfs, NULL, NULL, &server->timeout);
		}

		if (FD_ISSET(server->sock, &server->readfs) && server->current_client < 4) {
			my_putstr("clients incoming\n");
			if (accept_client(server->clients, server->sock) < 0)
				my_puterr("Client accept no worky\n");
			add_player(game);
			server->current_client++;
			buffer[server->current_client].x = game->pPlayers[server->current_client].positionRect.x;
			buffer[server->current_client].y = game->pPlayers[server->current_client].positionRect.y;
			my_putstr("Client accepted\n");
		}
		read_client(server->clients, buffer, &server->readfs, direction_buffer);
		//server->current_client = max_cli(server->clients);
		//handle_client_packets(buffer, game);
		prepare_packets(direction_buffer, buffer, game);
		send_to_clients(server->clients, buffer, &game->pPlayers[0].positionRect, game->bombKeyHoldCheck);
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
	FD_SET(server->sock, &server->readfs);
	if (server->current_client == 0){
		
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
	int player_number = -1;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	while (i < 4 && clients[i] > 0)
		i = i + 1;
	if (i >= 4)
		return (-1);
	my_putstr("index is good\n");
	clients[i] = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
	if (clients[i] < 0)
		return (-1);
	my_putstr("client is accepted is good\n");
	player_number = i+1;
	if (write(clients[i], &player_number, sizeof(int)) < 0){
		my_puterr("Could not send player number to client\n");
		return (-1);
	}
	my_putstr("write is good\n");
	return (0);
}

/* Read incoming inputs from client */

int read_client(int *clients, game_packet_t *buffer, fd_set *readfs, bool_t (*direction_buffer)[5])
{
	int i = 0;
	int read_size;
	int offset = 2;
	read_size = buffer[0].x;
	buffer[0].x = read_size;
	while (i < BOMBERMAN_MAX_CLIENTS && clients[i] > 0) {
		if (FD_ISSET(clients[i], readfs)){
			read_size = recv(clients[i], direction_buffer[i+1], sizeof(bool_t) * 5, MSG_WAITALL);
			if (read_size < 0){
				clients[i] = -1;
			} else {
				//buffer[i+1].x = player_buffer.x;
				//buffer[i+1].y = player_buffer.y;
				//multi_game_move_player(game->p)
			}
		}
		++i;
		offset += 2;
	}
	return (1);
}

/* send total new positionning information to clients, animation work is up to them */

int send_to_clients(int *clients, game_packet_t *buffer, SDL_Rect *coords, bool_t bomb)
{
	int i = 0;
	int w_s = 0;

	buffer[0].x = coords->x;
	buffer[0].y = coords->y;
	buffer[0].player = 0;
	buffer[0].bomb = bomb;
	buffer[0].alive = 1;
	while (i < BOMBERMAN_MAX_CLIENTS && clients[i] > 0) {
		w_s = write(clients[i], buffer, sizeof(game_packet_t) * 4);
		if (w_s < 0)
			my_putstr("client_disconnected\n");
		++i;
	}
	return (1);
}


int add_player(game_t *game)
{
	int i = 0;
	while (i < 4 && game->pPlayers[i].alive != 0)
		++i;
	if (i >= 4)
		return (-1);
	my_putstr("creating player\n");
	if (!player_init(&game->pPlayers[i], i, game->pRenderer)){
		my_putstr("init failed\n");
		return (-1);
	}
	if (!game->pPlayers[i].alive){
		my_putstr("dead?\n");
		return (-1);
	}
	my_putstr("alive?\n");
	return (1);
}

int max_cli(int *clients)
{
	int i = 0;
	int max = 0;

	while (i < BOMBERMAN_MAX_CLIENTS) {
		if (clients[max] < clients[i])
			max = i;
		i++;
	}
	return (max + (max > 0));
}

int handle_client_packets(game_packet_t *buffer, game_t *game)
{
	int i = 1;

	while (i < 4) {
		if (game->pPlayers[i].alive) {
			game->pPlayers[i].positionRect.x = buffer[i].x;
			game->pPlayers[i].positionRect.y = buffer[i].y;
		}
		++i;
	}
	return (0);
}

int prepare_packets(bool_t (*direction_buffer)[5], game_packet_t *buffer, game_t *game)
{
	int i = 0;
	int y = 0;
	bool_t bomb_request;

	while (i < 4) {
		if (game->pPlayers[i].alive) {
			if (i) {
				for (y = 0 ; y < 4 ; y++)
					game->pPlayers[i].directionKeyHoldMem[y] = direction_buffer[i][y];
				multi_game_move_player(&game->pPlayers[i], game->walls);
				bomb_request = direction_buffer[i][4];
			}
			buffer[i].x = game->pPlayers[i].positionRect.x;
			buffer[i].y = game->pPlayers[i].positionRect.y;
			buffer[i].alive = game->pPlayers[i].alive;
			if (bomb_request && !game->pPlayers[i].bombKeyHoldCheck) {
				add_bomb(&game->pBombs, &game->pPlayers[i].positionRect);
				buffer[i].bomb = 1;
			} else
				buffer[i].bomb = 0;
			game->pPlayers[i].bombKeyHoldCheck = bomb_request;
		}
		++i;
	}
	return (1);
}

/*
int reorganize_clients(int *buffer)
{
	int i = 0;
	int y = 0;
	int len = 3;

	while (i < len) {
		y = 0;
		while (y < len) {

		}
	}
}
*/