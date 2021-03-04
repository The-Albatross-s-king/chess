#pragma once

// used in min-max pieces_values[6]={100,500,300,300,900,0};
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
    enum pieces type;
    int alive;
    int moved;
    enum color color;
    int x;
    int y;
}piece;

typedef struct Game
{
piece* board[64];
piece* blacks[16]; //every black pieces
piece* whites[16];
}Game;

int get_pos(int x, int y);

//return type of eaten piece, -1 if None.
int move(Game* g,int x, int y, int x2, int y2);

//malloc pieces and init board
void set_game(Game* g);


//debugging fonction
void display(Game* g);

//free board
void free_game(Game* g);

void set_board(piece *board);

