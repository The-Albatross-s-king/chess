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
    printf("} -> %lf\n%lf\n", n->value, n->bias);
}

void build_neurone(neurone *n, size_t size)
{
    n->weights = malloc(size * sizeof(float));
    if(n->weights == NULL)
        errx(EXIT_FAILURE, "Your computer is going to die");
    n->bias = 0;
    n->value = 0;
    n->size = size;
}

void free_neurone(neurone *n)
{
    free(n->weights);
}

void init_neurone(neurone *n)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_sec + t.tv_usec * 1000000);
    for(size_t i = 0; i < n->size; ++i)
    {
        *(n->weights + i) = ((float)rand()/(float)(RAND_MAX) * 2 - 1);
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
        if((float)rand()/(float)(RAND_MAX) < 0.05f)
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

float first_act(float f)
{
    return logf(1 + expf(f));
}

float tanh_act(float f)
{
    float exp_f = expf(f);
    float exp_min_f = expf(-f);
    return (exp_f - exp_min_f) / (exp_f + exp_min_f);
}

float elu_act(float f)
{
    float exp_f = expf(f);
    if(f <= 0)
        return 2 * (exp_f - 1);
    return f;

}

float activation(float f)
{
    return first_act(f);
}

float soft_max(neurone *n, float f)
{
    n->value = expf(n->value) / f;
    return n->value;
}

void front_prop(neurone *n, layer *prev_l, char is_last)
{
    if(n->size != prev_l->size)
        errx(EXIT_FAILURE, "Try to front propagate with wrong sizes");

    float sum = 0;
    for(size_t i = 0; i < n->size; ++i)
        sum += prev_l->neurones[i].value * n->weights[i];

    sum += n->bias;
    if(!is_last)
    {
        sum = activation(sum);
    }
    n->value = sum;
}

void save_neurone(neurone *n, FILE *file)
{
    if (file == NULL)
        errx(EXIT_FAILURE, "The file can't be null");
    char str[10];
    sprintf(str, "%lu,", n->size);
    fputs(str, file);
    fputs("[", file);

    if(n->size != 0)
    {
        for (unsigned int i = 0; i < n->size - 1; i++) {
            snprintf(str, 10, "%f", n->weights[i]);
            fputs(str, file);
            fputs(",", file);
        }
        snprintf(str, 10, "%f", n->weights[n->size - 1]);
        fputs(str, file);
    }
    fputs("],", file);
    snprintf(str, 10, "%f", n->bias);
    fputs(str, file);
    fputs("\n", file);

}

void load_neurones(neurone *n, FILE *file)
{
    if (file == NULL)
        errx(EXIT_FAILURE, "The file can't be null");

    size_t size = 0;
    if (fscanf(file, "%lu,[", &size) == 0)
        errx(EXIT_FAILURE, "Can't read the file 1");
    build_neurone(n, size);
    if (size != 0)
    {
        for(size_t i = 0; i < size - 1; i++)
        {
            if (fscanf(file, "%f,", n->weights + i) == 0)
                errx(EXIT_FAILURE, "Can't read the file 2");
        }
        if (fscanf(file, "%f", n->weights + size - 1) == 0)
            errx(EXIT_FAILURE, "Can't read the file 3");

    }
    if (fscanf(file, "],%f\n", &n->bias) == 0)
        errx(EXIT_FAILURE, "Can't read the file 4");
}
