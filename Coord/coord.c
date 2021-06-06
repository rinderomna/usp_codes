#include <stdio.h>

int main(int argc, char *argv[]) {
  char teclas[6];
  int coordenadas[2] = {0, 0};

  for (int i = 0; i < 6; i++) {
    teclas[i] = getchar();
  }

  for (int i = 0; i < 6; i++) {
    switch (teclas[i]) {
      case 'W': 
        coordenadas[1]++;
        break;
      case 'S':
        coordenadas[1]--;
        break;
      case 'A':
        coordenadas[0]--;
        break;
      case 'D':
        coordenadas[0]++;
        break;
    }  
  }

  printf("%i %i \n", coordenadas[0], coordenadas[1]);

  return 0;
}
