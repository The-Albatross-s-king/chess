#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_COUNT 4
#define INPUT_SIZE 2
#define INPUT_LAYER 2
#define HIDDEN_LAYER 2
#define OUTPUT_LAYER 1
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

int main()
{
    int input[INPUT_COUNT][INPUT_SIZE] = {{0,0}, {0,1}, {1,0}, {1,1}};
    int expected_output[INPUT_COUNT] = {0, 1, 1, 0};

    float *hidden_weights = build_rand_f_arr(INPUT_LAYER * HIDDEN_LAYER);
    float *hidden_bias = build_rand_f_arr(HIDDEN_LAYER);
    float *output_weights = build_rand_f_arr(HIDDEN_LAYER * OUTPUT_LAYER);
    float *output_bias = build_rand_f_arr(OUTPUT_LAYER);

    printf("%lf\n", sigmoid(hidden_weights, hidden_bias, 4, 2));
}
