#pragma once

#include "board.h"
#include "list.h"

int is_treason(Game *g, Piece *p);
void king_suicide(Game *g, Piece *p, Move_list *king_moves);
