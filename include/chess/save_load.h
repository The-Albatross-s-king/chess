#pragma once

#include "board.h"
void clear_board(Game* g); 
Piece* put_piece(Game* g, int x, int y , int color, enum pieces_types type);
int load_from_str(Game* g, char* file_content);
int load(Game* g, char* path);
int save(Game* g, char* path);
