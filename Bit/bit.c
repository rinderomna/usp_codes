#include <stdio.h>

#define MASK3 0b11111111
#define MASK2 0b1111111100000000
#define MASK1 0b111111110000000000000000
#define MASK0 0b11111111000000000000000000000000

int main(int argc, char *argv[]) {
  long int entrada;
  char caracteres[5];
  int masks[4] = {MASK0,MASK1,MASK2,MASK3};

  caracteres[4] = '\0';
  
  scanf("%ld", &entrada);

  for (int i = 0; i < 4; i++) {
    caracteres[i] = ( entrada & masks[i] ) >> 8*(3 - i);
  }
  
  printf("%s \n", caracteres);
  
  return 0;
}
