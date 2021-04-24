#include <stdio.h>
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
    size_t sizes[] = {2, 2, 2};
    size_t nb_layer = 3;
    network *net = build_network(sizes, nb_layer);
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

void mutate_bot(bot *b)
{
    mutate_network(b->net);
}

void mix_bot(bot *b, bot *partner)
{
    mix_network(b->net, partner->net);
}

void play(bot *b)
{
    float inputs[] = {0, 0};
    float inputs[] = {0, 1};
    float inputs[] = {1, 0};
    float inputs[] = {1, 1};

}

void save_bot(bot *b, char *path)
{
    if(path == NULL)
        errx(EXIT_FAILURE, "The path can't be null");
    FILE *file = fopen(path, "r");
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
    FILE *file = fopen(path, "w");
    network *net = load_network(file);
    b->net = net;
    fclose(file);
    return b;
}
