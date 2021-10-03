// fila.c

#include <stdio.h>
#include <assert.h> // Usar para verificar se o ponteiro eh valido
										// ou seja, != NULL
#include <stdlib.h>
#include "fila.h" // esta na mesma pasta que fila.c por isso 
									// aspas duplas

// Usuario sabe da existencia desse tipo fila_t, mas nao
// sabe sua implementacao, que esta aqui

struct fila {
	int inicio, fim, total;
	// alocacao eh sequencial e estatica
	// usa tamanho de fila definido no .h
	// para a fila generica, trocamos elem por void *
	// pois nao sabemos o tipo de dado, o qual sera convertido
	// pelo compilador depois
	// e isso funciona na memoria porque todo ponteiro
	// ocupa mesmo espaco - 8 bytes nos computadores mais modernos 
	void *itens[TamFila]; // vetor que representa a Fila de itens
};

fila_t *criar() {
	// ponteiro para a fila, alocada dinamicamente
	fila_t *f;
	f = (fila_t *) malloc(sizeof(fila_t));
	assert(f != NULL);
	// inicializando campos para a fila no comeco
	f->total = 0; // sem elementos na fila
	f->inicio = 0; // elemento no inicio da fila
	f->fim = 0; // proximo elemento sera adicionado ao primeiro indice

	// o vetor itens ja foi alocado estaticamente
	return f; // para fora da funcao
}

int isEmpty(fila_t *f) {
	assert(f != NULL); // se for NULL e tentarmos acessa lo
										// dara segfault qdo acessarmos os campos,
										// inexistentes na estrutura nesta condicao

	if (f->total == 0) {
		return 1; // pois a fila esta vazia se nao ha elementos nela
	}
	
	// caso contrario
	return 0;
}

int isFull(fila_t *f) {
	assert(f != NULL); // A fila existe?

	if (f->total == TamFila) { // a qtd de elementos corresponde
														// a qtd total suportada na fila
		return 1;
	}
	
	return 0; // fila nao esta cheia
}

// incluir um elemento na fila
// passar o endereco do nosso TADFila
// retornar inteiro para dizer que a insercao foi feita com
// sucesso ou nao
int inserir(fila_t *f, void *x) {
	// verificar se a fila nao esta cheia
	if(isFull(f)) {
		return 0; // nao consigo adicionar um novo elemento
							// tratar esse 'erro'/condicao
	}
	// se nao deu o return, consegue inserir outro elemento

	// x atribuido ao vetor da fila. Nesse caso, o prof. fez a copia dos
	// elementos para dentro da fila.
	// aqui, armazenaremos a referencia pro elemento a inserir, o que
	// facilita o gerenciamento do dado. 
	f->itens[f->fim] = x;
	f->fim = (f->fim + 1) % TamFila; // fila circular
	/* Poder-se-ia fazer assim
	 * 	f->fim++;
	 *	f->fim %= TamFila;
	 */
	f->total++;
	
	// elemento inserido na fila com sucesso
	return 1;
}

// passar o elemento por referencia, pois ele sera alterado
// dentro desta funcao - tiraremos um elemento da fila
// x recebe o elemento a ser removido da fila
// assim como ocorreu com a pilha
// void ** porque vamos alterar a referencia do elemento x
int remover(fila_t *f, void **x) {
	// verificar se a fila nao esta vazia
	// se esta vazia, nao tem como remover
	if (isEmpty(f)) {
		return 0;
	}
	// armazenar no conteudo do endereco passado.
	//passamos a referencia com void **x
	// ao fazer *x, 'cancela' e fica tipo void *, que eh o valor
	// do elemento generico
	*x = f->itens[f->inicio];
	f->inicio = (f->inicio + 1) % TamFila; 
	/* Poder-se-ia fazer assim
	 * 	f->inicio++;
	 *	f->inicio %= TamFila;
	 */

	f->total--;

	// deu tudo certo
	return 1;
}

// desalocar memoria dinamicamente alocada
// so a fila foi alocada manualmente
// se tivessemos alocado o vetor itens dinamicamente, teriamos
// que desaloca lo antes da fila
void destruir(fila_t **f) { // mandar o endereco da estrutura fila
	if (*f != NULL) { // se a estrutura fila existir, libere
		free(*f);
	}

	*f = NULL; // seu ponteiro (na Stack) 
					// deve apontar para algo invalido agora
}