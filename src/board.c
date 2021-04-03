#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <display.h>
#include "board.h"
#include "list.h"
#include <err.h>

char* get_name(int type)
{
    switch(type)
    {
        case 0:
            return "PAWN";
        case 1:
            return "ROOK";
        case 2:
            return "KNIGHT";
        case 3:
            return "BISHOP";
        case 4:
            return "QUEEN";
        case 5:
            return "KING";
        default:
            return "NONE";
    }
}


int valid_pos(int x, int y)
{

    if(x >= 8 || y >= 8 || x < 0 || y < 0)
    {
        return 0;
    }
    return 1;
}
int get_pos(int x, int y)
{
    if(!valid_pos(x,y))
        errx(3, "Error, out of bound\n");
    return 8 * x + y;
}

//returns in p the piece at x,y. return 0  if out of bound
int get_piece(Game* g, int x, int y, Piece** p)
{
    if(!valid_pos(x,y))
    {
        *p=NULL; //to be sure for the next get_piece
        return 0;
    }
    *p=g->board[get_pos(x,y)];
    return 1;
}

//return 1 if pos occupied by opposite color or empty
int can_move_to(Game* g, int x, int y, Piece* p)
{
    Piece* target=NULL;
    if(get_piece(g, x, y, &target) && (target==NULL \
                || (target!=NULL && target->color != p->color)))
        return 1;
    return 0;
}



void get_cross_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{
    Piece* target=NULL; //usefull for the the build of def
    
    int x=p->x+1;
    int y=p->y;

    //moves up
    while(x<8)
    {
        if(can_move_to(g, x, y, p))
        {
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
        x++;
    }
    //moves down
    x=p->x-1;
    while(x>=0)
    {
        if(can_move_to(g, x, y, p))
        {
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
        x--;
    }

    x=p->x;
    y=p->y+1;
    while(y<8)
    {
        if(can_move_to(g, x, y, p))
        {
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
        y++;
    }
    //moves down
    y=p->y-1;
    while(y>=0)
    {
        if(can_move_to(g, x, y, p))
        {
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
        y--;
    }
}

void get_diagonal_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{
    Piece* target=NULL;
    int x=p->x+1;
    int y=p->y+1;
    //moves down right
    while(x<8 && y<8)
    {
        if(can_move_to(g, x, y, p))
        {
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
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
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
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
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
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
            add_list(atk,x,y);
        }
        if(get_piece(g, x, y, &target) && target!=NULL) 
        {
            if(target->color==p->color)
                secure_add_list(def, x, y);
            break;
        }
        y--;
        x--;
    }

}

void get_pawn_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{
    int s=1;//sens
    if(p->color==WHITE) //bottom of the board
        s=-1;
    
    Piece* target=NULL;
    if(get_piece(g, p->x+s, p->y, &target) && target==NULL)
    {
        add_list(atk, p->x+s, p->y);
    }
    if(get_piece(g, p->x+s, p->y+s, &target) && target!=NULL)
    {
        if(target->color!=p->color)
            add_list(atk, p->x+s, p->y+s);
        else
            secure_add_list(def, p->x+s, p->y+s);
    }
    if(get_piece(g, p->x+s, p->y-s, &target) && target!=NULL)
    {
        if(target->color!=p->color)
            add_list(atk, p->x+s, p->y-s);
        else
            secure_add_list(def, p->x+s, p->y-s);
    }
    if(!p->moved && valid_pos(p->x+s,p->y) && valid_pos(p->x+2*s,p->y) &&\
            g->board[get_pos(p->x+s,p->y)]==NULL && \
            g->board[get_pos(p->x+2*s,p->y)]==NULL)
    {       
        add_list(atk,p->x+2*s,p->y);
    }
}


void get_knight_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{

    int moves_x[8]={+2,+2,-2,-2,+1,+1,-1,-1};
    int moves_y[8]={+1,-1,+1,-1,+2,-2,+2,-2};
    Piece* target=NULL;
    //+2+1; +2-1; -2+1; -2   ;+1+2; -1+2; +1-2; -1-2; 
    for(int i=0; i<8; i++){
        if(can_move_to(g, p->x+moves_x[i], p->y+moves_y[i], p))
        {
            add_list(atk,p->x+moves_x[i],p->y+moves_y[i]);
        }
        else if(get_piece(g, p->x+moves_x[i], p->y+moves_y[i], &target) \
                        && target!=NULL && target->color==p->color)
        {
            secure_add_list(def, p->x+moves_x[i], p->y+moves_y[i]);
        }  
    }
}

void get_bishop_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{
    get_diagonal_moves(g,p,atk,def);

} 
void get_rook_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{
    get_cross_moves(g,p,atk,def);

} 

void get_queen_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{
    get_cross_moves(g,p,atk, def);
    get_diagonal_moves(g,p, atk, def);

}
void get_king_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{

    int moves_x[8]={1,1,1,-1,-1,-1,0,0};
    int moves_y[8]={1,-1,0,1,-1,0,1, -1};
    Piece* target=NULL;
    for(int i=0; i<8; i++)
    {
        if(can_move_to(g, p->x+moves_x[i], p->y+moves_y[i], p))
        {
            add_list(atk,p->x+moves_x[i],p->y+moves_y[i]);
        }
        else if(get_piece(g, p->x+moves_x[i], p->y+moves_y[i], &target) \
                        && target!=NULL && target->color==p->color)
        {
            secure_add_list(def, p->x+moves_x[i], p->y+moves_y[i]);
        }  
    }
}

//atk can't be null but def yes. 
//atk : returns a list of eatable pieces and null cases
//def : returns if not null all defended pieces
void get_moves(Game* g, Piece* p,  Move_list* atk, Move_list* def)
{
    if(p->alive==0)
        return;
    switch(p->type)
    {
        case PAWN:
            get_pawn_moves(g,p,atk,def);
            break;
        case ROOK:
            get_rook_moves(g,p,atk,def);
            break;
        case BISHOP:
            get_bishop_moves(g,p,atk,def);
            break;
        case KNIGHT:
            get_knight_moves(g,p,atk,def);
            break;
        case QUEEN:
            get_queen_moves(g,p,atk,def);
            break;
        case KING:
            get_king_moves(g,p,atk,def);
            break;
    }


}
//return 1 if move applied
int move(Game* g, Piece* p, int x2, int y2)
{
    Move_list* l=init_list();
    get_moves(g, p, l, NULL);
    if(in_list(l, x2, y2)){
        free_list(l);
        apply_move(g, p->x, p->y, x2, y2);
        return 1;
    }
    free_list(l);
    return 0;
}
Piece* apply_move(Game* g,int x, int y, int x2, int y2)
{
    Piece* p=g->board[get_pos(x,y)];
    if(p==NULL)
    {
        errx(3, "Error, case vide\n");
    }
    p->moved=1;
    int pos=get_pos(x2,y2);
    Piece* target=g->board[pos];
    if(target==NULL) //empty destination
    {
        g->board[pos]=p;
        g->board[get_pos(x,y)]=NULL; //old place empty
        p->x=x2;
        p->y=y2;
        return NULL;
    }
    target->alive=0;
    g->board[pos]=p;
    g->board[get_pos(x,y)]=NULL; //old place empty
    p->x=x2;
    p->y=y2;

    return target;
}

// Is_checkmate checks if the given king is in checkmate state.
int is_checkmate(Game* g, Piece *king)
{
    // Means opponent list, its the list of opponent's pieces.
    Piece *opp_list; 
    if(king->color == WHITE)
        opp_list = g->blacks;
    else
        opp_list = g->whites;

    Move_list *opp_li_moves=init_list();
    for(int i = 0; i < 16; i ++)
    {
        int x_opp = opp_list[i].x;
        int y_opp = opp_list[i].y;
        get_moves(g, g->board[get_pos(x_opp,y_opp)], opp_li_moves, NULL);
        if(in_list(opp_li_moves, king->x, king->y))
            return 1;
    }

    return 0;
}

void set_game(Game* g)
{
    // 1 : malloc pieces and init basic data
    // 2 : set type 
    //set blacks (up)
    for(int i=0; i<64; i++)
        g->board[i]=NULL;
    for(int i=0; i<2; i++)
    {
        for(int j=0;j<8;j++)
        {
            int x=i*8+j;
            g->blacks[x].color=BLACK;
            g->blacks[x].x=i;
            g->blacks[x].y=j;
            g->blacks[x].alive=1;
            g->blacks[x].moved=0;
            g->board[get_pos(i,j)]=&(g->blacks[x]);
        }
    }
    //set whites (down)s
    for(int i=6; i<8; i++)
    {
        for(int j=0;j<8;j++)
        {
            int x=(7-i)*8+j;
            g->whites[x].color=WHITE;
            g->whites[x].x=i;
            g->whites[x].y=j;
            g->whites[x].alive=1;
            g->whites[x].moved=0;
            g->board[get_pos(i,j)]=&(g->whites[x]);//+8 to keep same order of white 
        }
    }

    int types[8]={ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK};
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(0,j)]->type=types[j];
        g->board[get_pos(0,j)]->id=j;

    }
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(1,j)]->type=PAWN;
        g->board[get_pos(0,j)]->id=8+j;
    }
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(6,j)]->type=PAWN;
        g->board[get_pos(0,j)]->id=16+j;
    }
    for(int j=0;j<8;j++)
    {
        g->board[get_pos(7,j)]->id=24+j;
        g->board[get_pos(7,j)]->type=types[j];
    }
}


void show_moves(Game* g, Piece* p)
{
    Move_list* atk=init_list();
    Move_list* def=init_list();
    get_moves(g, p, atk, def);
    display_board((Piece**)&g->board, atk, WHITE);
    display_board((Piece**)&g->board, def, WHITE);

}
