/*#include <stdio.h>
#include <save_load.h>
#include <err.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <board.h>

#define BUF_SIZE 64*2//3+1


//Je veux pouvoir :
// deconnecter, envoyer un board, ou envoyer un coup
// 3 fonctions semblent bien
//


int send_move(int fd, int old_pos, int pos)
{

    char* s = malloc(9*sizeof(char));
    s=strcpy(s,"M00|00|\n");
    s[1]=old_pos/10+'0';
    s[2]=old_pos%10+'0';
    s[4]=pos/10+'0';
    s[5]=pos%10+'0';

    int r=write(fd, s, 9);
    if(r==-1)
    {
       return 0; 
    }

    return 1;
}


int read_apply_move(char* s)
{
    printf("start_reading_move\n");
    int pos=0;
    int old_pos=0;
    
    char* str=s;
    while(*str!='|')
    {
        old_pos*=10;
        old_pos+=*str-'0';
        str++;
    }
    str++;
     while(*str!='|')
    {
        pos*=10;
        pos+=*str-'0';
        str++;
    }
    printf("must apply old_pos : %d, pos: %d\n", old_pos, pos);
    return 1;
}

int send_save(int fd, const char* path)
{
    size_t size_load_file=64*2;//3+1;
    char buf[size_load_file];
    int file=open(path,O_RDONLY, 0666)  ;
     
    int rd=read(file, buf, size_load_file);
    if(rd==-1)
        errx(3,"Error while reading");
    rd=write(fd, "S", 1);
    if(rd==-1)
        errx(3, "Error while writing");
    rd=write(fd, buf, size_load_file);
    if(rd==-1)
        errx(3, "Error while writing");
    
    return 1;
}



int send_deconnexion(int fd)
{
    char* s="D\n";
    int r=write(fd, s, 2);
    if(r==-1)
    {
       return 0; 
    }

    return 1;
}


int read_answer(Game* g, int fd)
{
    char buf[BUF_SIZE];
    int rd=read(fd, buf, BUF_SIZE);
    if(rd==-1)
        errx(3,"Error while reading");

    if(buf[0]=='M')
        read_apply_move(buf+1);
    else if(buf[0]=='D')
        printf("Deconnexion\n");
    else if(buf[0]=='S')
        load_from_str(g, buf+1);
    else
    {
        printf("No symbol recognized\n");
    }
    return 1;

}

*/