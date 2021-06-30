#include <stdio.h>
#include <stdbool.h>

int main() {
  int n_linhas = 0, n_palavras = 0, n_chars = 0;

  char status = 0;
  bool primeiro = true;

  while (true) {
    char c = getchar();

    if (c == EOF) {
      if (status == 2)
        n_linhas++;
      break;
    }

    if (primeiro) {
      if (c != ' ' && c != '\n' && c != '\r' && c != '\t') {
        n_palavras++;
        primeiro = false;
      }
    } 

    n_chars++;

    if (status == 0) {
      if (c == ' ' || c == '\t') {
        status = 1;
     } else if (c == '\r') {
        status = 2;
     } else if (c == '\n') {
        status = 3;
        n_linhas++;
      } 
    } else if (status == 1) {
      if (c == ' ' || c == '\t') {
        status = 1;
     } else if (c == '\r') {
        status = 2;
     } else if (c == '\n') {
        status = 3;
        n_linhas++;
     } else {
        status = 0;
        n_palavras++;
      } 
    } else if (status == 2) {
      if (c == ' ' || c == '\t') {
        status = 1;
        n_linhas++;
      } else if (c == '\r') {
        status = 2;
        n_linhas++;
      } else if (c == '\n') {
        status = 3;
        n_linhas++;
      } else {
        status = 0;
        n_linhas++;
        n_palavras++;
      }
    } else if (status == 3) {
      if(c == ' ' || c == '\t') {
        status = 1;
      } else if (c == '\r') {
        status = 2;
      } else if (c == '\n') {
        status = 3;
        n_linhas++;
      } else {
        status = 0;
        n_palavras++;
      }
    }

  } 
  printf("Linhas\tPalav.\tCarac.\n");
  printf("%d\t%d\t%d", n_linhas, n_palavras, n_chars);
  printf("\n");

  return 0;
}