#include <stddef.h>

#pragma once

typedef struct neurone
{
    float *weights;
    float bias;
    float value;
    size_t size;
}neurone;

typedef struct layer
{
    neurone *neurones;
    size_t size;
}layer;

