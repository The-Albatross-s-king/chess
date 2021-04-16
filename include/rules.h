#pragma once

#include "board.h"
#include "list.h"

void is_treason(Game *g, Piece *p, Move_list *l);
void king_suicide(Game *g, Piece *p, Move_list *king_moves);
