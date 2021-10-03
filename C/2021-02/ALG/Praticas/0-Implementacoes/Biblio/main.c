// main

#include <stdio.h>
#include "biblio.h" // o fila.h eh usado pelo tad biblio, nao precisa
										// importar. Usuario nao lida com estrutura de dados
										// fila.

int main() {
	int opt; // opcoes do sistema de biblio
	int user_id, livro_id;
	// isso ja cadastra usuarios e livros, de acordo com o exemplo
	biblio_t *bib = cria_biblio();

	do {
		printf("Digite a opcao desejada:\n");
		printf("1 - Emprestar um livro\n");
		printf("2 - Devolver um livro\n");
		printf("0 - Sair do programa\n");
		scanf("%d", &opt);

		// se opt == 0, nao entra no switch e sai do while
		switch(opt) {
			case 1:
				printf("Digite o id do usuario: ");
				scanf("%d", &user_id);
				// o id eh valido?
				if(consulta_usuario(bib, user_id) == 0) {
					printf("Usuario nao cadastrado!\n");
					continue; // forca o do while -  a proxima iteracao,
										// pedindo nova opcao. A iteracao atual acaba.
				}
				// passando desse if,
				printf("Digite o id do livro: ");
				scanf("%d", &livro_id);
				if (consulta_livro(bib, livro_id) == 0) {
					printf("Livro nao cadastrado!\n");
					continue;
				}

				// ids validos. Verificar se o livro esta disponivel.
				if (livro_disponivel(bib, livro_id) == 1) {
					emprestar_livro(bib, user_id, livro_id);
					printf("Emprestimo realizado com sucesso!\n");
				}
				else { // se o livro nao esta disponivel,
					// inserir o usuario na fila de espera
					inserir_fila(bib, user_id, livro_id);
					printf("Livro ja emprestado, inserindo na fila...\n");
				}
				break;

			case 2:
				// livro ja emprestado tem o id do usuario que o empresta
				// na struct livro
				printf("Digite o id do livro: ");
				scanf("%d", &livro_id);
				if (consulta_livro(bib, livro_id) == 0) {
					printf("Livro nao cadastrado!\n");
					continue;
				}

				// certificar se de que o livro deu baixa no sistema e 
				// esta disponivel novamente
				// esse if confirma que deu baixa
				if (livro_disponivel(bib, livro_id) == 1) {
					printf("Livro ja foi devolvido\n");
				}
				else { // o else da a baixa pela primeira vez
					// verifica se a fila esta vazia. Se estiver, livro fica
					// disponivel. Senao, empresta para prox. usuario da fila.

					// info do usuario que devolve e do livro devolvido para 
					// a biblioteca bib.
					devolver_livro(bib, user_id, livro_id);
					printf("Livro devolvido com sucesso!\n");
				}
		}	

	} while (opt != 0);	

	apaga_biblio(bib);

	return 0;
}