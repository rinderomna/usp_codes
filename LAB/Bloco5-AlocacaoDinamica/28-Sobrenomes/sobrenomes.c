#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char **read_names_inline(bool *delimiter_found, int *n_names);

int main() {
  bool delimiter_found = false;
  int n_fullnames = 0;
  int *n_names_in_line = NULL;
  char ***fullnames = NULL;

  do {
    char **current_line;
    int n_names_in_current_line = 0;

    current_line = read_names_inline(&delimiter_found, &n_names_in_current_line);

    if (current_line != NULL) {
      n_fullnames++;

      n_names_in_line = (int *) realloc(n_names_in_line, n_fullnames * sizeof(int));
      *(n_names_in_line + n_fullnames - 1) = n_names_in_current_line;

      fullnames = (char ***) realloc(fullnames, n_fullnames * sizeof(char **));
      *(fullnames + n_fullnames - 1) = current_line;
    }
  } while (!delimiter_found);

  for (int i = 0; i < n_fullnames; i += 2) {
    if (i + 1 < n_fullnames) {
      n_names_in_line[i + 1]++;
      fullnames[i + 1] = (char **) realloc(fullnames[i + 1], n_names_in_line[i + 1] * sizeof(char *));

      char *new_lastname = fullnames[i + 1][n_names_in_line[i + 1] - 1];

      new_lastname = (char *) malloc(sizeof(fullnames[i][n_names_in_line[i] - 1]));

      strcpy(new_lastname, fullnames[i][n_names_in_line[i] - 1]);
    }
  }

  for (int i = 0; i < n_fullnames; i++) {
    for (int j = 0; j < n_names_in_line[i]; j++) {
      printf("%s", fullnames[i][j]);

      free(fullnames[i][j]);

      if (j != n_names_in_line[i] - 1)
        printf(" ");
    }

    free(fullnames[i]);

    printf("\n");
  }

  free(fullnames);

  return 0;
}

char **read_names_inline(bool *delimiter_found, int *n_names) {
  char **names_inline = NULL;
  char *current_name = NULL;

  *n_names = 0;
  bool forming_word = false;
  char current_n_chars = 0;
  char c;

  do {
    c = getchar();

    if (!forming_word && isalpha(c)) {
      forming_word = true;

      *n_names = *n_names + 1;
      names_inline = (char **) realloc(names_inline, *n_names * sizeof(char *));

      current_name = *(names_inline + *n_names - 1);
      current_n_chars = 1;
      current_name = (char *) malloc(current_n_chars);
      current_name[0] = c;      

    } else if (forming_word && isalpha(c)) {
      current_n_chars++;

      current_name = (char *) realloc(current_name, current_n_chars);
      *(current_name + current_n_chars - 1) = c;

    } else if (forming_word && c == ' ') {
      current_n_chars++;

      current_name = (char *) realloc(current_name, current_n_chars);
      *(current_name + current_n_chars - 1) = '\0';

      forming_word = false;
      current_n_chars = 0;

    } else if (forming_word && c == '$') {
      current_n_chars++;

      current_name = (char *) realloc(current_name, current_n_chars);
      *(current_name + current_n_chars - 1) = '\0';

      forming_word = false;
      current_n_chars = 0;

      *delimiter_found = true;

    } else if(!forming_word && c == '$') {
      *delimiter_found = true;

    }
  } while (c != '\n' && !delimiter_found);

  return names_inline;
}
