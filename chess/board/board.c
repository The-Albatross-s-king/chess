#include <stdio.h>
#include <stdlib.h>


const int BLACK=0;
const int WHITE=1;

const int PAWN=1;
const int ROOK=2;
const int KNIGHT=3;
const int BISH=4; //bishop -> fou
const int QUEEN=5;
const int KING=6;


typedef struct Piece
{
int type;
int alive;
int value;
int color;
int pos[2];
}Piece;



int GetPos(int x, int y)
{
	return x*8+y;
}

int Move(Piece* board[64],Piece* p, int x, int y)
{
int pos=GetPos(x,y);
Piece* target=board[pos];
if(target==NULL) //bouge simplement la piece
{
	board[pos]=p;
	board[GetPos(p->pos[0],p->pos[1])]=NULL; //old place empty
	p->pos[0]=x;
	p->pos[1]=y;
	return 0;
}
target->alive=0;
board[GetPos(p->pos[0],p->pos[1])]=NULL; //old place empty
p->pos[0]=x;
p->pos[1]=y;

board[pos]=p;
return target->value;
}


void SetPieces(Piece* board[64], Piece* blacks[16], Piece* whites[16])
{
	// 1 : malloc les pieces et mets les pointe communs
	// 2 : set value, et type specifiquement
	//deux premieres lignes
	for(int i=0; i<2; i++)
	{
		for(int j=0;j<8;j++)
		{
			int x=GetPos(i,j);
			board[x]=malloc(sizeof(Piece));
			board[x]->color=BLACK;
			board[x]->pos[0]=i;
			board[x]->pos[1]=j;
			board[x]->alive=1;
			blacks[x]=board[x];
		}
	}
	//deux dernieres lignes
	for(int i=6; i<8; i++)
	{
		for(int j=0;j<8;j++)
		{
			int x=GetPos(i,j);
			board[x]=malloc(sizeof(Piece));
			board[x]->color=WHITE;
			board[x]->pos[0]=i;
			board[x]->pos[1]=j;
			board[x]->alive=1;
			whites[(x+8)%16]=board[x];//+8 pour que les pions soit de 8 a 15
		}
	}

	int types[8]={ROOK,KNIGHT,BISH, KING, QUEEN, BISH, KNIGHT, ROOK};
	int values[8]={500,300,300,0,900,300,300,500};
	for(int j=0;j<8;j++)
	{
		board[GetPos(0,j)]->value=values[j];
		board[GetPos(0,j)]->type=types[j];

	}
	for(int j=0;j<8;j++)
	{
		board[GetPos(1,j)]->value=100;
	}
	for(int j=0;j<8;j++)
	{
		board[GetPos(6,j)]->value=100;
	}
	for(int j=0;j<8;j++)
	{
		board[GetPos(7,j)]->value=values[j];
		board[GetPos(0,j)]->type=types[j];
	}


}


void Display(Piece* b[64])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0; j<8;j++)
		{
			int x=GetPos(i,j);
			if(b[x]==NULL)
				printf("0   ");
			else{
			printf("%3d ",b[x]->type);
			}
		}

		printf("\n");
	}

}


int main()
{
Piece* board[64]; //le plateau
Piece* blacks[16]; //toutes les pieces noires dans l'ordre de debut de partie
Piece* whites[16]; //same
for(int i=0; i<64; i++)
	board[i]=NULL; //init a 0 toutes les pieces
SetPieces(board, blacks, whites); //remplit le plateau de pieces

printf("value : %d\n",Move(board,board[GetPos(0,4)],6,4));
Display(board); //fonction temporaire pour debugger
printf("\n");

printf("value : %d\n",Move(board,board[GetPos(6,4)],4,4));
Display(board);

//check les pieces
for(int i=0; i<16; i++)
	printf("%d ",whites[i]->value);
printf("\n");
}
