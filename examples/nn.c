#include "neurone.h"
#include "layer.h"
#include <stdlib.h>

int main()
{
    // int input[INPUT_COUNT][INPUT_SIZE] = {{0,0}, {0,1}, {1,0}, {1,1}};
    // int expected_output[INPUT_COUNT] = {0, 1, 1, 0};

    // float *hidden_weights = build_rand_f_arr(INPUT_LAYER * HIDDEN_LAYER);
    // float *hidden_bias = build_rand_f_arr(HIDDEN_LAYER);
    // float *output_weights = build_rand_f_arr(HIDDEN_LAYER * OUTPUT_LAYER);
    // float *output_bias = build_rand_f_arr(OUTPUT_LAYER);

    layer *l1 = build_layer(3);
    init_layer(l1, 3, 10);

    print_layer(l1);
    layer *l2 = copy_layer(l1, 1);
    print_layer(l2);

    free_layer(l1);
    free_layer(l2);
    // printf("%lf\n", sigmoid(hidden_weights, hidden_bias, 4, 2));
}
