#pragma once


enum pieces_colors {BLACK=0, WHITE=1};

// used in min-max pieces_values[6]={100,500,300,300,900,0};
enum pieces_types {
PAWN=0,
ROOK=1,
KNIGHT=2,
BISHOP=3, //bishop -> fou
QUEEN=4,
KING=5};
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
Piece* board[64];
Piece* blacks[16]; //every black pieces
Piece* whites[16];
}Game;

typedef struct Move_list
{
    struct Move_list* next;
    int x;
    int y;

}Move_list;




//returns in p the piece at x,y. return 0  if out of bound
int get_piece(Game* g, int x, int y, Piece** p);

//return 1 if pos occupied by opposite color or empty
int can_move_to(Game* g, int x, int y, Piece* p);

Move_list* init_list();

void add_list(Move_list* list, int x, int y);

int pop_list(Move_list* list, int* x, int* y);

void display_list(Move_list* l);
int get_pos(int x, int y);

//return type of eaten piece, -1 if None.
int move(Game* g,int x, int y, int x2, int y2);



Move_list* get_knight_moves(Game* g, Piece* p, int* len);
Move_list* get_pawn_moves(Game* g, Piece* p,int* len);
Move_list* get_rook_moves(Game* g, Piece* p,int* len);
Move_list* get_king_moves(Game* g, Piece* p, int* len);
Move_list* get_bishop_moves(Game* g, Piece* p, int* len);
Move_list* get_queen_moves(Game* g,Piece* p, int* len);
//malloc pieces and init board
void set_game(Game* g);


//debugging fonction
void display(Game* g);


//free board
void free_game(Game* g);
