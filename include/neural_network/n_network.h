#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

#define INPUT_COUNT 4
#define INPUT_SIZE 2
#define INPUT_LAYER 2
#define HIDDEN_LAYER 2
#define OUTPUT_LAYER 1

float sigmoid(float *weight, float *bias, size_t len_w, size_t len_b);
float *build_rand_f_arr(size_t len);
