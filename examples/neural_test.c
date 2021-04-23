#include "neurone.h"
#include "layer.h"
#include "neural_network.h"
#include <stdio.h>
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
    size_t sizes[] = {1 , 5, 10};
    float inputs[] = {0.5f};
    size_t nb = 3;

    network *net = build_network(sizes, nb);
    init_network(net);
    feed(net, inputs, sizes[0]);
    front_prop_network(net);
    float *res = get_output(net);
    print_network(net);
    print_arr(res, sizes[nb - 1]);
    free(res);
    free_network(net);
}
