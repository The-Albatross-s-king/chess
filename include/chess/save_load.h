#pragma once

#include "board.h"
#define file_size 64*2

void clear_board(Game* g); 
Piece* put_piece(Game* g, int x, int y , int color, enum pieces_types type);
void load_from_str(Game* g, char* file_content);
int load(Game* g, char* path);
int save(Game* g, char* path);
char *load_path();
