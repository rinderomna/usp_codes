#include <stdio.h>
#include <stdlib.h>

#include "generic_linked_list.h"
#include "priority_queue.h"
#include "str.h"

struct elem {
    void *datum;
    int priority;
};

struct p_queue {
    list_t *l;
    int datum_size;
};

p_queue_t *create_priority_queue(int datum_size) {
    p_queue_t *q = (p_queue_t *)malloc(sizeof(p_queue_t));

    q->l = create_list((int)sizeof(elem_t));

    q->datum_size = datum_size;

    return q;
}

int get_priority_queue_size(p_queue_t *q) {
    return get_list_size(q->l);
}

void add_to_priority_queue(p_queue_t *q, void *datum, int priority) {
    elem_t elem;

    elem.priority = priority;
    elem.datum = malloc(q->datum_size);
    copy_memory(elem.datum, datum, q->datum_size);

    int i = get_list_size(q->l);

    elem_t cur_elem;
    cur_elem.priority = 0;

    do {
        i--;
        
        if (i >= 0) {
            access_element(q->l, i, (void *)&cur_elem);
        }
    } while (priority < cur_elem.priority && i >= 0);

    i++;

    insert_in_list(q->l, (void *)&elem, i);
}

void remove_from_priority_queue(p_queue_t *q, void *datum) {
    if (get_list_size(q->l) > 0) {
        elem_t elem;

        access_element(q->l, 0, (void *)&elem);
        copy_memory(datum, elem.datum, q->datum_size);
        free(elem.datum);
        remove_from_list(q->l, 0);
    }
}

void destroy_priority_queue(p_queue_t **q) {
    while (get_list_size((*q)->l) > 0) {
        elem_t cur_elem;

        access_element((*q)->l, 0, (void *)&cur_elem);
        free(cur_elem.datum);
        remove_from_list((*q)->l, 0);
    }

    free((*q)->l);
    free(*q);

    *q = NULL;
}