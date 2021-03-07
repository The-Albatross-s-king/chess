#ifndef INPUT_H
#define INPUT_H

void input(int *x, int *y);
int verif_input_letter(char c);
int verif_input_number(char c);
void can_i_go(Game *game, int *x, int *y, Move_list *li, enum pieces_colors c);
int go_to(Game *game, int *x, int *y, int *new_x, int *new_y);

#endif
