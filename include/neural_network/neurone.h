#include <stdio.h>
#include <stddef.h>
#include "neural_struct.h"

#pragma once

void build_neurone(neurone *n, size_t size);

void init_neurone(neurone *n);

void free_neurone(neurone *n);

void copy_neurone(neurone *n, neurone *copy, char mutated);

void mix(neurone *n, neurone *m);

void print_neurone(neurone *n);

float activation(float f);

float sigmoid(float f);

float soft_max(neurone *n, float f);

void mutate(neurone *n);

void front_prop(neurone *n, layer *prev_l, char is_last);

void save_neurone(neurone *n, FILE *file);

void load_neurones(neurone *n, FILE *file);
