#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <netdb.h>
#include "list.h"
#include "board.h"
#include "display.h"
#include "checkmate.h"
#include "tie.h"
//#include "data_transfert.h"
#include "input.h"

void apply_go_to(Game *g, int x, int y, int new_x, int new_y)
{
	apply_move(g, x, y, new_x, new_y);
	Piece p = *g->board[get_pos(new_x, new_y)];
	/*if (p.type == PAWN)
		pawn_transformation(g, &p);*/
	if (p.type == KING)
	{
		Piece *team = p.color == WHITE ? g->whites : g->blacks;
		Piece rook = team[0];
		switch(y - new_y)
		{
			case 2:
				rook = team[0];
				apply_move(g, rook.x, rook.y, rook.x, rook.y+2);
				break;
			case -2:
				rook = team[7];
				apply_move(g, rook.x, rook.y, rook.x, rook.y-3);
				break;
			default:
				break;
		}
	}
}

void online_game(int efd, int color) //efd = enemy file directory
{
	Game *g = malloc(sizeof(Game));
	set_game(g);
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
	
	int info_size = 7; //we need following information: x, y, new_x, new_y, checkmate, tie.
	char info[info_size];
	info[7] = 0;
	
	display_board(g->board, moves, color);
	
	//TODO manage if the player wants to leave the game.

	while (!black_checkmate && !white_checkmate && !tie)
	{
		if (round % 2 == color)
		{
			//it's your turn !
			//get input
			display_board(g->board, moves, color);
			can_i_go(g, &input_x, &input_y, &moves, color);
			display_board(g->board, moves, color);
			
			if(go_to(g, moves, &input_x, &input_y, &new_x, &new_y))
			{
				round++;
				
				if(color)
				{
					black_checkmate = is_checkmate(g, &g->blacks[3]);
					info[4] = black_checkmate + '0';
				}
				else
				{
					white_checkmate = is_checkmate(g, &g->whites[3]);
					info[4] = white_checkmate + '0';
				}
				tie = is_tie(g, (round + 1) % 2);

				info[0] = input_x + '0';
				info[1] = input_y + '0';
				info[2] = new_x + '0';
				info[3] = new_y + '0';
				info[5] = tie + '0';

				//TODO take the value of piece transformation (need to modify function in input.c)

				if (send(efd, info, info_size, 0) == -1)
					errx(EXIT_FAILURE, "fail to send data");
				
			}
			else
				printf("Wrong move, try again.\n");
			
			free_list(moves->next);
	        moves->next=NULL;
		}
		else
		{
			//waiting for enemy turn...
			display_board(g->board, moves, color);
			printf("Wait for enemy turn...\n");
			if (recv(efd, info, info_size, 0) == -1)
				errx(EXIT_FAILURE, "fail to recceive data");

			input_x = info[0] - '0';
			input_y = info[1] - '0';
			new_x = info[2] - '0';
			new_y = info[3] - '0';
			tie = info[5] - '0';
			if (color)
				black_checkmate = info[4] - '0';
			else
				white_checkmate = info[4] - '0';
		
			get_moves(g, g->board[get_pos(input_x, input_y)], moves, NULL, 1);
			display_list(moves);
			apply_go_to(g, input_x, input_y, new_x, new_y);
			round++;
			free_list(moves->next);
			moves->next=NULL;
		}
	}

	display_board(g->board, NULL, color);
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
	free(g);
}
