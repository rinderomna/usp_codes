#include <stdio.h>
#include <stdbool.h>

#define AR ' '
#define AGUA '~'
#define AREIA '#'
#define CIMENTO '@'

#define LINHAS 32
#define COLUNAS 64

enum {ORIGINAL, COPIA};

void troca(char *a, char *b);
void zera_matriz(char Matriz[LINHAS][COLUNAS]);
void copia_matriz(char Matriz_Destino[LINHAS][COLUNAS], char Matriz_Original[LINHAS][COLUNAS]);
void imprime_matriz(char Matriz[LINHAS][COLUNAS]);
void atualiza_fisica(char Matriz_Frame[LINHAS][COLUNAS]);

int main() {
  char Matriz_Frame[LINHAS][COLUNAS];
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
      contador++;
      printf("frame: %d\n", contador);
      imprime_matriz(Matriz_Frame);
      atualiza_fisica(Matriz_Frame);
    }
    
    if (n_lido != EOF)
      Matriz_Frame[y][x] = Nova_Particula;
  }

  return 0;
}

void troca(char *a, char *b) {
  char aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void zera_matriz(char Matriz[LINHAS][COLUNAS]) {
  for (int i = 0; i < LINHAS; i++)
    for (int j = 0; j < COLUNAS; j++) 
      Matriz[i][j] = AR;
}

void copia_matriz(char Matriz_Destino[LINHAS][COLUNAS], char Matriz_Original[LINHAS][COLUNAS]) {
  for (int i = 0; i < LINHAS; i++) 
    for (int j = 0; j < COLUNAS; j++) 
      Matriz_Destino[i][j] = Matriz_Original[i][j]; 
}

void imprime_matriz(char Matriz[LINHAS][COLUNAS]) {
  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) 
      printf("%c", Matriz[i][j]);
    printf("\n");
  }
}

void atualiza_fisica(char Matriz_Frame[LINHAS][COLUNAS]) {
  // Criação de uma cópia da Matriz Frame onde serão feitas as alterações
  // (Na Matriz Frame serão feitas as comparações)

  char Matriz_Copia[LINHAS][COLUNAS];

  copia_matriz(Matriz_Copia, Matriz_Frame);

  // Percorrendo a matriz do topo para baixo, da esquerda para a direita, em posições (i, j)

  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      // Para cada partícula (i, j), poderá-se fazer comparações para uma possível troca de posições.
      // Como apenas Areia e Água fazem comparações, a comparação só será feita quando a
      // partícula atual (i, j) for de algum desses tipos
      
      if (Matriz_Frame[i][j] == AREIA || Matriz_Frame[i][j] == AGUA) {
        // Os Comparadores guardam os ponteiros para as posições de comparação de cada partícula (i, j)
        // Eles são 5 posições definidas em ordem decrescente de prioridade de 0 a 4 (primeiro índice da matriz)
        // O segundo índice da matriz de comparadores indica em qual matriz o elemento está (enum definido):
        //   * 0 para na Matriz Original
        //   * 1 para na Matriz Cópia

        char *Comparador[5][2];
        char Borda = CIMENTO;

        // Caso a posição de comparação exceda as dimensões da Matriz Frame,
        // ao comparador é atribuído um ponteiro para um cimento

        Comparador[0][ORIGINAL] = (i == LINHAS - 1) ? &Borda : &Matriz_Frame[i + 1][j];
        Comparador[1][ORIGINAL] = (i == LINHAS - 1 || j == 0) ? &Borda : &Matriz_Frame[i + 1][j - 1];
        Comparador[2][ORIGINAL] = (i == LINHAS - 1 || j == COLUNAS - 1) ? &Borda : &Matriz_Frame[i + 1][j + 1];
        Comparador[3][ORIGINAL] = (j == 0) ? &Borda : &Matriz_Frame[i][j - 1];
        Comparador[4][ORIGINAL] = (j == COLUNAS - 1) ? &Borda : &Matriz_Frame[i][j + 1];

        Comparador[0][COPIA] = (i == LINHAS - 1) ? &Borda : &Matriz_Copia[i + 1][j];
        Comparador[1][COPIA] = (i == LINHAS - 1 || j == 0) ? &Borda : &Matriz_Copia[i + 1][j - 1];
        Comparador[2][COPIA] = (i == LINHAS - 1 || j == COLUNAS - 1) ? &Borda : &Matriz_Copia[i + 1][j + 1];
        Comparador[3][COPIA] = (j == 0) ? &Borda : &Matriz_Copia[i][j - 1];
        Comparador[4][COPIA] = (j == COLUNAS - 1) ? &Borda : &Matriz_Copia[i][j + 1];

        switch (Matriz_Frame[i][j]) {
          case AREIA:
            // Areia faz a comparação com os 3 primeiros comparadores
            // Se Água ou Ar for encontrado primeiro no comparador da Matriz Original,
            // troca na Matriz Copia com a mesma posição de comparação
            for (int k = 0; k < 3; k++) {
              if (*Comparador[k][ORIGINAL] == AGUA || *Comparador[k][ORIGINAL] == AR) {
                troca(Comparador[k][COPIA], &Matriz_Copia[i][j]);
                break;
              }
            }
            break;
          case AGUA:
            // Água faz a comparação com todos os 5 comparadores
            // Se Ar for encontrado primeiro no comparador da Matriz Original,
            // troca na Matriz Copia com a mesma posição de comparação
            for (int k = 0; k < 5; k++) {
              if (*Comparador[k][ORIGINAL] == AR) {
                troca(Comparador[k][COPIA], &Matriz_Copia[i][j]);
                break;
              }
            }
            break;
          // Ar pode ser movido, mas não faz comparações
          // Cimento não faz comparações, nem pode ser movido
        }
      }
    }
  }

  // Após as alterações na Matriz Copia, 
  // elas são todas passadas para a Matriz Frame,
  // que estará, por fim, com a física atualizada

  copia_matriz(Matriz_Frame, Matriz_Copia);
}
