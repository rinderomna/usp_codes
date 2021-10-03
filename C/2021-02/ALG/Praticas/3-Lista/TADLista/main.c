// main.c

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {
	lista_t *l = cria(); // cria lista
	insere(l, 5); // insere sempre no final da lista
	insere(l, 2);
	insere(l, 3);
	insere(l, 7);
	insere(l, 8);

	imprimir(l); // lista inteira, sem remocao

	inverte(l);  // inverte e imprime
	imprimir(l);
	
	inverte(l);  // desinverte e imprime
	imprimir(l);

	remover(l, 5); // primeiro elemento da lista (caso 1)
	imprimir(l);

	remover(l, 8); // ultimo elemento da lista (caso 2)
	imprimir(l);

	remover(l, 3); // elemento no meio da lista (caso 3)
	imprimir(l);
	
	liberar(l);

	return EXIT_SUCCESS;
}