#include <stdio.h>
#include <stdlib.h>

#include "piece.h"

int main(){
    PIECE* table = calloc(64, sizeof(PIECE));
    table->type = pion;
    table->color = 0;
    start(table);    
    

    display_table(table);

    move_piece(table, 1, 1, 2, 2);
    
    display_table(table);
    
    //printf("it's good");

    free(table);

    return 0;
}
