#include <stddef.h>
#pragma once

generation *build_generation(size_t size);
void free_generation(generation *g);
void sort(generation *g);
generation *get_best_bots(generation *g, size_t n);
bot *select_bot_with_factor(generation *g, size_t fitness_sum);
bot *select_bot_random(generation *g);
void duplicate(generation *g, generation *gen);
void new_gen(generation *g, char display_best);
void play(generation *g);
void train(generation *g, size_t nb_gen);
generation *build_generation_from_file(size_t size, char *path);
