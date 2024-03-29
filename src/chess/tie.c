#include <stdio.h>
#include <err.h>
#include "board.h"
#include "list.h"
#include "rules.h"

// Verify if a move is possible for each piece
//      if there is a possible move, there is no tie
//      else there is a tie
int is_tie(Game *g, enum pieces_colors player)
{
    Move_list *mv_list = init_list();
    Piece *team = player == WHITE ? g->whites : g->blacks;
    int i = 0;

    while (i < 16)
    {
        if(team[i].alive != 0)
        {
            get_moves(g, &team[i], mv_list, NULL,0);
            if (team[i].type == KING)
            {
                king_suicide(g, &team[i], mv_list);
            }
            else
                is_treason(g, &team[i], mv_list);
            if (mv_list->next != NULL)
            {
                free_list(mv_list);
                return 0;
            }
        }
        i++;
    }
    free_list(mv_list);
    return 1;
}
