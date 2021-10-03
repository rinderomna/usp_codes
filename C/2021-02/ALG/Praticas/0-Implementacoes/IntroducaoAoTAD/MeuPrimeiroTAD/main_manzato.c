// main.c
// o programa empilha 10 elementos de 0 a 9 e os desempilha
// na logica LIFO -> 9 8 7 6... 0

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main() {
	pilha_t *p;

	p = create();

	for (int i = 0; i < 10; i++) {
		push(p, (elem) i);
	}
	
	int x;
// tirar o elemento da lista e imprimi lo
	while (!isEmpty(p)) {
		pop(p, &x);
		printf("%d", x);
	}

    printf("\n");

    destroy(&p);

	return EXIT_SUCCESS;
}