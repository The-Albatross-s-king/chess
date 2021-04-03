#pragma once
#include "board.h"

// return the sum of attack and defense
int get_position_score(Game* game, int cur_color);


int get_atk_def(Game *game, int pos, int* scores);

int in_danger(Game *game, int pos);

int is_protected(Game *game, int pos);
