// main.c
// aplicacao para o TAD

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

int main() {
  fila_t *f;
  f = criar();

  for (int i = 0; i < 10; i++) {
    inserir(f, i);
  }

  while (!isEmpty(f)) {
    int x;
    remover(f, &x);
    printf("%d ", x);
  }
  printf("\n");

  destruir(&f);

  return EXIT_SUCCESS;
}
