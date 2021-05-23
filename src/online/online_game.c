#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "checkmate.h"
#include "tie.h"
//#include "data_transfert.h"
#include "input.h"

void game(int yfd, int efd, int color) //yfd = your file directory, efd = enemy file directory
{
	yfd++;
	efd++;
	color++;
	Game g;
	set_game(&g);
	//white = 1, black = 0;
	int round = 1;
	int input_x;
	int input_y;
	int new_x;
	int new_y;
	int black_checkmate = 0;
	int white_checkmate = 0;
	int tie = 0;
	Move_list *moves = init_list();

	while (!black_checkmate && !white_checkmate && !tie)
	{
		if (round % 2 == color)
		{
			//it's your turn !
			//get input
			display_board(&g.board[0], moves, color);
			can_i_go(&g, &input_x, &input_y, &moves, color);
			display_board(&g.board[0], moves, color);
			
			if(go_to(&g, moves, &input_x, &input_y, &new_x, &new_y))
			{
				round++;
				if(color)
					black_checkmate = is_checkmate(&g, &g.blacks[3]);
				else
					white_checkmate = is_checkmate(&g, &g.whites[3]);
				tie = is_tie(&g, (round + 1) % 2);

				//TODO send information to adversary.

			}
			else
				printf("Wrong move, try again.\n");
			
			free_list(moves->next);
	        moves->next=NULL;
		}
		else
		{
			//waiting for enemy turn...
			// TODO get information from adversary and set the board.
			// And get if there is checkmate or tie.
		}
	}

	display_board(&g.board[0], NULL, color);
    if(black_checkmate)
        printf("Black is checkmate\nWHITES WIN !\n");
    else
    {
        if(white_checkmate)
        {
            printf("White is checkmate\nBLACKS WIN !\n");
            return;
        }
        else
            printf("Tie\nNo one won !\n");
    }
}
