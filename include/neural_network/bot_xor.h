#include "neural_struct.h"

#pragma once

void print_bot(bot *b);

bot *build_bot(void);

void free_bot(bot *b);

bot *copy_bot(bot *b, char mutated);

bot *crossover(bot *b, bot *partner);

void mutate_bot(bot *b);

void mix_bot(bot *b, bot *partner);

size_t scoring(float *resultat, float *expected, size_t size);

void play_bot(bot *b);

void save_bot(bot *b, char *path);

bot *load_bot(char *path);
