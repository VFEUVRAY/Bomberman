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

int main()
{
	struct sockaddr_in server_access;
	server_access.sin_addr.s_addr = inet_addr("127.0.1.1");
	server_access.sin_family = AF_INET;
	server_access.sin_port = htons(8001);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int packet;
	char buff[128];
	int read_size = 0;


	if (connect(sock, (struct sockaddr*)&server_access, sizeof(server_access)) < 0) {
		perror("connect()");
		return (84);
	}
	memset(buff, '\0', 128);
	while (1) {
		packet = -1;
		read_size = read(0, buff, 128);
		if (!strncmp(buff, "up", 2))
			packet = 0;
		else if (!strncmp(buff, "down", 4))
			packet = 1;
		else if (!strncmp(buff, "left", 4))
			packet = 2;
		else if (!strncmp(buff, "right", 5))
			packet = 3;
		else if (!strncmp(buff, "bomb", 4))
			packet = 4;
		else if (!strncmp(buff, "/quit", 5))
			return (0);
		if (packet >= 0)
			write (sock, &packet, sizeof(int));
		memset(buff, '\0', 128);
	}
}