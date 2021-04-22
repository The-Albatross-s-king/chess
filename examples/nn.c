#include "n_network.h"

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
