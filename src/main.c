#include <stdlib.h>
#include <stdio.h>

#include "board.h"

int main(){
    Game g;
    for(int i = 0; i < 64; i++)
        g.board[i] = NULL; //init a 0 toutes les pieces
    set_game(&g); //remplit le plateau de pieces

    
    int len;
    Move_list* l;
    display(&g);
    l=get_pawn_moves(&g, g.board[get_pos(1,4)], &len);
    display_list(l);

    move(&g, 6, 3, 2, 3);
    move(&g, 6, 4, 3, 4);
    display(&g);
    l=get_pawn_moves(&g, g.board[get_pos(1,4)], &len);
    display_list(l);




    free_game(&g);
    return 0;
}
