#include <stdio.h>
#include <err.h>
#include "board.h"
#include "rules.h"
#include "list.h"

// Is_check checks if the given king is in check state.
int is_check_coord(Game *g, int x, int y, enum pieces_colors player)
{
    // Means opponent list, its the list of opponent's pieces.
    Piece *opp_list;
    if(player == WHITE)
        opp_list = g->blacks;
    else
        opp_list = g->whites;

    for(int i = 0; i < 16; i ++)
    {
        Move_list *opp_li_moves = init_list();
        if (opp_list[i].alive == 0 || i == 3)
        {
            free_list(opp_li_moves);
            continue;
        }
        int x_opp = opp_list[i].x;
        int y_opp = opp_list[i].y;
        Piece *tmp = g->board[get_pos(x_opp, y_opp)];
        if(tmp != NULL)
            get_moves(g, tmp, opp_li_moves, NULL,0);
        if(in_list(opp_li_moves, x, y))
        {
            free_list(opp_li_moves);
            return 1;
        }
        free_list(opp_li_moves);
    }

    return 0;
}

int is_check(Game* g, Piece *king)
{
    return is_check_coord(g, king->x, king->y, king->color);
}

// Test if there is a check after a move given in argument.
int check_after_move(Game *g, Piece *p, int new_x, int new_y)
{
    if (p == NULL)
        errx(3, "The piece is NULL");
    int old_x = p->x;
    int old_y = p->y;

    Piece *king = p->color == WHITE ? &g->whites[3] : &g->blacks[3];

    Piece *victim = apply_move(g, old_x, old_y, new_x, new_y);

    char check = is_check(g, king);

    apply_move(g, new_x, new_y, old_x, old_y);
    if (victim != NULL)
    {
        victim->alive = 1;
        g->board[get_pos(victim->x, victim->y)] = victim;
    }

    return check;

}

// Is_checkmate checks if the game is win.
// Test for each piece if after a move the king is again in check.
int is_checkmate(Game* g, Piece *king)
{
    // Test if the checkmate is possible
    if (king == NULL)
        errx(1, "The king can't be NULL");
    if (king->alive == 0)
        return 0;
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

    // Run through the piece array of the player's color and test if
    // the king is again in check after each moves of a piece.
    // if a move save the king from check the function is stopped.
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
        if (p->alive == 0 || g->board[get_pos(p->x,p->y)] == NULL)
        {
            i++;
            continue;
        }

        Move_list *p_li_moves=init_list();
        get_moves(g, p, p_li_moves, NULL, 0);
        if(p->type != KING)
            is_treason(g, p, p_li_moves);
        Move_list *begin = p_li_moves;
        p_li_moves = p_li_moves->next;
        for (; p_li_moves != NULL; p_li_moves = p_li_moves->next)
        {
            check = check_after_move(g, p, p_li_moves->x, p_li_moves->y);
            if(!check)
            {
                free_list(begin);
                return check;
            }
        }
        free_list(begin);
        i++;
    }

    return check;
}
