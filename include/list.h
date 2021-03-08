#pragma once

typedef struct Move_list
{
    struct Move_list *next;
    int x;
    int y;
}Move_list;


Move_list* init_list();


size_t get_size_list(Move_list* list);

int is_empty(Move_list* list);

void add_list(Move_list* list, int x, int y);

int pop_list(Move_list* list, int* x, int* y);

int in_list(Move_list* list, int x, int y);

void free_list(Move_list* list);

void display_list(Move_list* l);


