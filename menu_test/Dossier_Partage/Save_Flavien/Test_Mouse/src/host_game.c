#include "../include/game.h"

int host_game(port) {

    stGame* game = game_init();
    
    printf("Initialisation fini\n");
    
    /*
    On initialise le serveur ici avec la variable "port" et on fait passer dans la boucle game_event l'envoi et reception des fichiers.
    Tant que tous les joueurs ne sont pas mort ou ont quittés = 0 si tous morts/quittés =1.
    */
    //server_init(port);
    
    //--------------Server init--------------//
    // printf("avant le int sock");
    int sock;
    int client1;
    int client2;
    socklen_t client_addr_len;
    struct sockaddr_in server;
    struct sockaddr_in client_addr;
    fd_set readfs;
    struct timeval timeout;
    //int port = 1234;

    printf("avant le sock\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock == -1) {
        perror("socket()");
        return (1);
    }

    //server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    printf("avant le bind\n");
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0 ) {
        perror("bind()");
        return (1);
    }
    printf("avant listen\n");
    listen(sock, 5);

    printf("avant accept\n");
    client1 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
    client2 = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
    printf("apres accept\n");
    if (client1 < 0 || client2 < 0) {
        perror("accept()");
        game_destroy(game);
        //menu();
        return (1);
    }

    printf("avant new client\n");
    if (client1) {
    puts("new clients 1");
    printf("apres puts\n");
    }
    if (client2) {
    puts("new clients 2"); 
    }
    //--------------Server init--------------//

    printf("fin de l'initialisation du server\n");


    int quit = 0;
    while(quit != 1) {

        printf("on rentre dans la boucle\n");

        //-------------Boucle response client to server---------------//
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        FD_ZERO(&readfs);

        FD_SET(client1, &readfs);
        FD_SET(client2, &readfs);

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
            return (1);
            break;
        }

        //puts("looping");

        //-------------Boucle response client to server---------------//

        
        //Dessiner le jeu
        game_draw(game);

        //Gestion des evenements
        quit = game_event(game);

        //response_client_to_server(timeout, readfs, client1, client2);

        //on attend un peu
        SDL_Delay(20);
        printf("QUIT dans le game_init = %d\n", quit);
    }

    printf("avant le close sock\n");
    close(sock);
    printf("avant le game_destoy\n");
    game_destroy(game);
    //menu();
    return (1);
    //return EXIT_SUCCESS;
}