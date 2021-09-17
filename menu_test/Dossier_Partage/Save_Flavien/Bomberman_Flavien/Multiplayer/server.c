#include "../include/game.h"

int read_client(int client) {

    int n;
    char message[128];//toujours le buffer

    if (client == -1) {
        return (1);
    }

    n = 0;
    memset(message, '\0', 128);
    while( ( n = recv(client, message, 128, 0)) >= 0) {
        if ( n == 0 ) {
            return (-1);
        }
        printf("received this : %s\n", message);
        if ( strcmp(message, "SDLK_ESCAPE" ) == 0 ) {

        }

        if (message[n - 1] == '\n') {
            memset(message, '\0', 128);
            break;
        }
    }
    return 0;
}

int response_client_to_server(struct timeval timeout, fd_set readfs, int client1, int client2){

    while (1) {
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        FD_ZERO(&readfs);

        FD_SET(client1, &readfs);
        FD_SET(client2, &readfs);

        // param 1 (numero du file descriptor le plus élevé + 1), param 2 (un set de FD (filedescriptor) a monitorer(surveiller) en lecture),
        // param3 (la meme mais en ecriture), param4 c'est la meme pareil mais en exception et le dernier c'est les parma du timeout.
        select(client2 + 1, &readfs, NULL, NULL, &timeout);

        if (FD_ISSET(client1, &readfs)) {
            if ( read_client(client1) == -1 ) {
                puts("client 1 disconnected");
                close(client1);
                client1 = -1;
            }
        } else if (FD_ISSET(client2, &readfs)) {
            if ( read_client(client2) == -1 ) {
                puts("client 2 disconnected");
                close(client2);
                client2 = -1;
            }
        }

        if ( client1 == -1 && client2 == -1 ) {
            break;
        }
        //puts("looping");
    }
    return (1);
}



int server_init(port) {
    int sock;
    int client1;
    int client2;
    socklen_t client_addr_len;
    struct sockaddr_in server;
    struct sockaddr_in client_addr;
    fd_set readfs;
    struct timeval timeout;
    //int port = 1234;


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock == -1) {
        perror("socket()");
        return (1);
    }
    
    //server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0 ) {
        perror("bind()");
        return (1);
    }
    
    listen(sock, 5);

    //puts("waiting for clients...");
    //puts("waiting for accept");


        client1 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
        client2 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client1 < 0 || client2 < 0) {
            perror("accept()");
            return (1);
        }

        // if (client1) {
        // puts("new clients 1");
        // }
        // if (client2) {
        // puts("new clients 2"); 
        // }

    response_client_to_server(timeout, readfs, client1, client2);
        

    close(sock);
    return 0;
}