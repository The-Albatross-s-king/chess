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
    int color=WHITE;

    display_board((Piece**)&g.board, NULL, WHITE);

    //apply_move(&g, 1, 4, 4, 5);
    for(int i=0; i<20; i++)
    {
        auto_move(&g, color);
        color=!color;
        sleep(0.7f);
        display_board((Piece**)&g.board, NULL, WHITE);
    }

    return 0;
}
