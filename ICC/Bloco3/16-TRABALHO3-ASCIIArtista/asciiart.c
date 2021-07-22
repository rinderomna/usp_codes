#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(FILE *stream);
char *str_concatenate(const char *str_1, const char *str_2);
void enquadra_arte(
	char *nome_do_art_file,
	int  altura_do_quadro,
	int  largura_do_quadro
);

int main(void) {
  FILE *art_file = NULL;
  char *art_name;
  char *path_to_art;

  art_name = read_line(stdin);
  path_to_art = str_concatenate("artes/", art_name);

  printf("%s\n", art_name);
  printf("%s\n", path_to_art);

  fopen(path_to_art, "r");

  free(art_name);
  free(path_to_art);

  return 0;
}

char *read_line(FILE *stream) {
  char *line = NULL;
  char c;
  int n_chars = 0;
  
  do {
    c = getc(stream);
    
    n_chars++;
    line = (char *) realloc(line, n_chars);

    if (c != '\n' && c != EOF)
      *(line + n_chars - 1) = c;
    else
      *(line + n_chars - 1) = '\0';

  } while (c != '\n' && c != EOF);

  return line;
}

char *str_concatenate(const char *str_1, const char *str_2) {
  char *str_final = NULL;
  int final_len = strlen(str_1) + strlen(str_2);

  str_final = (char *)malloc((final_len + 1) * sizeof(char));

  strcpy(str_final, str_1);
  str_final = strcat(str_final, str_2);

  return str_final;
}

void enquadra_arte(
	char *nome_do_art_file,
	int  altura_do_quadro,
	int  largura_do_quadro
) {
	FILE *f_arte_ptr = fopen(nome_do_art_file, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}