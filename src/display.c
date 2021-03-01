#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "board.h"

void display_table(PIECE *table){
    int offset = 0;
    int line = 'A';

    //printf("%d %d", table->type, (table + 1)->type);

    printf("_|01234567");
    for(unsigned int i = 0; i < 64; i++){
        if (i % 8 == 0){
            printf("|\n%c|", line);
            line++;
            offset = offset == 0 ? 1 : 0;
        }
        if ((table + i)->type == null){
            if ((i + offset) % 2 == 0){
                printf(" ");
            }
            else{
                printf("\033[100m \033[0m");
            }
        }
        else{
            if ((table + i)->color == 1){ 
                switch((table + i)->type){
                    case 1:
                        //printf("%d", table->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♙\033[0m");
                        else{printf("\033[1;100;38;5;17m♙\033[0m");}
                        break;
                    case 2:
                        //printf("%d", table->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♖\033[0m");
                        else{printf("\033[1;100;38;5;17m♖\033[0m");}
                        break;
                    case 3:
                        //printf("%d", table->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♘\033[0m");
                        else{printf("\033[1;100;38;5;17m♘\033[0m");}
                        break;
                    case 4:
                        //printf("%d", table->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♗\033[0m");
                        else{printf("\033[1;100;38;5;17m♗\033[0m");}
                        break;
                    case 5:
                        //printf("%d", table->type);
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;34m♕\033[0m");
                        else{printf("\033[1;100;38;5;17m♕\033[0m");}
                        break;
                    case 6:
                        //printf("%d", table->type);
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
                switch((table + i)->type){
                    case pion:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♟\033[0m");
                        else
                            printf("\033[1;100;33m♟\033[0m");
                        break;
                    case tour:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♜\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♜\033[0m");
                        break;
                    case cavalier:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♞\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♞\033[0m");
                        break;
                    case fou:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♝\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♝\033[0m");
                        break;
                    case dame:
                        if ((i + offset) % 2 == 0)
                            printf("\033[1;30m♛\033[0m");
                        else
                            printf("\033[1;100;38;5;0m♛\033[0m");
                        break;
                    case roi:
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
