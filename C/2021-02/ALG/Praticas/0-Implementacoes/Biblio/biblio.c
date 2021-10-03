// biblio.c

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "fila.h" // usamos a estrutura de dados fila para manipular 
									// os livros em suas filas de emprestimo

#include "biblio.h"

// implementacao da estrutura Usuario, que empresta, devolve o livro etc
struct usuario {
	int id; 
	char nome[100]; // nome do usuario com tamanho maximo de 100
};

struct livro {
	int id;
	char titulo[100];
	int disp; // esta disponivel ou nao
	fila_t *f;
	// cada livro tem sua fila. Entao, na estrutura livro, precisamos
	// de um ponteiro para a estrutura fila, disponivel para uso
	int user_id; 	
	// armazenar id do usuario que empresta o livro naquele momento.
	// Como se fosse uma ficha de historico de emprestimo, mas so
	// guardaremos o usuario que esta com o livro no momento
	// se o livro estiver disponivel, podemos setar esse campo para -1
};

// exportar um TADBiblioteca para que o usuario possa instanciar
// uma biblioteca em especifico
struct biblio {
	// o que tem dentro de uma biblioteca?
	// uma biblioteca tem um numero de usuarios no sistema
	usuario_t usuarios[N_USERS];

	// nao faremos dinamico para nao mexer com alocacao dinamica de varios
	// usuarios a cada execucao do programa (cadastrando usuarios, 
	// livros... novos)

	// poderiamos fazer isso ao executar e salvar os dados da execucao
	// em um arquivo - o Moacir fez isso nas aulas iniciais - arquivos
	// parte 3
	livro_t livros[N_LIVROS];
};

// implementar funcoes do tad biblioteca
// mesma ideia da fila
// criar biblioteca: criar ponteiro, fazer alocacao da estrutura
// biblioteca, inicializar informacoes e retornar ponteiro da struct
// biblio para fora da f.

biblio_t *cria_biblio() {
	biblio_t *bib = (biblio_t *) malloc(sizeof(biblio_t));
	assert(bib); // same as bib != NULL

	cadastra_usuarios(bib);
	cadastra_livros(bib);
	return bib;
} 

// para cada malloc, um free correspondente
void apaga_biblio(biblio_t *bib) {
	assert(bib);
	// destruir as filas de livros para cada livro
	// uso do fila.h
	for (int i = 0; i < N_LIVROS; i++){
		destruir(&bib->livros[i].f);
	}

	free(bib);
	// se for setar endereco para NULL, precisa passar **
	// porque quando passa *, passa uma copia da referencia
	// ao passar **, passa realmente a referencia

	// aqui, estamos desalocando o espaco de memoria apontado por bib
	// se fizessemos **bib, poderiamos setar para NULL o ponteiro/endereco
	// em si
}

// pode melhorar, ler um arquivo ou um banco de dados
void cadastra_usuarios(biblio_t *bib) {
	assert(bib);
	for (int i = 0; i < N_USERS; i++) {
		// posicao de cada usuario da lista de usuarios
		bib->usuarios[i].id = i; 
		// setar o id
		// aqui eh so um exemplo. O id poderia ser o No USP de cada usuario,
		// por ex.,
		// ou um outro identificador 
		// usuarios[i] . id porque usuarios eh uma struct, nao um ponteiro.
		// nao precisa de setinha ->
		strcpy(bib->usuarios[i].nome, "Nome de usuario");
	}
}

void cadastra_livros(biblio_t *bib) {
	assert(bib);
	for (int i = 0; i < N_LIVROS; i++) {
		bib->livros[i].id = i;
		// same as (*bib).usuarios[i].id -> para pegar o valor na struct
		// biblio
		strcpy(bib->livros[i].titulo, "Titulo do livro");
		// o strcpy vai copiar a string "Titulo do livro" para cada
		// indice da lista de livros
		bib->livros[i].disp = 1; // todos os livros disponiveis inicialmente
		bib->livros[i].f = criar();
		// criar a fila f para cada livro
		// cada livro tem um ponteiro que aponta para a estrutura fila
		// cada livro tem a fila propria

		bib->livros[i].user_id = -1; // inicializar assim
		// porque nenhum usuario esta com o livro emprestado nesse momento
	}

}

// consultar se usuario esta cadastrado na biblio
// a secretaria da biblioteca pede o cartao USP para ver se o id 
// consta no sistema para que esse usuario possa emprestar um livro
int consulta_usuario(biblio_t *bib, int user_id) {
	assert(bib); // bib existe?
	// verificar se o user_id eh valido
	// usar id do usuario e id do livro como indice do vetor
	// [isso porque estamos usando alocacao estatica].
	// num sistema real, usamos hashing para mapear o identificador id
	// do usuario, p. ex., o No USP, para a posicao de uma tabela ou um
	// vetor como esse para que tenhamos acesso constante ao conjunto de
	// livros ou de usuarios.
	// nao faremos isso (mapeamento) nesse exemplo.

	// verificar se o user_id eh valido
	if (user_id < 0 || user_id >= N_USERS) {
		return 0;
	}

	return 1;
}

// consultar se livro esta cadastrado na biblio
int consulta_livro(biblio_t *bib, int livro_id) {
	assert(bib);
	if (livro_id < 0 || livro_id >= N_LIVROS) {
		return 0;
	}
	
	return 1;
}

// o livro esta disponivel  ou esta emprestado? campo disp da struct
// livro
// lembrar do conceito de TAD - na main, o usuario do TAD nao tem acesso 
// ao disp, mas apenas as funcoes do .h e aos defines la feitos,
// precisar retornar isso para fora - o resultado se esta ou nao disponivel
int livro_disponivel(biblio_t *bib, int livro_id) {
	assert(bib);
	// passar o id do livro
	return bib->livros[livro_id].disp;
	// isso so retorna uma copia desse campo, com 1 ou 0
	// primeiro consultar se o livro existe, depois pode chamar essa f.

	// poderia colocar a chamada da f. consulta_livro aqui
	// mas faremos a chamada na main
}

void emprestar_livro(biblio_t *bib, int user_id, int livro_id) {
	// verificar se o livro esta disponivel na main para este exemplo
	// se estiver, chamamos essa funcao
	// precisa garantir que os ids do livro e do usuario sao validos
	// importante documentar esses criterios: "essa f. assume que 
	// tal coisa acontece..."
	// importa para que o usuario saiba utilizar seu TAD

	// assumindo que o livro esteja disponivel e que os ids existem, 
	assert(bib);
	bib->livros[livro_id].disp = 0; // livro nao mais disponivel
	// user id eh o campo da struct livro que indica
	// qual eh o usuario que esta com o livro no momento.
	// para emprestar, o usuario com user_id = user_id deve ser
	// quem esta com o livro no momento, agora
	bib->livros[livro_id].user_id = user_id; 
}

// se o livro estiver disponivel, emprestar_livro. 
// se o livro nao estiver disponivel, precisa de uma funcao para
// colocar o usuario na fila de lista de espera do livro desejado.

// essa f. poderia ser chamada dentro da emprestar_livro, caso
// o livro nao esteja disponivel ao usuario que o requisita
int inserir_fila(biblio_t *bib, int user_id, int livro_id) {
	assert(bib);
	// assumir que user_id e livro_id sao validos e que o livro
	// nao esta disponivel.
	// chamar a funcao inserir() do TADFila
	// passar de argumento a fila daquele livro e o usuario a inserir
	// na fila de espera pelo livro
	inserir(bib->livros[livro_id].f, (void *) &bib->usuarios[user_id]);
	// bib->usuarios[user_id] ja eh o objeto em si, nao eh uma copia,
	// pois quando acessamos um vetor com um determinado indice, acessamos
	// o objeto la na memoria, naquela posicao do vetor.

	// fila recebe ponteiro do elemento 
	// f. inserir recebe (fila_t *f, void *x)
	// e void *x, eh a referencia do objeto (ponteiro do objeto eh 
	// armazenado)

	// armazenar o endereco da posicao especifica do usuario
	// usuarios[5], por ex., eh a sexta posicao do vetor de usuarios.
	// la tem o endereco do usuario na sexta posicao.
	// assim, passamos &bib->usuarios[user_id]

	// isso eh um endereco para a estrutura usuario_t, um campo
	// da struct biblio. Temos, la, o endereco do usuario em questao.
	// Precisamos fazer conversao para void *

	// fica inserir(bib->livros[livro_id].f, (void *)&bib->usuarios[user_id])

	// se a fila de um determinado livro estiver cheia, temos que a f. inserir
	// do TADFila retorna 0. Podemos tratar isso com
	if (inserir(bib->livros[livro_id].f, (void *)&bib->usuarios[user_id]) == 0) {
		return 0;
	}

	// senao, retorna 1
	return 1;

	// eh importante ter codigo de erro e de sucesso
}

// a secretaria da biblio tem um menu de emprestimos e devolucoes.
// ela seleciona num menu de uma UI a operacao de devolucao, pede o id do 
// usuario e verifica o codigo do livro. Entao, faz a devolucao no sistema.

// a devolucao tem 2 funcionalidades: se tiver gente na fila do livro
// devolvido, ele eh repassado para a primeira pessoa da fila de espera,
// automaticamente. 
// se nao tiver ninguem na fila de espera, o disp do livro sera setado
// para 1 (livro disponivel)
void devolver_livro(biblio_t *bib, int user_id, int livro_id) {
	// verificar se ha usuarios esperando o livro na fila
	if (isEmpty(bib->livros[livro_id].f) == 1) { // fila vazia
		bib->livros[livro_id].disp = 1; // livro disponivel
		bib->livros[livro_id].user_id = -1; // nenhum usuario esta
																				// com o livro no momento
	}
	else { // se a fila nao esta vazia, tem um usuario aguardando
		// remove lo da fila - passar a fila *f e passar o elemento a remover
		// por void **x [passado por referencia - parametro de retorno
		// passado para receber alguma coisa como informacao]
		// remover um usuario recebido da fila f
		// quais sao os elementos da fila? Usuarios.
		// na verdade, armazenamos referencias a usuarios.
		// precisamos de uma variavel para receber o usuario retornado da 
		// estrutura fila
		usuario_t *novo_user; // proximo da fila
		// passar o novo_user por referencia, para nao fazer copia do ponteiro.
		// queremos o ponteiro em si.
		// passamos ponteiro de ponteiro para usuario_t - novo_user eh
		// ponteiro para usuario_t. Quando colocamos &novo_user, eh o 
		// ponteiro de ponteiro para um usuario_t.

		// fazer casting para void ** para usar a fila generica
		remover(bib->livros[livro_id].f, (void **) &novo_user);
		
		// o usuario_t aqui ja recebeu seu valor e o id de um usuario
		// que estava aguardando o livro na fiala

		// emprestar para o novo usuario
		// mandar o id do usuario, que vem do struct usuario
		emprestar_livro(bib, novo_user->id, livro_id);
		// se tiver sucesso:
		printf("Emprestando para novo usuario da fila: %d\n", novo_user->id);
	}
}