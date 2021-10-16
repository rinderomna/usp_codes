#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

struct pilha {
    int topo;
    elem_t *itens;
};

pilha_t *criar_pilha() {
    pilha_t *p = (pilha_t *)malloc(sizeof(pilha_t));

    p->topo = -1;
    p->itens = NULL;

    return p;
}

int get_tamanho_da_pilha(pilha_t *p) {
    return (p->topo + 1);
}

int estaCheia(pilha_t *p) {
    if (p->topo == TamPilhaMax - 1)
        return 1;

    else
        return 0;
}

int estaVazia(pilha_t *p) {
    if (p->topo == -1) {
        return 1;
    } else
        return 0;
}

int push(pilha_t *p, elem_t x) {
    if (estaCheia(p) == 1) {
        return -1;
    }

    int tamanho_da_pilha = get_tamanho_da_pilha(p);

    if (tamanho_da_pilha % BUFFER_SIZE == 0) {
        int novo_tamanho = (tamanho_da_pilha / BUFFER_SIZE + 1) * BUFFER_SIZE;

        p->itens = (elem_t *)realloc(p->itens, novo_tamanho * sizeof(elem_t));
    }

    p->itens[++(p->topo)] = x;

    return 1;
}

int pop(pilha_t *p, elem_t *x) {
    if (estaVazia(p) == 1) {
        return -1;
    }

    *x = p->itens[p->topo];

    p->topo--;

    return 1;
}

int top(pilha_t *p, elem_t *x) {
    if (estaVazia(p) == 1) {
        return -1;
    }

    *x = p->itens[p->topo];

    return 1;
}

void esvaziar_pilha(pilha_t *p) {
    int status_da_retirada = 1;

    do {
        elem_t x;
        status_da_retirada = pop(p, &x);
    } while (status_da_retirada != FAIL);
}

void destruir_pilha(pilha_t **p) {
    if (*p) {
        if ((*p)->itens) {
            free((*p)->itens);
        }

        free(*p);
    }

    *p = NULL;
}