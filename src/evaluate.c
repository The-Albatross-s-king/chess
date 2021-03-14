#include <err.h>
#include "evaluate.h"
#include <stdlib.h>
#include "board.h"
#include "list.h"


int get_atk_def(Game *game, int pos, int* scores)
{
    
    Move_list *atk = init_list(); 
    Move_list *def = init_list();

    get_moves(game, game->board[pos], atk, def);

    if (atk == NULL)
        err(3, "atk list is null");

    if (def == NULL)
        err(3, "def list is null");
    
    int sum = 0;

    def = def->next;
    int x=0;
    int y=0;
    while (!is_empty(def))
    {
        pop_list(def, &x, &y);
        sum += scores[game->board[x * 8 + y]->type] / 2;
    }

    atk = atk->next;
    while (!is_empty(atk))
    {
        pop_list(def, &x, &y);
        if (game->board[x * 8 + y] != NULL)
            sum += scores[game->board[x * 8 + y]->type] / 2;
    }
    free_list(atk);
    free_list(def);
    return sum;
}
