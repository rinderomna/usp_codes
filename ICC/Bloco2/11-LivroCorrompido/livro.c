#include <stdio.h>
#include <stdlib.h>

char *read_line(void);

int main() {
  int n_lines;

  scanf("%d", &n_lines);
  
  getchar(); //Consumes '\n'
  
  char *lines[n_lines];

  for (int i = 0; i < n_lines; i++)
    lines[i] = read_line();

  int v;

  scanf("%d", &v);

  int true_lines[v];

  for (int i = 0; i < v; i++)
    scanf("%d", &true_lines[i]);

  for (int i = 0; i < v; i++)
    printf("%s\n", lines[true_lines[i]]);

  for(int i = 0; i < n_lines; i++)
    free(lines[i]);

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

    if (c != '\n')
      *(line + n_chars - 1) = c;
    else
      *(line + n_chars - 1) = '\0';

  } while (c != '\n');

  return line;
}
