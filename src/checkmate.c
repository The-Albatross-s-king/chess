#include <stdio.h>
#include <err.h>
#include "board.h"
#include "list.h"

// Is_check checks if the given king is in check state.
int is_check(Game* g, Piece *king)
{
    // Means opponent list, its the list of opponent's pieces.
    Piece *opp_list; 
    if(king->color == WHITE)
        opp_list = g->blacks;
    else
        opp_list = g->whites;

    Move_list *opp_li_moves = init_list();
    for(int i = 0; i < 16; i ++)
    {
        if (opp_list[i].alive == 0)
            continue;
        int x_opp = opp_list[i].x;
        int y_opp = opp_list[i].y;
        get_moves(g, g->board[get_pos(x_opp, y_opp)], opp_li_moves, NULL);
        if(in_list(opp_li_moves, king->x, king->y))
            return 1;
    }
    free_list(opp_li_moves);

    return 0;
}

int check_after_move(Game *g, Piece *p, int new_x, int new_y)
{
    if (p == NULL)
        errx(3, "The piece is NULL");
    int old_x = p->x;
    int old_y = p->y;

    Piece *king = p->color == WHITE ? &g->whites[3] : &g->blacks[3];

    Piece *victim = apply_move(g, old_x, old_y, new_x, new_y);

    char check = is_check(g, king);

    if (victim != NULL)
    {
        victim->alive = 1;
        g->board[get_pos(victim->x, victim->y)] = victim;
    }
    apply_move(g, new_x, new_y, old_x, old_y);

    return check;

}

// Is_checkmate checks if the game is win.
int is_checkmate(Game* g, Piece *king)
{
    char check = 1;
    if(!is_check(g, king))
    {
        return 0;
    }

    Piece *p_list;
    if(king->color == WHITE)
        p_list = g->whites;
    else
        p_list = g->blacks;

    int order[] = {3, 4, 2, 5, 0, 7, 1, 6};
    int i = 0;
    while(check && i < 16)
    {
        Piece *p;
        if(i < 8)
        {
            p = &p_list[order[i]];
        }
        else
        {
            p = &p_list[i];
        }
        if (p->alive == 0)
        {
            i++;
            continue;
        }
        if(g->board[get_pos(p->x,p->y)] == NULL)
        {
            i++;
            continue;
        }
        Move_list *p_li_moves=init_list();
        printf("dans is_checkmate\n");
        get_moves(g, g->board[get_pos(p->x,p->y)], p_li_moves, NULL);
        p_li_moves = p_li_moves->next;
        for (; p_li_moves != NULL; p_li_moves = p_li_moves->next)
        {
            check = check_after_move(g, p, p_li_moves->x, p_li_moves->y);
            if(!check)
            {
                return check;
            }
        }
        free_list(p_li_moves);
        i++;
    }

    return check;
}


