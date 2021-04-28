#include "neurone.h"
#include "layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>

void print_layer(layer *l)
{
    printf("The layer contains %zu neurones.\n", l->size);
    for(size_t i = 0; i < l->size; ++i)
        print_neurone(l->neurones + i);
}

void build_layer(layer *l, size_t size)
{
    l->neurones = malloc(size * sizeof(neurone));
    if(l->neurones == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");

    l->size = size;
}

void free_layer(layer *l)
{
    for (size_t i = 0; i < l->size; i++)
    {
        free_neurone(l->neurones+i);
    }
    free(l->neurones);
}

void init_layer(layer *l, size_t size, size_t prev_size)
{
    for(size_t i = 0; i < size; ++i)
    {
        build_neurone(l->neurones+i, prev_size);
        init_neurone(l->neurones + i);
    }
}

void copy_layer(layer *l, layer *copy, char mutated)
{
    //build_layer(dest, l->size);
    //init_layer(dest, l->size, l->neurones->size);
    for(size_t i = 0; i < l->size; ++i)
    {
        copy_neurone(l->neurones + i, copy->neurones + i, mutated);
    }
}

void front_prop_layer(layer *l, layer *prev_l, char is_last)
{
    for(size_t i = 0; i < l->size; ++i)
        front_prop(l->neurones + i, prev_l, is_last);
    if(is_last)
        soft_max_layer(l);
}

void soft_max_layer(layer *l)
{
    float sum = 0;
    for(size_t i = 0; i < l->size; ++i)
        sum += expf(l->neurones[i].value);

    for(size_t i = 0; i < l->size; ++i)
        soft_max(l->neurones + i, sum);
}

void mix_layer(layer *l, layer *partner)
{
    if(l->size != partner->size)
        errx(EXIT_FAILURE, "Trying to mix layer with different sizes");

    for(size_t i = 0; i < l->size; ++i)
    {
        mix(l->neurones + i, partner->neurones + i);
    }
}

void mutate_layer(layer *l)
{
    for(size_t i = 0; i < l->size; ++i)
        mutate(l->neurones + i);
}

void save_layer(layer *l, FILE *file)
{
    if(file == NULL)
        errx(EXIT_FAILURE, "The file can't be null");
    char str[10];
    sprintf(str, "%lu\n", l->size);
    fputs(str, file);
    for(size_t i = 0; i < l->size; i++)
    {
        save_neurone(l->neurones + i, file);
    }
}

void load_layer(layer *l, FILE *file)
{
    if (file == NULL)
        errx(EXIT_FAILURE, "The file can't be null");

    size_t size = 0;
    if (fscanf(file, "%lu\n", &size) <= 0)
        errx(EXIT_FAILURE, "Can't read the file in load_layer");
    build_layer(l, size);

    for(size_t i = 0; i < size; i++)
    {
        load_neurones(l->neurones+i, file);
    }
}
