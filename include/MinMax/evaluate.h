#pragma once
#include "board.h"

// return the sum of attack and defense
double position_score(Piece *p);

double get_atk_def_pos(Game *game, int pos, int* scores);

double evaluate(Game* g, int cur_color, int* SCORES);

double random_double(void);
