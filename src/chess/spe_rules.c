#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "spe_rules.h"
#include "board.h"
#include "list.h"
#include "checkmate.h"

void take_choice(Game *g, Piece *pawn);

// Verify if the pawn is in the border of the board and can be changed
// then ask for the piece the player wants to revive and replace the pawn
// by the piece choosen.
void pawn_transformation(Game *g, Piece *pawn)
{
    // test if the pawn is in the case when the changement
    // occurs
    if(pawn == NULL)
    {
        errx(1, "The pawn can't be NULL");
    }
    if(pawn->type != PAWN)
        return;

    if (pawn->x != 0 && pawn->x != 7)
        return;

    // If the pawn is in a corresponding situation call the function take_choice
    take_choice(g, pawn);
}

// Replace the pawn by the piece selected.
void replace(Game *g, Piece *pawn, Piece *selected)
{
    pawn->alive = 0;
    selected->x = pawn->x;
    selected->y = pawn->y;
    selected->alive = 1;

    g->board[get_pos(selected->x, selected->y)] = selected;
}


// Ask for a piece and call the replace function when the input is valide.
void take_choice(Game *g, Piece *pawn)
{
    printf("Your pawn is at the end of the board, "
            "you have to choose a piece to revive it\n");
    Piece *team = pawn->color == WHITE ? g->whites : g->blacks;

    // print possible choices.
    for(int i = 0; i < 8; i++)
    {
        if(team[i].alive == 0 && team[i].type != KING)
        {
            printf("| %d : %s ", i, get_name(team[i].type));
        }
    }
    printf("|\n");
    int choice = 0;

    // while the choice is not correct, re-ask for a piece.
    while (1)
    {
        printf("Type the number of the piece you want to revive:\n");
        int e = scanf("%i", &choice);
		if (e != 0)
			errx(EXIT_FAILURE, "erreur while scaning input");
        if(choice >= 0 && choice <= 7 && choice != 3 && team[choice].alive == 0)
        {
            break;
        }
        else
        {
            printf("It is not a good input.\n");
        }
    }
    // call the replace function
    replace(g, pawn, &team[choice]);
}
