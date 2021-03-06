#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include "board.h"
#include "input.h"

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
void is_piece(int *x, int *y, Game *game, enum color side)
{
    int pos = get_pos(*x, *y);
    if(game->board[pos] == NULL || game->board[pos]->color != side)
    {
        printf("Not valid piece at selected coordinates.\nTry again...\n");
        input(x, y);
    }
    /*
    ** else
    ** {
    **  generate_moves(board[pos]);
    ** }
    */
}

// Call intput to set the coordinates of the destination's position.
// When called; pass different coordinates than starting x y.
void target_pos(int *new_x, int *new_y /*Maybe add a list of move*/)
{
    printf("Enter targeted postition:\n");
    input(new_x, new_y);

    // Iterate over list of moves to check if the move is possible.
    // If move is possible call move.
}

// Blocking function, wait for input user. 
// If the input is not valid, recall the function.
// Set x on abscissa (letter) and y on ordinate (number).
// If the input is "help", set x and y on -1.
void input(int *x, int *y){
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
		input(x, y);
		return;
	}
	
	if (buf[0] == 'h' && buf[1] == 'e' && buf[2] == 'l' && buf[3] == 'p' && buf[4] == '\n'){
		printf("aide de l'IA\n");
		*x = -1;
		*y = -1;
	}
	
	else{
		int tmp = 0;

		tmp = verif_input_letter(buf[0]);	
		if (buf[0] == '\n' || tmp == -1){
			printf("Unknow command. Try again\n");
			input(x,y);
			return;
		}

		*x = tmp;


		tmp = verif_input_number(buf[1]);
		if (buf[1] == '\n' || tmp == -1){
			printf("Unknow command. Try again\n");
			input(x,y);
			return;
		}

		*y = tmp;

		if (buf[2] != '\n'){
			printf("Unknow command. Try again\n");
			input(x,y);
			return;
		}
	}
}
