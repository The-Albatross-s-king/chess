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
    bot b1;
    bot b2;
    build_bot(&b1);
    build_bot(&b2);
    
    Game g;
    set_game(&g); //remplit le plateau de pieces

    IA_vs_IA_nn(&g, 20, &b1, &b2);
}