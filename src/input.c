#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include "board.h"
#include "input.h"
#include "rules.h"

int verif_input_letter(char c){
    if (c >= 'a' && c <= 'h')
        return c - 'a';
    if (c >= 'A' && c <= 'H')
        return c - 'A';
    return -1;
}

int verif_input_number(char c){
    if (c >= '1' && c <= '8')
        return c - '1';
    return -1;
}

// Call input again if the piece does not exist at the targeted position.
// If the piece called is valid, must generate the possibles moves.
void can_i_go(Game *game, int *x, int *y, Move_list **li, enum pieces_colors c)
{
    int not_valid = 1;
    while (not_valid){
        not_valid = 0;
        input(x, y);
        Piece *target = NULL;
        if(!get_piece(game, *x, *y, &target))
            errx(1, "Out of bound in chessboard");

        if(target == NULL || target->color != c)
        {
            printf("Not valid piece at selected coordinates.\nTry again...\n");
            not_valid = 1;
        }
        else
        {
        	get_moves(game, game->board[get_pos(*x, *y)], *li, NULL);
            if (li == NULL)
                errx(EXIT_FAILURE, "Move_list is egal to NULL");
			if ((*li)->next == NULL)
			{
				printf("This piece can not move.\n");
				not_valid = 1;
			}
            else if (target->type == KING)
                king_suicide(game, target, *li);
			else
			{
            	is_treason(game, target, *li);
				if ((*li)->next == NULL)
				{
					printf("This piece protect your King from being in check, you can not move it.\n"
                    	"Try again...\n");
            		not_valid = 1;
				}
			}
        }
    }
}

// Call intput to set the coordinates of the destination's position.
// When called; please pass different coordinates than starting x y.
int go_to(Game *game, Move_list *l, int *x, int *y, int *new_x, int *new_y)
{
    printf("Enter targeted postition:\n");
    input(new_x, new_y);
    //TODO Check if the move is possible ? 
    // Check if a piece is in the way.
    while(!valid_pos(*new_x, *new_y))
    {
        printf("Invalid target\n");
        input(new_x, new_y);
    }

	if(in_list(l, *new_x, *new_y))
	{
		apply_move(game, *x, *y, *new_x, *new_y);
		return 1;
	}
	
	return 0;
	
}

// Blocking function, wait for input user. 
// If the input is not valid, recall the function.
// Set x on abscissa (letter) and y on ordinate (number).
// If the input is "help", set x and y on -1.
void input(int *y, int *x){
    char not_valid = 1;
    while (not_valid){
        not_valid = 0;
        printf("Wait for coordinates...\n");
        char buf[16];
        ssize_t r = 16;
        r = read(STDIN_FILENO, buf, 16);
        if (r == -1)
            errx(r, "Error while reading input");
        if (r > 5){
            printf("your input is too long, please try again\n");
            while (buf[r-1] != '\n'){
                r = read(STDIN_FILENO, buf, 16);
            }
            not_valid = 1;
        }

        else if(buf[0] == 'h' && buf[1] == 'e' && buf[2] == 'l' && buf[3] == 'p' && buf[4] == '\n'){
            printf("aide de l'IA\n");
            *x = -1;
            *y = -1;
        }

        else{
            int tmp = 0;

            tmp = verif_input_letter(buf[0]);	
            if (buf[0] == '\n' || tmp == -1){
                printf("Unknow command. Try again\n");
                not_valid = 1;
                continue;
            }

            *x = tmp;


            tmp = verif_input_number(buf[1]);
            if (buf[1] == '\n' || tmp == -1){
                printf("Unknow command. Try again\n");
                not_valid = 1;
                continue;
            }

            *y = tmp;

            if (buf[2] != '\n'){
                printf("Unknow command. Try again\n");
                not_valid = 1;
                continue;
            }
        }
    }
}

