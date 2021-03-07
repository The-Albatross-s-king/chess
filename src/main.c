#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "minmax.h"
int main()
{
    Game g;
    for(int i = 0; i < 64; i++)
        g.board[i] = NULL; //init a 0 toutes les pieces

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
