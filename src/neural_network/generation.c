#include "neural_struct.h"
#include "bot_xor.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <err.h>

// Build a 'size' bots generation.
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
        build_bot(g->bots+i);
    }
    g->average = 0;

    return g;
}

void free_generation(generation *g)
{
    for (size_t i = 0; i < g->size; i++)
        free_bot(g->bots+i);
    free(g->bots);
    free(g);
}

// Bubble sort puts the best bots in first in the generation 'g'.
void sort(generation *g)
{
    /* Bubble sort :
    ** Compare each bot size times, and put the worst at the end.
    ** Do it again if the array is not sorted for --size.
    */
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

// Keep the 'n' best bots in the 'g' generation.
generation *get_best_bots(generation *g, size_t n)
{
    sort(g);
    generation *best = build_generation(n);
    for(size_t i = 0; i < n; ++i)
    {
        copy_bot(g->bots+i, best->bots+i, 0);
    }
    best->size = n;

    return best;
}

// Select "random" (tendancy to last) bot according to a factor 'fitness_sum"
bot *select_bot_with_factor(generation *g, size_t fitness_sum)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    // Random seed generation every micro second.
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

// Select a random bot among the [100, size] bots.
bot *select_bot_random(generation *g)
{
    if(g->size < 100)
        errx(EXIT_FAILURE, "Generation has too few bots");
    struct timeval t;
    gettimeofday(&t, NULL);
    // Random seed generation every micro second.
    srand(t.tv_sec + t.tv_usec * 1000000);
    size_t x = (rand() % g->size - 100) + 99;
    return g->bots + x;
}

// Copy, mix and mutate every bot of generation 'g' with generation 'gen'.
// Into 'g'.
void duplicate(generation *g, generation *gen)
{
    size_t sum = 0;
    for(size_t i = 0; i < g->size; i++)
        sum += g->bots[i].score;

    gen->bots[0] = g->bots[0];
    for(size_t i = 1; i < g->size; i++)
    {
        // Copy and mix
        crossover(select_bot_with_factor(g, sum), select_bot_with_factor(g, sum), gen->bots + i);
        //Mutate
        mutate_bot(gen->bots + i);
    }
    *g = *gen;
}

// Sort the 'g' generation, then duplicate it with a new one.
void new_gen(generation *g, char display_best)
{
    sort(g);
    if(display_best)
    {
        // Take inputs, generate expected output, front propagate the network.
        // Get the score.
        play_bot(g->bots);
    }

    generation *gen = build_generation(g->size);
    duplicate(g, gen);
    free(gen);
}

// Custom Mutate, Mix [0, 20] bots with [20, 200] bots, Mutate [20, 200] bots.
// Copy first bot on [size-200, size-100] bots and mutate them,
// mix them with 20 bests.
// Reset last 100 bots.
void mutate_generation(generation *g)
{
    // bot *best = g->bots;
    for(size_t i = 20; i < g->size-200; i++)
    {
        mix_bot(g->bots + i, g->bots + i%20);
        mutate_bot(g->bots+i);
    }
    for (size_t i = g->size-200; i < g->size-100; i++)
    {
        copy_bot(g->bots, g->bots+i, 1);
        mix_bot(g->bots+i, g->bots+i%20);
    }
    for(size_t i = g->size-100; i < g->size; i++)
    {
        free_bot(g->bots+i);
        build_bot(g->bots+i);
    }
}

void mutate_generation2(generation *g)
{
    // bot *best = g->bots;
    for(size_t i = g->size / 40; i < g->size / 20; i++)
    {
        copy_bot(g->bots, g->bots+i, 1);
        mix_bot(g->bots + i, g->bots + i%(g->size/20));
    }
    for(size_t i = g->size / 20; i < g->size/6; i++)
    {
        mutate_bot(g->bots+i);
    }
    for(size_t i = g->size/6; i < g->size/2; i++)
    {
        mix_bot(g->bots + i, g->bots + i%(g->size/20));
    }
    for (size_t i = g->size/2; i < g->size/2 + g->size/10; i++)
    {
        copy_bot(g->bots, g->bots+i, 1);
        //mix_bot(g->bots+i, g->bots+i%40);
    }
    for(size_t i = g->size/2 + g->size/10; i < g->size/2 + g->size/5; i++)
    {
        free_bot(g->bots+i);
        build_bot(g->bots+i);
    }
    for(size_t i = g->size/2 + g->size/5; i < g->size; i++)
    {
        mix_bot(g->bots+i, g->bots+i%g->size/20);
    }
}

// Play every bot of the generation 'g'.
void play(generation *g)
{
    float average = 0;
    for(size_t i = 0; i < g->size; ++i)
    {
        play_bot(g->bots + i);
        average += g->bots[i].score;
    }
    g->average = average / g->size;
}

// Play, sort and mutate the generation 'g'.
void new_gen2(generation *g, char display_best)
{
    //play(g);
    if(display_best)
    {
        // Play Function
        play_bot(g->bots);
    }
    play(g);
    sort(g);
    mutate_generation2(g);
}

// Play the generation 'nb_gen' times.
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
        copy_bot(saved, g->bots+i, 0);

    return g;
}
