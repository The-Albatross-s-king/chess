#include "tree.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

Tree* select_tree(Tree *t, int pos, int old_pos)
{
    if (t == NULL)
        err(3, "Tree is NULL");
  
    
    Tree *tmp = t;
    t = t->child;
    
    while (t != NULL && t->pos != pos && t->old_pos != old_pos)
    {
        tmp = t;
        t = t->sibling;
        free_tree(tmp);
    }

    tmp = t->sibling;

    while (tmp!=NULL)
    {
        t->sibling=tmp->sibling;
        free_tree(tmp);
        tmp = t->sibling;
    }
    if (t == NULL)
        err(3, "the move (old_pos->pos) does not exit");
    
    return t;
}

Tree* new_tree(void)
{
    Tree* t=malloc(sizeof(Tree));
    if(t==NULL)
        errx(3,"Can't free a new tree");
    t->score=0;
    t->max=0;
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

    Tree *tmp = t->child;
    Tree *tmp2;

    while (tmp != NULL)
    {
        tmp2 = tmp->sibling;
        free_tree(tmp);
        tmp = tmp2;
    }

    free(t);

}

void get_max_tree(Tree *t, int *pos, int *old_pos)
{
    if (t == NULL)
        err(3, "Tree is NULL");
    
    if (t->child == NULL)
        err(3, "Tree has no child");

    t = t->child;
    
    double score = t->max;
    *old_pos= t->old_pos;
    *pos= t->pos;
    
    t = t->sibling;
    while (t != NULL)
    {
        //printf("%d ->", t->max);
        if (t->max > score)
        {
            *old_pos = t->old_pos;
            *pos = t->pos;
            score = t->max;
        }
        t=t->sibling;
    }
    printf("\n");
}