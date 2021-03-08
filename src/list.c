#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <board.h>

Move_list* init_list()
{
    Move_list* sentinel=malloc(sizeof(Move_list));
    sentinel->next=NULL;
    sentinel->x=-1;
    return sentinel;
}
void add_list(Move_list* list, int x, int y)
{
    Move_list* new=malloc(sizeof(Move_list));
    new->x=x;
    new->y=y;
    new->next=list->next;
    list->next=new;
}

size_t get_size_list(Move_list* list)
{
    size_t len=0;
    list=list->next;
    while(list!=NULL)
    {
        len++;
        list=list->next;
    }
    return len;
}
// reads list and free the pop, returns 1 if valide 0 otherwise
int pop_list(Move_list* list, int* x, int* y)
{
    if(list->next==NULL)
        return 0;
    *x=list->next->x;
    *y=list->next->y;
    Move_list* tmp=list->next;
    list->next=tmp->next;
    free(tmp);
    return 1;
}
//return 1 if x,y in the list
int in_list(Move_list* list, int x, int y)
{
list=list->next;
while(list!=NULL)
{
    if(list->x==x && list->y==y)
        return 1;
    list=list->next;
}
return 0;
}

int is_empty(Move_list* list)
{
    if(list==NULL)
        errx(3, "is_empty : try to use NULL pointeuri\n");
    return list->next==NULL;
}

void free_list(Move_list* list)
{

Move_list* tmp;
while(list!=NULL)
{
    tmp=list;
    list=list->next;
    free(tmp);
}
}

void display_list(Move_list* l)
{
    printf("coups possibles :\n");
    l=l->next;
    while(l!=NULL)
    {
        printf("%d %c -> ",l->x+1,(char)(l->y+'A'));
        l=l->next;
    }
    printf("NULL\n");
}
