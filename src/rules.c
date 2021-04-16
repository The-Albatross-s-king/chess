#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "rules.h"
#include "board.h"
#include "list.h"
#include "checkmate.h"


void impossible_diag_move(Piece *p, Move_list *l, int x, int y);
void impossible_cross_move(Piece *p, Move_list *l, int x, int y);

/*
   call this function after get_move() when a piece
   (different of the king) is selected.
   This is to avoid the case where the movement of a piece
   make check your king.
   */
void is_treason(Game *g, Piece *p, Move_list *l)
{
    if (p->alive == 0)
        errx(1, "The piece is dead");
    Piece *k;
    if (p->color == WHITE)
        k = &(g->whites[3]);
    else
        k = &(g->blacks[3]);

    int x = p->x - k->x;
    int y = p->y - k->y;

    if (x == y || -x == y || x == 0 || y == 0)
    {
        int i = 0;

        if (x < 0)
            i = -1;
        else if (x > 0)
            i = 1;

        int j = 0;

        if (y < 0)
            j = -1;
        else if (y > 0)
            j = 1;

        int a = -1; // a = step, depend of the position of the piece with the king.
        int step = a;

        int i_max = p->x + i*a;
        int j_max = p->y + j*a;

        while (i_max >= 0 && i_max < 8 && j_max >= 0 && j_max < 8 &&
                g->board[get_pos(i_max, j_max)] == NULL)
        {
            a += step;
            i_max = p->x + i*a;
            j_max = p->y + j*a;
        }

        if (i_max < 0 || i_max >= 8 || j_max < 0 || j_max >= 8 ||
                g->board[get_pos(i_max, j_max)]->type != KING)
            return;

        a = -step;
        step = a;

        i_max = p->x + i*a;
        j_max = p->y + j*a;

        while (i_max >= 0 && i_max < 8 && j_max >= 0 && j_max < 8 &&
                g->board[get_pos(i_max, j_max)] == NULL)
        {
            a += step;
            i_max = p->x + i*a;
            j_max = p->y + j*a;
        }

        if (i_max < 0 || i_max >= 8 || j_max < 0 || j_max >= 8)
            return;

        Piece *enemy = g->board[get_pos(i_max, j_max)];

        if (enemy == NULL)
            errx(1, "The enemy is NULL");

        if (enemy->color != p->color && (x == 0 || y == 0) &&
                (enemy->type == ROOK || enemy->type == QUEEN))
            impossible_cross_move(p, l, x, y);

        else if (enemy->color != p->color &&
                (enemy->type == BISHOP || enemy->type == QUEEN))
            impossible_diag_move(p, l, x, y);
    }
}

// remove all diagonal move in Move_list that the piece can not do.
void impossible_diag_move(Piece *p, Move_list *l, int x, int y)
{
    Move_list *prev = l;
    l = l->next;
    for (; l != NULL; l = l->next)
    {
        int rx = p->x - l->x; // relative x
        int ry = p->y - l->y; // relative y

        if ((x == y && rx == ry) || (x == -y && rx == -ry))
        {
            prev = l;
            continue;
        }

        Move_list *tmp = l;
        prev->next = l->next;
        free(tmp);
        l = prev;
    }
}

// remove all diaonal move in Move_list that the piece can not do.
void impossible_cross_move(Piece *p, Move_list *l, int x, int y)
{
    Move_list *prev = l;
    l = l->next;

    for (; l != NULL; l = l->next)
    {
        int rx = p->x - l->x; // relative x
        int ry = p->y - l->y; // relative y

        if ((x == 0 && rx == 0) || (y == 0 && ry == 0))
        {
            prev = l;
            continue;
        }

        Move_list *tmp = l;
        prev->next = l->next;
        free(tmp);
        l = prev;
    }

}

// need to add a new parameter to get_moves()
// the king can eat a piece, but this piece could be protected by another piece.
void king_suicide(Game *g, Piece *p, Move_list *king_moves)
{
    if (p->type != KING)
    {
        errx(EXIT_FAILURE, "you have give a piece to the king_suicide"
                "function which is not a king.");
    }

    Piece *enemy;
    if (p->color == WHITE)
        enemy = g->blacks;
    else
        enemy = g->whites;

    Move_list *enemy_moves=init_list();
    for (int i = 0; i < 16; i++)
    {
        if (enemy[i].alive == 0)
            continue;
        get_moves(g, enemy+i, enemy_moves, NULL);
        int x;
        int y;
        while (pop_list(enemy_moves, &x, &y))
        {
            Move_list *tmp = king_moves->next;
            Move_list *last = king_moves;
            while (tmp != NULL)
            {
                if (tmp->x == x && tmp->y == y)
                {
                    last->next = tmp->next;
                    free(tmp);
                    tmp = last->next;
                }
                else
                {
                    last = last->next;
                    tmp = tmp->next;
                }
            }
        }
    }
    free_list(enemy_moves);
}
