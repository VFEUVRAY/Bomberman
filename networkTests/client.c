/*
** ETNA PROJECT, 13/07/2021 by feuvra_v
** client
** File description:
**      basic client for multiclient server
*/

#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

int exit_with_error(char const *str)
{
    perror(str);
    return (84);
}

int main()
{
    struct sockaddr_in server_access;
    int sock;
    char buff[128];
    int read_size = 0;

    struct hostent *hostinfo = NULL;
    hostinfo = gethostbyname("88.166.84.68");
    server_access.sin_addr.s_addr = inet_addr("172.20.0.1");
    //server_access.sin_addr.s_addr = *(in_addr_t *)hostinfo->h_addr_list[0];
    server_access.sin_family = AF_INET;
    server_access.sin_port = htons(8001);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(sock, (struct sockaddr*)&server_access, sizeof(server_access)) < 0)
        exit_with_error("connect()");
    while (1){
        read_size = read(0, buff, 128);
        if (read_size < 0 || !strncmp(buff, "/quit", 5))
            return (0);
        write(sock, buff, read_size);
        memset(buff, '\0', 128);
    }
    return(84);
}