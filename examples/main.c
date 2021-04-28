#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "checkmate.h"
#include "input.h"
#include "save_load.h"
#include "tie.h"

// In work
void run_game(Game *g, int *x_input, int *y_input, int *new_x, int *new_y)
{
    int black_checkmate = 0;
    int white_checkmate = 0;
    int tie = 0;
    size_t round = 1;
    enum pieces_colors player = WHITE;
    Move_list *piece_moves = NULL;

    while(!black_checkmate && !white_checkmate && !tie)
    {
        piece_moves = init_list();
        player = round % 2;
        display_board(g->board, piece_moves, player);
        printf("It's %s's turn !\n", player ? "WHITE" : "BLACK");
        can_i_go(g, x_input, y_input, &piece_moves, player);
        display_board(g->board, piece_moves, player);
        if(go_to(g, piece_moves ,x_input, y_input, new_x, new_y))
        {
            round++;
        }
        else
        {
            printf("Wrong move, try again loser !!\n");
            sleep(2);
        }
        black_checkmate = is_checkmate(g, &g->blacks[3]);
        white_checkmate = is_checkmate(g, &g->whites[3]);
        tie = is_tie(g, (player + 1) % 2);
        free_list(piece_moves);
    }

    display_board(g->board, NULL, player);
    if(black_checkmate)
        printf("Black is checkmate\nWHITE WON !\n");
    else
    {
        if(white_checkmate)
        {
            printf("White is checkmate\nBLACK WON !\n");
            return;
        }
        else
            printf("Tie\nNo one won !\n");
    }
    return;
}

int main(int argc, char **argv)
{
    if (argc > 2)
        errx(1, "too many arguments");
    Game g;
    for(int i = 0; i < 64; i++)
        g.board[i] = NULL; // Use memset instead

    set_game(&g); //Initial state of a the checkerboard
    if(argc == 2)
    {
        load(&g, argv[1]);
    }
    int x = -1;
    int y = -1;
    int new_x = -1;
    int new_y = -1;
    run_game(&g, &x, &y, &new_x, &new_y);
    // display_board(g.board, NULL, 0);

    return 0;
}

