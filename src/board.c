#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

// Mean to set the color and starting piece position.
void set_board(piece *board)
{
    memset(board, 0, 64 * sizeof(piece));
    piece p = {ROOK, BLACK};
    board[0] = p;
    board[7] = p;

    p.piece_type = KNIGHT;
    board[1] = p;
    board[6] = p;

    p.piece_type = BISHOP;
    board[2] = p;
    board[5] = p;

    p.piece_type = QUEEN;
    board[3] = p;

    p.piece_type = KING;
    board[4] = p;

    p.piece_type = PAWN;
    for(int i = 0; i < 8; i++)
        board[8 + i] = p;

    p.color = WHITE;
    p.piece_type = ROOK;
    board[56] = p;
    board[63] = p;

    p.piece_type = KNIGHT;
    board[57] = p;
    board[62] = p;

    p.piece_type = BISHOP;
    board[58] = p;
    board[61] = p;

    p.piece_type = QUEEN;
    board[59] = p;

    p.piece_type = KING;
    board[60] = p;

    p.piece_type = PAWN;
    for(int i = 0; i < 8; i++)
        board[48 + i] = p;
}
