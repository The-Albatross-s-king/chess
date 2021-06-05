#include "bot_xor.h"
#include "generation.h"
#include "neural_network.h"
#include "neurone.h"
#include "layer.h"
#include "board.h"
#include "display.h"
#include "tree.h"
#include "chess_nn.h"

#include <stdlib.h>

int main()
{
    generation *g = build_generation(10);
    train(g, 10);
    // Generer la generation
    // Training - > Mutation.
    //      Jouer une partie entre 2 bots.
    //      Attribuer des scores.
    //      Selectionner les meilleurs -> Mutation de la generation.
    save_bot(g->bots, "save/bot_chess.nn");
    free_generation(g);
}