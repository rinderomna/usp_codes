// main.c

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// elemento a inserir na pilha - aplicacao do usuario
// usuario quer guardar pontos na pilha
typedef struct ponto {
	int x, y;
} ponto_t;

int main() {
	pilha_t *p;

  // criando a pilha considerando o tamanho dos elementos
	p = create(sizeof(ponto_t));

	ponto_t ponto;
	for (int i = 0; i < 10; i++) {
		ponto.x = i;
		ponto.y = -i;
		push(p, &ponto); // passa o endereco porque a variavel criada
	// nao eh ponteiro, eh normal
	}

	while (!isEmpty(p)) {
	// usar variavel ponto para retornar valor, porque
	// ponto ja tem espaco alocado para ela, entao podemos usar
		pop(p, &ponto);
		printf("(%d, %d) ", ponto.x, ponto.y);
	}

	destroy(&p);

	return EXIT_SUCCESS;
}