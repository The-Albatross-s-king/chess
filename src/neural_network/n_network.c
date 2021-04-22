#include "n_network.h"
/*void print_input(int input[INPUT_COUNT][INPUT_SIZE])
{
    for(size_t i = 0; i < INPUT_COUNT; ++i)
    {
        printf("{");
        for(size_t j = 0; j < INPUT_SIZE; ++j)
            printf("%d%c", input[i][j], j == INPUT_SIZE - 1 ? '}' : ',');
        printf("\n");
    }
}
*/
float *build_rand_f_arr(size_t len)
{
    float *arr = malloc(len * sizeof(float));
    for(size_t i = 0; i < len; ++i)
    {
        *(arr + i) = (float)rand()/(float)(RAND_MAX);
    }

    return arr;
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

