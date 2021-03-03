#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "board.h"

void display_board(piece *board){
    int offset = 0;
    int line = 'A';

    //printf("%d %d", board->piece_type, (board + 1)->piece_type);

    printf("_|01234567");
    for(unsigned int i = 0; i < 64; i++){
        if (i % 8 == 0){
            printf("|\n%c|", line);
            line++;
            offset = offset == 0 ? 1 : 0;
        }
        if ((board[i]).piece_type == null){
            if ((i + offset) % 2 == 0){
                printf(" ");
            }
            else{
                printf("\033[100m \033[0m");
            }
        }
        else{
            if ((board[i]).color == 1){ 
                switch((board[i]).piece_type){
                    case 1:
                        //printf("%d", board->piece_type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♙\033[0m");
                        else{printf("\033[1;100;38;5;17m♙\033[0m");}
                        break;
                    case 2:
                        //printf("%d", board->piece_type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♖\033[0m");
                        else{printf("\033[1;100;38;5;17m♖\033[0m");}
                        break;
                    case 3:
                        //printf("%d", board->piece_type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♘\033[0m");
                        else{printf("\033[1;100;38;5;17m♘\033[0m");}
                        break;
                    case 4:
                        //printf("%d", board->piece_type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♗\033[0m");
                        else{printf("\033[1;100;38;5;17m♗\033[0m");}
                        break;
                    case 5:
                        //printf("%d", board->piece_type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♕\033[0m");
                        else{printf("\033[1;100;38;5;17m♕\033[0m");}
                        break;
                    case 6:
                        //printf("%d", board->piece_type);
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
                switch((board[i]).piece_type){
                    case 1:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♟\033[0m");
                        else
                            printf("\033[1;100;33m♟\033[0m");
                        break;
                    case 2:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♜\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♜\033[0m");
                        break;
                    case 3:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♞\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♞\033[0m");
                        break;
                    case 4:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♝\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♝\033[0m");
                        break;
                    case 5:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♛\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♛\033[0m");
                        break;
                    case 6:
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
