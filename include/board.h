#pragma once

enum pieces
{
    null, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum color
{
    WHITE, BLACK
};

struct piece
{
    enum pieces piece;
    enum color color;
};

struct piece board[8][8];

void set_board();
