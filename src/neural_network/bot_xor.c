#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <err.h>
#include "neural_network.h"

void print_bot(bot *b)
{
    printf("Son score est %lu\n", b->score);
    print_network(b->net);
}

bot *build_bot(void)
{
    size_t sizes[] = {2, 4, 4, 4, 2};
    size_t nb_layer = 5;
    network *net = build_network(sizes, nb_layer);
    init_network(net);
    bot *b = malloc(sizeof(bot));
    if(b == NULL)
        errx(EXIT_FAILURE, "Can't malloc");
    b->net = net;
    b->score = 0;
    return b;
}

void free_bot(bot *b)
{
    free(b);
}

bot *copy_bot(bot *b, char mutated)
{
    bot *copy = malloc(sizeof(bot));
    if(copy == NULL)
        errx(EXIT_FAILURE, "Can't malloc");
    copy->net = copy_network(b->net, mutated);

    return copy;
}

void mix_bot(bot *b, bot *partner)
{
    mix_network(b->net, partner->net);
}

bot *crossover(bot *b, bot *partner)
{
    bot *new = copy_bot(b, 0);
    mix_bot(new, partner);
    return new;
}


void mutate_bot(bot *b)
{
    mutate_network(b->net);
}


size_t scoring(float *resultat, float *expected, size_t size)
{
    size_t score = 0;
    int res = resultat[0] > resultat[1] ? 0 : 1;
    float sign = 1;
    if (!expected[res])
        sign = -35.0f;
    for(size_t i = 0; i < size; i++)
    {
        score += sign * (1 - fabs(expected[i] - resultat[i])) * 1000;
    }
    return score;
}

void play_bot(bot *b)
{
    float inputs[] = {0, 0};
    float expected[] = {1, 0};
    size_t score = 0;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    float *res = get_output(b->net);
    score += scoring(res, expected, 2);

    inputs [0] = 0;
    inputs [1] = 1;
    expected [0]= 0;
    expected [1]= 1;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    res = get_output(b->net);
    score += scoring(res, expected, 2);

    inputs[0] = 1;
    inputs[1] = 0;
    expected[0] = 0;
    expected[1] = 1;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    res = get_output(b->net);
    score += scoring(res, expected, 2);

    inputs[0] = 1;
    inputs[1] = 1;
    expected[0] = 1;
    expected[1] = 0;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    res = get_output(b->net);
    score += scoring(res, expected, 2);

    b->score = score;
}

void save_bot(bot *b, char *path)
{
    if(path == NULL)
        errx(EXIT_FAILURE, "The path can't be null");
    FILE *file = fopen(path, "w");
    if(file == NULL)
        errx(EXIT_FAILURE, "The path is invalid");
    save_network(b->net, file);
    fclose(file);

}

bot *load_bot(char *path)
{
    bot *b = malloc(sizeof(bot));
    if(b == NULL)
        errx(EXIT_FAILURE, "Can't malloc");
    FILE *file = fopen(path, "r");
    network *net = load_network(file);
    b->net = net;
    fclose(file);
    return b;
}
