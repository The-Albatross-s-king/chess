#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "rules.h"
#include "board.h"
#include "list.h"
#include "checkmate.h"


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
    
    Piece *e;
    int check = is_one_check(g, k, &e);
    if (check > 1)
    {
        free_list(l->next);
        l->next = NULL;
        return;
    }
    else if (check == 1)
    {
        need_protect(g, p, l, e);
        return;
    }

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

        else if (enemy->color != p->color && (x == y || x == -y) &&
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
        errx(EXIT_FAILURE, "you have give a piece to the king_suicide "
                "function which is not a king.");
    }

    Piece *enemy;
    int direction; // to know if pawns move up or down.
    if (p->color == WHITE)
    {
        direction = 1;
        enemy = g->blacks;
    }
    else
    {    
        direction = -1;
        enemy = g->whites;
    }
    Move_list *enemy_moves = init_list();
	Move_list *enemy_protect = init_list();
    for (int i = 0; i < 16; i++)
    {
        if (enemy[i].alive == 0)
            continue;

        int x;
        int y;

        if ((enemy+i)->type == PAWN)
        {
            x = (enemy+i)->x;
            if (x > 0 && x < 7)
            {
                y = (enemy+i)->y;
                int n = 0;

                if (y != 0)
                    n += 1;

                if (y != 7)
                    n += 1;


                Move_list *tmp = king_moves->next;
                Move_list *last = king_moves;
                while (tmp != NULL)
                {
                    if (tmp->x == x + direction && tmp->y == y + 1)
                    {
                        last->next = tmp->next;
                        free(tmp);
                        tmp = last->next;
                        n--;
                    }
                    else if (tmp->x == x + direction && tmp->y == y - 1)
                    {
                        last->next = tmp->next;
                        free(tmp);
                        tmp = last->next;
                        n--;
                    }
                    else
                    {
                        last = last->next;
                        tmp = tmp->next;
                    }
                }
            }
        }

        else
        {
            get_moves(g, enemy+i, enemy_moves, enemy_protect);

            int rx = (enemy+i)->x - p->x;
            int ry = (enemy+i)->y - p->y;
            int in_axe = 0;

            if ((rx == ry || rx == -ry) && ((enemy+i)->type == BISHOP || (enemy+i)->type == QUEEN))
            {   
                int i = 1;
                int j = 1;
                if (rx < 0)
                    i = -1;
                if (ry < 0)
                    j = -1;
                rx = p->x + i;
                ry = p->y + j;
                
                if (g->board[get_pos(rx,ry)] == NULL)
                    in_axe = 1;
            }

            else if ((rx == 0 || ry == 0) && (rx>1 || rx<-1 || ry>1 || ry<-1) && 
                ((enemy+i)->type == ROOK || (enemy+i)->type == QUEEN))
            {   
                int i = 0;
                int j = 0;
                if (rx < 0)
                    i = -1;
                else if (rx > 0)
                    i = 1;
                if (ry < 0)
                    j = -1;
                else if (ry > 0)
                    j = 1;
                rx = p->x + i;
                ry = p->y + j;
                
                if (g->board[get_pos(rx,ry)] == NULL)
                    in_axe = 1;
            }    
            

            int n = 2;
			int x2;
			int y2;

            while (king_moves->next != NULL && (pop_list(enemy_moves, &x, &y) || pop_list(enemy_protect, &x2, &y2)) && n)
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
                        if (in_axe)
                        {
							if ((enemy+i)->type != QUEEN)
								n--;
						}
                    }
					else if (in_axe && tmp->x == p->x + (p->x - x) && 
                            tmp->y == p->y + (p->y - y))
                    {	
                    	last->next = tmp->next;
                        free(tmp);
                        tmp = last->next;
                        if ((enemy+i)->type != QUEEN)
							n--;
                    }
                    else if (tmp->x == x2 && tmp->y == y2)
                    {
                        last->next = tmp->next;
                        free(tmp);
                        tmp = last->next;
                    }
                    else if ((((enemy+i)->type == ROOK && (p->x - (enemy+i)->x == 0 || p->y - (enemy+i)->y == 0))
                        || (enemy+i)->type == QUEEN) && tmp->x == p->x + (p->x - (enemy+i)->x) && 
                        tmp->y == p->y + (p->y - (enemy+i)->y))
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
			free_list(enemy_moves->next);
            enemy_moves->next = NULL;
            free_list(enemy_protect->next);
            enemy_protect->next = NULL;
        }

        if (king_moves->next == NULL)
            break;
    }
    free_list(enemy_moves);
    free_list(enemy_protect);

}


int is_one_check(Game *g, Piece *k, Piece **p)
{
    int nb_check = 0;
    Piece *enemy;
    int direction;
    if (k->color == WHITE)
    {    
        enemy = g->blacks;
        direction = 1;
    }
    else
    {
        enemy = g->whites;
        direction = -1;
    }
    Move_list *opp_list = init_list();
    int x;
    int y;
    int i = 0;
    for (; i < 8; i++)
    {
        if (i == 3 || !(enemy+i)->alive)
            continue;
        get_moves(g, enemy+i, opp_list, NULL);
        while (pop_list(opp_list, &x, &y) && (x != k->x || y != k->y))
        {
            continue;
        }
        if (opp_list->next != NULL)
        {
            *p = enemy+i;
            nb_check++;
            free_list(opp_list->next);
            opp_list->next = NULL;
        }
        
    }
    for (; i < 16; i++)
    {
        if (!(enemy+i)->alive)
            continue;
        x = (enemy+i)->x;
        if (x > 0 && x < 7)
        {
            y = (enemy+i)->y;

            if (k->x == x + direction && k->y == y + 1)
            {
                *p = enemy+i;
                nb_check++;
                continue;
            }
            else if (k->x == x + direction && k->y == y - 1)
            {
                *p = enemy+i;
                nb_check++;
                continue;
            }
        }
    }
     
    return nb_check;
}

void need_protect(Game *g, Piece *p, Move_list *l, Piece *enemy)
{
    Piece *k;
    if (p->color == WHITE)
    {
        k = &g->whites[3];
    }
    else
    {
        k = &g->blacks[3];
    }

    Move_list *tmp = l;
    l = l->next;

    if (enemy->type == QUEEN || enemy->type == ROOK || 
        enemy->type == BISHOP)
    {
        int rx = enemy->x - k->x;
        int ry = enemy->y - k->y;
        int x = 0;
        int y = 0;
        if (rx < 0)
            x = -1;
        else if (rx > 0)
            x = 1;
        if (ry < 0)
            y = -1;
        else if (ry > 0)
            y = 1;

        while (l != NULL)
        {
            rx = k->x + x;
            ry = k->y + y;
            while ((l->x != rx || l->y != ry) && (enemy->x != rx || enemy->y != ry))
            {
                rx += x;
                ry += y;
            }

            if (l->x != rx || l->y != ry)
            {
                tmp->next = l->next;
                free(l);
                l = tmp->next;
            }
            else
            {
                tmp = l;
                l = l->next;
            }

        }
    }
    else
    {
        while (l != NULL && (l->x != enemy->x || l->y != enemy->y))
        {
            tmp->next = l->next;
            free(l);
            l = tmp->next;
        }
        
        if (l != NULL && l->next != NULL)
        {
            free_list(l->next);
            l->next = NULL;
        }
    }
}