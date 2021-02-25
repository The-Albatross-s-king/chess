#include <stdio.h>
#include <stdlib.h>
#include "piece.h"


/*char verify_pawn (PIECE *table, int b_x, int b_y, int e_x, int e_y){
    PIECE begin = *(table + b_y * 8 + b_x);
    if (e_x == b_x ){
        if((b_y == e_y + 2 && begin->has_moved == false && begin->color == black
                && (table + 16)->type != null)
        || (b_y == e_y - 2 && begin->has_moved == false && begin->color == white
                && (table - 16)->type != null)
        || (b_y == e_y + 1 && begin->color == black
                && (table + 8)->type != null)
        || (b_y == e_y - 1 && begin->color == white
                && (table - 8)->type != null)){
            begin.has_moved = true; 
            return 1;
        }
        else{
            return 0;
        }
    }
    if (e_x == b_x ){

}

void verify (PIECE *table, int b_x, int b_y, int e_x, int e_y){

    

}
*/
void move_piece (PIECE *table, int b_x, int b_y, int e_x, int e_y){
    PIECE begin = *(table + b_y * 8 + b_x);
    (table + b_y * 8 + b_x)->type = 0;
    (table + b_y * 8 + b_x)->color = 0;
    (table + e_y * 8 + e_x)->type = begin.type;
    (table + e_y * 8 + e_x)->color = begin.color;
}

void start(PIECE *table){
    table->type = tour;
    table->color = 1;
    table++;
    table->type = cavalier;
    table->color = 1;
    table++;
    table->type = fou;
    table->color = 1;
    table++;
    table->type = dame;
    table->color = 1;
    table++;
    table->type = roi;
    table->color = 1;
    table++;
    table->type = fou;
    table->color = 1;
    table++;
    table->type = cavalier;
    table->color = 1;
    table++;
    table->type = tour;
    table->color = 1;
    table++;

    for(unsigned int i = 0; i < 8; i++){
        table->type = 1;
        table->color = 1;
        table++;
    }
    for(unsigned int i = 0; i < 32; i++){
        table->type = 0;
        table->color = 0;
        table++;
    }
    for(unsigned int i = 0; i < 8; i++){
        table->type = pion;
        table->color = 0;
        table++;
    }

    table->type = tour;
    table->color = 0;
    table++;
    table->type = cavalier;
    table->color = 0;
    table++;
    table->type = fou;
    table->color = 0;
    table++;
    table->type = dame;
    table->color = 0;
    table++;
    table->type = roi;
    table->color = 0;
    table++;
    table->type = fou;
    table->color = 0;
    table++;
    table->type = cavalier;
    table->color = 0;
    table++;
    table->type = tour;
    table->color = 0;
    table++;

}


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

/*int main (void){
    PIECE *table = calloc(64, sizeof(PIECE));
    display_table(table);
    free(table);
}*/

