#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "checkmate.h"
#include "tie.h"
#include "save_load.h"
#include "input.h"

void human_vs_human(Game* g)
{
    int x_input;
    int y_input;
    int new_x; 
    int new_y;
    int black_checkmate = 0;
    int white_checkmate = 0;
    int tie = 0;
    size_t round = 1;
    enum pieces_colors player = WHITE;
    Move_list *piece_moves = init_list();

    while(!black_checkmate && !white_checkmate && !tie)
    {
        player = round % 2;
        display_board(g->board, piece_moves, player);
        printf("It's %s's turn !\n", player ? "WHITES" : "BLACKS");
        can_i_go(g, &x_input, &y_input, &piece_moves, player, 0);
        display_board(g->board, piece_moves, player);
        if(go_to(g, piece_moves , &x_input, &y_input, &new_x, &new_y))
        {
            round++;
            if(player)
                black_checkmate = is_checkmate(g, &g->blacks[3]);
            else
                white_checkmate = is_checkmate(g, &g->whites[3]);
            tie = is_tie(g, (player + 1) % 2);
        }
        else
        {
            printf("Wrong move, try again.\n");
        }

        free_list(piece_moves->next);
        piece_moves->next=NULL;
    }

    display_board(g->board, NULL, player);
    if(black_checkmate)
        printf("Black is checkmate\nWHITES WIN !\n");
    else
    {
        if(white_checkmate)
        {
            printf("White is checkmate\nBLACKS WIN !\n");
            return;
        }
        else
            printf("Tie\nNo one won !\n");
    }
    free_list(piece_moves);
}
