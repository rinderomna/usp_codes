// lista.c
#include "lista.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct no no_t;

struct no { // estrutura no, para armazenar cada elemento
	elem info; // campos de info e prox no
	no_t *prox;
};
struct lista { // estrutura lista
	no_t *ini, *fim; // campos inicio e fim [ponteiros]
	int tam; // tamanho total da lista; numero de elementos ali
					// armazenados no momento
};

// nao criamos na struct lista o ponteiro p, que percorre cada elemento
// presente. Ele sera criado dentro das funcoes
// caso precisemos percorrer a lista com um ponteiro p para cada no
// que a compoe, criamos ele na hora que necessitamos

// temos duas estruturas: a de no, para cada no 
// e da lista, que sera uma estrutura so - uma so lista com um inicio
// e um fim
// funcoes insere e retira elementos
// elementos serao armazenados de maneira encadeada na memoria

lista_t *cria() { // retorna ponteiro para lista
	// criar ponteiro para lista
	lista_t *l = (lista_t *) malloc(sizeof(lista_t)); // aloca espaco
															// para a lista vazia
	assert(l); // alocacao deu certo, l != NULL
	
	// para a lista recem criada, vazia,
	// ponteiros inicializados com NULL
	l->ini = NULL;
	l->fim = NULL;
	l->tam = 0;

	return l;
}

// liberar lista ja criada, quando nao precisamos mais dela
// precisa percorrer todos os elementos da lista, desalocando
// cada um separadamente
void liberar(lista_t *l) {
	// so liberar se a lista existir 
	if (l) { // same as l != NULL; lista existe 
		no_t *p = l->ini; // vamos liberar do comeco para o fim
											// pegar o no inicial; primeiro elemento da lista
		while (p) { // same as p != NULL
			l->ini = p->prox; // mudar o inicio da lista para liberar o elemento
												// anterior
			free(p); // liberar o elemento
			p = l->ini; // mudar o inicio
		}
		// depois de liberar elemento por elemento e nao haver mais
		// nos na lista, podemos libera la, liberando ponteiros de ini
		// e fim, mais o tamanho da lista, que eh um int.

		// enfim, liberar a estrutura lista.
		free(l);
	}

}

// insere elemento x na lista. O elemento pode ser repetido e ser
// adicionado a lista
// inserir no final da lista
void insere(lista_t *l, elem x) {
	assert(l); // lista existe

	// isso para nao adicionar elementos repetidos e facilitar a
	// funcao remover elemento paara o nosso caso.
	// isso ignora a funcao insere().
	// impoe regra que somente elementos distintos estarao armazenados
	// na lista.
	if (esta_na_lista(l, x) == 1) {
		return;
	}
	
	// alocar o no que recebe o elemento x
	no_t *p = (no_t *) malloc(sizeof(no_t));
	
	p->info = x; // ja que x eh o elemento a adicionar na lista
	p->prox = NULL; // pois esta no fim da lista, nao tem prox ainda


	// dois casos para a lista
	// 1. lista vazia
	if (!l->ini) { // same as l->ini == NULL
		// isso significa que tanto ini como fim apontam para NULL
		// entao, ambos devem apontar para p, que agora existe na lista
		// como elemento unico
		l->ini = p;
		//l->fim = p;
	}
	// 2. lista com pelo menos um elemento
	else {
		// o p deve ser inserido no final da lista
		//l->fim->prox deve apontar para p
		l->fim->prox = p;
		//l->fim deve apontar para p (inserido agora no fim da lista)
		//l->fim = p
	}

	// comando repetido, pode tirar da condicional
	l->fim = p;

	// incrementar o tamanho da lista
	l->tam++;
}

// tamanho da lista
int tamanho(lista_t *l) {
	assert(l);

	return l->tam;
}

// exibir infos da lista na tela
void imprimir(lista_t *l) {
	assert(l);

	// basta percorrer a lista
	no_t *p = l->ini;

	while (p) {
		printf("%d", p->info);
		p = p->prox; // imprime o proximo no, seguindo logica da lista
								// encadeada
	}
	// podemos alterar o p como quisermos; este no percorre a lista.
	// nao podemos alterar a variavel ini para nao perdermos referencia
	// para o inicio da lista.
	// so mexemos com ela na f. liberar()
	printf("\n");
}

// funcao de busca por elemento x na lista
// retorno true se esta na lista e false se nao esta
int esta_na_lista(lista_t *l, elem x) {
	assert(l);

	no_t *p = l->ini; // comecar a busca pelo no inicial da lista,
										// ou seja, pelo primeiro elem
	while (p) { // enquanto existirem nos na lista, verifique o elem
		if (p->info == x) {
			return 1; // TRUE - elem esta na lista
		}
		// senao, procure prox. elemento ate encontrar elemento
		// ou a lista acabar
		p = p->prox;
	}

	return 0; // FALSE - elemento nao existe na lista, ja percorrida
}

// funcao REMOVER da lista - a mais dificil
// para a implementacao ficar mais facil, so vamos INSERIR
// na lista elementos que nao sao repetidos [impor essa restricao
// na lista]
// nao insere elemento se ele ja tiver sido inserido

// isso para evitar que remova mais de um elemento na mesma chamada.
// Assim, se a funcao encontrar o x, eh so ele que precisa remover
// depois, podemos estender a funcao para remover mais de um elemento,
// quando ha repeticao
int remover(lista_t *l, elem x) {
	assert(l);
	// ponteiro auxiliar, guardando o no anterior ao percorrido
	// por p
	no_t *ant = NULL;


	// primeiro, encontrar o elemento que desejamos remover.
	no_t *p = l->ini;
	while (p) { // enquanto houver nos, busque o elemento x na lista
		if (p->info == x) { // elemento encontrado
			// entao, remova
			// aqui, temos a situacao em que p aponta para o elemento
			// a remover e o ant aponta para o elemento imediatamente 
			// anterior aquele a ser removido.

			// temos, aqui, 3 casos.
			// 1o caso: remover do inicio.
			if (!ant) { // same as ant == NULL // poderia checar p == l->ini
				// a condicional acima garante que esta no inicio da lista,
				// pois nao ha elemento anterior.
				//  lembrando que p aponta para o elemento que quero remover
				
				l->ini = p->prox; // mudar o inicio
				free(p); // remover elemento atual da lista
			}
			// 2o caso: remover do fim
			else if (p == l->fim) { // quando eh o no final
				l->fim = ant; // trocar o fim
				l->fim->prox = NULL; // acabou a lista
				free(p);
			}
			// 3o caso: remover do meio
			else {
				ant->prox = p->prox;
				free(p);
			}
			// o 4o caso nao precisa ser tratado aqui, pois
			// nao entra no primeiro if de elemento encontrado.
			// se desejamos remover um elemento inexistente, essa f.
			// so ignora isso.
			
			// todos esses 3 casos fazem a lista diminuir,
			// entao, 
			l->tam--;
			return 1; // encontrou e removeu elemento com sucesso

		}
		else { // senao,
			ant = p; // guardar o no anterior
			p = p->prox; // procure o proximo
		}
	}
	return 0; // nao encontrou elemento
}

void inverte(lista_t *l) {
	no_t *p, *prev;

	do {
		prev = NULL;
		p = l->ini;

		while (p->prox) {
			prev = p;
			p = p->prox;
		}

		if (prev) {
			p->prox = prev;
			prev->prox = NULL;
		}
	} while (prev);

	p = l->fim;
	l->fim = l->ini;
	l->ini = p;
}