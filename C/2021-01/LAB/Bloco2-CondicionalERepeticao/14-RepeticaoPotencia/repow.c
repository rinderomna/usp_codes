#include <stdio.h>

int main(int argc, char *argv[]) {
  int base, exponent;
  int answer = 1;
  
  scanf("%i %i", &base, &exponent);

  for(int i = 0; i < exponent; i++) {
    answer *= base;
  }
  
  printf("%i \n", answer);

  return 0;
}
