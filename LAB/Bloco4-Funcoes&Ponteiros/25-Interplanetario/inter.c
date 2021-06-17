#include <stdio.h>
#include <string.h>

void CalculoHorario(unsigned long long int *segundos, char *planeta, unsigned long long int dhms[4]);

int main() {
  unsigned long long int dhms[4];
  unsigned long long int segundos;
  char planeta[10];

  scanf("%llu ", &segundos);
  scanf("%s", planeta);
  
  CalculoHorario(&segundos, planeta, dhms);

  printf("%llu segundos no planeta %s equivalem a:\n", segundos, planeta);
  printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n", dhms[0], dhms[1], dhms[2], dhms[3]);

  return 0;
}

void CalculoHorario(unsigned long long int *segundos, char *planeta, unsigned long long int dhms[4]) {
  char terra[] = "Terra"; 
  char venus[] = "Venus";
  char mercurio[] = "Mercurio";
  char jupiter[] = "Jupiter";

  dhms[2] = *segundos / 60;
  dhms[3] = *segundos % 60;

  if (strcmp(planeta, jupiter) == 0) { 
    dhms[0] = dhms[2] / 596;
    dhms[2] = dhms[2] % 596;
    dhms[1] = dhms[2] / 60;
    dhms[2] = dhms[2] % 60;
  } else if (strcmp(planeta, terra) == 0) {
    dhms[1] = dhms[2] / 60;
    dhms[2] = dhms[2] % 60;
    dhms[0] = dhms[1] / 24;
    dhms[1] = dhms[1] % 24;
  } else if (strcmp(planeta, mercurio) == 0) {
    dhms[1] = dhms[2] / 60;
    dhms[2] = dhms[2] % 60;
    dhms[0] = dhms[1] / 1408;
    dhms[1] = dhms[1] % 1408;
  } else if (strcmp(planeta, venus) == 0) {
    dhms[1] = dhms[2] / 60;
    dhms[2] = dhms[2] % 60;
    dhms[0] = dhms[1] / 5832;
    dhms[1] = dhms[1] % 5832;
  }
}