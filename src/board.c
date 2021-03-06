#include <stdio.h>
#include <stdlib.h>
#include "board.h"
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

Move_list* init_list()
{
    Move_list* sentinel=malloc(sizeof(Move_list));
    sentinel->next=NULL;
    sentinel->x=-1;
    return sentinel;
}
void add_list(Move_list* list, int x, int y)
{
    Move_list* new=malloc(sizeof(Move_list));
    new->x=x;
    new->y=y;
    new->next=list->next;
    list->next=new;
}

size_t get_size_list(Move_list* list)
{
    size_t len=0;
    list=list->next;
    while(list!=NULL)
    {
        len++;
        list=list->next;
    }
    return len;
}
// reads list and free the pop, returns 1 if valide 0 otherwise
int pop_list(Move_list* list, int* x, int* y)
{
    if(list->next==NULL)
        return 0;
    *x=list->next->x;
    *y=list->next->y;
    Move_list* tmp=list->next;
    list->next=tmp->next;
    free(tmp);
    return 1;
}
//return 1 if x,y in the list
int in_list(Move_list* list, int x, int y)
{
list=list->next;
while(list!=NULL)
{
    if(list->x==x && list->y==y)
        return 1;
    list=list->next;
}
return 0;
}

int is_empty(Move_list* list)
{
    if(list==NULL)
        errx(3, "is_empty : try to use NULL pointeuri\n");
    return list->next==NULL;
}

void free_list(Move_list* list)
{

Move_list* tmp;
while(list!=NULL)
{
    tmp=list;
    list=list->next;
    free(tmp);
}
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

Move_list* get_pawn_moves(Game* g, Piece* p)
{
    Move_list* l=init_list();
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
    return l;
}


Move_list* get_knight_moves(Game* g, Piece* p)
{
    Move_list* l=init_list();

    int moves_x[8]={+2,+2,-2,-2,+1,+1,-1,-1};
    int moves_y[8]={+1,-1,+1,-1,+2,-2,+2,-2};
    //+2+1; +2-1; -2+1; -2   ;+1+2; -1+2; +1-2; -1-2; 
    for(int i=0; i<8; i++){
        if(can_move_to(g, p->x+moves_x[i], p->y+moves_y[i], p))
        {
            add_list(l,p->x+moves_x[i],p->y+moves_y[i]);
        }
    }
    return l;
}

Move_list* get_bishop_moves(Game* g, Piece* p)
{
    Move_list* l=init_list();
    get_diagonal_moves(g,p,l);
    return l;

} 
Move_list* get_rook_moves(Game* g, Piece* p)
{
    Move_list* l=init_list();
    get_cross_moves(g,p,l);
    return l;

} 

Move_list* get_queen_moves(Game* g,Piece* p)
{
    Move_list* l=init_list();
    get_cross_moves(g,p,l);
    get_diagonal_moves(g,p,l);
    return l;

}
Move_list* get_king_moves(Game* g, Piece* p)
{
    Move_list* l=init_list();
    int moves_x[8]={1,1,1,-1,-1,-1,0,0};
    int moves_y[8]={1,-1,0,1,-1,0,1, -1};
    for(int i=0; i<8; i++){
        if(can_move_to(g, p->x+moves_x[i], p->y+moves_y[i], p))
        {
            add_list(l,p->x+moves_x[i],p->y+moves_y[i]);
        }
    }
    return l;
}

Move_list* get_moves(Game* g, int x, int y)
{
    
    Move_list* l;
    Piece* p=g->board[get_pos(x,y)];
    if(p==NULL)
    {
        l=init_list();
        return l;
    }
    switch(p->type)
    {
        case PAWN:
            l=get_pawn_moves(g,p);
            break;
        case ROOK:
            l=get_rook_moves(g,p);
            break;
        case BISHOP:
            l=get_bishop_moves(g,p);
            break;
        case KNIGHT:
            l=get_knight_moves(g,p);
            break;
         case QUEEN:
            l=get_queen_moves(g,p);
            break;
        case KING:
            l=get_king_moves(g,p);
            break;
        default:
            errx(3, "invalid type\n");
    }
    return l;


}
//return 1 if move applied
int move(Game* g, int x, int y, int x2, int y2)
{
    Move_list* l=get_moves(g, x, y);
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

void free_game(Game* g)
{
    for(int i = 0; i < 16 ; i++)
    { 
        free(&(g->blacks[i]));
        free(&(g->whites[i]));
    }
}


void display(Game* g)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0; j<8;j++)
        {
            int x=get_pos(i,j);
            if(g->board[x]==NULL)
                printf("x ");
            else{
                printf("%d ",g->board[x]->type);
            }
        }

        printf("\n");
    }
}

void display_list(Move_list* l)
{
    printf("coups possibles :\n");
    l=l->next;
    while(l!=NULL)
    {
        printf("%d %d -> ",l->x,l->y);
        l=l->next;
    }
    printf("NULL\n");
}




