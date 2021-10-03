#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

struct node {
  int data;
  node_t *next;
};

struct list {
  node_t *start;
  node_t *end;
  int size;
  int max_size;
};

list_t *create_list(int max_size) {
    list_t *l = (list_t *) malloc(sizeof(list_t));

    l->max_size = max_size;

    l->size = 0;
    l->start = NULL;
    l->end = NULL;

    return l;
}

int get_list_size(list_t *list) {
    return list->size;
}

void append_to_list(list_t *l, int number) {
    if (!l) return;

    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->data = number;
    p->next = NULL;
    if (l->size == 0) {
      l->start = p;
    } else {
      l->end->next = p;
    }
    l->end = p;
    l->size++;
}

void access_data(list_t *l, int index, int *number) {
    if (!l) return;

    node_t *cur_node_pointer = l->start;

    for (int i = 0; i < index; i++) {
        cur_node_pointer = cur_node_pointer->next;
    }

    *number = cur_node_pointer->data;
}

void remove_from_list(list_t *l, int index) {
    if (!l) return;

    node_t *prev_node_pointer = NULL;
    node_t *cur_node_pointer = l->start;

    for (int i = 0; i < index; i++) {
        prev_node_pointer = cur_node_pointer;
        cur_node_pointer = cur_node_pointer->next;
    }

    if (prev_node_pointer == NULL) {
        l->start = l->start->next;
        free(cur_node_pointer);
    } else {
        prev_node_pointer->next = cur_node_pointer->next;
        free(cur_node_pointer);    
    }

    l->size--;
}

void destroy_list(list_t **l) {
    node_t *p = (*l)->start;
    while (p) {
        (*l)->start = (*l)->start->next;
        free(p);
        p = (*l)->start;
        (*l)->size--;
    }

    free(*l);

    *l = NULL;
}