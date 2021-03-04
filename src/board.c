#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include <err.h>

int get_pos(int x, int y)
{
    if(x>8 || y>8)
        errx(3, "Error, out of bound\n");
    return x*8+y;
}

int move(Game* g,int x, int y, int x2, int y2)
{

    piece* p=g->board[get_pos(x,y)];
    if(p==NULL)
        errx(3, "Error, case vide\n");
    int pos=get_pos(x2,y2);
    piece* target=g->board[pos];
    if(target==NULL) //bouge simplement la piece
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
    // 1 : malloc les pieces et mets les pointe communs
    // 2 : set value, et type specifiquement
    //deux premieres lignes
    for(int i=0; i<2; i++)
    {
        for(int j=0;j<8;j++)
        {
            int x=get_pos(i,j);
            g->board[x]=malloc(sizeof(piece));
            g->board[x]->color=BLACK;
            g->board[x]->x=i;
            g->board[x]->y=j;
            g->board[x]->alive=1;
            g->board[x]->moved=0;
            g->blacks[x]=g->board[x];
        }
    }
    //deux dernieres lignes
    for(int i=6; i<8; i++)
    {
        for(int j=0;j<8;j++)
        {
            int x=get_pos(i,j);
            g->board[x]=malloc(sizeof(piece));
            g->board[x]->color=WHITE;
            g->board[x]->x=i;
            g->board[x]->y=j;
            g->board[x]->alive=1;
            g->board[x]->moved=0;
            g->whites[(x+8)%16]=g->board[x];//+8 pour que les pions soit de 8 a 15
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
        g->board[get_pos(7,j)]->type=types[j];
    }


}


void free_game(Game* g)
{
    for(int i = 0; i < 16 ; i++)
    { 
        free(g->blacks[i]);
        free(g->whites[i]);
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
                printf("   x");
            else{
                printf("%3d ",g->board[x]->type);
            }
        }

        printf("\n");
    }
}

// Mean to set the color and starting piece position.
void set_board(piece *board)
{
    memset(board, 0, 64 * sizeof(piece));
    piece p = {ROOK, 1, 0, BLACK, 0, 0};
    board[0] = p;
    board[7] = p;

    p.type = KNIGHT;
    board[1] = p;
    board[6] = p;

    p.type = BISHOP;
    board[2] = p;
    board[5] = p;

    p.type = QUEEN;
    board[3] = p;

    p.type = KING;
    board[4] = p;

    p.type = PAWN;
    for(int i = 0; i < 8; i++)
        board[8 + i] = p;

    p.color = WHITE;
    p.type = ROOK;
    board[56] = p;
    board[63] = p;

    p.type = KNIGHT;
    board[57] = p;
    board[62] = p;

    p.type = BISHOP;
    board[58] = p;
    board[61] = p;

    p.type = QUEEN;
    board[59] = p;

    p.type = KING;
    board[60] = p;

    p.type = PAWN;
    for(int i = 0; i < 8; i++)
        board[48 + i] = p;
}
