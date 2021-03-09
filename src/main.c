#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "input.h"

// In work
int run_game(Game *g, int *x_input, int *y_input, int *new_x, int *new_y)
{
    int black_checkmate = 0;
    int white_checkmate = 0;
    size_t round = 1;
    enum pieces_color player = WHITE;
    Move_list *piece_moves;

    while(!black_checkmate && !white_checkmate)
    {
        display_board(g->board);
        is_piece(g, x_input, y_input, );
        target_pos(g, *x_input, *y_input, new_x, new_y);
        black_checkmate = is_checkmate(g, g->blacks[4]);
        white_checkmate = is_checkmate(g, g->whites[3]);
    }
}

int main()
{
    Game g;
    for(int i = 0; i < 64; i++)
        g.board[i] = NULL; //init a 0 toutes les pieces

    set_game(&g); //remplit le plateau de pieces
    Move_list* l;
    l=get_moves(&g, 1, 4);
    display_list(l);
    free_list(l);

    int applied=move(&g, 1, 4, 4, 4);
    printf("moved :%d\n",applied);
    l=get_moves(&g,3,3);
    display_list(l);
    free_list(l);

    int x = -1;
    int y = -1;
    input(&x,&y); 

    return 0;
}
