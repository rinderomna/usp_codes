#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);

int main(void) {
  int a, b;
  scanf("%i%i",&a,&b);
  printf("\na vale %i e b vale %i\n\n",a,b);

  swap(&a,&b);

  printf("\na vale %i e b vale %i\n\n",a,b);
  return 0;
}

void swap(int *x, int *y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}
