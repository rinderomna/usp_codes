#include <stdio.h>

int main(int argc, char *argv[]) {
  double numeros[4];
  double temp;
  double media;

  for (int i = 0; i < 4; i++) {
    scanf("%lf", &numeros[i]);
  }

  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 3; i++) {
      if (numeros[i + 1] < numeros[i]) {
        temp = numeros[i];
        numeros[i] = numeros[i + 1];
        numeros[i + 1] = temp;
      }
    }
  }
  
  media = (numeros[1] + numeros[2] + numeros[3]) / 3.0;

  printf("%.4f \n", media);

  return 0;
}
