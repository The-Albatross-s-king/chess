#include <stdio.h>
#include <stdlib.h>
#include "minmax.h"
#include "display.h"
#include "board.h"
#include "list.h"
#include <unistd.h>
#define DEPTH_MAX 1

int SCORES[6]={100,500,300,300,900,10000};
int rec_minmax(Game* g, int cur_color, int depth, int max)
{
    Piece* b;
    if(cur_color==WHITE)
        b=&g->whites[0];
    else
        b=&g->blacks[0];
    
    Move_list* moves= init_list();
    Move_list cur_move;
    int score_cur_move=0;
    int best_score=0;
    Piece* p;
    Piece* piece_eat;
    int old_x, old_y,old_moved;
    for(int i=0; i<16; i++)
    {
        p=&b[i]; //get the piece
        if(!p->alive)
            continue;
        old_x=p->x;
        old_y=p->y;
        old_moved=p->moved;
        get_moves(g,p,moves); //get the moves
        //display_board(g->board, moves, cur_color);
        // sleep(2);
        while(!is_empty(moves))
        {
            pop_list(moves,&cur_move.x, &cur_move.y); //get one move
            piece_eat=apply_move(g, p->x, p->y,cur_move.x, cur_move.y);
            //evaluate the last move
            if(piece_eat!=NULL)
                score_cur_move=SCORES[piece_eat->type]*(-1+2*max);
            else
                score_cur_move=0;
            //continue recurcion
            if(depth<DEPTH_MAX)
                score_cur_move+=rec_minmax(g, !cur_color, depth+1, !max );
            //choose best move
            if(max && score_cur_move>best_score)
                best_score=score_cur_move;
            else if(!max && score_cur_move<best_score)
                best_score=score_cur_move;
            //undo the move
            apply_move(g, cur_move.x, cur_move.y, old_x, old_y);
            if(piece_eat!=NULL)
            {
                piece_eat->alive=1;
            }
            p->moved=old_moved;
            g->board[get_pos(cur_move.x, cur_move.y)]=piece_eat;
        }
    }
    free_list(moves);
    return best_score; //negative if max==0
}

void minmax(Game* g, int* x, int* y, Piece** best_piece, int cur_color) 
{

    //MUST DO A MAX INITIALY AND CALL A MIN
    Piece* b;
    if(cur_color==WHITE)
        b=&g->whites[0];
    else
        b=&g->blacks[0];
    
    int depth=1;
    Move_list* moves= init_list();
    Move_list cur_move;
    int score_cur_move=0;
    int best_score=-1;
    Piece* p;
    Piece* piece_eat;
    int old_x, old_y, old_moved;
    for(int i=0; i<16; i++)
    {
        p=&b[i]; //get the piece
        if(!p->alive)
            continue;
        old_x=p->x;
        old_y=p->y;
        old_moved=p->moved;
        get_moves(g,p,moves); //get the moves
        //display_board(g->board, moves, cur_color);
        //sleep(2);
        //printf("%lu move of %d at pos %d %d\n", get_size_list(moves), p->type, p->x, p->y); 
        while(!is_empty(moves))
        {
            pop_list(moves,&cur_move.x, &cur_move.y); //get one move
            piece_eat=apply_move(g, p->x, p->y,cur_move.x, cur_move.y);
            
            //evaluate the last move
            if(piece_eat!=NULL)
                score_cur_move=SCORES[piece_eat->type];
            else
                score_cur_move=0;
            //continue recurcion
            if(depth<DEPTH_MAX)
                score_cur_move+=rec_minmax(g, !cur_color, depth+1, 0 );
            //choose best move
            if(score_cur_move>best_score)
            {
                best_score=score_cur_move;
                *best_piece=p;
                *x=p->x;
                *y=p->y;
            }
            //undo the move
            apply_move(g, p->x, p->y, old_x, old_y);
            if(piece_eat!=NULL)
            {
                piece_eat->alive=1;
            }
            p->moved=old_moved;
            g->board[get_pos(cur_move.x, cur_move.y)]=piece_eat;
        }
    }
    free_list(moves);  


}

void auto_move(Game* g, int cur_color)
{
int x=0;
int y=0;
Piece* p;
minmax(g,&x, &y, &p, cur_color); 
printf("moved a %s from %c/%d to %c/%d\n",\
        get_name(p->type), p->x+'A', p->y, x+'A',y);
apply_move(g,p->x, p->y, x, y);

}




