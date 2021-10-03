#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  CONSULTAR_ALUNO = 1,
  CONSULTAR_CURSO = 2,
  CONSULTAR_TUDO = 3
};

typedef struct aluno {
  long long int id;
  char *nome;
  char *curso;
  int idade;
} Aluno;

char *read_line(void);
void imprimir_aluno(Aluno aluno);

int main() {
  Aluno *alunos = NULL; 
  int n_alunos = 0;

  long long int id_lido;
  do {
    scanf(" %lld", &id_lido);

    if (id_lido != -1) {
      n_alunos++;

      Aluno novo_aluno;
      novo_aluno.id = id_lido;
      novo_aluno.nome = read_line();
      novo_aluno.curso = read_line();
      scanf(" %d", &novo_aluno.idade);

      alunos = (Aluno *) realloc(alunos, n_alunos * sizeof(Aluno));

      alunos[n_alunos - 1] = novo_aluno;
    }
  } while (id_lido != -1);
   
  int operacao;
  do { 
    scanf(" %d", &operacao);

    if (operacao == CONSULTAR_ALUNO) {
      long long int id_aluno;
      int contador = 0;

      scanf(" %lld", &id_aluno);

      for (int i = 0; i < n_alunos; i++) {
        if (alunos[i].id == id_aluno) {
          imprimir_aluno(alunos[i]);
          contador++;
        }
      }
      if (contador == 0) {
        printf("Aluno nao cadastrado\n");
      }
    } else if (operacao == CONSULTAR_CURSO) {
      char *curso_consultado = read_line();
      
      for (int i = 0; i < n_alunos; i++) {
        if (strcmp(alunos[i].curso, curso_consultado) == 0) {
          imprimir_aluno(alunos[i]);
        }
      }
      free(curso_consultado);
    } else if (operacao == CONSULTAR_TUDO) {
      for (int i = 0; i < n_alunos; i++) {
        imprimir_aluno(alunos[i]);
      }
    }

  } while (operacao != -1);

  for (int i = 0; i < n_alunos; i++) {
    free(alunos[i].curso);
    free(alunos[i].nome);
  }
  free(alunos);

  return 0;
}

char *read_line(void) {
  char *line = NULL;
  char c;
  int n_chars = 0;

  while ((c = getchar()) == '\n' || (c == '\r'));

  if (c != EOF) ungetc(c, stdin);
  
  do {
    c = getchar();
    
    n_chars++;
    line = (char *) realloc(line, n_chars);

    if (c != '\n')
      *(line + n_chars - 1) = c;
    else
      *(line + n_chars - 1) = '\0';

  } while (c != '\n');

  return line;
}

void imprimir_aluno(Aluno aluno) {
  printf("Nome: %s\n", aluno.nome);
  printf("Curso: %s\n", aluno.curso);
  printf("N USP: %lld\n", aluno.id);
  printf("IDADE: %d\n", aluno.idade);
  printf("\n");
}