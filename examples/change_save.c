#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <err.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "alpha_beta.h"
#include "tree.h"
#include "input.h"
#include "save_load.h"
#include "human.h"


int main( int argc, char** argv)
{
    Game g;
    set_game(&g);
    load(&g, "save/basic.txt");
    printf("load finished\n");
    save(&g, "save/basic.txt");
}
