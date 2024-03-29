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
    enum pieces_colors color;
    int alive;
    int moved;
    int x;
    int y;
    int id;
}Piece;

typedef struct Game
{
    Piece *board[64];
    Piece blacks[16]; //every black pieces
    Piece whites[16];
    enum pieces_colors turn;
}Game;


//usefull to describe the pieces through print
char* get_name(int type);
//returns in p the piece at x,y. return 0  if out of bound
int get_piece(Game* g, int x, int y, Piece** p);

void next_turn(Game* g);

//return 1 if pos occupied by opposite color or empty
int can_move_to(Game* g, int x, int y, Piece* p);

int get_pos(int x, int y);

//return type of eaten piece, -1 if None.
Piece* apply_move(Game* g,int x, int y, int x2, int y2);

int is_checkmate(Game* g, Piece *king);
int valid_pos(int x, int y);

void get_knight_moves(Game* g, Piece* p, Move_list* atk, Move_list* def);
void get_pawn_moves(Game* g, Piece* p, Move_list* atk, Move_list* def);
void get_rook_moves(Game* g, Piece* p, Move_list* atk, Move_list* def);
void get_king_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def, int get_rock);
void get_bishop_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def);
void get_queen_moves(Game* g,Piece* p,  Move_list* atk, Move_list* def);
void get_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def, int get_rock);
//malloc pieces and init board
void set_game(Game* g);

void show_moves(Game* g, Piece* p);
