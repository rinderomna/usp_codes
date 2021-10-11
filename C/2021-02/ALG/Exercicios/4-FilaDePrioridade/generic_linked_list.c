#include <stdio.h>
#include <stdlib.h>

#include "generic_linked_list.h"

struct node {
    void *elem;
    node_t *next;
};

struct list {
    node_t *start;
    node_t *end;
    int size;
    int elem_size;
};

void *copy_memory(void *dest, void *src, size_t n_bytes) {
    char *d = (char *)dest;
    char *s = (char *)src;

    for (int i = 0; i < (int)n_bytes; i++) {
        d[i] = s[i];
    }

    return dest;
}

list_t *create_list(int elem_size) {
    list_t *l = (list_t *)malloc(sizeof(list_t));

    l->size = 0;
    l->start = NULL;
    l->end = NULL;
    l->elem_size = elem_size;

    return l;
}

int get_list_size(list_t *l) {
    return l->size;
}

void append_to_list(list_t *l, void *elem) {
    if (!l) return;

    node_t *p = (node_t *)malloc(sizeof(node_t));

    p->elem = malloc(l->elem_size);
    copy_memory(p->elem, elem, l->elem_size);

    p->next = NULL;
    if (l->size == 0) {
        l->start = p;
    } else {
        l->end->next = p;
    }

    l->end = p;
    l->size++;
}

void insert_in_list(list_t *l, void *elem, int index) {
    if (!l) return;

    node_t *p = (node_t *)malloc(sizeof(node_t));

    p->elem = malloc(l->elem_size);
    copy_memory(p->elem, elem, l->elem_size);
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

    if (!curr_node_pointer) {
        l->end = p;
    }

    l->size++;
}

void access_element(list_t *l, int index, void *elem) {
    if (!l) return;

    node_t *curr_node_pointer = l->start;

    for (int i = 0; i < index; i++) {
        curr_node_pointer = curr_node_pointer->next;
    }

    copy_memory(elem, curr_node_pointer->elem, l->elem_size);
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
    } else {
        if (!curr_node_pointer->next) {
            l->end = prev_node_pointer;
        }
        prev_node_pointer->next = curr_node_pointer->next;
    }

    free(curr_node_pointer->elem);
    free(curr_node_pointer);

    l->size--;
}

void invert_list(list_t *l) {
    node_t *p, *prev;

    do {
        prev = NULL;
        p = l->start;

        while (p->next) {
            prev = p;
            p = p->next;
        }

        if (prev) {
            p->next = prev;
            prev->next = NULL;
        }
    } while (prev);

    p = l->end;
    l->end = l->start;
    l->start = p;
}

void right_rotate_list(list_t *l, int n) {
    int last_index = get_list_size(l) - 1;
    void *datum = malloc(l->elem_size);

    for (int i = 0; i < n; i++) {
        access_element(l, last_index, datum);
        remove_from_list(l, last_index);
        insert_in_list(l, datum, 0);
    }

    free(datum);
}

void destroy_list(list_t **l) {
    node_t *p = (*l)->start;
    
    while (p) {
        (*l)->start = (*l)->start->next;
        free(p->elem);
        free(p);
        p = (*l)->start;
        (*l)->size--;
    }

    free(*l);

    *l = NULL;
}
