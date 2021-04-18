#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "spe_rules.h"
#include "board.h"
#include "list.h"
#include "checkmate.h"

void take_choice(Game *g, Piece *pawn);

void pawn_transformation(Game *g, Piece *pawn)
{
    if(pawn == NULL)
    {
        errx(1, "The pawn can't be NULL");
    }
    if(pawn->type != PAWN)
        return;

    if (pawn->x != 0 && pawn->x != 7)
        return;
    take_choice(g, pawn);
}

void replace(Game *g, Piece *pawn, Piece *selected)
{
    pawn->alive = 0;
    selected->x = pawn->x;
    selected->y = pawn->y;
    selected->alive = 1;

    g->board[get_pos(selected->x, selected->y)] = selected;
}

void take_choice(Game *g, Piece *pawn)
{
    printf("Your pawn is at the end of the board, "
            "you have to choose a piece to revive it\n");
    Piece *team = pawn->color == WHITE ? g->whites : g->blacks;
    for(int i = 0; i < 8; i++)
    {
        if(team[i].alive == 0 && team[i].type != KING)
        {
            printf("| %d : %s ", i, get_name(team[i].type));
        }
    }
    printf("|\n");
    int choice = 0;
    while (1)
    {
        printf("Type the number of the piece you want to revive:\n");
        scanf("%i", &choice);
        if(choice >= 0 && choice <= 7 && choice != 3)
        {
            break;
        }
        else
        {
            printf("It is not a good input.\n");
        }
    }
    replace(g, pawn, &team[choice]);
}
