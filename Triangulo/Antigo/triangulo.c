#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n;
  char symb;

  scanf("%i %c", &n, &symb);

  if(n <= 0 || n > 25) {
    printf("Altura invalida\n");
    exit(0);
  }

  for(int j = 1; j <= 2*n - 1; j = j + 2) {
    int line = (j - 1) / 2 + 1;
    
    for(int k = 0; k < n - line; k++) {
      printf(" ");
    }
    for(int i = 1; i <= j; i++) {
      printf("%c", symb);
    }
    printf("\n");
  }

  return 0;
}
