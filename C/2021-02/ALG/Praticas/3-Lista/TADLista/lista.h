// lista.h

typedef int elem; // tipo elem - informacao armazenada na lista
typedef struct lista lista_t; // outra estrutura para armazenar ponteiros
// de inicio e fim, informacoes referentes a lista
// quando o usuario quiser usar uma lista, declara ponteiro para Lista_t
// e chama a funcao criar() para criar uma lista inicialmente vazia

lista_t *cria();
void liberar(lista_t *l);
void insere(lista_t *l, elem x);
int tamanho(lista_t *l);
void imprimir(lista_t *l);
int esta_na_lista(lista_t *l, elem x);
int remover(lista_t *l, elem x);
void inverte(lista_t *l);