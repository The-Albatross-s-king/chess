#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "display.h"
#include "board.h"

// clear the teminal
int clear_display()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    if (write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11) == -1)
        errx(1, "Can't clear the termial");
    return 0;
}

// Create a bitmap to store list of moves in a more readable way for the display
// function.
unsigned long create_bitboard(Move_list *list)
{
    unsigned long bitboard = 0;
    unsigned long pos = 1;
    if(list == NULL)
        return 0;
    list = list->next;
    if(list == NULL)
        return 0;
    for (; list != NULL; list = list->next)
    {
        int index = get_pos(list->x, list->y);
        bitboard = (pos << index) | bitboard;
    }

    return bitboard;
}

// It display the board with the list of possible move
void display_board(Piece **board, Move_list *list, enum pieces_colors side)
{
    int step = 1;
    int begin = 0;
    int line = 2;
    int offset = 0;
    //clear_display();
    if (side == BLACK)
    {
        offset = 1;
        line = 7;
        printf("_|HGFEDCBA|\n8|");
        step = -1;
        begin = 63;
    }
    else
        printf("_|ABCDEFGH|\n1|");
    unsigned long bitboard = create_bitboard(list);
    int white_bg = 100;
    int white_p = 96;
    int black_p = 31;
    int possible = 42;

    char is_move = 0;
    unsigned char column = 0;
    for(int i = begin; (step == 1 && i < 64) || (i >= 0 && step == -1); i+= step){
        is_move = (bitboard >> i) % 2;
        if (column == 8)
        {
            printf("|\n%d|", line);
            line += step;
            offset = offset == 0 ? 1 : 0;
            column = 0;
        }
        column++;
        if (board[i] == NULL){
            if (is_move)
            {
                printf("\033[%dm \033[0m", possible);
            }
            else
            {
                if ((i + offset) % 2 == 0){
                    printf(" ");
                }
                else{
                    printf("\033[%dm \033[0m", white_bg);
                }
            }
        }
        else{
            if (board[i]->color == 1){ 
                switch(board[i]->type){
                    case 0:
                        if (is_move)
                            printf("\033[1;%d;%dm♙\033[0m", possible, white_p);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♙\033[0m", white_p);
                            else{printf("\033[1;%d;%dm♙\033[0m", white_bg, white_p);}
                        }
                        break;
                    case 1:
                        if (is_move)
                            printf("\033[1;%d;%dm♖\033[0m", white_p, possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♖\033[0m", white_p);
                            else{printf("\033[1;%d;%dm♖\033[0m", white_bg, white_p);}
                        }
                        break;
                    case 2:
                        if (is_move)
                            printf("\033[1;%d;%dm♘\033[0m", possible, white_p);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♘\033[0m", white_p);
                            else{printf("\033[1;%d;%dm♘\033[0m", white_p, white_bg);}
                        }
                        break;
                    case 3:
                        if (is_move)
                            printf("\033[1;%d;%dm♗\033[0m", white_p, possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♗\033[0m", white_p);
                            else{printf("\033[1;%d;%dm♗\033[0m", white_p, white_bg);}
                        }
                        break;
                    case 4:
                        if (is_move)
                            printf("\033[1;%d;%dm♕\033[0m", possible, white_p);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♕\033[0m", white_p);
                            else{printf("\033[1;%d;%dm♕\033[0m", white_p, white_bg);}
                        }
                        break;
                    case 5:
                        if (is_move)
                            printf("\033[1;%d;%dm♔\033[0m", white_p, possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♔\033[0m", white_p);
                            else{printf("\033[1;%d;%dm♔\033[0m", white_p, white_bg);}
                        }
                        break;
                    default:
                        if (is_move)
                            printf("\033[1;%dm \033[0m", possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm \033[0m", white_p);
                            else
                                printf("\033[1;%dm \033[0m", white_bg);
                        }
                }
            }
            else{
                switch(board[i]->type){
                    case 0:
                        if (is_move)
                            printf("\033[1;%dm♙\033[0m", possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♙\033[0m", black_p);
                            else
                                printf("\033[1;%d;%dm♙\033[0m", white_bg, black_p);
                        }
                        break;
                    case 1:
                        if (is_move)
                            printf("\033[1;%d;%dm♜\033[0m", black_p, possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♜\033[0m", black_p);
                            else
                                printf("\033[1;%d;%dm♜\033[0m", black_p, white_bg);
                        }
                        break;
                    case 2:
                        if (is_move)
                            printf("\033[1;%d;%dm♞\033[0m",black_p, possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♞\033[0m", black_p);
                            else
                                printf("\033[1;%d;%dm♞\033[0m", black_p, white_bg);
                        }
                        break;
                    case 3:
                        if (is_move)
                            printf("\033[1;%d;%dm♝\033[0m", black_p, possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♝\033[0m", black_p);
                            else
                                printf("\033[1;%d;%dm♝\033[0m", white_bg, black_p);
                        }
                        break;
                    case 4:
                        if (is_move)
                            printf("\033[1;%d;%dm♛\033[0m", possible, black_p);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♛\033[0m", black_p);
                            else
                                printf("\033[1;%d;%dm♛\033[0m", black_p, white_bg);
                        }
                        break;
                    case 5:
                        if (is_move)
                            printf("\033[1;%d;%dm♚\033[0m", possible, black_p);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;%dm♚\033[0m", black_p);
                            else
                                printf("\033[1;%d;%dm♚\033[0m", black_p, white_bg);
                        }
                        break;
                    default:
                        if (is_move)
                            printf("\033[1;%dm \033[0m", possible);
                        else
                        {
                            if ((i + offset) % 2 == 0)
                                printf("\033[1;m \033[0m");
                            else
                                printf("\033[1;%dm \033[0m", white_bg);
                        }
                }
            }

        }
    }
    printf("|\n");
}
