#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void init_list(List *list) {
  *list = NULL;
}

void prepend_list(List *list, int data) { 
  Item *new_item;

  new_item = (Item *)malloc(sizeof(Item));
  new_item->next = *list;
  new_item->data = data;
  *list = new_item;
}

void append_list(List *list, int data) {
  Item *new_item;
  Item *last;

  new_item = (Item *)malloc(sizeof(Item));
  assert(new_item);
  new_item->next = NULL;
  new_item->data = data;

  if (*list == NULL) {
    *list = new_item;
  }
  else {
    for (last = *list; last->next != NULL;
                             last = last->next) 
      ;
    last->next = new_item;
  }
}

void delete_list(List* list, int data){
  Item* item = *list;
  if(item->data == data){
    *list = item->next;
    free(item);  
  }else{
    Item* previous;
    Item* current = *list;
    int found = 0;
    while(!found){
      previous = current; 
      current = current->next;
      found = current != NULL && current->data == data;
    }
    if(current != NULL){
      if(current->next == NULL){
        previous->next = NULL;
        free(current);
      }else{
        previous->next = current->next;
        free(current);
      }
    }
  }
}

void clear_list(List *list) {
  if (*list != NULL) {
    clear_list(&(*list)->next);
    free(*list);
    *list = NULL;
  }
}


void print_list(List list) {
  Item *i;
  for (i = list; i != NULL; i = i->next) {
    printf("%d ", i->data);
    fflush(stdout);
  }
  printf("\n");
}

