#include <stdio.h>

void Cria_Particula(char Particula, int x, int y,char Matriz[32][64]);
void Copia_Matriz(char Matriz_Destino[32][64], char Matriz_Original[32][64]);
void Imprime_Matriz(char Matriz[32][64]);
void Atualiza_Fisica(char Matriz_Frame[32][64]);

int main() {
  char Matriz_Frame[32][64];
  int n_frames, frame, x, y;
  char nova_particula;

  scanf("%d", &n_frames);

  int contador = 0;
  while (contador < n_frames) {
    int n_lido = scanf(" %d: %d %d %c", &frame, &x, &y, &nova_particula);
    
    if (n_lido == EOF) {
      frame = n_frames;
    }
    
    // Calcula todos os frames até o próximo frame onde queremos criar
    // uma partícula.
    while (contador < frame) {
      printf("frame: %d\n", contador + 1);
      Imprime_Matriz(Matriz_Frame);
      /* Seu código de calcular a física */
      contador++;
    }
    
    // Se há uma particula a ser criada, crie ela.
    if (n_lido != EOF) {
      Cria_Particula(nova_particula, x, y, Matriz_Frame);
    }
  }

  return 0;
}

void Cria_Particula(char Particula, int x, int y, char Matriz[32][64]) {
  Matriz[y][x] = Particula;
}

void Copia_Matriz(char Matriz_Destino[32][64], char Matriz_Original[32][64]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 64; j++) {
      Matriz_Destino[i][j] = Matriz_Original[i][j]; 
    }
  }
}

void Imprime_Matriz(char Matriz[32][64]) {
  for (int j = 0; j < 64; j++) {
    for (int i = 0; i < 32; i++) {
      printf("%c", Matriz[i][j]);
    }
  }
}

void Atualiza_Fisica(char Matriz_Frame[32][64]) {
  char Matriz_Copia[32][64];
  Copia_Matriz(Matriz_Copia, Matriz_Frame);

  for (int i = 0; i < 32; i++) {
    for(int j = 0; j < 64; j++) {
      
    }
  }
}
