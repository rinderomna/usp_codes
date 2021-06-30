#include <stdio.h>

#define pBolinha 5
#define pMordida 3

int main(int argc, char *argv[]) {
  int nBolinhas, nMordidas, deltaPeso;
  char resultado;

  scanf("%i %i", &nBolinhas, &nMordidas);
  
  deltaPeso = pMordida * nMordidas - pBolinha * nBolinhas;

  if(deltaPeso <= -30) {
    resultado = 'P';
  } else if (deltaPeso <= 0) {
    resultado = 'B';
  } else {
    resultado = 'R';
  }

  printf("%c \n", resultado);

  return 0;
}
