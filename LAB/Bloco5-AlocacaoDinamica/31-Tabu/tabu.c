#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(void);

int main() {
  char PalavraTabu[21];
  scanf("%s\n", PalavraTabu);

  char *Frase = read_line();

  int Tamanho_Palavra = strlen(PalavraTabu);

  int n_ocorrencias = 0;
  char *ocorrencia;
  do {
    ocorrencia = strstr(Frase, PalavraTabu);

    if (ocorrencia != NULL)  {
      n_ocorrencias++;
      strcpy(ocorrencia, ocorrencia + Tamanho_Palavra);
    }
  } while (ocorrencia != NULL);

  printf("A palavra tabu foi encontrada %d vezes\n", n_ocorrencias);
  printf("Frase: %s\n", Frase);

  free(Frase);

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
