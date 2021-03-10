#ifndef INPUT_H
#define INPUT_H

void input(int *x, int *y);
int verif_input_letter(char c);
int verif_input_number(char c);
void is_piece(Game *game, int *x, int *y, Move_list *li);
int target_pos(Game *game, int *x, int *y, int *new_x, int *new_y);

#endif
