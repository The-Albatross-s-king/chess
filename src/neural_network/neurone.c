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

// Builds a neurone containing weights, number of weights, a bias and a value.
void build_neurone(neurone *n, size_t size)
{
    /*
    ** n : the neurone to build
    ** size : the weight's number
    */
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
// Puts pseudo-random value in weights and bias.
void init_neurone(neurone *n)
{
    /*
    ** n : the neurone to initialize.
    */
    struct timeval t;
    gettimeofday(&t, NULL);
    // Get a different seed for pseudo random generation every micro seconds.
    // t.tv_sec + t.tv_usec * 1000000
    srand(1231);
    for(size_t i = 0; i < n->size; ++i)
    {
        *(n->weights + i) = ((float)rand()/(float)(RAND_MAX) * 2 - 1);
    }
    n->bias = (float)rand()/(float)(RAND_MAX) * 2 - 1;
}

// Change the value of 15 weights/bias out of 100.
void mutate(neurone *n)
{
    /*
    ** n : the neurone to mutate
    */
    struct timeval t;
    gettimeofday(&t, NULL);
    // Random seed every micro second.
    double seed= t.tv_sec + t.tv_usec * 1000000;
    srand(seed);
    // Weights mutation.
    for(unsigned int i = 0; i < n->size; i++)
    {
        if((float)rand()/(float)(RAND_MAX) < 1)
        {
            float x1 = 1 - (float)rand()/(float)(RAND_MAX);
            float x2 = 1 - (float)rand()/(float)(RAND_MAX);
            // Mutation method.
            *(n->weights + i) += sqrtf(-2 * logf(x1)) * cosf(2 * 3.14159f *x2) / 5;
            // Weights has been marked out between 1 and -1.
            if (*(n->weights + i) > 1.0f)
                *(n->weights + i) = 1.0f;
            if (*(n->weights + i) < -1.0f)
                *(n->weights + i) = -1.0f;
        }
    }
    // Bias mutation.
    if((float)rand()/(float)(RAND_MAX) < 1)
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
    /*
    ** n : The neurone to copy into copy.
    ** copy : The copy of the neurone n.
    ** mutated : boolean mutating copy if true.
    */
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
// Merges two neurone by way of a calculation method.
void mix(neurone *n, neurone *m)
{
    /*
    ** n : Neurone to mix into.
    ** m : Neurone to mix into n.
    */
    // N and M must be the same size.
    if (n->size != m->size)
        errx(EXIT_FAILURE, "The size can't be different");
    struct timeval t;
    gettimeofday(&t, NULL);
    // Random seed every micro second.
    srand(t.tv_sec + t.tv_usec * 1000000);
    // Mix 1 weight out of 2.
    for(unsigned int i = 0; i < n->size; i++)
    {
        if((float)rand()/(float)(RAND_MAX) < 0.5f)
        {
            float x = 0;
            while (x == 0)
            {
                x = (float)rand()/(float)(RAND_MAX);
            }
            // Mix method.
            *(n->weights + i) += x * (*(m->weights + i) - *(n->weights + i));
            // *(n->weights + i) = *(m->weights + i);
        }
    }
    // Mix 1 bias out of 2.
    if((float)rand()/(float)(RAND_MAX) < 0.5f)
    {
        n->bias = m->bias;
    }
}

// Activation function returns a value according to a neurone.
float sigmoid(float f)
{
    /*
    ** weight : weights of a neurone to sum to its bias.
    ** bias : bias of the neurone.
    ** len_w : the lenght of the weights
    ** len_b : the lenght of the bias
    */
    return 1/(1 + expf(-f));
}

// Bunch of activation functions.
float softplus_act(float f)
{
    /*
    ** f : a float corresponding to the value of a neurone.
    */
    return logf(1 + expf(f));
}

float tanh_act(float f)
{
    /*
    ** f : a float corresponding to the value of a neurone.
    */
    float exp_f = expf(f);
    float exp_min_f = expf(-f);
    return (exp_f - exp_min_f) / (exp_f + exp_min_f);
}

float elu_act(float f)
{
    /*
    ** f : a float corresponding to the value of a neurone.
    */
    float exp_f = expf(f);
    if(f <= 0)
        return 2 * (exp_f - 1);
    return f;

}

float leaky_relou(float f)
{
    return f < 0 ? 0.01 * f : f;
}

float activation(float f)
{
    /*
    ** f : a float corresponding to the value of a neurone.
    */
    // Activation function used for the neurone.
    return leaky_relou(f);
}



// Probability of a neurone value.
float soft_max(neurone *n, float f)
{
    /*
    ** n : the neurone to proceed.
    ** f : the sum of neurones value in a layer.
    */
    n->value = expf(n->value) / f;
    return n->value;
}

// Front propagation of a layer.
// Calculate value of a neurone according to its previous layer.
void front_prop(neurone *n, layer *prev_l, char is_last)
{
    /*
    ** n : the neurone to proceed.
    ** prev_l : the layer to front propagate.
    ** is_last : call activation function if its the last layer of the network.
    */
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
