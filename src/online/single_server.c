#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "online_game.h"

void server(char *port, int color)
{
	struct addrinfo hints;
	struct addrinfo *result;
	int e;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	e = getaddrinfo(NULL, port, &hints, &result);

	if (e != 0)
		errx(EXIT_FAILURE, "error get address information with port %s : %s",
			port, gai_strerror(e));
	
	int sfd;
	struct addrinfo *r;
	for (r = result; r != NULL; r = r->ai_next)
	{
		sfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
		if (sfd == -1)
			continue;
		int val = 1;
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) == -1)
			errx(EXIT_FAILURE, "fail setting socket option");

		if (bind(sfd, r->ai_addr, r->ai_addrlen) == 0)
			break;
		close(sfd);
	}

	if (r == NULL)
	{
		freeaddrinfo(result);
		errx(EXIT_FAILURE, "could not create a socket");
	}
	freeaddrinfo(result);

	if (listen(sfd, 5) == -1)
	{
		close(sfd);
		errx(EXIT_FAILURE, "could not listen");
	}
	
	struct sockaddr addr;
	socklen_t len;
	int cfd;
	if ((cfd = accept(sfd, &addr, &len)) == -1)
	{
		close(sfd);
		close(cfd);
		errx(EXIT_FAILURE, "could not accept");
	}

	printf("Connection successful!\n");
	

	//game(sfd, cfd, color);
	
	/*char buff[128];
	while (1)
	{
		int r;
		if ((r = recv(cfd, buff, 128, 0)) == -1)
			errx(EXIT_FAILURE, "fail to receive data");

		if (write(cfd, buff, r) == -1)
			errx(EXIT_FAILURE, "fail to write data");
	}*/
	
	char enemy_color[1];
	enemy_color[0] = !color;
	if(send(cfd, enemy_color, 1, 0) == -1)
		errx(EXIT_FAILURE, "fail to send color");
	
	online_game(cfd, color);

	close(sfd);
	close(cfd);
	
}
