// pilha.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> // para usar memcpy
#include "pilha.h"   

struct pilha {
	int topo;
	void **itens; // aloc. dinamica
	// podia fazer void *itens[TamPilha]

	// passar tb o tamanho de cada elemento, que pode ser 
	// variavel, como uma estrutura contendo varios campos
	// por isso, precisamos armazenar o tamanho de cada elemento
	int tamElem;
};

pilha_t *create(int tamElem) {
	// alocar a struct pilha e seus campos (topo, itens, tamElem)
	// com essa alocacao, aloca so o ponteiro 
	// nao esta alocando o tamanho, o vetor, de fato, da estrutura
	// ou seja, o **itens
	pilha_t *p = (pilha_t *) malloc(sizeof(pilha_t));
	assert(p != NULL);
	
	// usando aloc. dinamica e sequencial
	// malloc() do vetor
	// criamos uma alocacao dinamica, com variacoes no tamanho
	
	// precisa ainda fazer alocacao de **itens
	// uma lista de itens - os elementos armazenados
	// podem, assim, ser de tamanho variado
	p->itens = (void **) malloc(sizeof(void *) * TamPilha);
	assert(p->itens != NULL);
	// nao precisaria disso se deixasse void *itens[TamPilha]
	// como fizemos alocaçao dinamica do vetor, precisou disso


	// topo - variavel de indice do ultimo elemento inserido ->
	// se a pilha esta vazia, a variavel topo nao pode ser 0 (indice 0
	// primeira posicao... indice 1 segunda posicao...), entao 
	// a definimos como -1 para indicar que nao ha nada na pilha

	// acesso a variavel topo, que eh um campo da pilha p,
	// p eh uma variavel ponteiro 
	// assim, acessamos seus campos dessa forma:
	p->topo = -1; // inicializacao do topo inexistente
	// -> ja acessa e traduz simultaneamente
	// poderia escrever (*p).topo -> primeiro traduz, depois acessa campo

	// inicializar tamanho do elemento
	// armazenar os tamanhos dos elementos q estao dentro da pilha
	p->tamElem = tamElem;

	return p;
}

// destruir pilha previamente criada, desalocando
// a funcao recebe ponteiro para a pilha que o usuario cria,
// para que possa desalocar aquele endereco

// desalocar a pilha em si, nao so a estrutura, mas 
// tambem seu conteudo
// antes de desalocar a pilha, precisa desalocar seu conteudo
// ou seja, seu campo void **itens - que foi alocado dinamicamente

void destroy(pilha_t **p) { // endereco efetivo da pilha
// desalocar o vetor de ponteiros
// cada ponteiro pode estar apontando para um espaco de memoria 
// que foi criado tambem com aloc dinamica
// antes de fazer essa desalocacao, precisa desalocar elemento por 
// elemento, pois p->itens eh um vetor de void*
// void * eh um ponteiro que aponta para um espaco de memoria
// que pode estar alocado dinamicamente (precisa ser desalocado)
 
// esse while so sera chamado caso o usuario queira fazer destroy
// com elementos na pilha
// se ocorrer destroy com a pilha vazia, nao faz o while
while ((*p)->topo >= 0) {
   free((*p)->itens[(*p)->topo]);	
	 (*p)->topo--;
 }
// 1 desaloc. o cod acima desaloca cada posicao apontada por void *

// 2 desaloc. desaloca o vetor de void*
 if ((*p)->itens != NULL) {
	 free((*p)->itens);
 }
 if (*p != NULL) { // traduz **p -> *(**p) = *p - o valor de **p eh *p, que tb eh um 
// endereco, mas para os elementos da pilha, que sao inteiros
// se esse endereco for != NULL, eh pq tem coisas armazenadas na pilha. Precisamos
// liberar esses inteiros em seus enderecos, e eles alocados na Heap (dinamicamente)
		
// 3 desaloc. desalocar a estrutura pilha
	free(*p);
	}

// o endereco *p continua na Stack. Atribuir NULL a ele para dizer que a pilha
// esta vazia e desalocada e nao precisa de destroy
	*p = NULL;
}

// funcao para verificar se a pilha esta cheia ou vazia
// retornar 1 se a pilha estiver cheia e 0 se nao estiver
int isFull(pilha_t *p) {
	// se p for nulo, encerra a funcao. Isso substitui um if
	assert(p != NULL);
	// tamanho da pilha eh o tamanho do vetor, mas o index comeca em zero
	// verificar valor da variavel topo
	if (p->topo == TamPilha - 1) 
		return 1; 

	else
		return 0;
}

// verificar se a pilha esta vazia
int isEmpty(pilha_t *p) {
	// certificar se a condicao eh verdadeira para prosseguir com a rotina
	// leia-se: CERTIFIQUE-SE/ASSEGURE-SE de que tal coisa ocorre para
	// continuar a execucao
	assert(p != NULL);
	if (p->topo == -1) {
		return 1;
	}
	else
		return 0;
}

// para inserir elementos na pilha
// o elemento inserido nao eh mais elem, 
// mas um void *
int push(pilha_t *p, void *x) {
	// assegurar-se de q a pilha p esta alocada
	assert(p != NULL);

// se a pilha estiver cheia, nao da para inserir um elemento nela
	if(isFull(p) == 1) {
		return -1; // codigo de erro 
// lembrando que o TAD abstrai as coisas para o usuario. Definir
// como tratamento de erro com codigo -1 um erro durante a insercao
// de elemento - assim, o usuario consegue tratar na aplicacao
	}
	
	// se a pilha nao estiver cheia, adicione o elemento
	//1. incremente o topo
	p->topo++;

	// armazenar o valor novo
	// nao pode mais fazer como estava anteriormente, ou seja, 
	// p->itens[p->topo] = x;
	// se fizermos assim, estamos copiando o endereco de memoria
	// alocado fora dessa funcao. Pode ser que o usuario altere
	// o espaco de memoria fora dessa funcao, entao faz-se necessario
	// que facamos uma copia do elemento criado pelo usuario fora 
	// para que nao dependamos do usuario

	// o usuario pode ja ter feito alocacao do elemento que deseja inserir,
	// em um processo externo a esta funcao
	// se ele alterar o conteudo, isso interfere o elemento inserido na 
	// pilha
	// inserindo um valor numa lista e alterando o valor fora da lista,
	// isso afeta a lista
	// podemos fazer uma copia do conteudo inteiro

	// fazer alocacao do ponteiro para void (void *)
	// a qtd de memoria alocada para esse ponteiro sera tamElem, um campo
	// da struct pilha
	// tamElem = tamanho do elemento em si armazenado
	p->itens[p->topo] = (void *) malloc(p->tamElem);
	assert(p->itens[p->topo] != NULL);

	// copia de memoria com memcpy
	// manda para o endereco p->itens[p->topo] o segundo argumento
	// que eh o x, com uma determinada qtd de bytes, que eh p->tamElem

	// isso copia o conteudo de x, que veio de fora dessa funcao, 
	// para dentro do ponteiro p->itens[p->topo], que precisa 
	// da alocacao inicial p->itens[p->topo] = (void *) malloc(p->tamElem);
	// feita acima
	memcpy(p->itens[p->topo], x, p->tamElem);

	return 1; // se a insercao foi feita com sucesso
}

// o retorno sera codigo de erro
// mandar o elem x por referencia para que a funcao pop retorne
// o codigo de erro e o elemento na pilha, via parametro passado por 
// referencia
int pop(pilha_t *p, void *x) {
	assert(p != NULL); // esta alocado

	if(isEmpty(p) == 1) {
		return -1;
	}

	// copiar para x o conteudo do topo da pilha
	// copiar para x o conteudo de p->itens[p->topo], o qual tem
	// p->tamElem de qtd de memoria alocada em bytes
	memcpy(x, p->itens[p->topo], p->tamElem);

	// liberar espaco do elemento que estava no topo
	free(p->itens[p->topo]);

	// tirando o elemento, o topo decrementa
	p->topo--;

	return 1; // o elemento foi removido com sucesso
}

// ao inves de decrementar o topo, ele eh mantido para consulta
// do ultimo elemento na pilha
int top(pilha_t *p, void *x) {
	assert(p != NULL); // esta alocado

	if(isEmpty(p) == 1) {
		return -1; // se a pilha for vazia, nao tem o que consultar
	}

	// copiar o conteudo do topo da pilha para x
	// para chamar funcao top, precisa que x tenha memoria alocada
	// senao tenta copiar para x p->tamElem de qtd de bytes, estourando
	// a memoria do x
	memcpy(x, p->itens[p->topo], p->tamElem);

	return 1; // sucesso ao consultar
}