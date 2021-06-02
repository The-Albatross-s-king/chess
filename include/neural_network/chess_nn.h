#pragma once

#include "neural_struct.h"
#include "board.h"

void alphabeta_nn();

void auto_move_alphabeta_nn(Game* g, int cur_color, bot *bo);

void IA_vs_IA_nn(Game *g, int nb_turn, bot *b1, bot *b2);

void human_vs_IA_nn(Game *g, int color_human, bot *b);