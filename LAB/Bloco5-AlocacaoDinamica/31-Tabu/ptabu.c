#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(void);

int main() {
  char palavra_tabu[21];
  scanf("%s\n", palavra_tabu);

  char *frase = read_line();

  int tamanho_palavra_tabu = strlen(palavra_tabu);

  int n_ocorrencias = 0;
  char *ocorrencia;
  do {
    ocorrencia = strstr(frase, palavra_tabu);

    if (ocorrencia != NULL)  {
      // tamanho_ate_o_final conta tamanho da ocorrencia até antes do '\0'
      int tamanho_ate_final = strlen(ocorrencia);
      // tamanho_restante conta tamanho partindo depois da palavra tabu,
      // até o '\0' incluso.
      int tamanho_restante = tamanho_ate_final - tamanho_palavra_tabu + 1;
      n_ocorrencias++;
      memmove(ocorrencia, ocorrencia + tamanho_palavra_tabu, tamanho_restante);
    }
  } while (ocorrencia != NULL);

  printf("A palavra tabu foi encontrada %d vezes\n", n_ocorrencias);
  printf("Frase: %s\n", frase);

  free(frase);

  return 0;
}

char *read_line(void) {
  char *line = NULL;
  char c;
  int n_chars = 0;
  
  do {
    c = getchar();
    
    n_chars++;
    line = (char *) realloc(line, n_chars);

    if (c != '$')
      *(line + n_chars - 1) = c;
    else
      *(line + n_chars - 1) = '\0';

  } while (c != '$');

  return line;
}
