#include <stdio.h>

#define BOOL char
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
  unsigned int ano;

 // Booleano b ser bissexto:
  BOOL b;
  
  scanf("%i", &ano);

  if (ano % 400 == 0) {
    b = TRUE;
  } else if (ano % 100 == 0) {
    b = FALSE;
  } else if (ano % 4 == 0) {
    b = TRUE;
  } else {
    b = FALSE;
  }

  if (b) {
    printf("SIM \n");
  } else {
    printf("NAO \n");
  }

  return 0;
}
