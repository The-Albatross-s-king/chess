#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "rules.h"
#include "board.h"
#include "list.h"

/* 
call this function before get_move() when a piece
(different of the king) is selected.
This is to avoid the case where the movement of a piece
make check your king.
*/
int is_treason(Game *g, Piece *p)
{
	Piece *k;
	if (p->color == WHITE)
		k = &(g->whites[4]);
	else
		k = &(g->blacks[3]);
	
	int x = k->x - p->x;
	int y = k->y - p->y;;

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

		int a = 1;
		int i_max = p->x + i*a;
		int j_max = p->y + j*a;
		while (i_max >= 0 && i_max < 8 && j_max >= 0 && j_max < 8 && 
			g->board[(i_max)*8 + j_max] == NULL)
		{
			a++;
			i_max = p->x + i*a;
			j_max = p->y + j*a;
		}
		if (i_max < 0 && i_max >= 8 && j_max < 0 && j_max >= 8 && 
			g->board[(p->x + i*a)*8 + p->y + y*a]->type != KING)
			return 0;

		a = -1;
		
		while (i_max >= 0 && i_max < 8 && j_max >= 0 && j_max < 8 && 
			g->board[(i_max)*8 + j_max] == NULL)
		{
			a++;
			i_max = p->x + i*a;
			j_max = p->y + j*a;
		}

		if (i_max < 0 && i_max >= 8 && j_max < 0 && j_max >= 8)
			return 0;
		Piece *enemy = g->board[i_max*8 + j_max];

		if (enemy->color != p->color && (x == 0 || y == 0) && 
			(enemy->type == ROOK || enemy->type == QUEEN))
			return 1;

		if (enemy->color != p->color && 
			(enemy->type == BISHOP || enemy->type == QUEEN))
			return 1;
	}
	
	return 0;

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
		enemy = &(g->blacks[0]);
	else
		enemy = &(g->whites[0]);

	Move_list *enemy_moves;
	for (int i = 0; i < 16; i++)
	{
		enemy_moves = get_moves(g, (enemy+i)->x, (enemy+i)->y);
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
}
