#ifndef BOARD_H
#define BOARD_H

enum pieces
{
    null, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum color
{
    WHITE, BLACK
};

typedef struct piece
{
    enum pieces piece_type;
    enum color color;
}piece;

void set_board(piece *board);

#endif
