// fila.h

#define TamFila 100

typedef int elem;
typedef struct fila fila_t;

/* |criar|
 * Cria fila alocada e retorna o ponteiro para o bloco de
 * memória alocado.
 *
 * @return (fila_t *): ponteiro para o primeiro byte alocado
 * para a fila que acabou de ser criada.
 */
fila_t *criar();

/* |isEmpty|
 * Checa se a fila passada é vazia.
 *
 * @param f (fila_t *): ponteiro para fila que será checada 
 * se está ou não vazia.
 * @return (int): inteiro booleano que é 1 se a fila está 
 * vazia e 0 se a fila não está vazia.
 */
int isEmpty(fila_t *f);

/* |isFull|
 * Checa se a fila passada é vazia.
 *
 * @param f (fila_t *): ponteiro para fila que será checada 
 * se está ou não vazia.
 * @return (int): inteiro booleano que é 1 se a fila está 
 * vazia e 0 se a fila não está vazia.
 */
int isFull(fila_t *f);

/* |inserir|
 * Insere elemento na fila. Checa se ela está cheia.
 *
 * @param f (fila_t *): ponteiro para fila em cujo fim será
 * inserido o elemento.
 * @param x (elem): elemento a ser inserido.
 * @return (int): inteiro booleano que indica se deu tudo 
 * certo com a inserção.
 */
int inserir(fila_t *f, elem x);

/* |remover|
 * Remove elemento do início e retorna por referência.
 * 
 * @param f (fila_t *): ponteiro para fila de cujo início
 * será removido elemento.
 * @param x (elem *): endereço para onde enviar valor do 
 * elemento removido.
 * @return (int): inteiro booleano que indica se deu tudo 
 * certo com a remoção.
 */
int remover(fila_t *f, elem *x);

/* |destruir|
 * Desaloca toda memória relacioda à fila passada e atribui
 * NULL a seu ponteiro.
 * 
 * @param f (fila_t **): ponteiro para ponteiro da fila que 
 * será destruída.
 */
void destruir(fila_t **f);