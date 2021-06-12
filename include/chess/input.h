#ifndef INPUT_H
#define INPUT_H

void input(Game *game ,int *x, int *y, int cur_color, int online);
int verif_input_letter(char c);
int verif_input_number(char c);
void can_i_go(Game *game, int *x, int *y, Move_list **li, enum pieces_colors c, int online);
int go_to(Game *game, Move_list *l, int *x, int *y, int *new_x, int *new_y);

#endif
