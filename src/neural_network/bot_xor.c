#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <err.h>

#include "evaluate.h"
#include "neural_network.h"

void print_bot_xor(bot *b)
{
    printf("Son score est %f\n", b->score);
    print_network(b->net);
}

void build_bot(bot *b)
{
    size_t sizes[] = {64, 32, 32, 2};
    size_t nb_layer = 4;
    network *net = build_network(sizes, nb_layer);
    init_network(net);
    b->net = net;
    b->score = 0;
}

void build_bot_xor(bot *b)
{
    size_t sizes[] = {2, 4, 2};
    size_t nb_layer = 3;
    network *net = build_network(sizes, nb_layer);
    init_network(net);
    b->net = net;
    b->score = 0;
}

void free_bot(bot *b)
{
    free_network(b->net);
}

void copy_bot(bot *b, bot *dest, char mutated)
{
    network *tmp = dest->net;

    dest->net = copy_network(b->net, mutated);

    free_network(tmp); 
}

void mix_bot(bot *b, bot *partner)
{
    mix_network(b->net, partner->net);
}

void crossover(bot *b, bot *partner, bot *dest)
{
    copy_bot(b, dest, 0);
    mix_bot(dest, partner);
}

void mutate_bot(bot *b)
{
    mutate_network(b->net);
}

float scoring_xor(float *resultat, float *expected, size_t size)
{
    int exp = expected[0] ? 0 : 1;
    int res = resultat[0] > resultat[1] ? 0 : 1;
    size = 2 * size;
    if (exp != res)
        return 5 * (1 - resultat[exp]) - 5;
    return  10 + 20 * resultat[exp];
}

double scoring(Game *g, int color)
{
    return get_atk_def_pos(g, color);
}

float scoring_xor_2(float *resultat, float *expected, size_t size)
{
    int exp = expected[0] ? 0 : 1;
    int res = resultat[0] > resultat[1] ? 0 : 1;
    size = 2 * size;
    if (exp != res)
        return - resultat[exp == 0 ? 1 : 0];
    return  10 + 20 * resultat[exp];
}

void play_bot(bot *b)
{
    float inputs[] = {0, 0};
    float expected[] = {1, 0};
    float score = 0.0f;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    float *res = get_output(b->net);
    score += scoring_xor_2(res, expected, 2);
    free(res);

    inputs [0] = 0;
    inputs [1] = 1;
    expected [0]= 0;
    expected [1]= 1;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    res = get_output(b->net);
    score += scoring_xor_2(res, expected, 2);
    free(res);

    inputs[0] = 1;
    inputs[1] = 0;
    expected[0] = 0;
    expected[1] = 1;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    res = get_output(b->net);
    score += scoring_xor_2(res, expected, 2);
    free(res);

    inputs[0] = 1;
    inputs[1] = 1;
    expected[0] = 1;
    expected[1] = 0;
    feed(b->net, inputs, 2);
    front_prop_network(b->net);
    res = get_output(b->net);
    score += scoring_xor_2(res, expected, 2);
    // printf("%f\n", score);
    free(res);
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
