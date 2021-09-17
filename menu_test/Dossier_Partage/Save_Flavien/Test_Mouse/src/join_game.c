#include "../include/game.h"

int host_game(port) {

    stGame* game = game_init();
    
    printf("Initialisation fini\n");
    
    /*
    On initialise le serveur ici avec la variable "port" et on fait passer dans la boucle game_event l'envoi et reception des fichiers.
    Tant que tous les joueurs ne sont pas mort ou ont quittés = 0 si tous morts/quittés =1.
    */   

    //--------------Client init--------------//
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
    //--------------Client init--------------//
    puts("fin de l'initialisation du client");


    //--------------Client connect--------------//
    if (connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        perror("connect()");
        exit(errno);
    }
    //--------------Client connect--------------//
    puts("client connecté");

    memset(message, '\0', 128);
    int quit = 0;


    while(quit != 1) {

        printf("on rentre dans la boucle\n");
        //-------------Boucle response server to client---------------//
        recv(sock, message, 128, MSG_DONTWAIT);// avant a la place de recv c'etait read , donc le 4eme parametre c'est un flags : MSG_DONTWAIT(active le mode non bloquant), MSG_WAITALL(bloque tant que l'on a pas recu len octets).
        //-------------Boucle response server to client---------------//

        
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
    menu();
    return 0;
    //return EXIT_SUCCESS;
}