#ifndef PIECE_H
#define PIECE_H

#include "board.h"

unsigned long create_bitboard(Move_list *list);
void display_board(Piece **board, Move_list *list, enum pieces_colors side);

#endif
