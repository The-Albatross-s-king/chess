#pragma once

#include "board.h"

void compute_minmax(int* first_move, int max, Tree* parent, Tree* T);

void alphabeta();

void auto_move_alphabeta(Game* g, int cur_color);

void IA_vs_IA(Game *g, int nb_turn);

void human_vs_IA(Game *g, int color_human);