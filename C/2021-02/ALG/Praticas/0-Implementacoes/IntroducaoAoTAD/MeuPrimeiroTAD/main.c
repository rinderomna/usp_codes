#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void converter(pilha_t *pilha, int valor) {
	if (valor == 0) {
		return;
	}
	
	push(pilha, (elem) (valor % 2));
	converter(pilha, valor / 2);
}

int main(int argc, char *argv[]) {
	pilha_t *pilha;

    if (argc < 2) {
        printf("Favor, fornecer argumento\n");
        return 1;
    }

	int numero_decimal = atoi(argv[1]);
	
    pilha = create();
	converter(pilha, numero_decimal);

	while (!isEmpty(pilha)) {
		int x;
        pop(pilha, &x);

		printf("%d", x);
	}

	destroy(&pilha);

	printf("\n");

	return 0;
}