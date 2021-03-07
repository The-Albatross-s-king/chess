#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "minmax.h"
#include "input.h"

// In work
void run_game(Game *g, int *x_input, int *y_input, int *new_x, int *new_y)
{
    int black_checkmate = 0;
    int white_checkmate = 0;
    size_t round = 1;
    enum pieces_colors player = WHITE;
    Move_list *piece_moves = NULL;

    while(!black_checkmate && !white_checkmate)
    {
        player = round % 2;
        display_board(g->board, NULL, player);
        printf("It's %s's turn !\n", player ? "WHITE" : "BLACK");
        can_i_go(g, x_input, y_input, piece_moves, player);
        if(go_to(g, x_input, y_input, new_x, new_y))
        {
            round++;
        }
        else
        {
            printf("Wrong move, try again loser !!\n");
            sleep(2);
        }
        black_checkmate = is_checkmate(g, &g->blacks[3]);
        white_checkmate = is_checkmate(g, &g->whites[4]);
    }

    display_board(g->board, NULL, player);
    if(black_checkmate)
        printf("Black is checkmate\nWHITE WON !");
    else
        printf("White is checkmate\nBLACK WON !");

    return;
}

int main()
{
    Game g;
    set_game(&g); //remplit le plateau de pieces
    int color=BLACK;


    apply_move(&g, 1, 3, 3, 2);
    for(int i=0; i<10; i++)
    {
        auto_move(&g, color);
        color=!color;
        display_board(g.board);
    }
    //Piece* to_move;
    //apply_move(&g, 0, 3, 4, 4);
    
    //printf("%d %d\n", to_move->x, to_move->y);
    /*Move_list* l=init_list();
    get_moves(&g, &g.blacks[3], l);
    printf("size : %ld\n", get_size_list(l));
    display_list(l);
    while(!is_empty(l))
        pop_list(l,&x,&y);
    get_moves(&g, &g.blacks[3], l);
    printf("size : %ld\n", get_size_list(l));
    display_list(l);
    
    int applied=move(&g, 1, 4, 4, 4);
    printf("moved :%d\n",applied);
    get_moves(&g,3,3,l);
    display_list(l);
    free_list(l);*/
   return 0;
}
