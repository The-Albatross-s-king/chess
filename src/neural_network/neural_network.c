#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "neurone.h"
#include "layer.h"
#include "neural_network.h"

void print_network(network *net)
{
    printf("The network contains %zu layers.\n", net->nb_layer);
    for(size_t i = 0; i < net->nb_layer; ++i)
        print_layer(net->layers + i);
}

network *build_network(size_t *sizes, size_t nb_layer)
{
    network *net = malloc(sizeof(network));
    if(net == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");

    net->layers = malloc(nb_layer * sizeof(layer));
    if(net->layers == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");

    net->sizes = malloc(nb_layer * sizeof(size_t));
    if(net->sizes == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");
    for(size_t i = 0; i < nb_layer; i++)
    {
        net->sizes[i] = sizes[i];
    }

    net->nb_layer = nb_layer;
    return net;
}

void free_network(network *net)
{
    free(net->sizes);
    free(net->layers);
    free(net);
}

void init_network(network *net)
{
    for (size_t i = 0; i < net->nb_layer; i++)
    {
        net->layers[i] = *build_layer(net->sizes[i]);
        init_layer(net->layers + i, net->sizes[i], i == 0 ? 0 : net->sizes[i - 1]);
    }
}

void feed(network *net, float *input, size_t input_size)
{
    if(net->sizes[0] != input_size)
        errx(EXIT_FAILURE, "The input size must be equal to the size of the "
                "first layer");
    for(size_t i = 0; i < input_size; i++)
    {
        net->layers[0].neurones[i].value = input[i];
    }
}

void front_prop_network(network *net)
{
    for(size_t i = 1; i < net->nb_layer; i++)
    {
        front_prop_layer(net->layers + i, net->layers + i -1, i == net->nb_layer-1);
    }
}

float *get_output(network *net)
{
    float *result = malloc(sizeof(float) * net->sizes[net->nb_layer - 1]);
    for(size_t i = 0; i < net->sizes[net->nb_layer - 1]; i++)
    {
        result[i] = net->layers[net->nb_layer - 1].neurones[i].value;
    }
    return result;
}

void mix_network(network *net, network *partner)
{
    if(net->nb_layer != partner->nb_layer)
        errx(EXIT_FAILURE, "The number of layer must be identic in mix.");
    for(size_t i = 0; i < net->nb_layer; i++)
    {
        mix_layer(net->layers + i, partner->layers + i);
    }
}

void mutate_network(network *net)
{
    for(size_t i = 0; i < net->nb_layer; i++)
    {
        mutate_layer(net->layers + i);
    }
}

