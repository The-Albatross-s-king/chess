#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "display.h"
#include "board.h"
    
int clear_display()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    if (write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11) == -1)
        errx(1, "Can't clear the termial");
    return 0;
}

void display_board(Piece **board)
{
    clear_display();
    int offset = 0;
    int line = 1;

    //printf("%d %d", board->type, (board + 1)->type);

    printf("_|ABCDEFGH");
    for(unsigned int i = 0; i < 64; i++){
        if (i % 8 == 0){
            printf("|\n%d|", line);
            line++;
            offset = offset == 0 ? 1 : 0;
        }
        if (board[i] == NULL){
            if ((i + offset) % 2 == 0){
                printf(" ");
            }
            else{
                printf("\033[100m \033[0m");
            }
        }
        else{
            if (board[i]->color == 1){ 
                switch(board[i]->type){
                    case 0:
                        //printf("%d", board->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♙\033[0m");
                        else{printf("\033[1;100;38;5;17m♙\033[0m");}
                        break;
                    case 1:
                        //printf("%d", board->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♖\033[0m");
                        else{printf("\033[1;100;38;5;17m♖\033[0m");}
                        break;
                    case 2:
                        //printf("%d", board->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♘\033[0m");
                        else{printf("\033[1;100;38;5;17m♘\033[0m");}
                        break;
                    case 3:
                        //printf("%d", board->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♗\033[0m");
                        else{printf("\033[1;100;38;5;17m♗\033[0m");}
                        break;
                    case 4:
                        //printf("%d", board->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♕\033[0m");
                        else{printf("\033[1;100;38;5;17m♕\033[0m");}
                        break;
                    case 5:
                        //printf("%d", board->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♔\033[0m");
                        else{printf("\033[1;100;38;5;17m♔\033[0m");}
                        break;
                    default:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m \033[0m");
                        else
                            printf("\033[1;100;38;5;17m \033[0m");
                }
            }
            else{
                switch(board[i]->type){
                    case 0:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♟\033[0m");
                        else
                            printf("\033[1;100;33m♟\033[0m");
                        break;
                    case 1:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♜\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♜\033[0m");
                        break;
                    case 2:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♞\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♞\033[0m");
                        break;
                    case 3:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♝\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♝\033[0m");
                        break;
                    case 4:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♛\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♛\033[0m");
                        break;
                    case 5:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;90m♚\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♚\033[0m");
                        break;
                    default:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;90m \033[0m");
                        else
                            printf("\033[1;100m \033[0m");
                }
            }

        }
    }
    printf("|\n");
}
