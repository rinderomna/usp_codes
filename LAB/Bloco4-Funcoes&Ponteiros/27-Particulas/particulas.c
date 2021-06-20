#include <stdio.h>
#include <stdbool.h>

enum {
  ORIGINAL,
  COPIA
};

void cria_particula(char Particula, int x, int y,char Matriz[32][64]);
void troca(char *a, char *b);
void zera_matriz(char Matriz[32][64]);
void copia_matriz(char Matriz_Destino[32][64], char Matriz_Original[32][64]);
void imprime_matriz(char Matriz[32][64]);
void atualiza_fisica(char Matriz_Frame[32][64]);

int main() {
  char Matriz_Frame[32][64];
  int n_frames, frame, x, y;
  char Nova_Particula;

  zera_matriz(Matriz_Frame);

  scanf("%d", &n_frames);

  int contador = 0;
  while (contador < n_frames) {
    int n_lido = scanf(" %d: %d %d %c", &frame, &x, &y, &Nova_Particula);
    
    if (n_lido == EOF)
      frame = n_frames;
    
    while (contador < frame) {
      printf("frame: %d\n", contador + 1);
      imprime_matriz(Matriz_Frame);
      atualiza_fisica(Matriz_Frame);
      contador++;
    }
    
    if (n_lido != EOF) {
      cria_particula(Nova_Particula, x, y, Matriz_Frame);
    }
  }

  return 0;
}

void cria_particula(char Particula, int x, int y, char Matriz[32][64]) {
  Matriz[y][x] = Particula;
}

void troca(char *a, char *b) {
  char aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void zera_matriz(char Matriz[32][64]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      Matriz[i][j] = ' ';
    }
  }
}

void copia_matriz(char Matriz_Destino[32][64], char Matriz_Original[32][64]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      Matriz_Destino[i][j] = Matriz_Original[i][j]; 
    }
  }
}

void imprime_matriz(char Matriz[32][64]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      printf("%c", Matriz[i][j]);
    }
    printf("\n");
  }
}

void atualiza_fisica(char Matriz_Frame[32][64]) {
  char Matriz_Copia[32][64];

  copia_matriz(Matriz_Copia, Matriz_Frame);

  for (int i = 0; i < 32; i++) {
    for(int j = 0; j < 64; j++) {
      char *Comparador[5][2];
      char Borda = '@';

      Comparador[0][ORIGINAL] = (i == 31) ? &Borda : &Matriz_Frame[i + 1][j];
      Comparador[1][ORIGINAL] = (i == 31 || j == 0) ? &Borda : &Matriz_Frame[i + 1][j - 1];
      Comparador[2][ORIGINAL] = (i == 31 || j == 63) ? &Borda : &Matriz_Frame[i + 1][j + 1];
      Comparador[3][ORIGINAL] = (j == 0) ? &Borda : &Matriz_Frame[i][j - 1];
      Comparador[4][ORIGINAL] = (j == 63) ? &Borda : &Matriz_Frame[i][j + 1];

      Comparador[0][COPIA] = (i == 31) ? &Borda : &Matriz_Copia[i + 1][j];
      Comparador[1][COPIA] = (i == 31 || j == 0) ? &Borda : &Matriz_Copia[i + 1][j - 1];
      Comparador[2][COPIA] = (i == 31 || j == 63) ? &Borda : &Matriz_Copia[i + 1][j + 1];
      Comparador[3][COPIA] = (j == 0) ? &Borda : &Matriz_Copia[i][j - 1];
      Comparador[4][COPIA] = (j == 63) ? &Borda : &Matriz_Copia[i][j + 1];

      switch(Matriz_Frame[i][j]) {
        case '#':
          for (int k = 0; k < 3; k++) {
            if (*Comparador[k][ORIGINAL] == '~' || *Comparador[k][ORIGINAL] == ' ') {
              troca(Comparador[k][COPIA], &Matriz_Copia[i][j]);
              break;
            }
          }
          break;
        case '~':
          for (int k = 0; k < 5; k++) {
            if (*Comparador[k][ORIGINAL] == ' ') {
              troca(Comparador[k][COPIA], &Matriz_Copia[i][j]);
              break;
            }
          }
          break;
      }
    }
  }

  copia_matriz(Matriz_Frame, Matriz_Copia);
}