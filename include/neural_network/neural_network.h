#include "neural_struct.h"

#pragma once

void print_network(network *net);

network *build_network(size_t *size, size_t nb_layer);

void free_network(network *net);

void init_network(network *net);

void feed(network *net, float *input, size_t input_size);

void front_prop_network(network *net);

float *get_output(network *net);

void mix_network(network *net, network *partner);

void mutate_network(network *net);
