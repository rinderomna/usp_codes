#include <stdio.h>

int maior(int n, int *numeros);

int menor(int n, int *numeros);

float media(int n, int *numeros);

int moda(int n, int *numeros);

int main() {
  int valores[10];

  for (int i = 0; i < 10; i++) {
    scanf("%d", &valores[i]);
  }

  printf("%d ", maior(10, valores));
  printf("%d ", menor(10, valores));
  printf("%.2f ", media(10, valores));
  printf("%d\n", moda(10, valores));

  return 0;
}

int maior(int n, int *numeros) {
  int maior = numeros[0];

  for (int i = 1; i < n; i++) {
    if (numeros[i] > maior)
      maior = numeros[i];
  }

  return maior;
}


int menor(int n, int *numeros) {
  int menor = numeros[0];

  for (int i = 1; i < n; i++) {
    if (numeros[i] < menor)
      menor = numeros[i];
  }

  return menor;
}

float media(int n, int *numeros) {
  float media = 0;

  for (int i = 0; i < n; i++) {
    media += (float) numeros[i] / (float) n;
  }

  return media;
}

int moda(int n, int *numeros) {
  int moda = 0, moda_contador = 0;

  for (int i = 0; i < n; i++) {
    int contador = 0;

    for (int j = 0; j < n - 1; j++) {
      if (numeros[j] == numeros[i])
        contador++;
    }

    if (contador > moda_contador) {
      moda_contador = contador;
      moda = numeros[i];
    }
  }

  return moda;
}
