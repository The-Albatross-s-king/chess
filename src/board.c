#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "list.h"
#include <err.h>

int get_pos(int x, int y)
{
    if(x>=8 || y>=8 || x<0 || y<0)
        errx(3, "Error, out of bound\n");
    return x*8+y;
}

//returns in p the piece at x,y. return 0  if out of bound
int get_piece(Game* g, int x, int y, Piece** p)
{
    if(x>=8 || y>=8 || x<0 || y<0)
        return 0;
    *p=g->board[get_pos(x,y)];
    return 1;
}

//return 1 if pos occupied by opposite color or empty
int can_move_to(Game* g, int x, int y, Piece* p)
{
    Piece* target=NULL;
    if((get_piece(g, x, y, &target) && (target==NULL && p->type != PAWN)) \
            || (target!=NULL && target->color != p->color))
        return 1;
    return 0;
}



void get_cross_moves(Game* g, Piece* p, Move_list* l)
{
    int x=p->x+1;
    int y=p->y;
    //moves up
    while(x<8)
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    x++;
    }
    //moves down
    x=p->x-1;
    while(x>=0)
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    x--;
    }

    x=p->x;
    y=p->y+1;
    while(y<8)
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    y++;
    }
    //moves down
    y=p->y-1;
    while(y>=0)
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    y--;
    }
}

void get_diagonal_moves(Game* g, Piece* p, Move_list* l)
{
    int x=p->x+1;
    int y=p->y+1;
    //moves down right
    while(x<8 && y<8)
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    x++;
    y++;
    }
    //moves down left
    x=p->x+1;
    y=p->y-1;
    while(x<8 && y>=0 )
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    x++;
    y--;
    }

    x=p->x-1;
    y=p->y+1;
    //moves up right 
    while(x>=0 && y<8)
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    x--; 
    y++;
    }
    //moves up left
    x=p->x-1;
    y=p->y-1;
    while(x>=0 && y>=0)
    {
    if(can_move_to(g, x, y, p))
        {
            add_list(l,x,y);
        }
    if(g->board[get_pos(x,y)]!=NULL)
        break;
    y--;
    x--;
    }

}

void get_pawn_moves(Game* g, Piece* p,Move_list* l)
{
    int s=1;//sens
    if(p->color==WHITE) //bottom of the board
        s=-1;
    if(g->board[get_pos(p->x+s,p->y)]==NULL)
    {
        add_list(l, p->x+s, p->y);
    }
    if(can_move_to(g, p->x+s, p->y+s, p))
    {
        add_list(l, p->x+s, p->y+s);
    }
    if(can_move_to(g, p->x+s, p->y-s, p))
    {
        add_list(l, p->x+s, p->y-s);
    }
    if(!p->moved && g->board[get_pos(p->x+s,p->y)]==NULL && \
            g->board[get_pos(p->x+2*s,p->y)]==NULL)
    {       
        add_list(l,p->x+2*s,p->y);
    }
}


void get_knight_moves(Game* g, Piece* p,Move_list* l)
{

    int moves_x[8]={+2,+2,-2,-2,+1,+1,-1,-1};
    int moves_y[8]={+1,-1,+1,-1,+2,-2,+2,-2};
    //+2+1; +2-1; -2+1; -2   ;+1+2; -1+2; +1-2; -1-2; 
    for(int i=0; i<8; i++){
        if(can_move_to(g, p->x+moves_x[i], p->y+moves_y[i], p))
        {
            add_list(l,p->x+moves_x[i],p->y+moves_y[i]);
        }
    }
}

void get_bishop_moves(Game* g, Piece* p,Move_list* l)
{
    get_diagonal_moves(g,p,l);

} 
void get_rook_moves(Game* g, Piece* p,Move_list* l)
{
    get_cross_moves(g,p,l);

} 

void get_queen_moves(Game* g,Piece* p,Move_list* l)
{
    get_cross_moves(g,p,l);
    get_diagonal_moves(g,p,l);

}
void get_king_moves(Game* g, Piece* p,Move_list* l)
{
    
    int moves_x[8]={1,1,1,-1,-1,-1,0,0};
    int moves_y[8]={1,-1,0,1,-1,0,1, -1};
    for(int i=0; i<8; i++){
        if(can_move_to(g, p->x+moves_x[i], p->y+moves_y[i], p))
        {
            add_list(l,p->x+moves_x[i],p->y+moves_y[i]);
        }
    }
}

void get_moves(Game* g, int x, int y, Move_list* l)
{
    
    Piece* p=g->board[get_pos(x,y)];
    if(p==NULL)
    {
        return;
    }
    switch(p->type)
    {
        case PAWN:
            get_pawn_moves(g,p,l);
            break;
        case ROOK:
            get_rook_moves(g,p,l);
            break;
        case BISHOP:
            get_bishop_moves(g,p,l);
            break;
        case KNIGHT:
            get_knight_moves(g,p,l);
            break;
         case QUEEN:
            get_queen_moves(g,p,l);
            break;
        case KING:
            get_king_moves(g,p,l);
            break;
    }


}
//return 1 if move applied
int move(Game* g, int x, int y, int x2, int y2)
{
    Move_list* l=init_list();
    get_moves(g, x, y, l);
    if(in_list(l, x2, y2)){
        free_list(l);
        apply_move(g, x, y, x2, y2);
        return 1;
    }
    free_list(l);
    return 0;
}
int apply_move(Game* g,int x, int y, int x2, int y2)
{

    Piece* p=g->board[get_pos(x,y)];
    if(p==NULL)
        errx(3, "Error, case vide\n");
    p->moved=1;
    int pos=get_pos(x2,y2);
    Piece* target=g->board[pos];
    if(target==NULL) //empty destination
    {
        g->board[pos]=p;
        g->board[get_pos(x,y)]=NULL; //old place empty
        p->x=x2;
        p->y=y2;
        return -1;
    }
    target->alive=0;
    g->board[get_pos(x,y)]=NULL; //old place empty
    p->x=x2;
    p->y=y2;

    g->board[pos]=p;
    return target->type;
}


void set_game(Game* g)
{
    // 1 : malloc pieces and init basic data
    // 2 : set type 
    //set blacks (up)
    for(int i=0; i<2; i++)
    {
        for(int j=0;j<8;j++)
        {
            int x=get_pos(i,j);
            g->blacks[x].color=BLACK;
            g->blacks[x].x=i;
            g->blacks[x].y=j;
            g->blacks[x].alive=1;
            g->blacks[x].moved=0;
            g->board[x]=&(g->blacks[x]);
        }
    }
    //set whites (down)s
    for(int i=6; i<8; i++)
    {
        for(int j=0;j<8;j++)
        {
            int x=get_pos(i,j);
            g->whites[x].color=WHITE;
            g->whites[x].x=i;
            g->whites[x].y=j;
            g->whites[x].alive=1;
            g->whites[x].moved=0;
            g->board[x]=&(g->whites[(x+8)%16]);//+8 to keep same order of white 
        }
    }

    int types[8]={ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK};
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(0,j)]->type=types[j];

    }
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(1,j)]->type=PAWN;
    }
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(6,j)]->type=PAWN;
    }
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(7,j)]->type=types[7-j];
    }
}
