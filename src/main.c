#include <stdlib.h>
#include <stdio.h>

#include "board.h"

int main(){
    Piece* board[64]; //le plateau
    Piece* blacks[16]; //toutes les pieces noires dans l'ordre de debut de partie
    Piece* whites[16]; //same
    for(int i = 0; i < 64; i++)
        board[i] = NULL; //init a 0 toutes les pieces
    SetPieces(board, blacks, whites); //remplit le plateau de pieces

    printf("value : %d\n",Move(board,board[GetPos(0,4)],6,4));
    Display(board); //fonction temporaire pour debugger
    printf("\n");

    printf("value : %d\n",Move(board,board[GetPos(6,4)],4,4));
    Display(board);

    //check les pieces
    for(int i = 0; i < 16; i++)
        printf("%d ",whites[i]->value);
    printf("\n");

    return 0;
}
