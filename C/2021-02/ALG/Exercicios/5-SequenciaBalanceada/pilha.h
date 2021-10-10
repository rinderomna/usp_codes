#define TamPilha 10000

#define FAIL -1

typedef char elem_t;
typedef struct pilha pilha_t;

/* |criar_pilha|
 * Cria uma pilha, alocando-a na Heap e retornando o devido ponteiro para a
 * pilha criada.
 *
 * @return (pilha_t *): endereco da primeira posicao na Heap contendo a pilha 
 * alocada.
 */
pilha_t *criar_pilha();

/* |get_tamanho_da_pilha|
 * Retorna o número de elementos na pilha.
 *
 * @param p (pilha_t *): ponteiro para a pilha cujo tamanho será consultada.
 * @return (int): número de elementos na pilha especificada.
 */
int get_tamanho_da_pilha(pilha_t *p);

/* |isFull|
 * Recebe ponteiro para a pilha, a qual será testada.
 * Se estiver cheia (número de elementos é o máximo estipulado),
 * retornará 1 (true). Caso contrário, retonará 0 (false).
 *
 * @param p (pilha_t *): ponteiro para a pilha
 * @return (int): inteiro tipo booleano que indica se pilha está cheia
 */
int isFull(pilha_t *p);

/* |isEmpty|
 * Recebe ponteiro para a pilha, a qual será testada.
 * Se estiver vazia (número de elementos é zero),
 * retornará 1 (true). Caso contrário, retonará 0 (false).
 *
 * @param p (pilha_t *): ponteiro para a pilha
 * @return (int): inteiro tipo booleano que indica se pilha está vazia
 */
int isEmpty(pilha_t *p);

/* |push|
 * Adiciona elemento ao topo da pilha
 *
 * @param p (pilha_t *): pilha à qual será adicionado um elemento
 * @param x (elem_t): elemento a ser adiciona à pilha especificada
 * @return (int): inteiro tipo flag para tratamento de erros.
 *  -> se for -1, indica que a pilha estava cheia.
 *  -> se for  1, é porque deu tudo certo com a adição
 */
int push(pilha_t *p, elem_t x);

/* |pop|
 * Adiciona elemento ao topo da pilha e armazena seu valor na variável
 * especificada
 *
 * @param p (pilha_t *): pilha da qual será desempilhada o elemento do topo.
 * @param x (elem_t *): endereço da variável na qual será armazenada o valor do
 * elemento que será tirado do topo.
 * @return (int): inteiro tipo flag para tratamento de erros.
 *  -> se for -1, indica que a pilha estava vazia.
 *  -> se for  1, é porque deu tudo certo com a remoção
 */
int pop(pilha_t *p, elem_t *x);

/* |top|
 * Consulta elemento e armazena seu valor na variável especificada
 *
 * @param p (pilha_t *): pilha cujo topo será consultado.
 * @param x (elem_t *): endereço da variável na qual será armazenada o valor do
 * elemento consultado do topo da pilha especificada.
 * @return (int): inteiro tipo flag para tratamento de erros.
 *  -> se for -1, indica que a pilha estava vazia.
 *  -> se for  1, é porque deu tudo certo com a consulta ao topo
 */
int top(pilha_t *p, elem_t *x);

/* |esvaziar_pilha|
 * Remove todos os elementos da pilha.
 *
 * @param p (pilha_t *): ponteiro para a pilha a se esvaziar.
 */
void esvaziar_pilha(pilha_t *p);


/* |destruir_pilha|
 * Recebe a ponteiro da pilha por referência para
 * desalocá-la e atribuir-lhe NULL
 *
 * @param p (pilha_t **): ponteiro para ponteiro da pilha
 */
void destruir_pilha(pilha_t **p);