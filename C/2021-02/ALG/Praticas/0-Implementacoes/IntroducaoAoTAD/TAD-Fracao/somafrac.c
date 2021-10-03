#include <stdio.h>
#include "fracao.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 5) {
		printf("Passe 4 números\n");
	
		return 1;
	}
	
	fracao_t *f1, *f2;
	f1 = criar(atoi(argv[1]), atoi(argv[2]));
	f2 = criar(atoi(argv[3]), atoi(argv[4]));

	fracao_t *f3 = somar(f1, f2);

	imprimir(f1);

	printf("+\n");

	imprimir(f2);

	printf("=\n");

	imprimir(f3);

	destruir(&f1);
	destruir(&f2);
	destruir(&f3);

	return 0;
}
