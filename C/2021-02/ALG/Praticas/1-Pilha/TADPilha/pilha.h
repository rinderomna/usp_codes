// Definição de constante TamPilha que indica o tamanho máximo da pilha
#define TamPilha 100000

// Flag que indica falha na execução da função
#define FAIL -1

// Definição do tipo elem (int)
typedef int elem_t;

// Definição do tipo pilha_t (struct pilha)
typedef struct pilha pilha_t;

/* |create|
 * Cria uma pilha, alocando-a na Heap e retornando
 * o devido ponteiro para a pilha criada.
 *
 * @return (pilha_t *): endereco da primeira posicao
 * na Heap contendo a pilha alocada.
 */
pilha_t *create();

/* |destroy|
 * Recebe a ponteiro da pilha por referência para
 * desalocá-la e atribuir-lhe NULL
 *
 * @param p (pilha_t **): ponteiro para ponteiro da pilha
 */
void destroy(pilha_t **p);

/* |get_stack_size|
 * Retorna o tamanho da pilha especificada.
 *
 * @param p (pilha_t *): ponteiro para a pilha cujo tamanho será consultado
 * @return (int): inteiro que indica o número de elementos na pulha
 */
int get_stack_size(pilha_t *p);

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
