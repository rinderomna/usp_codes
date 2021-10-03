#include <stdio.h>

int main(int argc, char *argv[]) {
  float velocidade, limite, multa;
  limite = 80.0;

  scanf("%f", &velocidade);
  
  multa = 2.0 * (velocidade - limite);

  if (velocidade > limite) {
    printf("Limite de velocidade excedido! Multado no valor de R$%.2f!\n", multa);
  } else {
    printf("Velocidade dentro do limite permitido.\n");
  }

  return 0;
}
