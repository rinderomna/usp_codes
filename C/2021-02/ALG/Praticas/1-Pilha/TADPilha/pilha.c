// pilha.c

#include "pilha.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

struct pilha {
    int topo;
    elem_t *itens;
};

pilha_t *create() {
    pilha_t *p = (pilha_t *)malloc(sizeof(pilha_t));
    assert(p != NULL);

    p->topo = -1;
    p->itens = (elem_t *)malloc(BUFFER_SIZE * sizeof(elem_t));

    return p;
}

int get_stack_size(pilha_t *p) {
    return p->topo + 1;
}

void destroy(pilha_t **p) {
    if (*p) {
        if ((*p)->itens) {
            free((*p)->itens);
        }

        free(*p);
    }

    *p = NULL;
}

int isFull(pilha_t *p) {
    assert(p != NULL);

    if (p->topo == TamPilha - 1)
        return 1;

    else
        return 0;
}

int isEmpty(pilha_t *p) {
    assert(p != NULL);
    if (p->topo == -1) {
        return 1;
    } else
        return 0;
}

int push(pilha_t *p, elem_t x) {
    assert(p != NULL);

    if (isFull(p) == 1) {
        return -1;
    }

    int stack_size = get_stack_size(p);

    if (stack_size % BUFFER_SIZE == 0) {
        int new_size = ((stack_size / BUFFER_SIZE) + 1) * BUFFER_SIZE;

        p->itens = (elem_t *)realloc(
            p->itens,
            (new_size) * sizeof(elem_t));
    }

    p->topo++;

    p->itens[p->topo] = x;

    return 1;
}

int pop(pilha_t *p, elem_t *x) {
    assert(p != NULL);

    if (isEmpty(p) == 1) {
        return -1;
    }

    *x = p->itens[p->topo--];

    return 1;
}

int top(pilha_t *p, elem_t *x) {
    assert(p != NULL);

    if (isEmpty(p) == 1) {
        return -1;
    }

    *x = p->itens[p->topo];

    return 1;
}