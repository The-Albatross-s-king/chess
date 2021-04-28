#pragma once

#include "board.h"
#include "list.h"

void is_treason(Game *g, Piece *p, Move_list *l);

void king_suicide(Game *g, Piece *p, Move_list *king_moves);

void impossible_diag_move(Piece *p, Move_list *l, int x, int y);

void impossible_cross_move(Piece *p, Move_list *l, int x, int y);

void need_protect(Game *g, Piece *p, Move_list *l, Piece *enemy);

int is_one_check(Game *g, Piece *k, Piece **p);