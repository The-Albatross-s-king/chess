#ifndef CHECKMATE_H
#define CHECKMATE_H

int is_check(Game* g, Piece *king);

int check_after_move(Game *g, Piece *p, int new_x, int new_y);

int is_checkmate(Game* g, Piece *king);

#endif
