#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <netdb.h>

void client(char *host, char *port, int color)
{
	color++;
	
	struct addrinfo hints;
	struct addrinfo *results;
	int e;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	e = getaddrinfo(host, port, &hints, &results);

	if (e != 0)
	{
		errx(EXIT_FAILURE, "Fail getting address for %s on port %s: %s",
			host, port, gai_strerror(e));
	}

	int cfd;
	struct addrinfo *r;
	for (r = results; r != NULL; r = r->ai_next)
	{
		cfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
		if (cfd == -1)
			continue;
		if (connect(cfd, r->ai_addr, r->ai_addrlen) != -1)
			break;
		close(cfd);
	}
	if (r == NULL)
	{
		freeaddrinfo(results);
		errx(EXIT_FAILURE, "Could not create a socket");
	}

	freeaddrinfo(results);
	
	char buff[128];
	char resp[128];
	while (1)
	{
		printf("Enter message :\n");
		int r = read(STDIN_FILENO, buff, 128);
		if (send(cfd, buff, r, 0) == -1)
			errx(EXIT_FAILURE, "fail to send information");

		if (recv(cfd, resp, 128, 0) == -1)
			errx(EXIT_FAILURE, "fail to receive data");

		printf("%s", resp);
	}
	close(cfd);
}
