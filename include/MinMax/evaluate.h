#pragma once
#include "board.h"

// return the sum of attack and defense
double position_score(Piece *p);

double get_atk_def_pos(Game *game, int pos);

double evaluate(Game* g, int cur_color);

double random_double(void);

int get_score_piece(Piece *p);
