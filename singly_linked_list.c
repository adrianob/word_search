#include <stdlib.h>
#include <stdio.h>
#include "singly_linked_list.h"

LIST_NODE * initialize(void){
  return NULL;
}

void swap(LIST_NODE **node1, LIST_NODE **node2){
  void *data = (*node2)->data;
  (*node2)->data = (*node1)->data;
  (*node1)->data = data;
}

void sort(LIST_NODE **head_ref, filter filter){
  LIST_NODE *current = (*head_ref);
  int finished = 0;
  while(!finished){
    finished = 1;
    while(current->next){
      if (filter(current->data, current->next->data)) {
        swap(&current, &current->next);
        finished = 0;
      }
      current = current->next;
    }
    current = (*head_ref);
  }
}

void push(LIST_NODE **head_ref, void *element){
  LIST_NODE *node = (LIST_NODE *) malloc(sizeof(LIST_NODE));
  node->data = element;
  node->next = *head_ref;

  *head_ref = node;
}

void append(LIST_NODE **head_ref, void *element){
  LIST_NODE *node = (LIST_NODE *) malloc(sizeof(LIST_NODE));
  LIST_NODE *tail = last_node(*head_ref);
  node->data = element;
  node->next = NULL;

  if (!*head_ref) {
    *head_ref = node;
  }
  else{
    tail->next = node;
  }

}

void for_each(LIST_NODE *head, iterator iterator){
  LIST_NODE *node = head;
  while(node){
    iterator(node->data);
    node = node->next;
  }
}

void for_each_reverse(LIST_NODE *head, iterator iterator){
  LIST_NODE *node = head;
  if(node){
    for_each_reverse(node->next, iterator);
    iterator(node->data);
  }
}

LIST_NODE * last_node(LIST_NODE *head){
  LIST_NODE *node = head;
  if (node) {
    while(node->next){
      node = node->next;
    }
  }
  return node;
}

void destroy(LIST_NODE **head_ref){
  LIST_NODE *current = *head_ref;
  LIST_NODE *next;

  while(current){
    next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
  *head_ref = NULL;
}

void remove_all(LIST_NODE **head_ref, filter filter, void * filter_arg ){
  LIST_NODE *aux = *head_ref;
  LIST_NODE *next;
  LIST_NODE *prev = NULL;
  while(aux){
    next = aux->next;
    if (filter(aux->data, filter_arg)) {//remove
      if (aux == *head_ref) {//first element
        *head_ref = aux->next;
      }
      else {
        prev->next = aux->next;
      }
      free(aux->data);
      free(aux);
      aux = NULL;
    }

    if (aux) {
      prev = aux;
    }
    aux = next;
  }

}

int list_size(LIST_NODE *head){
  unsigned int i = 0;
  LIST_NODE *node = head;
  while(node){
    i++;
    node = node->next;
  }
  return i;
}
