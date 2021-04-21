#include <err.h>
#include "evaluate.h"
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "list.h"

double score_circle[4]={0.5, 1.0, 1.5, 2.0};

double king_positions[]=
{
-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0,
2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0
};

double queen_positions[]=
{
    -2.0, -1.0, -1.0, -0,5, -0.5, -1.0, -1.0, -2.0,
    -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
    -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
    -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
    -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
     0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
    -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
    -2.0, -1.0, -1.0, -0,5, -0.5, -1.0, -1.0, -2.0
};

double rook_positions[]=
{
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5,
    -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
    -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
    -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
    -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
    -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
    0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0

};

double bishop_positions[]=
{
    -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
    -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0,
    -1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0,
    -1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0,
    -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0,
    -1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0,
    -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0
};

double knight_positions[]=
{
    -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
    -4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
    -3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
    -3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
    -3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
    -3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
    -4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
    -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0
};

double pawn_positions[]=
{
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0,
    1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0,
    0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5,
    0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0,
    0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5,
    0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

double* pieces_positions[]={&pawn_positions[0], &rook_positions[0], &king_positions[0], &bishop_positions[0], &queen_positions[0], &king_positions[0]};

double position_score(Piece* p)
{
    int x = p->x;
    if(p->color==BLACK)
        x=7-p->x;
    
    return pieces_positions[p->type][get_pos(x, p->y)];
}

int get_circle_position(Piece* p)
{
    int x=p->x;
    int y=p->y;

    if(x==0 || x==7 || y==0 || y==7)
    {
        return 0;
    }
    else if(x==1 || x==6 || y==1 || y==6)
    {
        return 1;
    }
    else if(x==2 || x==5 || y==2 || y==5)
    {
        return 2;
    }
    
	return 3;
}

double get_position_score(Game* game, int cur_color)
{
    double sum=0;
    int is_black = -1+2*(cur_color==BLACK); 
    for(int i=0;i<16; i++)
    {
        sum+=position_score(&(game->blacks[i]))*is_black;
        sum-=position_score(&(game->whites[i]))*is_black;
    }
    return sum;
}


double get_atk_def(Game *game, int cur_color, int* scores)
{

    Move_list *atk = init_list(); 
    Move_list *def = init_list();
    int sum = 0;
    for(int i=0;i<16; i++)
    {
        if(cur_color==WHITE)
            get_moves(game, &game->whites[i], atk, def);
        else
            get_moves(game, &game->blacks[i], atk, def);

        int x=0;
        int y=0;
        
        while (!is_empty(def))
        {
            pop_list(def, &x, &y);
            if(scores[game->board[x * 8 + y]->type!=KING])
                sum += scores[game->board[x * 8 + y]->type] / 5;
        }

        while (!is_empty(atk))
        {
            pop_list(atk, &x, &y);
            if (game->board[x * 8 + y] != NULL)
                sum += scores[game->board[x * 8 + y]->type] / 5;
        }
    }
    free_list(atk);
    free_list(def);
    return (double)sum;
}
