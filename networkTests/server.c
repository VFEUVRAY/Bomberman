/*
** ETNA PROJECT, 13/07/2021 by feuvra_v
** server
** File description:
**      multiclient server in c
*/

#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

int exit_with_error(const char *str)
{
    perror(str);
    return (84);
}

int read_client(int client)
{
    if (client < 0)
        return(-1);
    char buff[128];
    int read_size = 0;
    memset(buff, '\0', 128);
    while ((read_size = read(client, buff, 128)) > 0) {
        printf("Received from Client %d : %s", client, buff);
        if (buff[read_size - 1] == '\n') {
            memset(buff, '\0', 128);
            return (0);
        }
    }
    return (-1);
}

void reorganize_clients(int **clients, const int size)
{
    int last_connected_index = -1;
    int disconnected_index = -1;
    for (int i = 0 ; i < size ; i++) {
        if ((*clients)[i] > 0)
            last_connected_index = i;
        if ((*clients)[i] < 0 && disconnected_index < 0)
        disconnected_index = i;
    }
    if (disconnected_index == -1)
        (*clients) = NULL;
    if (disconnected_index > last_connected_index || last_connected_index == -1)
        return ;
    printf("kek\n");
    (*clients)[disconnected_index] = (*clients)[last_connected_index];
    (*clients)[last_connected_index] = -1;
}

int main()
{
    struct sockaddr_in server;
    struct sockaddr_in client_addr;
    int sock;
    socklen_t client_addr_len;
    int (*clients) = malloc(sizeof(int) * 4);
    int current_client = 0;
    struct timeval timeout;
    fd_set readfs;

    struct hostent *hostinfo = NULL;
    hostinfo = gethostbyname("88.166.84.68");
    if (!hostinfo)
        return(exit_with_error("gethostbyname"));
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(8001);

    sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    if (sock < 0)
        exit_with_error("socket()");
    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
        return (exit_with_error("bind()"));
    if (listen(sock, 4) < 0)
        return (exit_with_error("listen()"));
    for (int i = 0 ; i < 4 ; i++)
        clients[i] = -1;
    printf("Server On\n");
    while (1) {
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfs);
        FD_SET(sock, &readfs);
        for (int i = 0 ; i < 4 ; i++)
            FD_SET(clients[i], &readfs);
        if (current_client > 0)
            select(clients[current_client - 1] + 1, &readfs, NULL, NULL, &timeout);
        else
            select(sock + 1, &readfs, NULL, NULL, &timeout);
        if (FD_ISSET(sock, &readfs)) {
            clients[current_client] = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
            if (clients[current_client] < 0)
                return (exit_with_error("accept()"));
            printf("Client %d accepted\n", clients[current_client]);
            current_client++;
        }
        for (int y = 0 ; y < 4 ; y++) {
            if (FD_ISSET(clients[y], &readfs)) {
                if (read_client(clients[y]) < 0 && clients[y] > 0) {
                    printf("Client %d disconnected\n", clients[y]);
                    close(clients[y]);
                    clients[y] = -1;
                    reorganize_clients(&clients, 4);
                    if (!clients) {
                        printf("Major client handling error, exiting");
                        return (84);
                    }
                    printf("Current clients: %d ; %d ; %d ; %d\n", clients[0], clients[1], clients[2], clients[3]);
                    current_client--;
                }
            }
        }
        printf("Looping\n");
    }
    return (0);
}