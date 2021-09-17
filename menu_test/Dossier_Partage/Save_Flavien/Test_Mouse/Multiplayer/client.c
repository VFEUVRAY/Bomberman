//#include "../include/game.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

 int client_init() {
// int main() {

    int sock;
    struct sockaddr_in client;
    char message[128]; // le buffer
    int port = 1111;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1 ) {
        perror("socket()");
        exit(errno);
    }

    client.sin_addr.s_addr = inet_addr("10.0.2.15");
    //client.sin_addr.s_addr = INADDR_ANY;//inet_addr("10.0.2.15");
    client.sin_family = AF_INET;
    client.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        perror("connect()");
        exit(errno);
    }

    memset(message, '\0', 128);
    int quit = 0; 

    while (quit == 0) {
        memset(message, '\0', 128);
        //fgets(message, 128, stdin);
        // if (send(sock, message, strlen(message), MSG_NOSIGNAL) < 0 ) {
        //     puts("send failed");// on peut mettre erreur de connection/ deconnection etc...
        //     close(sock);
        //     return 1;
        // } else if ( strcmp( message , "exit\n" ) == 0 ) {
        //     printf("A bientot\n");
        //     close(sock);
        //     return 1;
        // }

        // switch (expression)->

        //     memset(message, '\0', 128);

        //     case SDLK_z:
        //         message = SDLK_z ;
        //         send(sock, message, strlen(message), MSG_NOSIGNAL);
        //         printf("sended %s\n", message);
        //         move_player(SDLK_z);

        //     case SDLK_escape:
        //         message = SDLK_escape;
        //         send(sock, message, strlen(message), MSG_NOSIGNAL);
        //         printf("sended %s\n", message);
        //         move_player(SDLK_escape);

        //     defaut :
        //         puts("connais pas ca réessaye !");


        printf("sended %s\n", message);
        recv(sock, message, 128, MSG_DONTWAIT);// avant a la place de recv c'etait read , donc le 4eme parametre c'est un flags : MSG_DONTWAIT(active le mode non bloquant), MSG_WAITALL(bloque tant que l'on a pas recu len octets).
        //on devrait recevoir une réponse du serveur pour les déplacement des autres joueurs.
    }


    close(sock);
    return 0;
}
