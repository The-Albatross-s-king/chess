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
    2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0,
    1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0,
    0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5,
    0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0,
    0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5,
    0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

double* pieces_positions[]={&pawn_positions[0], &rook_positions[0], &knight_positions[0], &bishop_positions[0], &queen_positions[0], &king_positions[0]};

int SCORES[6]={10,50,30,30,90,900};

int get_score_piece(Piece *p)
{
    return SCORES[p->type];
}

double random_double(void)
{
    //srandom(NULL);
    long int x=rand();
    return ((double)x)/RAND_MAX;
}


double evaluate(Game* g, int cur_color)
{
    double score=0;
    score+=get_atk_def_pos(g,cur_color);
    return score;
}

double position_score(Piece* p)
{
    if (!p->alive)
        return 0;
    int x = 7-p->x;
    if(p->color==BLACK)
        x=p->x;
    
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

double get_atk_def_pos(Game *game, int cur_color)
{

    Move_list *atk = init_list(); 
    Move_list *def = init_list();
    double sum = 0;
    Piece* cur_pieces=&game->blacks[0];
    Piece* opp_pieces=&game->whites[0];
    if(cur_color==WHITE)
    {
        cur_pieces=&game->whites[0];
        opp_pieces=&game->blacks[0];
    }
    for(int i=0;i<16; i++)
    {
        //atk & def
        get_moves(game, &cur_pieces[i], atk, def, 0);
        
        int x=0;
        int y=0;
        int factor_def=50;
        int factor_atk=20;
        while (!is_empty(def) && !is_empty(atk))
        {
            pop_list(def, &x, &y);
            if(game->board[x * 8 + y]->type!=KING)
                sum += ((double)get_score_piece(game->board[x * 8 + y])) / factor_def;
            pop_list(atk, &x, &y);
            if (game->board[x * 8 + y] != NULL)
                sum += ((double)get_score_piece(game->board[x * 8 + y]))/ factor_atk;
        }
        
        while (!is_empty(def))
        {
            pop_list(def, &x, &y);
            if(game->board[x * 8 + y]->type!=KING)
                sum += ((double)get_score_piece(game->board[x * 8 + y])) / factor_def;
        }

        while (!is_empty(atk))
        {
            pop_list(atk, &x, &y);
            if (game->board[x * 8 + y] != NULL)
                sum += ((double)get_score_piece(game->board[x * 8 + y]))/ factor_atk;
        }

        //position
        sum+=position_score(&cur_pieces[i]);
        sum-=position_score(&opp_pieces[i]);
    }
    free_list(atk);
    free_list(def);
    return sum;
}
