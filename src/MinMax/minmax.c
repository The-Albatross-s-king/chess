#include <stdio.h>
#include <stdlib.h>
#include "minmax.h"
#include "display.h"
#include "board.h"
#include "evaluate.h"
#include "list.h"
#include <unistd.h>
#define DEPTH_MAX 4


void print_evaluate(int depth, double score)
{
    for(int i=0; i<depth; i++)
    {
        printf("-");
    }
    printf(" eval : %lf\n", score);
}
void print_etage(int depth, int max)
{
    for(int i=0; i<depth; i++)
    {
        printf("-");
    }
    if(max)
        printf(" MAX\n");
    else
        printf(" MIN\n");
}

void print_coup(Piece* p, int depth, double score)
{
    for(int i=0; i<depth; i++)
    {
        printf("-");
    }
    printf(": %lf [%s to %d/%c]\n", score, get_name(p->type), p->x+1,p->y+'A');

}

int rec_minmax(Game* g, int cur_color, int depth, int max)
{
    //print_etage(depth,max);
    Piece* b;
    if(cur_color==WHITE)
        b=&g->whites[0];
    else
        b=&g->blacks[0];
    
    Move_list* moves= init_list();
    Move_list cur_move;
    double score_cur_move=0;
    int first_move = 1;
    double best_score=0;
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
        get_moves(g,p,moves, NULL, 0); //get the moves
        //display_board(g->board, moves, cur_color);
        // sleep(2);
        while(!is_empty(moves))
        {
            pop_list(moves,&cur_move.x, &cur_move.y); //get one move
            piece_eat=apply_move(g, p->x, p->y,cur_move.x, cur_move.y);
            //evaluate the last move
            if(piece_eat!=NULL)
                score_cur_move=get_score_piece(piece_eat)*(-1+2*max);
            else
                score_cur_move=0;
            //continue recurcion
            //print_coup(p, depth, score_cur_move);
            if(depth<DEPTH_MAX)
                score_cur_move+=rec_minmax(g, !cur_color, depth+1, !max );
            else
            {
                int init_color=cur_color;
                if(!max)
                    init_color=!cur_color;
                score_cur_move+=evaluate(g, init_color);
                //print_evaluate(depth, evaluate(g, init_color));
            } 
            //choose best move
            if( first_move ||(max && score_cur_move>best_score))
            {
                best_score=score_cur_move;
                first_move=0;
            }
            else if( first_move ||( !max && score_cur_move<best_score))
            {
                first_move=0;
                best_score=score_cur_move;
            }
            else if (score_cur_move == best_score)
            {
                double r = random_double();
                if (r > 0.5)
                    best_score = score_cur_move;
            }
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
    //print_etage(1, 1);
    //MUST DO A MAX INITIALY AND CALL A MIN
    Piece* b;
    if(cur_color==WHITE)
        b=&g->whites[0];
    else
        b=&g->blacks[0];
    
    int depth=1;
    Move_list* moves= init_list();
    Move_list cur_move;
    double score_cur_move=0;
    double best_score=0;
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
        get_moves(g,p,moves, NULL, 0); //get the moves
        //display_board(g->board, moves, cur_color);
        //sleep(2);
        //printf("%lu move of %d at pos %d %d\n", get_size_list(moves), p->type, p->x, p->y); 
        while(!is_empty(moves))
        {
            pop_list(moves,&cur_move.x, &cur_move.y); //get one move
            piece_eat=apply_move(g, p->x, p->y,cur_move.x, cur_move.y);
            
            //evaluate the last move
            if(piece_eat!=NULL)
                score_cur_move=get_score_piece(piece_eat);
            else
                score_cur_move=0;
            //continue recurcion
            if(depth<DEPTH_MAX)
            {
                score_cur_move+=rec_minmax(g, !cur_color, depth+1, 0 );
                //print_coup(p, depth, score_cur_move);
            }
            else
            {
                score_cur_move+=evaluate(g, cur_color);//choose best move
                //print_evaluate(depth, evaluate(g, cur_color));
            }
            if(*best_piece==NULL || score_cur_move>best_score)
            {
                best_score=score_cur_move;
                *best_piece=p;
                *x=p->x;
                *y=p->y;
            }
            //undo the move
            apply_move(g, p->x, p->y, old_x, old_y);
            p->moved=old_moved;
            if(piece_eat!=NULL)
            {
                piece_eat->alive=1;
            }
            g->board[get_pos(cur_move.x, cur_move.y)]=piece_eat;
        }
    }
    //printf("best :%lf\n",best_score);
    free_list(moves);  
}


void auto_move_minmax(Game* g, int cur_color)
{
	int x=0;
	int y=0;
	Piece* p=NULL;
	minmax(g,&x, &y, &p, cur_color); 
	//printf("moved a %s from %c/%d to %c/%d\n",
	 //       get_name(p->type), p->x+'A', p->y, x+'A',y);
    
    //double pos1=position_score(p);
	apply_move(g,p->x, p->y, x, y);
    //double pos2=position_score(p);
    //printf("Score variation : %lf\n", pos1-pos2);


}  




