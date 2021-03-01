#pragma once

typedef struct Piece
{
    int type;
    int alive;
    int value;
    int color;
    int pos[2];
}Piece;

int GetPos(int x, int y);

int Move(Piece* board[64], Piece *p, int x, int y);

void SetPieces(Piece* board[64], Piece* blacks[16], Piece* whites[16]);

void Display(Piece* b[64]);
