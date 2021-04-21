#include <err.h>
#include "evaluate.h"
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "list.h"

int get_position_score(Game* game, int cur_color)
{
    int sum=0;
    Piece p;
    for(int i=0;i<16; i++)
    {
        if(cur_color==WHITE)
        {
            p=game->whites[i];
            sum+=7-p.x;
        }
        else
        {
            p=game->blacks[i];
            sum+=p.x;
        }
    }
    return sum;
}


int get_atk_def(Game *game, int cur_color, int* scores)
{

    Move_list *atk = init_list(); 
    Move_list *def = init_list();
    int sum = 0;
    for(int i=0;i<16; i++)
    {
        if(cur_color==WHITE)
            get_moves(game, &game->whites[i], atk, def);
        else
            get_moves(game, &game->blacks[i], atk, def);

        int x=0;
        int y=0;
        
        while (!is_empty(def))
        {
            pop_list(def, &x, &y);
            if(scores[game->board[x * 8 + y]->type!=KING])
                sum += scores[game->board[x * 8 + y]->type] / 5;
        }

        while (!is_empty(atk))
        {
            pop_list(atk, &x, &y);
            if (game->board[x * 8 + y] != NULL)
                sum += scores[game->board[x * 8 + y]->type] / 5;
        }
    }
    free_list(atk);
    free_list(def);
    return sum;
}
