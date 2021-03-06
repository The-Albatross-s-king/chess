#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "board.h"

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

    return 0;
}
