#include <stdio.h>
#include <stdlib.h>
#include "fracao.h"

fracao_t *criar(int num, int den) {
	if (den == 0) // não pode
		return NULL;

	fracao_t *f = (fracao_t *) malloc(sizeof(fracao_t));
	if (f == NULL)
		return NULL;

	// atribuicoes de valores aos campos do TAD fracao_t
	f->num = num;
	f->den = den;

	return f;
}

void imprimir(fracao_t *f) {
	if (f != NULL) { // so exibe se a fracao existe, se foi criada
		if (f->den == 1)
			printf("%d\n", f->num);
		else
			printf("%d / %d\n", f->num, f->den);
	}
}

void destruir(fracao_t **f) {
	if ((*f) != NULL) {
		free(*f);
		*f = NULL; // importante para tratar erros de novas fracoes possivelmente							// criadas futuramente
	}
}

int mdc(int a, int b) {
	if (b == 0) return a;
  else return mdc(b, a % b);
}

int mmc(int a, int b) {
	return (a * b) / mdc(a, b);
}

void simplificar(fracao_t *f) {
	int fator = mdc(f->num, f->den);

	f->num = f->num / fator;
	f->den = f->den / fator;
}

fracao_t *somar(fracao_t *f1, fracao_t *f2) {
	if (f1 == NULL || f2 == NULL)
		return NULL;

	fracao_t *f = (fracao_t *) malloc(sizeof(fracao_t));
	
	if (f == NULL)
		return NULL;

	f->den = mmc(f1->den, f2->den);
	f->num = (f->den/ f1->den) * f1->num + (f->den / f2->den) * f2->num;

	simplificar(f);

	return f;
}
