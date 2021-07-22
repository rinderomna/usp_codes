// Helio Nogueira Cardoso
// N°USP: 10310227

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct art_ {
  char *name;
  char *path;
  char **matrix;
  int height;
  int width;
} art_t;

typedef struct pixel_ {
  int x;
  int y;
} pixel_t;

char *read_line(FILE *stream, bool *has_EOF);
char *str_concatenate(const char *str_1, const char *str_2);
void free_art(art_t *art);
void load_art(art_t *art);
void print_art(art_t art);
bool is_out_of_bounds(art_t art, pixel_t pixel);
void paint_art_recursively(art_t *art, pixel_t pixel, char color, char which_to_paint);
void paint_art(art_t *art, pixel_t pixel, char color);
void enquadra_arte(char *nome_do_art_file,
	int altura_do_quadro,
	int largura_do_quadro
);

int main(void) {
  FILE *art_file = NULL;
  art_t art;
  
  load_art(&art);
  print_art(art);

  pixel_t pixel;

  pixel.x = 10;
  pixel.y = 13;
  paint_art(&art, pixel, 'o');

  pixel.x = 10;
  pixel.y = 20;
  paint_art(&art, pixel, 'o');

  pixel.x = 14;
  pixel.y = 17;
  paint_art(&art, pixel, 'x');

  print_art(art);

  free_art(&art);

  return 0;
}

char *read_line(FILE *stream, bool *has_EOF) {
  char *line = NULL;
  char c;
  int n_chars = 0;
  
  do {
    c = getc(stream);
    
    n_chars++;
    line = (char *) realloc(line, n_chars);

    if (c == '\n') {
      *(line + n_chars - 1) = '\0';
      *has_EOF = false;
    } else if (c ==  EOF) {
      *(line + n_chars - 1) = '\0';
      *has_EOF = true;
    } else {
      *(line + n_chars - 1) = c;
      *has_EOF = false;
    }

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

void free_art(art_t *art) {
  free(art->name);
  free(art->path);

  for (int i = 0; i < art->height; i++) {
    free(art->matrix[i]);
  }
  free(art->matrix);
}

void load_art(art_t *art) {
  FILE *art_file;
  bool has_EOF = false;

  art->name = read_line(stdin, &has_EOF);
  art->path = str_concatenate("artes/", art->name);

  art_file = fopen(art->path, "r");

  if (art_file == NULL) {
    printf("File '%s' does not exist.\n", art->path);
    free_art(art);
    exit(EXIT_FAILURE);
  }

  art->matrix = NULL;
  art->height = 0;

  do {
    int cur_index = art->height;
    art->matrix = (char **) realloc(art->matrix, ++art->height * sizeof(char *));
    
    art->matrix[cur_index] = read_line(art_file, &has_EOF);
  } while (!has_EOF);

  art->width = strlen(art->matrix[0]);

  fclose(art_file);
}

void print_art(art_t art) {
  for (int i = 0; i < art.height; i++) {
    printf("%s\n", art.matrix[i]);
  }
}

bool is_out_of_bounds(art_t art, pixel_t pixel) {
  bool is_out_of_bounds;
  
  if (pixel.x < 0 || pixel.x >= art.height) {
    is_out_of_bounds = true;
  } else if (pixel.y < 0 || pixel.y >= art.width) {
    is_out_of_bounds = true;  
  } else {
    is_out_of_bounds = false;
  }

  return is_out_of_bounds;
}

void paint_art_recursively(art_t *art, pixel_t pixel, char color, char which_to_paint) {
  if (art->matrix[pixel.x][pixel.y] == which_to_paint) {
    art->matrix[pixel.x][pixel.y] = color;
  } else {
    return;
  }

  pixel_t pixel_up;
  pixel_up.x = pixel.x - 1;
  pixel_up.y = pixel.y;

  pixel_t pixel_down;
  pixel_down.x = pixel.x + 1;
  pixel_down.y = pixel.y;

  pixel_t pixel_left;
  pixel_left.x = pixel.x;
  pixel_left.y = pixel.y - 1;

  pixel_t pixel_right;
  pixel_right.x = pixel.x;
  pixel_right.y = pixel.y + 1;

  if(!is_out_of_bounds(*art, pixel_up)) {
    paint_art_recursively(art, pixel_up, color, which_to_paint);
  }

  if(!is_out_of_bounds(*art, pixel_down)) {
    paint_art_recursively(art, pixel_down, color, which_to_paint);
  }

  if(!is_out_of_bounds(*art, pixel_left)) {
    paint_art_recursively(art, pixel_left, color, which_to_paint);
  }

  if(!is_out_of_bounds(*art, pixel_right)) {
    paint_art_recursively(art, pixel_right, color, which_to_paint);
  }
}

void paint_art(art_t *art, pixel_t pixel, char color) {
  char which_to_paint = art->matrix[pixel.x][pixel.y];

  paint_art_recursively(art, pixel, color, which_to_paint);
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