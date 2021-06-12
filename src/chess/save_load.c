#include <err.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "save_load.h"
#include "board.h"

#define BUFFER_SIZE 32

void clear_board(Game* g)
{
    for(int i=0; i<64; i++)
        g->board[i]=NULL;
    for(int i=0; i<16; i++)
    {
        g->blacks[i].alive=0;
        g->whites[i].alive=0;
    }
}

Piece* put_piece(Game* g, int x, int y, int color, enum pieces_types type)
{
    if(color=='1')
    {
        for(int i=0; i<16; i++)
        {
            if(g->blacks[i].type==type && g->blacks[i].alive==0)
            {
                g->blacks[i].alive=1;
                g->blacks[i].x=x;
                g->blacks[i].y=y;
                g->board[8*x+y]=&g->blacks[i];
                return &g->blacks[i];
            }

        }
    }
    else
    {
        for(int i=0; i<16; i++)
        {
            if(g->whites[i].type==type && g->whites[i].alive==0)
            {
                g->whites[i].alive=1;
                g->whites[i].x=x;
                g->whites[i].y=y;
                g->board[8*x+y]=&g->whites[i];
                return &g->whites[i];
            }
        }
    }
    printf("Can't put more pieces of type : %s\n", get_name(type));
    return NULL;
}

void load_from_str(Game* g, char* file_content)
{
    set_game(g);
    //reset all board
    clear_board(g); 

    g->turn = file_content[0]-'0'; 
    for(int i=0; i<64; i++)
    {
        int x=i*3+1;
        if(file_content[x]=='0')
        {
            continue;
        }
        else
        {
            put_piece(g, i/8, i%8, file_content[x], file_content[x+2]-'0');
            g->board[get_pos(i/8, i%8)]->moved=file_content[x+1]-'0';
        }

    }
}


int load(Game* g, char* path)
{
    int fd=open(path,O_RDONLY, 0666);
    size_t size_file=64*3+1;
    char file_content[size_file];
    int rd=read(fd, file_content, size_file);
    if(rd==-1)
        errx(3, "Error while reading");

    load_from_str(g,file_content); 
    return 1;

}

int save(Game* g, char* path)
{
    //TODO get "has moved" and "players turn"
    //save in a file under this form
    //64 couple of int
    // first int is color (1=BLACK, 2=WHITE)
    // seconde is type of the piece
    // if case is NULL, write a 0
    int fd=open(path, O_CREAT | O_RDWR, 0666)  ;
    if(fd==-1)
    {
        printf("Can't load at this path");
        return 0;
    }
    Piece* p;
    char* white="2";
    char* black="1";
    char* null="000";
    int err;
    char turn = g->turn + '0';
    err = write(fd, &turn, 1);
    if(err == -1)
    {
        errx(EXIT_FAILURE, "Error while writing");
    }
    for(int i=0; i<64; i++)
    {
        p=g->board[i];
        if(p==NULL)
        {
            err = write(fd, null, 3);
            continue;
        }
        if(p->color==WHITE)
            err = write(fd,white, 1);
        else
            err = write(fd,black,1);
       
        char moved= p->moved + '0';
        err = write(fd, &moved, 1);
        char x=(char)(p->type+'0');
        err = write(fd, &x,1);
    }

    if (err == -1)
        printf("Can't write at this path\n");

    close(fd);
    return 1;
}

char *load_path()
{
    printf("Please enter the name of the save you want :\n");
    int is_parent = fork();
    if(is_parent)
    {
        int tmp;
        waitpid(is_parent, &tmp, 0);
    }
    else
    {
        char* args[]={"ls", "save/", NULL};
        execvp("ls", args);
        errx(EXIT_FAILURE,"couldn’t exec %s or an other argument", args[0]);
    }

    //recup le path
    char *path = malloc((5+BUFFER_SIZE)*sizeof(char));
    path= strcpy(path, "save/");
    int r = read(STDIN_FILENO, &path[5], BUFFER_SIZE);
    if (r == -1)
        errx(EXIT_FAILURE, "critical error while reading answer");
    if ( r > 1 && path[5] == 'q' && path[6] == '\n')
        exit(EXIT_SUCCESS);
    path[r+4] = 0;
    
    //check exist
    int fd=open(path, O_RDONLY, 0666);
    while(fd==-1)
    {
        close(fd);
        printf("%s does not exist, try again. (q to quit) :\n", path);
        while(r == BUFFER_SIZE) 
        {
            if ((r = read(STDIN_FILENO, &path[5], BUFFER_SIZE)) == -1)
                errx(EXIT_FAILURE, "critical error while reading answer");
        }
        
        if((r = read(STDIN_FILENO, &path[5], BUFFER_SIZE)) == -1)
            errx(EXIT_FAILURE, "critical error while reading answer");
        
        if ( r > 1 && path[5] == 'q' && path[6] == '\n')
            exit(EXIT_SUCCESS);
        
        path[r+4] = 0;
        fd=open(path, O_RDONLY, 0666);
    }
    close(fd);
    return path;
}
