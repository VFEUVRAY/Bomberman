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
	game_packet_t buffer[4];
	//struct sockaddr_in client_addr;
	//socklen_t client_addr_len;
	//fd_set readfs;
	//int i = 0;
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
			my_putstr("clients incoming\n");
			//server->clients[server->current_client] = accept(server->sock, (struct sockaddr*)&client_addr, &client_addr_len);
			//server->current_client++;
			if (accept_client(server->clients, server->sock) < 0)
				my_puterr("Client accept no worky\n");
			add_player(game);
			server->current_client++;
			my_putstr("Client accepted\n");
		}
		/*
		for (i = 0 ; i < BOMBERMAN_MAX_CLIENTS && server->clients[i] > 0 ; i++) {
			if (FD_ISSET(server->clients[i], &server->readfs))
				read_client(server->clients, &buffer, &server->readfs);
		}
		*/
		read_client(server->clients, buffer, &server->readfs);
		server->current_client = max_cli(server->clients);
		send_to_clients(server->clients, buffer, &game->pPlayer.positionRect, game->bombKeyHoldCheck);
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

int read_client(int *clients, game_packet_t *buffer, fd_set *readfs)
{
	int i = 0;
	int read_size;
	game_packet_t player_buffer;
	int offset = 2;
	while (i < BOMBERMAN_MAX_CLIENTS && clients[i] > 0) {
		if (FD_ISSET(clients[i], readfs)){
			read_size = read(clients[i], &player_buffer, (sizeof(game_packet_t)));
			if (read_size < 0)
				clients[i] = -1;
			else {
				buffer[i+1] = player_buffer;
				//printf("received some shit %d %d\n", (*buffer)[i + offset], (*buffer)[i + offset + 1]);
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
	//printf("data being sent %d %d %d %d\n", buffer[0].x, buffer[0].y, buffer[1].x, buffer[1].y);
	while (i < BOMBERMAN_MAX_CLIENTS && clients[i] > 0) {
		w_s = write(clients[i], buffer, sizeof(game_packet_t) * 4);
		if (w_s < 0)
			printf("Clients %d disconnected", clients[i]);
		++i;
	}
	return (1);
}


int add_player(game_t *game)
{
	int i = 0;
	while (game->pPlayers[i].alive != 0)
		++i;
	if (i >= 4)
		return (-1);
	printf("creating player\n");
	if (!player_init(&game->pPlayers[i], 2, game->pRenderer)){
		printf("init failed\n");
		return (-1);
	}
	if (!game->pPlayers[i].alive){
		printf("dead?\n");
		return (-1);
	}
	printf("alive?\n");
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

int max_cli(int *clients)
{
	int i = 0;
	int max = -1;

	while (i < BOMBERMAN_MAX_CLIENTS) {
		if (max < clients[i])
			max = i;
		i++;
	}
	return (max);
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