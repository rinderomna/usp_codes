/*  SCC0221 - Introducao a Ciencia de Computacao I (2021)
 *  Trabalho 03 - ASCII Artista
 * 
 *  Helio Nogueira Cardoso
 *  N°USP: 10310227
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct art_ {
  char *path_to_file;
  char **matrix;
  int height;
  int width;
} art_t;

typedef struct pixel_ {
  int x;
  int y;
} pixel_t;

char *read_line(FILE *stream, bool *has_EOF);
void free_art(art_t *art);
void load_art(art_t *art);
void save_art(art_t *art);
void print_art(art_t art);
bool is_out_of_bounds(art_t art, pixel_t pixel);
void paint_art_recursively(art_t *art, pixel_t pixel, char color, char which_to_paint);
void paint_art(art_t *art, pixel_t pixel, char color);
void enquadra_arte(char *nome_do_art_file,
	int altura_do_quadro,
	int largura_do_quadro
);

int main(void) {
  art_t art;
  
  // Read 1st line with art's path name and load to art variable
  load_art(&art);

  // Print the initial art
  printf("Arte inicial:\n");
  print_art(art);

  // Read 2nd line with number of paintings to be done
  int n_paintings;
  scanf(" %d", &n_paintings);

  // Read the next n_paintings lines with the related painting parameters:
  // color, x and y
  for (int i = 0; i < n_paintings; i++) {
    // Read the char that represents the color to paint
    char color;
    scanf(" %c", &color);

    // Read the pixel coordenate (x, y) inside the area to be painted
    pixel_t pixel;
    scanf(" %d", &pixel.x);
    scanf(" %d", &pixel.y);

    // Perform the proper painting
    paint_art(&art, pixel, color);
    
    // Print the art after each painting step
    printf("\nArte apos a etapa %d:\n", i);
    print_art(art);
  }

  // Update the art's file with all paintings done
  save_art(&art);
  
  // Frame final art
  printf("\nArte enquadrada:\n");
  enquadra_arte(art.path_to_file, art.height, art.width);
 
  // Free all dynamically allocated memories
  free_art(&art);

  return 0;
}

// Read a line from a stream, which may be a file.
// Change by reference a boolean has_EOF.
// That boolean checks whether the line read is the last of the file (ends in EOF)
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

// Free all alocated memory related to an art
void free_art(art_t *art) {
  free(art->path_to_file);

  for (int i = 0; i < art->height; i++) {
    free(art->matrix[i]);
  }
  free(art->matrix);
}

// Load art from a file, whose name is read from standard input
void load_art(art_t *art) {
  FILE *art_file;
  bool has_EOF = false;

  // Read file's path name from standard input
  art->path_to_file = read_line(stdin, &has_EOF);

  art_file = fopen(art->path_to_file, "r");

  if (art_file == NULL) {
    printf("File '%s' does not exist.\n", art->path_to_file);
    free_art(art);
    exit(EXIT_FAILURE);
  }

  // Art's matrix dynamically allocated and read line by line from file
  art->matrix = NULL;
  art->height = 0; // art's height represents the number of lines

  do {
    int cur_index = art->height;
    art->matrix = (char **) realloc(art->matrix, ++(art->height) * sizeof(char *));
    
    art->matrix[cur_index] = read_line(art_file, &has_EOF);
  } while (!has_EOF);

  // art's width is the length of any line, such as the first,
  // since all of the them must have the same length
  art->width = strlen(art->matrix[0]);

  fclose(art_file);
}

// Update the art's file with the current art's matrix
void save_art(art_t *art) {
  FILE *art_file = NULL;

  art_file = fopen(art->path_to_file, "w");

  int i;
  for (i = 0; i < art->height - 1; i++) {
    fprintf(art_file, "%s", art->matrix[i]);
    fprintf(art_file, "\n");
  }
  fprintf(art_file, "%s", art->matrix[i]);

  fclose(art_file);
}

void print_art(art_t art) {
  for (int i = 0; i < art.height; i++) {
    printf("%s\n", art.matrix[i]);
  }
}

// Check whether the pixel is out of the art's matrix bounds
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

// Paint the region inside the area where the pixel passed is inside with the color passed.
// Only paint the pixel if its initial color is which_to_paint.
// If the pixel is successfully painted:
//  the function call itself for each of its 4 neighbours (up, down, left and right),
//  but only if that neighbour is not out of the art's matrix bounds
void paint_art_recursively(art_t *art, pixel_t pixel, char color, char which_to_paint) {
  if (art->matrix[pixel.x][pixel.y] == which_to_paint) {
    art->matrix[pixel.x][pixel.y] = color;
  } else {
    return;
  }

  pixel_t pixel_up;
  pixel_up.x = pixel.x;
  pixel_up.y = pixel.y - 1;

  pixel_t pixel_down;
  pixel_down.x = pixel.x;
  pixel_down.y = pixel.y + 1;

  pixel_t pixel_left;
  pixel_left.x = pixel.x - 1;
  pixel_left.y = pixel.y;

  pixel_t pixel_right;
  pixel_right.x = pixel.x + 1;
  pixel_right.y = pixel.y;

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

// Assing the initial color of the pixel passed to a which_to_paint char variable.
// Then, call paint_art_recursively function with same parameters + which_to_paint.
// This will properly paint the region where the pixel passed is with the color passed
void paint_art(art_t *art, pixel_t pixel, char color) {
  char which_to_paint = art->matrix[pixel.x][pixel.y];

  paint_art_recursively(art, pixel, color, which_to_paint);
}

// Print the art inside the file, whose path name is nome_do_art_file, framing it.
// Also receive:
// * Art's height -> altura_do_quadro
// * Art's width -> lasrgura_do_quadro
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