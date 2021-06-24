#include <stdio.h>
#include <stdlib.h>

int main() {
  long long int La, Ca, Lb, Cb;
  long long int seed;
  
  scanf("%lli %lli %lli %lli", &La, &Ca, &Lb, &Cb);

  if (Ca != Lb || La <= 0 || Ca <= 0 || Lb <= 0 || Cb <= 0) {
    printf("Valores invalidos para a multiplicacao.\n");
    exit(0);
  }

  long long int A[La][Ca], B[Lb][Cb], C[La][Cb];
    
  scanf("%lli", &seed);

  srand(seed);

  for (int i = 0; i < La; i++) {
    for (int j = 0; j < Ca; j++) {
      A[i][j] = rand()%50 - 25;
    }
  }

  for (int i = 0; i < Lb; i++) {
    for (int j = 0; j < Cb; j++) {
      B[i][j] = rand()%50 - 25;
    }
  }

  for (int i = 0; i < La; i++) {
    for (int j = 0; j < Cb; j++) {
      C[i][j] = 0;
      for (int k = 0; k < Ca; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  for (int i = 0; i < La; i++) {
    printf("Linha %i: ", i);
    for (int j = 0; j < Cb; j++) {
      printf("%lli", C[i][j]);
      if (j < Cb - 1) {
        printf(" ");
      }
    }
    printf("\n");
  }

  return 0;
}
