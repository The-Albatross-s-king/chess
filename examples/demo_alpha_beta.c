#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "alpha_beta.h"
#include "tree.h"
#include "input.h"
#include "save_load.h"
#include <err.h>

// In work
int main(int argc, char** argv)
{
    Game g;
    set_game(&g); //remplit le plateau de pieces
    int want_load = argc==2;
    if(argc>2)
        err(3, "Too much arguments");
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
          */
        //save(&g,file) ;
    }
    int color=WHITE;

    display_board(&g.board[0], NULL, color);

    //apply_move(&g, 1, 4, 4, 5);
    human_vs_IA(&g, color);
    return 0;
}
