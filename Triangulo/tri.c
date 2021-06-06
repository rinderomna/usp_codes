#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  char c;

  scanf("%i %c", &n, &c);

  if(n <= 0 || n > 25) {
    printf("Altura invalida\n");
    exit(0);
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 0; j < n - i; j++)
      printf(" ");
    for(int k = 0; k < 2 * i - 1; k++) 
      printf("%c", c);
    printf("\n");
  }

  return 0;
}
