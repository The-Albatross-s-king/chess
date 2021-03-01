#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

// Mean to set the color and starting pieces position.
void set_board()
{
    //TODO  set colors of case to white and black.
    memset(&board, 0, 64);
    struct piece p = {ROOK, BLACK};
    board[0][0] = p;
    board[0][7] = p;

    p.piece = KNIGHT;
    board[0][1] = p;
    board[0][6] = p;

    p.piece = BISHOP;
    board[0][2] = p;
    board[0][5] = p;

    p.piece = QUEEN;
    board[0][3] = p;

    p.piece = KING;
    board[0][4] = p;

    p.piece = PAWN;
    for(int i = 0; i < 8; i++)
        board[1][i] = p;

    p.color = WHITE;
    p.piece = ROOK;
    board[7][0] = p;
    board[7][7] = p;

    p.piece = KNIGHT;
    board[7][1] = p;
    board[7][6] = p;

    p.piece = BISHOP;
    board[7][2] = p;
    board[7][5] = p;

    p.piece = QUEEN;
    board[7][3] = p;

    p.piece = KING;
    board[7][4] = p;

    p.piece = PAWN;
    for(int i = 0; i < 8; i++)
        board[6][i] = p;
}
