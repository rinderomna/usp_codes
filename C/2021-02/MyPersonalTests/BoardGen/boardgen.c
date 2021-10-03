#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int string_len(char *str) {
  int len = 0;

  while (str[len] != '\0') len++;

  return len;
}

void *copy_memory(void *dest, void *src, int n_bytes) {
  char *d = (char *) dest;
  char *s = (char *) src;

  for (int i = 0; i < n_bytes; i++) {
    d[i] = s[i];
  }
  
  return dest;
}

int main(int argc, char *argv[]) { 
  if (argc < 4) {
    printf("Entre os dados apropriados\n\t./boardgen <nome> <n_rows> <n_cols> {<b_odds>}\n");
  }

  char *board_name = argv[1];
  int n_rows = atoi(argv[2]);
  int n_cols = atoi(argv[3]);
  int b_odds = 7; 
  
  if (argc >= 5) {  
    b_odds = atoi(argv[4]);
  }

  char extension[] = ".board";

  int name_len = string_len(board_name);
  int ext_len = string_len(extension);

  char *board_filename = (char *)malloc((name_len + ext_len + 1) * sizeof(char));
  copy_memory(board_filename, board_name, name_len);
  copy_memory(board_filename + name_len, extension, ext_len + 1);  

  char **matrix = (char **)malloc(n_rows * sizeof(char *));
 
  for (int i = 0; i < n_rows; i++) {
    matrix[i] = (char *)malloc(n_cols * sizeof(char));
  }

  srand(time(NULL));

  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      int rmd = rand() % b_odds;

      if (rmd == 0) {
        matrix[i][j] = '*';
      } else {
        matrix[i][j] = '.';
      }
    }
  }
  
  FILE *bf = NULL; 

  bf = fopen(board_filename, "w");

  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      fprintf(bf, "%c", matrix[i][j]);
    }

    if (i < n_rows - 1) fprintf(bf, "\n");
  }
  
  fclose(bf);

  for (int i = 0; i < n_rows; i++) {
    free(matrix[i]);
  }

  free(matrix);
  free(board_filename);

  return EXIT_SUCCESS;
}
