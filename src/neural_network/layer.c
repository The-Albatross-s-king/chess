#include "layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

void print_layer(layer *l)
{
    printf("The layer contains %zu neurones.\n", l->size);
    for(size_t i = 0; i < l->size; ++i)
        print_neurone(l->neurones + i);
}

layer *build_layer(size_t size)
{
    layer *l = malloc(sizeof(layer));
    if(l == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");

    l->neurones = malloc(size * sizeof(neurone));
    if(l->neurones == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");

    l->size = size;
    return l;
}

void free_layer(layer *l)
{
    free(l->neurones);
    free(l);
}

void init_layer(layer *l, size_t size, size_t prev_size)
{
    for(size_t i = 0; i < size; ++i)
    {
        l->neurones[i] = *build_neurone(prev_size);
        init_neurone(l->neurones + i);
    }
}

layer *copy_layer(layer *l, char mutated)
{
    layer *copy_l = build_layer(l->size);
    init_layer(copy_l, l->size, l->neurones->size);
    for(size_t i = 0; i < l->size; ++i)
    {
        copy_neurone(l->neurones + i, copy_l->neurones + i, mutated);
    }

    return copy_l;
}
