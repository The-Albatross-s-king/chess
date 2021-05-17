#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <netdb.h>

void serveur(char *port)
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
			port, gai_sterror(e));
	
	int sfd;
	struct addrinfo *r;
	for (r = result; r != NULL; r = r->next)
	{
		sfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);	
	}
	
	return 0;
}
