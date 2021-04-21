#include "tree.h"
#include "board.h"
#include <stdlib.h>
#include <err.h>

Tree* select_tree(Tree *t, int pos, int old_pos)
{
    if (t == NULL)
        err(3, "Tree is NULL");
  
    
    Tree *tmp = t;
    t = t->child;
    free(t);
    
    while (t != NULL && t->pos != pos && t->old_pos != old_pos)
    {
        tmp = t;
        t = t->sibling;
        free_tree(tmp);
    }

    while (tmp!=NULL)
    {
        t->sibling=tmp->sibling;
        free_tree(tmp);
        tmp = t->sibling;
    }
    if (t == NULL)
        err(3, "pos does not exit");
    
    return t;
}

Tree* new_tree(void)
{
    Tree* t=malloc(sizeof(Tree));
    if(t==NULL)
        errx(3,"Can't free a new tree");
    
    t->child=NULL;
    t->sibling=NULL;
    return t;
}
void set_tree(Tree* t, int old_x, int old_y, int new_x, int new_y)
{
    if(t==NULL)
        errx(3, "set_tree can't use NULL pointer");
    
    t->pos=new_x*8+new_y;
    t->old_pos=old_x*8+old_y;
}

void free_tree(Tree* t)
{
    if(t==NULL)
        return;

    for(Tree* tmp=t->child; tmp!=NULL; tmp=tmp->sibling)
        free_tree(tmp);
    free(t);
}

void get_max_tree(Tree *t, int *x, int *y)
{
    if (t == NULL)
        err(3, "Tree is NULL");
    
    if (t->child == NULL)
        err(3, "Tree has no child");

    t = t->child;
    
    int score = t->score;
    *x = t->pos / 8;
    *y = t->pos % 8;
    
    t = t->sibling;
    while (t != NULL)
    {
        if (t->score > score)
        {
            *x = t->pos / 8;
            *y = t->pos % 8;
            score = t->score;
        }
    }
}