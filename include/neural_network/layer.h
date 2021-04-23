#include "neurone.h"

#pragma once

typedef struct layer
{
    neurone *neurones;
    size_t size;
}layer;

void print_layer(layer *l);
layer *build_layer(size_t size);
void free_layer(layer *l);
void init_layer(layer *l, size_t size, size_t prev_size);
layer *copy_layer(layer *l, char mutated);
