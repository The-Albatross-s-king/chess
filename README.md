# test_chess

Use of the board.c

struct Game contains crucial informations about the party:
the board flatten (64 slots)
2 tabs of all the pieces of each side (blacks and whites)

struct Piece contains informations about a piece:
type, color, alive, position and if it already moved


to move a piece with a check of the possibility use:
int move(Game* g, int x, int y, int x2, int y2)
but if you want to move without check use: (usefull to undo a move)
int apply_move(Game* g, int x, int y, int x2, int y2)

to get all moves possible in a chained-list use:
get_moves(Game* g, int x, int y, int* len);
it returns struct Move_list* sentinel. 

to use and manipulate the list you can use:
pop_list(Move_list* l, int* x, int* y);
it returns in *x and *y the position of the first move, and then removes it.
in_list(Move_list* l, int x, int y);
it returns 1 if the combinaison x,y is the the list.
display_list(Move_list* l);
usefull to debbug.

It is IMPORTANT to avoid memory leaks to use free_list(Move_list* list)
after each get_moves()
