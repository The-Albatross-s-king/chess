#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "display.h"
#include "save_load.h"
#include "evaluate.h"
#include "list.h"
#include "tree.h"
#include "input.h"
#include "board.h"
#include "checkmate.h"
#include "tie.h"

//ALWAYS SUPERIOR TO 2
#define DEPTH_MAX 4
#define CRITICAL_SCORE -100


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
        if (r > 0.5f)
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

    if(depth <= DEPTH_MAX-2 && parent->child != NULL)
    {
        C=parent->child;
        while(C!=NULL)
        {
            p = g->board[C->old_pos];
            old_moved = p->moved; //c bo
            C->sum = C->score + parent->sum;
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
            int old_pos=p->x*8+p->y;
            old_pos=old_pos+1-1;
            old_moved=p->moved;
            get_moves(g, p, moves, NULL);
            
            while(!is_empty(moves))
            {
                pop_list(moves, &cur_move.x, &cur_move.y);
                piece_eat=apply_move(g, p->x, p->y,cur_move.x, cur_move.y);
                
                if(piece_eat!=NULL)
                    score_cur_move = get_score_piece(piece_eat)*(-1+2*max);
                else
                    score_cur_move=0;
                
                Tree *T = new_tree();
                set_tree(T, old_x, old_y, cur_move.x, cur_move.y);
                T->score = score_cur_move;
                T->sum = T->score + parent->sum;
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

                if(depth<DEPTH_MAX && T->sum > CRITICAL_SCORE) //AND LIMITE
                {
                        alphabeta(g, !color, depth+1, !max, T);
                }
                else if (T->sum > CRITICAL_SCORE)
                {
                    int init_color=color;
                    if(!max)
                        init_color=!color;
                    T->max = evaluate(g, init_color) + T->sum;
                    //printf("eval :%lf\n", T->max);
                }
                else
                    T->max = T->sum;
                
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

void IA_vs_IA(Game *g, int nb_turn)
{
    Tree *T1 = new_tree();
    Tree *T2 = new_tree();
    int color = 1;
    int old_pos;
    int pos;
    Tree* select = NULL;
    //display_board(&g->board[0], NULL, WHITE);

    for(;nb_turn!=0;nb_turn--)
    {
        if(color)
        {
            //manipule T1
            
            alphabeta(g, color, 1, 1, T1);
            get_max_tree(T1, &pos, &old_pos);
            //play T1
            select=select_tree(T1, pos, old_pos);
                       
            //display_board(&g->board[0], NULL, WHITE);
            apply_move(g, old_pos/8, old_pos%8, pos/8, pos%8);
            T1->child=select->child;
            free(select);
            //clean T2
            if(T2->child!=NULL)
            {
                select=select_tree(T2, pos, old_pos);
                T2->child=select->child;
                free(select);
            }
        }
        else
        {
            //manipule T2
            alphabeta(g, color, 1, 1, T2);
            get_max_tree(T2, &pos, &old_pos);
            //play T2
            select=select_tree(T2, pos, old_pos);
            apply_move(g, old_pos/8, old_pos%8, pos/8, pos%8);
            T2->child = select->child;
            free(select);
            //clean T1
            if (T1->child != NULL)
            {   
                select=select_tree(T1, pos, old_pos);
                T1->child = select->child;
                free(select);
            }
        }
        display_board(&g->board[0], NULL, WHITE);
        
        Piece *k;
        if (color)
            k = &g->blacks[3];
        else
            k = &g->whites[3];
       
        if (is_checkmate(g, k))
        {
            if(color)
                printf("The black king is checkmate, whites WIN\n");
            else
                printf("The white king is checkmate, blacks WIN\n");
            break;
        }

        color = !color;
    }
    free_tree(T1);
    free_tree(T2);
}

void human_vs_IA(Game *g, int color_human)
{
    int x_input;
    int y_input;
    int new_x;
    int new_y;
    int color = 1;
    int checkmate = 0;
    int tie = 0;
    Tree *T = new_tree();
    int old_pos;
    int pos;
    Tree* select = NULL;
    Piece *king = &g->blacks[3];
    Move_list *piece_moves = init_list();


    display_board(g->board, piece_moves, color_human);

    while(!checkmate && !tie)
    {
        if (color==color_human) //sans Tree
        {
            printf("It's your turn !\n");
            can_i_go(g, &x_input, &y_input, &piece_moves, color_human);
            display_board(g->board, piece_moves, color_human);
            if (!go_to(g, piece_moves ,&x_input, &y_input, &new_x, &new_y))
            {
                printf("Wrong move, try again.\n");
                free_list(piece_moves->next);
                piece_moves->next = NULL;
                display_board(g->board, NULL, color_human);
                continue;
            }
            free_list(piece_moves->next);
            piece_moves->next = NULL;
            old_pos = x_input*8 + y_input;
            pos = new_x*8 + new_y;
        }
        else
        {
            if(T->child!=NULL)
            {
                select=select_tree(T, pos, old_pos); //got from the human input
                T->child=select->child;
                free(select);
            }
            alphabeta(g, color, 1, 1, T);
            get_max_tree(T, &pos, &old_pos);
            //play T1
            select=select_tree(T, pos, old_pos);
                       
            //display_board(&g->board[0], NULL, WHITE);
            apply_move(g, old_pos/8, old_pos%8, pos/8, pos%8);
            T->child=select->child;
            free(select);
        }

        display_board(g->board, NULL, color_human);

        if(color)
            king = &g->blacks[3];
        else
            king = &g->whites[3];
        
        checkmate = is_checkmate(g, king);
        tie = is_tie(g, (color + 1) % 2);

        color = !color;
    }
    if (tie)
        printf("Tie ! The game wins !\n");
    else if(color)
        printf("The black king is checkmate, whites WIN\n");
    else
        printf("The white king is checkmate, blacks WIN\n");

    free_tree(T);
    free_list(piece_moves);
}
