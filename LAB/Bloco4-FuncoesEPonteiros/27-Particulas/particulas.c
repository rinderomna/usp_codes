#include <stdio.h>
#include <stdbool.h>

#define AR ' '
#define AGUA '~'
#define AREIA '#'
#define CIMENTO '@'

#define N_LINHAS 32
#define N_COLUNAS 64

enum {ORIGINAL, COPIA};

void troca(char *a, char *b);
void zera_matriz(char matriz[N_LINHAS][N_COLUNAS]);
void copia_matriz(char matriz_destino[N_LINHAS][N_COLUNAS], 
  char matriz_original[N_LINHAS][N_COLUNAS]
);
void imprime_matriz(char matriz[N_LINHAS][N_COLUNAS]);
void compara_posicoes(
  char matriz_frame[N_LINHAS][N_COLUNAS], 
  char matriz_copia[N_LINHAS][N_COLUNAS], 
  int i, int j
);
void atualiza_fisica(char matriz_frame[N_LINHAS][N_COLUNAS]);

int main() {
  char matriz_frame[N_LINHAS][N_COLUNAS];
  int n_frames, frame, x, y;
  char nova_particula;

  zera_matriz(matriz_frame);

  scanf("%d", &n_frames);

  int contador = 0;
  while (contador < n_frames) {
    int n_lido = scanf(" %d: %d %d %c", &frame, &x, &y, &nova_particula);
    
    if (n_lido == EOF) frame = n_frames;
    
    while (contador < frame) {
      contador++;
      printf("frame: %d\n", contador);
      imprime_matriz(matriz_frame);
      atualiza_fisica(matriz_frame);
    }
    
    if (n_lido != EOF) matriz_frame[y][x] = nova_particula;
  }

  return 0;
}

void troca(char *a, char *b) {
  char temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void zera_matriz(char matriz[N_LINHAS][N_COLUNAS]) {
  for (int i = 0; i < N_LINHAS; i++)
    for (int j = 0; j < N_COLUNAS; j++) 
      matriz[i][j] = AR;
}

void copia_matriz(char matriz_destino[N_LINHAS][N_COLUNAS], 
  char matriz_original[N_LINHAS][N_COLUNAS]
) {
  for (int i = 0; i < N_LINHAS; i++) 
    for (int j = 0; j < N_COLUNAS; j++) 
      matriz_destino[i][j] = matriz_original[i][j]; 
}

void imprime_matriz(char matriz[N_LINHAS][N_COLUNAS]) {
  for (int i = 0; i < N_LINHAS; i++) {
    for (int j = 0; j < N_COLUNAS; j++) printf("%c", matriz[i][j]);
    printf("\n");
  }
}

void compara_posicoes(
  char matriz_frame[N_LINHAS][N_COLUNAS], 
  char matriz_copia[N_LINHAS][N_COLUNAS], 
  int i, int j
) {
  // Para cada partícula (i, j), poderá-se fazer comparações para 
  // uma possível troca de posições. Como apenas Areia e Água 
  // fazem comparações, a comparação só será feita quando a 
  // partícula atual (i, j) for de algum desses tipos
  
  if (matriz_frame[i][j] == AREIA || matriz_frame[i][j] == AGUA) {
    // Os comparadores guardam os ponteiros para as posições de 
    // comparação de cada partícula (i, j). Eles são 5 posições 
    // definidas em ordem decrescente de prioridade de 0 a 4 
    // (primeiro índice da matriz). O segundo índice da matriz 
    // de comparadores indica em qual matriz o elemento está:
    //   * 0 para na matriz Original
    //   * 1 para na matriz Cópia

    char *comparador[5][2];

    char borda = CIMENTO;
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 2; j++)
        comparador[i][j] = &borda;

    // Caso a posição de comparação exceda as dimensões da matriz 
    // frame, ao comparador é atribuído um ponteiro para um cimento

    if (i != N_LINHAS - 1) {
      comparador[0][ORIGINAL] = &matriz_frame[i + 1][j];
      comparador[0][COPIA] = &matriz_copia[i + 1][j];
    }
    if (i != N_LINHAS - 1 && j != 0) {
      comparador[1][ORIGINAL] = &matriz_frame[i + 1][j - 1];
      comparador[1][COPIA] = &matriz_copia[i + 1][j - 1];
    }
    if (i != N_LINHAS - 1 && j != N_COLUNAS - 1) {
      comparador[2][ORIGINAL] = &matriz_frame[i + 1][j + 1];
      comparador[2][COPIA] = &matriz_copia[i + 1][j + 1];
    }
    if (j != 0) {
      comparador[3][ORIGINAL] = &matriz_frame[i][j - 1];
      comparador[3][COPIA] = &matriz_copia[i][j - 1];
    }
    if (j != N_COLUNAS - 1) {
      comparador[4][ORIGINAL] = &matriz_frame[i][j + 1];
      comparador[4][COPIA] = &matriz_copia[i][j + 1];
    }

    switch (matriz_frame[i][j]) {
      case AREIA:
        // Areia faz a comparação com os 3 primeiros comparadores
        // Se Água ou Ar for encontrado primeiro no comparador da matriz 
        // original, troca na matriz Copia com a mesma posição de comparação
        for (int k = 0; k < 3; k++) {
          if (*comparador[k][ORIGINAL] == AGUA || *comparador[k][ORIGINAL] == AR) {
            troca(comparador[k][COPIA], &matriz_copia[i][j]);
            break;
          }
        }
        break;
      case AGUA:
        // Água faz a comparação com todos os 5 comparadores
        // Se Ar for encontrado primeiro no comparador da matriz original,
        // troca na matriz Copia com a mesma posição de comparação
        for (int k = 0; k < 5; k++) {
          if (*comparador[k][ORIGINAL] == AR) {
            troca(comparador[k][COPIA], &matriz_copia[i][j]);
            break;
          }
        }
        break;
      // Ar pode ser movido, mas não faz comparações
      // Cimento não faz comparações, nem pode ser movido
    }
  }
}

void atualiza_fisica(char matriz_frame[N_LINHAS][N_COLUNAS]) {
  // Criação de uma cópia da matriz Frame onde serão feitas 
  // as alterações (na matriz Frame serão feitas as comparações)

  char matriz_copia[N_LINHAS][N_COLUNAS];

  copia_matriz(matriz_copia, matriz_frame);

  // Percorrendo a matriz do topo para baixo, da esquerda 
  // para a direita, em posições (i, j)

  for (int i = 0; i < N_LINHAS; i++) 
    for (int j = 0; j < N_COLUNAS; j++)
      compara_posicoes(matriz_frame, matriz_copia, i, j);    

  // Após as alterações na matriz Copia, 
  // elas são todas passadas para a matriz Frame,
  // que estará, por fim, com a física atualizada

  copia_matriz(matriz_frame, matriz_copia);
}