#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

struct pilha {
  int topo;
  elem_t *itens;
};

pilha_t *criar_pilha() {
  pilha_t *p = (pilha_t *) malloc(sizeof(pilha_t));

  p->topo = -1;
  p->itens = NULL;

  return p;
}

int get_tamanho_da_pilha(pilha_t *p) {
  return (p->topo + 1);
}

int isFull(pilha_t *p) {

  if (p->topo == TamPilha - 1)
    return 1;

  else
    return 0;
}

int isEmpty(pilha_t *p) {
  if (p->topo == -1) {
    return 1;
  } else
    return 0;
}

int push(pilha_t *p, elem_t x) {

  if (isFull(p) == 1) {
    return -1;
  }

  p->topo++;

  p->itens = (elem_t *) realloc(
    p->itens, 
    (p->topo + 1) * sizeof(elem_t)
  );

  p->itens[p->topo] = x;

  return 1;
}

int pop(pilha_t *p, elem_t *x) {

  if (isEmpty(p) == 1) {
    return -1;
  }
  
  *x = p->itens[p->topo];

  p->topo--;

  p->itens = (elem_t *) realloc(
    p->itens, 
    (p->topo + 1) * sizeof(elem_t)
  );

  return 1;
}

int top(pilha_t *p, elem_t *x) {

  if (isEmpty(p) == 1) {
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