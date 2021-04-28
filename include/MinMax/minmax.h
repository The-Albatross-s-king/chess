#pragma once
#include "board.h"

///retourne le score
//

void auto_move_minmax(Game* g, int cur_color);
void minmax(Game* g, int* x, int* y, Piece** best_piece, int cur_color); 
