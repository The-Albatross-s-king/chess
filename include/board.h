#pragma once

#include "list.h"

enum pieces_colors 
{
    BLACK=0,
    WHITE=1
};

// used in min-max pieces_values[6]={100,500,300,300,900,0};
enum pieces_types
{
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP, //bishop -> fou
    QUEEN,
    KING
};
typedef struct Piece
{
    enum pieces_types type;
    int alive;
    int moved;
    int color;
    int x;
    int y;
}Piece;

typedef struct Game
{
    Piece *board[64];
    Piece blacks[16]; //every black pieces
    Piece whites[16];
}Game;



//returns in p the piece at x,y. return 0  if out of bound
int get_piece(Game* g, int x, int y, Piece** p);

//return 1 if pos occupied by opposite color or empty
int can_move_to(Game* g, int x, int y, Piece* p);

int get_pos(int x, int y);

//check if valid and return 1 if move applied, use apply_move for no condition
int move(Game* g, int x, int y, int x2, int y2);
//return type of eaten piece, -1 if None.
int apply_move(Game* g,int x, int y, int x2, int y2);


void get_knight_moves(Game* g, Piece* p, Move_list* l);
void get_pawn_moves(Game* g, Piece* p, Move_list* l);
void get_rook_moves(Game* g, Piece* p, Move_list* l);
void get_king_moves(Game* g, Piece* p, Move_list* l);
void get_bishop_moves(Game* g, Piece* p, Move_list* l);
void get_queen_moves(Game* g,Piece* p, Move_list* l);
void get_moves(Game* g, int x, int y, Move_list* l);
//malloc pieces and init board
void set_game(Game* g);

//debugging fonction
void display(Game* g);

//free board
void free_game(Game* g);
