#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "input.h"

// In work
void run_game(Game *g, int *x_input, int *y_input, int *new_x, int *new_y)
{
    int black_checkmate = 0;
    int white_checkmate = 0;
    size_t round = 0;
    //enum pieces_colors player = WHITE;
    Move_list *piece_moves = NULL;

    while(!black_checkmate && !white_checkmate)
    {
        round++;
        display_board(g->board);
        is_piece(g, x_input, y_input, piece_moves);
        target_pos(g, x_input, y_input, new_x, new_y);
        black_checkmate = is_checkmate(g, &g->blacks[4]);
        white_checkmate = is_checkmate(g, &g->whites[3]);
    }

    if(black_checkmate)
        printf("Black is checkmate\nWHITE WON !");
    else
        printf("White is checkmate\nBLACK WON !");

    return;
}

int main()
{
    Game g;
    for(int i = 0; i < 64; i++)
        g.board[i] = NULL; // Use memset instead

    set_game(&g); //Initial state of a the checkerboard
    int x = -1;
    int y = -1;
    int new_x = -1;
    int new_y = -1;
    run_game(&g, &x, &y, &new_x, &new_y);

    return 0;
}
