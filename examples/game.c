#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <err.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "alpha_beta.h"
#include "tree.h"
#include "input.h"
#include "save_load.h"
#include "human.h"

#define BUFFER_SIZE 32

void want_exit(int q)
{
    if (q == 2)
        exit(EXIT_SUCCESS);
}

int get_answer(char *buff)
{
    int too_long = 0;
    int r = 0;
    if ((r = read(STDIN_FILENO, buff, BUFFER_SIZE)) == -1)
        errx(EXIT_FAILURE, "critical error while reading answer");

    while(r == BUFFER_SIZE)
    {
        if ((r = read(STDIN_FILENO, buff, BUFFER_SIZE)) == -1)
            errx(EXIT_FAILURE, "critical error while reading answer");
        too_long = 1;
    }
    if (too_long || buff[0] == '\n')
        return -1;

    if (buff[0] == '0')
        return 0;
    if (buff[0] == '1')
        return 1;
    if (buff[0] == 'q')
        return 2;

    return -1;

}

// In work
int main(int argc, char** argv)
{
    //Choisir offline/online
    //online -> trouver le joueur 
    //offline -> human ou IA ?
    //IA ? -> alphabeta ou reseau ?
    //Voulez vous charger une partie ?
    //Choix de la couleur
    //HERE WE GO!

    char buff[BUFFER_SIZE];
    int want_offline= -1 ;
    int want_IA= -1;
    int want_alpha= -1;
    int want_load= -1;
    int want_white= -1;
    int is_host=1;


    //online offline
    printf("Do you want to play online (0) or offline (1) ? (q to quit) :\n");
    want_offline = get_answer(buff);
    while(want_offline == -1)
    {
        printf("You have entered a wrong input, please make sure it is 0, 1 or q :\n");
        want_offline = get_answer(buff);
    }

    want_exit(want_offline);

    //man or IA
    if(want_offline)
    {
        printf("Do you want to play against a local friend (0) or an IA (1)? (q to quit) :\n");
        want_IA = get_answer(buff);
        while(want_IA == -1)
        {
            printf("You have entered a wrong input, please make sure it is 0, 1 or q :\n");
            want_IA = get_answer(buff);
        }
    }

    want_exit(want_IA);

    //alpha_beta or NN
    if(want_offline && want_IA)
    {
        printf("Do you want to play against a neural network (0) or an algorithmique IA (1) ? (q to quit) :\n");
        want_alpha = get_answer(buff);
        while(want_alpha == -1)
        {
            printf("You have entered a wrong input, please make sure it is 0, 1 or q :\n");
            want_alpha = get_answer(buff);
        }
        want_exit(want_alpha);
    }
    else if(want_offline)
    {
        //HUMAN VS HUMAN LOCAL
    }
    else
    {
        //MANAGE CONNECTION WITH PPL human vs human    
        printf("HAHA NOT IMPLEMENTED LOOSER ! But play online is covid safe, nice choice !\n");
    }

    Game g;
    set_game(&g);
    //load
    printf("Do you want create a new game (0) or load a save (1) ? (q to quit) :\n");
    want_load = get_answer(buff);
    while(want_load == -1)
    {
        printf("You have entered a wrong input, please make sure it is 0, 1 or q :\n");
        want_load = get_answer(buff);
    }
    want_exit(want_load);
    //chose the save
    if(want_load)
    {
        printf("Please type de name of the save you want :\n");
        int is_parent=fork();
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
        char path[5+BUFFER_SIZE]="save/";
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
        printf("path : %s\n",path);
        load(&g, path);

    }
        
    if ((!want_offline && is_host) || want_IA)
    {
        printf("Do you want to play with blacks (0) or whites (1) ? (q to quit) :\n");
        want_white = get_answer(buff);
        while(want_white == -1)
        {
            printf("You have entered a wrong input, please make sure it is 0, 1 or q :\n");
            want_white = get_answer(buff);
        }
        want_exit(want_white);
    }


    if (want_IA)
    {
        if (want_alpha)
        {
            human_vs_IA(&g, want_white);
        }
        else
        {
            // human_vs_nn
        }
    }
    else if(want_offline)
    {
        human_vs_human(&g);
    }
    else
    {
        //human_vs_far_human
    }


}
