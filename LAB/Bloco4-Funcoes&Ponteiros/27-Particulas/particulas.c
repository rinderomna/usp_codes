#include <stdio.h>
#include <stdbool.h>

enum {
  ORIGINAL,
  COPIA
};

void Cria_Particula(char Particula, int x, int y,char Matriz[32][64]);
void Troca(char *a, char *b);
void Zera_Matriz(char Matriz[32][64]);
void Copia_Matriz(char Matriz_Destino[32][64], char Matriz_Original[32][64]);
void Imprime_Matriz(char Matriz[32][64]);
void Atualiza_Fisica(char Matriz_Frame[32][64]);

int main() {
  char Matriz_Frame[32][64];
  int n_frames, frame, x, y;
  char nova_particula;

  Zera_Matriz(Matriz_Frame);

  scanf("%d", &n_frames);

  int contador = 0;
  while (contador < n_frames) {
    int n_lido = scanf(" %d: %d %d %c", &frame, &x, &y, &nova_particula);
    
    if (n_lido == EOF)
      frame = n_frames;
    
    while (contador < frame) {
      printf("frame: %d\n", contador + 1);
      Imprime_Matriz(Matriz_Frame);
      Atualiza_Fisica(Matriz_Frame);
      contador++;
    }
    
    if (n_lido != EOF) {
      Cria_Particula(nova_particula, x, y, Matriz_Frame);
    }
  }

  return 0;
}

void Cria_Particula(char Particula, int x, int y, char Matriz[32][64]) {
  Matriz[y][x] = Particula;
}

void Troca(char *a, char *b) {
  char aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void Zera_Matriz(char Matriz[32][64]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      Matriz[i][j] = ' ';
    }
  }
}

void Copia_Matriz(char Matriz_Destino[32][64], char Matriz_Original[32][64]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      Matriz_Destino[i][j] = Matriz_Original[i][j]; 
    }
  }
}

void Imprime_Matriz(char Matriz[32][64]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      printf("%c", Matriz[i][j]);
    }
    printf("\n");
  }
}

void Atualiza_Fisica(char Matriz_Frame[32][64]) {
  char Matriz_Copia[32][64];

  Copia_Matriz(Matriz_Copia, Matriz_Frame);

  for (int i = 0; i < 32; i++) {
    for(int j = 0; j < 64; j++) {
      char *comparador[5][2];
      char Borda = '@';

      comparador[0][ORIGINAL] = (i == 31) ? &Borda : &Matriz_Frame[i + 1][j];
      comparador[1][ORIGINAL] = (i == 31 || j == 0) ? &Borda : &Matriz_Frame[i + 1][j - 1];
      comparador[2][ORIGINAL] = (i == 31 || j == 63) ? &Borda : &Matriz_Frame[i + 1][j + 1];
      comparador[3][ORIGINAL] = (j == 0) ? &Borda : &Matriz_Frame[i][j - 1];
      comparador[4][ORIGINAL] = (j == 63) ? &Borda : &Matriz_Frame[i][j + 1];

      comparador[0][COPIA] = (i == 31) ? &Borda : &Matriz_Copia[i + 1][j];
      comparador[1][COPIA] = (i == 31 || j == 0) ? &Borda : &Matriz_Copia[i + 1][j - 1];
      comparador[2][COPIA] = (i == 31 || j == 63) ? &Borda : &Matriz_Copia[i + 1][j + 1];
      comparador[3][COPIA] = (j == 0) ? &Borda : &Matriz_Copia[i][j - 1];
      comparador[4][COPIA] = (j == 63) ? &Borda : &Matriz_Copia[i][j + 1];

      switch(Matriz_Frame[i][j]) {
        case '#':
          for (int k = 0; k < 3; k++) {
            if (*comparador[k][ORIGINAL] == '~' || *comparador[k][ORIGINAL] == ' ') {
              Troca(comparador[k][COPIA], &Matriz_Copia[i][j]);
              break;
            }
          }
          break;
        case '~':
          for (int k = 0; k < 5; k++) {
            if (*comparador[k][ORIGINAL] == ' ') {
              Troca(comparador[k][COPIA], &Matriz_Copia[i][j]);
              break;
            }
          }
          break;
      }
    }
  }

  Copia_Matriz(Matriz_Frame, Matriz_Copia);
}