#include "neural_struct.h"

#pragma once

void print_layer(layer *l);

void build_layer(layer *l, size_t size);

void free_layer(layer *l);

void init_layer(layer *l, size_t size, size_t prev_size);

void copy_layer(layer *l, layer *copy, char mutated);

void front_prop_layer(layer *l, layer *prev_l, char is_last);

void soft_max_layer(layer *l);

void mix_layer(layer *l, layer *partner);

void mutate_layer(layer *l);

void save_layer(layer *l, FILE *file);

void load_layer(layer *l, FILE *file);
