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

typedef struct network
{
    layer *layers;
    size_t *sizes;
    size_t nb_layer;
}network;

typedef struct bot
{
    network *net;
    double score;
}bot;

typedef struct generation
{
    bot *bots;
    size_t size;
    float average;
}generation;

