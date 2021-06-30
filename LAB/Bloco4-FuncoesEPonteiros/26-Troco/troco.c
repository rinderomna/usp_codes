#include <stdio.h>

void CalculoTroco(unsigned long long int *centavos, unsigned long long int moedas[6]);

int main() {
  unsigned long long int centavos;
  unsigned long long int moedas[6];

  scanf("%llu", &centavos);

  CalculoTroco(&centavos, moedas);

  printf("O valor consiste em %llu moedas de 1 real\n", moedas[0]);
  printf("O valor consiste em %llu moedas de 50 centavos\n", moedas[1]);
  printf("O valor consiste em %llu moedas de 25 centavos\n", moedas[2]);
  printf("O valor consiste em %llu moedas de 10 centavos\n", moedas[3]);
  printf("O valor consiste em %llu moedas de 5 centavos\n", moedas[4]);
  printf("O valor consiste em %llu moedas de 1 centavo\n", moedas[5]);

  return 0;
}

void CalculoTroco(unsigned long long int *centavos, unsigned long long int moedas[6]) {
  moedas[0] = *centavos / 100;
  moedas[5] = *centavos % 100;
  moedas[1] = moedas[5] / 50;
  moedas[5] = moedas[5] % 50;
  moedas[2] = moedas[5] / 25;
  moedas[5] = moedas[5] % 25;
  moedas[3] = moedas[5] / 10;
  moedas[5] = moedas[5] % 10;
  moedas[4] = moedas[5] / 5;
  moedas[5] = moedas[5] % 5;
}
