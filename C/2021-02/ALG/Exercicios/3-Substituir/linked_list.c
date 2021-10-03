#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

struct node {
    elem_t datum;
    node_t *next;
};

struct list {
    node_t *start;
    node_t *end;
    int size;
};

list_t *create_list() {
    list_t *l = (list_t *)malloc(sizeof(list_t));

    l->size = 0;
    l->start = NULL;
    l->end = NULL;

    return l;
}

int get_list_size(list_t *l) {
    return l->size;
}

void append_to_list(list_t *l, elem_t elem) {
    if (!l) return;

    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->datum = elem;
    p->next = NULL;
    if (l->size == 0) {
        l->start = p;
    } else {
        l->end->next = p;
    }
    l->end = p;
    l->size++;
}

void insert_in_list(list_t *l, elem_t elem, int index) {
    if (!l) return;

    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->datum = elem;
    p->next = NULL;

    node_t *prev_node_pointer = NULL;
    node_t *curr_node_pointer = l->start;

    for (int i = 0; i < index; i++) {
        prev_node_pointer = curr_node_pointer;
        curr_node_pointer = curr_node_pointer->next;
    }

    if (prev_node_pointer) {
        prev_node_pointer->next = p;
    } else {
        l->start = p;
    }
    p->next = curr_node_pointer;

    if (curr_node_pointer == NULL) {
        l->end = p;
    }

    l->size++;
}

void access_datum(list_t *l, int index, elem_t *elem) {
    if (!l) return;

    node_t *curr_node_pointer = l->start;

    for (int i = 0; i < index; i++) {
        curr_node_pointer = curr_node_pointer->next;
    }

    *elem = curr_node_pointer->datum;
}

void remove_from_list(list_t *l, int index) {
    if (!l) return;

    node_t *prev_node_pointer = NULL;
    node_t *curr_node_pointer = l->start;

    for (int i = 0; i < index; i++) {
        prev_node_pointer = curr_node_pointer;
        curr_node_pointer = curr_node_pointer->next;
    }

    if (prev_node_pointer == NULL) {
        l->start = l->start->next;
        free(curr_node_pointer);
    } else {
        prev_node_pointer->next = curr_node_pointer->next;
        free(curr_node_pointer);
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