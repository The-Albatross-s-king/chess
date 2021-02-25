#ifndef PIECE_H
#define PIECE_H

enum type{
    null,
    pion,
    tour,
    cavalier,
    fou,
    dame,
    roi
};

enum color{
    white,
    black
};

enum has_moved{
    false,
    true
};

typedef struct piece{
    enum type type;
    enum color color;
    enum has_moved hm;
}PIECE;

void display_table(PIECE *table);
void start(PIECE *table);
void move_piece(PIECE *table, int b_x, int b_y, int e_x, int e_y);

#endif
