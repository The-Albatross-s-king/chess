#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include "online_game.h"
#include "save_load.h"

int send_save(int fd, const char* path)
{
    size_t size_load_file=file_size;//3+1;
    char buf[size_load_file];
    int file=open(path,O_RDONLY, 0666)  ;
     
    int rd=read(file, buf, size_load_file);
    if(rd==-1)
        errx(3,"Error while reading");
    rd=write(fd, buf, size_load_file);
    if(rd==-1)
        errx(3, "Error while writing");
    
    return 1;
}


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

	int valid = 0;
	char buf[32];
	while (!valid)
	{
		printf("Do you want to load a game from a save? (0 for no, 1 for yes)\n");
		int r = read(STDIN_FILENO, buf, 32);
		if(r == -1)
			errx(EXIT_FAILURE, "Error while reading");
		
		if((buf[0]=='1'|| buf[0] == '0') && buf[1] == '\n')
			valid = 1;

		while (r == 32)
		{
			r = read(STDIN_FILENO, buf, 32);
			if (r == -1)
				errx(EXIT_FAILURE, "Error while reading");
		}
	}
	Game g;
	if(buf[0]=='1' && buf[1] == '\n')
	{
		char* path=load_path();
		send_save(cfd, path);
		load(&g, path);
		printf("Save sent.\n");
		free(path);
	}
	else
	{
		load(&g, "save/basic.txt");
		send_save(cfd, "save/basic.txt");
		printf("New game synchronisation.");
	}

	char enemy_color[1];
	enemy_color[0] = !color;
	if(send(cfd, enemy_color, 1, 0) == -1)
		errx(EXIT_FAILURE, "fail to send color");
	
	online_game(&g, cfd, color);

	close(sfd);
	close(cfd);
	
}
