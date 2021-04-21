#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "display.h"
#include "evaluate.h"
#include "list.h"
#include "tree.h"
#include "board.h"

//ALWAYS SUPERIOR TO 2
#define DEPTH_MAX 4
#define CRITICAL_SCORE -200

//TODO put it in evaluate (do a function)
int ab_SCORES[6]={10,50,30,30,90,900};

void compute_minmax(int* first_move, int max, Tree* parent, Tree* T)
{
    if (*first_move ||(max && T->max > parent->max))
    {
        parent->max=T->max;
        *first_move=0;
    }
    else if (*first_move ||( !max && T->max < parent->max))
    {
        parent->max=T->max;
        *first_move=0;
    }
    else if (T->max == parent->max)
    {
        double r = random_double();
        if (r > 0.5)
            parent->max=T->max;
    }
}


//build tree, compute leafs
void alphabeta(Game *g, int color, int depth, int max, Tree* parent)
{
    //PREFIX
    //for all moves
    //get moves
    //create Tree child or add sibling to the child
    //get score from apply move
    //store pos ,old_pos,score and max=score
    //if score too bad : dont recurcive
    //else launch recurcion
    
    //SUFFIX
    //if leaf set max = score+evaluate()
    //else max= maximum(max of the childs)
    //restore move

    Piece *b;
    if(color == WHITE)
        b=&g->whites[0];
    else
        b=&g->blacks[0];

    Move_list *moves = init_list();
    Move_list cur_move;
    int first_move = 1;
    Piece *p;
    Piece *piece_eat;
    int old_x;
    int old_y;
    int old_moved;
    Tree *C = NULL;
    int score_cur_move = 0;

    //IF ALREADY COMPUTED

    if(depth < DEPTH_MAX-2 && parent->child != NULL)
    {
        C=parent->child;
        while(C!=NULL)
        {
            p = g->board[C->old_pos];
            old_moved = p->moved; //c bo
            C->max = C->score + parent->score;
            piece_eat = apply_move(g, C->old_pos/8, C->old_pos%8, C->pos/8, C->pos%8);
            
            alphabeta(g, !color, depth+1, !max, C);
            
            apply_move(g, C->pos/8, C->pos%8, C->old_pos/8, C->old_pos%8);
            
            if(piece_eat!=NULL)
            {
                piece_eat->alive=1;
            }

            p->moved=old_moved;
            g->board[C->pos]=piece_eat;
            
            compute_minmax(&first_move, max, parent, C);

            C=C->sibling;
        }
    }
    else  //NOT COMPUTED
    {
        for(int i=0; i<16; i++)
        {
            p = &b[i];
            if (!(p->alive))
                continue;
            old_x=p->x;
            old_y=p->y;
            old_moved=p->moved;
            get_moves(g, p, moves, NULL);
            
            while(!is_empty(moves))
            {
                pop_list(moves, &cur_move.x, &cur_move.y);
                piece_eat=apply_move(g, p->x, p->y,cur_move.x, cur_move.y);
                
                if(piece_eat!=NULL)
                    score_cur_move = ab_SCORES[piece_eat->type]*(-1+2*max);
                else
                    score_cur_move=0;
                
                Tree *T = new_tree();
                set_tree(T, p->x, p->y, cur_move.x, cur_move.y);
                T->score = score_cur_move;
                T->max = T->score + parent->score;
                if(C==NULL)
                {
                    parent->child = T;
                    C=T;
                }
                else
                {
                    C->sibling=T;
                    C=C->sibling;
                }

                if(depth<DEPTH_MAX && T->max > CRITICAL_SCORE) //AND LIMITE
                {
                        alphabeta(g, !color, depth+1, !max, T);
                }
                else if (T->max > CRITICAL_SCORE)
                {
                    int init_color=color;
                    if(!max)
                        init_color=!color;
                    T->max+=evaluate(g, init_color, &ab_SCORES[0]);
                } 
                
                compute_minmax(&first_move, max, parent, T);

                apply_move(g, cur_move.x, cur_move.y, old_x, old_y);
                if(piece_eat!=NULL)
                {
                    piece_eat->alive=1;
                }
                p->moved=old_moved;
                g->board[get_pos(cur_move.x, cur_move.y)]=piece_eat;
            }
        }
    }
    free_list(moves);
}

//GESTION DE LA SENTINEL PROCHAINE FOIS A VERIFIER !!!

//IL FAUT TROUVER UN MOYEN DE RECUP LE DERNIER MOVE CORRECTEMENT
void auto_move_alphabeta(Game* g, int cur_color, Tree** T, int oldpos_lastmove, int pos_lastmove)
{
    //Step forward 1 times:
    //  -select_tree the last played moves
    Tree* select = NULL;
    if((*T)->child != NULL)
        select=select_tree(*T, oldpos_lastmove, pos_lastmove);
    else //INIT parent de la suite ?
        select= *T;
    if(select==NULL)
        errx(3, "Can't select Tree");
    *T=select;
    //Launch alphabeta
    alphabeta(g, cur_color, 1, 1, *T);
    //search best "max" from the childs
    //play the best move
    
    //Step forward 1 time with the last move
}



