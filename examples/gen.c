#include "bot_xor.h"
#include "generation.h"
#include "neural_network.h"
#include "neurone.h"
#include "layer.h"
#include <stdlib.h>

void print_arr(float *arr, size_t len)
{
    printf("[");
    for(size_t i = 0; i < len - 1; i++)
    {
        printf("%f, ", arr[i]);
    }
    printf("%f]\n", arr[len - 1]);
}


int main()
{
    generation *gen = build_generation(200);
    train(gen, 10000);
    bot *best = get_best_bots(gen, 1)->bots;

    float inputs[] = {0, 0};
    float expected[] = {1, 0};
    feed(best->net, inputs, 2);
    front_prop_network(best->net);

    float *res = get_output(best->net);
    print_arr(res, 2);
    printf("%f\n", best->score);
    save_bot(best, "save/best.nn");
    free_generation(gen);

    return 0;
}
