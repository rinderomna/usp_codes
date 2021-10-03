typedef struct {
	int num, den;
} fracao_t;

// Operações
//    Apenas assinatura, protótipo, cabeçalho... 
//    Implementação escondida do usuário

// Usuario sabe exatamente quais dados esta manipulando, mas nao
// sabe como esses dados sao manipulados para retornar o que ele deseja
// retorno: ponteiro para a funcao criada la dentro
// operacao: criar fracao
fracao_t *criar(int num, int den);

// operacao: imprimir fracao na tela
// lembrando que a impressao nao tem processamentos, entao retorna void
void imprimir(fracao_t *f);

// operacao: destruir fracao - desalocar memoria apontada pelo ponteiro de 
// parametro
void destruir(fracao_t **f);

// simplifica a fracao
void simplificar(fracao_t *f);

// criar uma fracao que eh resultado da soma de outras duas fracoes
// retorno: nova fracao, resultado dessa soma de fracoes
fracao_t *somar(fracao_t *f1, fracao_t *f2);