#include <stddef.h>

#pragma once

#define INPUT_COUNT 4
#define INPUT_SIZE 2
#define INPUT_LAYER 2
#define HIDDEN_LAYER 2
#define OUTPUT_LAYER 1

typedef struct neurone
{
    float *weights;
    float bias;
    float value;
    size_t size;
}neurone;

neurone *build_neurone(size_t size);

void init_neurone(neurone *n);

void copy_neurone(neurone *n, neurone *copy, char mutated);

void mix(neurone *n, neurone *m);

void print_neurone(neurone *n);

float activation(float f);

float sigmoid(float *weight, float *bias, size_t len_w, size_t len_b);

float soft_max(neurone *n, float f);
