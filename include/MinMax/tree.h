#pragma once


typedef struct Tree
{
    struct Tree* child;
    struct Tree* sibling;
    int score;
    double max;
    int pos;
    int old_pos;
}Tree;

Tree* new_tree();
void set_tree(Tree* t, int old_x, int old_y, int new_x, int new_y);

//free root and all childs at h=1 expect the one with pos==x*8+y
//which is returned
Tree* select_tree(Tree* t, int x, int y);

void free_tree(Tree* t);

//set x,y with the move associated to the best score
void get_max_tree(Tree* t, int* x, int* y);