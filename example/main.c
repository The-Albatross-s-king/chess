#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "display.h"
#include "input.h"

int main(){
    Game g;
    for(int i = 0; i < 64; i++)
        g.board[i] = NULL; //init a 0 toutes les pieces
    set_game(&g); //remplit le plateau de pieces

    printf("value : %d\n",move(&g,0,4,6,4));
    display(&g); //fonction temporaire pour debugger
    printf("\n");

    printf("value : %d\n",move(&g,6,4,4,4));
    display(&g);

    display_board(*g.board);

	int x = -1;
	int y = -1;
	input(&x,&y); 

    free_game(&g);
    return 0;
}
