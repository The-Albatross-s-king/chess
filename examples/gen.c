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

void print_score(bot *best)
{
    float inputs[] = {0, 0};
    float expected[] = {1, 0};
    int resultat = 0;

    printf("===============================\n");
    printf("Score: %f\n", best->score);

    int succ = 0;
    inputs [0] = 0;
    inputs [1] = 0;
    expected [0]= 1;
    expected [1]= 0;
    feed(best->net, inputs, 2);
    front_prop_network(best->net);
    printf("Inputs: ");
    print_arr(inputs, 2);
    float *res = get_output(best->net);
    printf("Output: %d   (%f)", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
    // printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
    resultat = res[0] > res[1] ? 0 : 1;
    printf("  %s\n", expected[resultat] ? " \033[42m OK \033[0m" : " \033[41m KO \033[0m");
    succ += expected[resultat];
    free(res);

    inputs [0] = 0;
    inputs [1] = 1;
    expected [0]= 0;
    expected [1]= 1;
    feed(best->net, inputs, 2);
    front_prop_network(best->net);
    printf("Inputs: ");
    print_arr(inputs, 2);
    res = get_output(best->net);
    printf("Output: %d   (%f)", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
    // printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
    resultat = res[0] > res[1] ? 0 : 1;
    printf("  %s\n", expected[resultat] ? " \033[42m OK \033[0m" : " \033[41m KO \033[0m");
    succ += expected[resultat];
    free(res);

    inputs[0] = 1;
    inputs[1] = 0;
    expected[0] = 0;
    expected[1] = 1;
    feed(best->net, inputs, 2);
    front_prop_network(best->net);
    printf("Inputs: ");
    print_arr(inputs, 2);
    res = get_output(best->net);
    printf("Output: %d   (%f)", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
    // printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
    resultat = res[0] > res[1] ? 0 : 1;
    printf("  %s\n", expected[resultat] ? " \033[42m OK \033[0m" : " \033[41m KO \033[0m");
    succ += expected[resultat];
    free(res);

    inputs[0] = 1;
    inputs[1] = 1;
    expected[0] = 1;
    expected[1] = 0;
    feed(best->net, inputs, 2);
    front_prop_network(best->net);
    printf("Inputs: ");
    print_arr(inputs, 2);
    res = get_output(best->net);
    printf("Output: %d   (%f)", res[0] < res[1] ? 1 : 0, res[0] < res[1] ? res[1] : res[0]);
    // printf("resultat: %d => %f\n", res[0] > res[1] ? 1 : 0, res[0] > res[1] ? res[1] : res[0]);
    resultat = res[0] > res[1] ? 0 : 1;
    printf("  %s\n", expected[resultat] ? " \033[42m OK \033[0m" : " \033[41m KO \033[0m");
    succ += expected[resultat];
    free(res);
    printf("Number of good answers: %d/4\n\n", succ);

}


int main()
{
    generation *gen = build_generation(1000);
    train(gen, 100);
    // generation *best_gen = get_best_bots(gen, 1);
    // bot *best = malloc(sizeof(bot));
    // build_bot(best);
    // copy_bot(best_gen->bots, best, 0);
    bot *best = gen->bots;
    float inputs[] = {0, 0};
    float expected[] = {1, 0};
    int resultat = 0;
    // bot *b = gen->bots;

    int i = 1;

    while (best->score < 55.0f)
    {
        printf("===============================\n");
        printf("Iteration : %d\n", i);
        i++;
        play(gen);
        sort(gen);

        print_score(best);

        train(gen, 100);
    }

    printf("===============================\n");
    printf("Iteration : %d\n", i);
    print_score(best);
    save_bot(best, "save/best.nn");
    free_generation(gen);
    // free_generation(best_gen);
    // free_bot(best);
    // free(best);

    return 0;
}
