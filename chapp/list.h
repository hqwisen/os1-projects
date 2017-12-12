#ifndef __LIST_H
#define __LIST_H

typedef struct ITEM {
  struct ITEM *next;
  int data;
} Item;

typedef Item *List;

void init_list(List *l);
void prepend_list(List* list, int data);
void append_list(List* list, int data);
void delete_list(List* list, int data);
void clear_list(List* list);
void print_list(List list);

#endif
