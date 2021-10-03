#include <stdio.h>
#include <stdlib.h>

void imprime_vetor(int *v, int n);
void intercala(int *v, int ini, int fim);
void mergesort(int *v, int ini, int fim);

int main() {
  int v[8] = {6, 5, 2, 4, 1, 8, 3, 7};

  printf("Vetor antes:\n\t");
  imprime_vetor(v, 8);

  mergesort(v, 0, 7);

  printf("\nVetor depois:\n\t");
  imprime_vetor(v, 8);

  return EXIT_SUCCESS;
}

void imprime_vetor(int *v, int n) {
  printf("[");

  for (int i = 0; i < n; i++) {
    printf("%d", v[i]);
    if (i < n - 1) printf(", ");
  }

  printf("]\n");
}

void intercala(int *v, int ini, int fim) {
  int *aux = (int *)malloc((fim - ini + 1) * sizeof(int));

  int c = (ini + fim) / 2;  // recálculo do centro

  // Valores iniciais dos iteradores
  int i = ini;    // iterador no subvetor esquerdo
  int j = c + 1;  // iterador no subvertor direito
  int k = 0;      // iterador no vetor auxiliar

  // enquanto ainda houverem elementos das duas listas para
  // serem comparados, faremo-lo
  while (i <= c && j <= fim) {
    if (v[i] <= v[j]) {
      aux[k] = v[i];
      i++;
    } else {
      aux[k] = v[j];
      j++;
    }

    k++;
  }

  // Terminar de preencher
  // Apenas um dos 2 próximos loops irá ocorrer
  while (i <= c) {
    aux[k] = v[i];
    i++;
    k++;
  }

  while (j <= fim) {
    aux[k] = v[j];
    j++;
    k++;
  }

  // Copiar ordenado para o vetor original
  for (i = ini, k = 0; i <= fim; i++, k++) {
    v[i] = aux[k];
  }

  free(aux);
}

void mergesort(int *v, int ini, int fim) {
  //  caso base - conquistar
  if (ini == fim) {
    return;
  }

  // dividir
  int c = (ini + fim) / 2;

  mergesort(v, ini, c);      // 1a metade
  mergesort(v, c + 1, fim);  // 2a metade

  intercala(v, ini, fim);
}
