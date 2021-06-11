#include <stdio.h>
#include <string.h>

int main() {
  unsigned long long int segundos;
  unsigned long long int dhms[4];
  char planeta[10];

  char terra[] = "Terra"; 
  char venus[] = "Venus";
  char mercurio[] = "Mercurio";
  char jupiter[] = "Jupiter";

  scanf("%llu ", &segundos);
  scanf("%s", planeta);
  
  dhms[2] = segundos / 60;
  dhms[3] = segundos % 60;
  dhms[1] = dhms[2] / 60;
  dhms[2] = dhms[2] % 60;
  dhms[0] = dhms[1] / 24;
  dhms[1] = dhms[1] % 24;

  if (strcmp(planeta, venus)) {

  } else if (strcmp(planeta, mercurio)) {

  } else if (strcmp(planeta, jupiter)) {

  }

  printf("%llu d, %llu h, %llu m, %llu s \n", dhms[0], dhms[1], dhms[2], dhms[3]);

  return 0;
}
