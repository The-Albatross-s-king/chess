#include "neural_struct.h"
#include "board.h"

#pragma once

void print_bot(bot *b);

void build_bot(bot *b);

void build_bot_xor(bot *b);

void free_bot(bot *b);

void copy_bot(bot *b, bot *dest, char mutated);

void crossover(bot *b, bot *partner, bot *dest);

void mutate_bot(bot *b);

void mix_bot(bot *b, bot *partner);

size_t scoring(Game *g, int color);

void play_bot(bot *b);

void save_bot(bot *b, char *path);

bot *load_bot(char *path);
