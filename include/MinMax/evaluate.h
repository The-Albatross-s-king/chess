#pragma once
#include "board.h"

// return the sum of attack and defense
double get_position_score(Game* game, int cur_color);

double position_score(Piece *p);

double get_atk_def(Game *game, int pos, int* scores);

double in_danger(Game *game, int pos);

double is_protected(Game *game, int pos);
