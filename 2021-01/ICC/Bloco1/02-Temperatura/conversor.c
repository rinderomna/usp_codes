#include <stdio.h>

int main(int argc, char *argv[]) {
  float fator = 10.0/18.0;
  float tCelsius, tFahrenheit;

  scanf("%f", &tFahrenheit);

  tCelsius = fator * (tFahrenheit - 32);

  printf("%.2f \n", tCelsius);

  return 0;
}
