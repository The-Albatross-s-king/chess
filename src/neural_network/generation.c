#include "neural_struct.h"
#include "bot_xor.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <err.h>

generation *build_generation(size_t size)
{
    generation *g = malloc(sizeof(generation));
    if(g == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");

    g->bots = malloc(size * sizeof(bot));
    if(g->bots == NULL)
        errx(EXIT_FAILURE, "Can not allocate memory");

    g->size = size;
    for(size_t i = 0; i < size; ++i)
    {
        g->bots[i] = *build_bot();
    }

    return g;
}

void free_generation(generation *g)
{
    free(g->bots);
    free(g);
}

void sort(generation *g)
{
    char sorted;
    for(ssize_t i = g->size - 1; i > -1; --i)
    {
        sorted = 1;
        bot temp;
        for(ssize_t j = 0; j < i; ++j)
        {
            if(g->bots[j].score < g->bots[j + 1].score)
            {
                temp = g->bots[j];
                g->bots[j] = g->bots[j + 1];
                g->bots[j + 1] = temp;
                sorted = 0;
            }
        }

        if(sorted)
            break;
    }
}

generation *get_best_bots(generation *g, size_t n)
{
    sort(g);
    generation *best = build_generation(n);
    for(size_t i = 0; i < n; ++i)
    {
        best->bots[i] = g->bots[i];
    }

    return best;
}

bot *select_bot_with_factor(generation *g, size_t fitness_sum)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_sec + t.tv_usec * 1000000);
    float x = (float)rand()/(float)(RAND_MAX);
    float s = 0;
    for(size_t i = 0; i < g->size; ++i)
    {
        s+= g->bots[i].score;
        if(x < s / fitness_sum)
            return  g->bots + i;
    }

    return g->bots;
}

bot *select_bot_random(generation *g)
{
    if(g->size < 100)
        errx(EXIT_FAILURE, "Generation has too few bots");
    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_sec + t.tv_usec * 1000000);
    size_t x = (rand() % g->size - 100) + 99;
    return g->bots + x;
}

void duplicate(generation *g, generation *gen)
{
    size_t sum = 0;
    for(size_t i = 0; i < g->size; i++)
        sum += g->bots[i].score;

    gen->bots[0] = g->bots[0];
    for(size_t i = 1; i < g->size; i++)
    {
        gen->bots[i] = *crossover(select_bot_with_factor(g, sum), select_bot_with_factor(g, sum));
        mutate_bot(gen->bots + i);
    }
    *g = *gen;
}

void new_gen(generation *g, char display_best)
{
    sort(g);
    if(display_best)
    {
        // Play Function
        play_bot(g->bots);
    }

    generation *gen = build_generation(g->size);
    duplicate(g, gen);
    free(gen);
}

void mutate_generation(generation *g)
{
    // bot *best = g->bots;
    for(size_t i = 0; i < g->size; i++)
    {
        mutate_bot(g->bots + i);
    }
}

void play(generation *g)
{
    for(size_t i = 0; i < g->size; ++i)
        play_bot(g->bots + i);
}

void new_gen2(generation *g, char display_best)
{
    play(g);
    sort(g);
    if(display_best)
    {
        // Play Function
        play_bot(g->bots);
    }
    mutate_generation(g);
    play(g);
}


void train(generation *g, size_t nb_gen)
{
    for(size_t i = 0; i < nb_gen; ++i)
    {
        play(g);
        if(i % 100 == 0)
        {
            new_gen2(g, 1);
        }
        else
        {
            new_gen2(g, 0);
        }

        // printf("%zu", i);
    }
}

generation *build_generation_from_file(size_t size, char *path)
{
    generation *g = build_generation(size);
    bot *saved = load_bot(path);
    for(size_t i = 0; i < size; ++i)
        g->bots[i] = *copy_bot(saved, 0);

    return g;
}
