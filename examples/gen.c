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
    generation *gen = build_generation(500);
    train(gen, 100);
    bot *best = get_best_bots(gen, 1)->bots;
    float inputs[] = {0, 0};
    float expected[] = {1, 0};
    int resultat = 0;
    bot *b = gen->bots;

    for (unsigned int i = 0; i < 5; i++)
    {
        play_bot(b);
        // for(size_t j = 0; j < gen->size; j++)
           //  play_bot(gen->bots + j);
        // play_bot(best);
        printf("Score: %f\n", b->score);
        int succ = 0;
        inputs [0] = 0;
        inputs [1] = 0;
        expected [0]= 1;
        expected [1]= 0;
        feed(best->net, inputs, 2);
        front_prop_network(best->net);
        printf("inputs: ");
        print_arr(inputs, 2);
        float *res = get_output(best->net);
        printf("resultat: %d => %f\n", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
        printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
        resultat = res[0] > res[1] ? 0 : 1;
        succ += expected[resultat];

        inputs [0] = 0;
        inputs [1] = 1;
        expected [0]= 0;
        expected [1]= 1;
        feed(best->net, inputs, 2);
        front_prop_network(best->net);
        printf("inputs: ");
        print_arr(inputs, 2);
        res = get_output(best->net);
        printf("resultat: %d => %f\n", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
        printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
        resultat = res[0] > res[1] ? 0 : 1;
        succ += expected[resultat];

        inputs[0] = 1;
        inputs[1] = 0;
        expected[0] = 0;
        expected[1] = 1;
        feed(best->net, inputs, 2);
        front_prop_network(best->net);
        printf("inputs: ");
        print_arr(inputs, 2);
        res = get_output(best->net);
        printf("resultat: %d => %f\n", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
        printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
        resultat = res[0] > res[1] ? 0 : 1;
        succ += expected[resultat];

        inputs[0] = 1;
        inputs[1] = 1;
        expected[0] = 1;
        expected[1] = 0;
        feed(best->net, inputs, 2);
        front_prop_network(best->net);
        printf("inputs: ");
        print_arr(inputs, 2);
        res = get_output(best->net);
        printf("resultat: %d => %f\n", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
        printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
        resultat = res[0] > res[1] ? 0 : 1;
        succ += expected[resultat];
        printf("%d\n", succ);
        train(gen, 100);
    }

    // save_bot(best, "save/best.nn");
    free_generation(gen);

    return 0;
}
