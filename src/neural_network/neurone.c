#include <err.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "neurone.h"

void print_neurone(neurone *n)
{
    printf("{");
    for(size_t i = 0; i < n->size; ++i)
    {
        printf("%lf, ", *(n->weights + i));
    }
    printf("}\n%lf\n", n->bias);
}

neurone *build_neurone(size_t size)
{
    neurone *n = malloc(sizeof(neurone));
    if(n == NULL)
        errx(EXIT_FAILURE, "Your computer is going to die");
    n->weights = malloc(size * sizeof(float));
    if(n->weights == NULL)
        errx(EXIT_FAILURE, "Your computer is going to die");
    n->bias = 0;
    n->value = 0;
    n->size = size;
    return n;
}

void free_neurone(neurone *n)
{
    free(n->weights);
    free(n);
}

void init_neurone(neurone *n)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_sec + t.tv_usec * 1000000);
    for(size_t i = 0; i < n->size; ++i)
    {
        *(n->weights + i) = (float)rand()/(float)(RAND_MAX) * 2 - 1;
    }
    n->bias = (float)rand()/(float)(RAND_MAX) * 2 - 1;
}

void mutate(neurone *n)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_sec + t.tv_usec * 1000000);
    for(unsigned int i = 0; i < n->size; i++)
    {
        if((float)rand()/(float)(RAND_MAX) < 0.15f)
        {
            float x1 = 1 - (float)rand()/(float)(RAND_MAX);
            float x2 = 1 - (float)rand()/(float)(RAND_MAX);
            *(n->weights + i) += sqrtf(-2 * logf(x1)) * cosf(2 * 3.14159f *x2) / 5;
            if (*(n->weights + i) > 1.0f)
                *(n->weights + i) = 1.0f;
            if (*(n->weights + i) < -1.0f)
                *(n->weights + i) = -1.0f;
        }
    }
    if((float)rand()/(float)(RAND_MAX) < 0.05f)
    {
        float x1 = 1 - (float)rand()/(float)(RAND_MAX);
        float x2 = 1 - (float)rand()/(float)(RAND_MAX);
        n->bias += sqrtf(-2 * logf(x1)) * cosf(2 * 3.14159f *x2) / 5;
        if (n->bias > 1.0f)
            n->bias = 1.0f;
        if (n->bias < 1.0f)
            n->bias = -1.0f;
    }
}

void copy_neurone(neurone *n, neurone *copy, char mutated)
{
    if (n->size != copy->size)
        errx(EXIT_FAILURE, "The size can't be different");
    for(unsigned int i = 0; i < n->size; i++)
    {
        *(copy->weights + i) = *(n->weights + i);
    }
    copy->bias = n->bias;
    if(mutated)
    {
        printf("mutate\n");
        mutate(copy);
    }
}

void mix(neurone *n, neurone *m)
{
    if (n->size != m->size)
        errx(EXIT_FAILURE, "The size can't be different");
    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_sec + t.tv_usec * 1000000);
    for(unsigned int i = 0; i < n->size; i++)
    {
        if((float)rand()/(float)(RAND_MAX) < 0.5f)
        {
            float x = 0;
            while (x == 0)
            {
                x = (float)rand()/(float)(RAND_MAX);
            }
            *(n->weights + i) += x * (*(m->weights + i) - *(n->weights + i));
            // *(n->weights + i) = *(m->weights + i);
        }
    }
    if((float)rand()/(float)(RAND_MAX) < 0.5f)
    {
        n->bias = m->bias;
    }
}

float sigmoid(float *weight, float *bias, size_t len_w, size_t len_b)
{
    float sum = 0;
    for(size_t i = 0; i < len_w; ++i)
        sum += *(weight + i);
    for(size_t i = 0; i < len_b; ++i)
        sum += *(bias + i);

    return 1/(1 + expf(-sum));
}

float activation(float f)
{
    return logf(1 + expf(f));
}

float soft_max(neurone *n, float f)
{
    n->value = expf(n->value) / f;
    return n->value;
}
