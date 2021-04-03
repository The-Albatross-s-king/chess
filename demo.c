#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "minmax.h"
#include "input.h"
#include "save_load.h"
#include <err.h>

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
        display_list(piece_moves);
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

int main(int argc, char** argv)
{
    Game g;
    set_game(&g); //remplit le plateau de pieces
    int want_load= argc==2;
    if(argc>=3)
        err(3, "Need filename to load");
    //char* file="save/situation3.txt";
    //load(&g, "save/basic.txt");
    if(want_load)
    {
        load(&g, argv[1]);
    }
    else
    {
        /*clear_board(&g);
        char black='1';
        char white='2';
        put_piece(&g, 0, 7, black, KING);
        put_piece(&g, 2, 6, white, PAWN);
        put_piece(&g, 3, 4, white, BISHOP);
        put_piece(&g, 1, 6, black, ROOK);
        */
        /*show_moves(&g, p);
          auto_move(&g, BLACK);
          show_moves(&g, p);*/
        //save(&g,file) ;
    }
    int color=BLACK;

    display_board((Piece**)&g.board, NULL, WHITE);
    
    //apply_move(&g, 1, 4, 4, 5);
    for(int i=0; i<1; i++)
    {
        auto_move(&g, color);
        color=!color;
        sleep(1);
        display_board((Piece**)&g.board, NULL, WHITE);
    }

   return 0;
}
