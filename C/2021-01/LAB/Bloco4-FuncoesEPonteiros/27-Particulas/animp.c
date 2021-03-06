#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define AR ' '
#define AGUA '~'
#define AREIA '#'
#define CIMENTO '@'

#define N_LINHAS 32
#define N_COLUNAS 64

enum {ORIGINAL, COPIA};

void msleep(long msec){
  struct timespec ts;

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  nanosleep(&ts, &ts);
}

void troca(char *a, char *b);
void zera_matriz(char matriz[N_LINHAS][N_COLUNAS]);
void copia_matriz(char matriz_destino[N_LINHAS][N_COLUNAS], 
  char matriz_original[N_LINHAS][N_COLUNAS]
);
void mostrar_particula(char particula);
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
      system("clear");
      printf("frame: %d\n", contador);
      imprime_matriz(matriz_frame);
      atualiza_fisica(matriz_frame);
      msleep(250);
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

void mostrar_particula(char particula) {
    switch (particula) {
        case CIMENTO:
            printf("\033[1;31m");
            break;
        case AREIA:
            printf("\033[0;33m");
            break;
        case AR:
            printf("\033[2;34m");
            break;
        case AGUA:
            printf("\033[0;34m");
            break;
    }
    printf("%c\033[0m", particula);
}

void imprime_matriz(char matriz[N_LINHAS][N_COLUNAS]) {

    for (int i = 0; i < 66; i++) {
        mostrar_particula(CIMENTO);
    }
    printf("\n");

    for (int i = 0; i < N_LINHAS; i++) {
        mostrar_particula(CIMENTO);
        for (int j = 0; j < N_COLUNAS; j++) {
            mostrar_particula(matriz[i][j]);
        }
        mostrar_particula(CIMENTO);
        printf("\n");
    } 

    for (int i = 0; i < 66; i++) {
        mostrar_particula(CIMENTO);
    }
    printf("\n");
}

void compara_posicoes(
  char matriz_frame[N_LINHAS][N_COLUNAS], 
  char matriz_copia[N_LINHAS][N_COLUNAS], 
  int i, int j
) {
  // Para cada part??cula (i, j), poder??-se fazer compara????es para 
  // uma poss??vel troca de posi????es. Como apenas Areia e ??gua 
  // fazem compara????es, a compara????o s?? ser?? feita quando a 
  // part??cula atual (i, j) for de algum desses tipos
  
  if (matriz_frame[i][j] == AREIA || matriz_frame[i][j] == AGUA) {
    // Os comparadores guardam os ponteiros para as posi????es de 
    // compara????o de cada part??cula (i, j). Eles s??o 5 posi????es 
    // definidas em ordem decrescente de prioridade de 0 a 4 
    // (primeiro ??ndice da matriz). O segundo ??ndice da matriz 
    // de comparadores indica em qual matriz o elemento est??:
    //   * 0 para na matriz Original
    //   * 1 para na matriz C??pia

    char *comparador[5][2];

    char borda = CIMENTO;
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 2; j++)
        comparador[i][j] = &borda;

    // Caso a posi????o de compara????o exceda as dimens??es da matriz 
    // frame, ao comparador ?? atribu??do um ponteiro para um cimento

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
        // Areia faz a compara????o com os 3 primeiros comparadores
        // Se ??gua ou Ar for encontrado primeiro no comparador da matriz 
        // original, troca na matriz Copia com a mesma posi????o de compara????o
        for (int k = 0; k < 3; k++) {
          if (*comparador[k][ORIGINAL] == AGUA || *comparador[k][ORIGINAL] == AR) {
            troca(comparador[k][COPIA], &matriz_copia[i][j]);
            break;
          }
        }
        break;
      case AGUA:
        // ??gua faz a compara????o com todos os 5 comparadores
        // Se Ar for encontrado primeiro no comparador da matriz original,
        // troca na matriz Copia com a mesma posi????o de compara????o
        for (int k = 0; k < 5; k++) {
          if (*comparador[k][ORIGINAL] == AR) {
            troca(comparador[k][COPIA], &matriz_copia[i][j]);
            break;
          }
        }
        break;
      // Ar pode ser movido, mas n??o faz compara????es
      // Cimento n??o faz compara????es, nem pode ser movido
    }
  }
}

void atualiza_fisica(char matriz_frame[N_LINHAS][N_COLUNAS]) {
  // Cria????o de uma c??pia da matriz Frame onde ser??o feitas 
  // as altera????es (na matriz Frame ser??o feitas as compara????es)

  char matriz_copia[N_LINHAS][N_COLUNAS];

  copia_matriz(matriz_copia, matriz_frame);

  // Percorrendo a matriz do topo para baixo, da esquerda 
  // para a direita, em posi????es (i, j)

  for (int i = 0; i < N_LINHAS; i++) 
    for (int j = 0; j < N_COLUNAS; j++)
      compara_posicoes(matriz_frame, matriz_copia, i, j);    

  // Ap??s as altera????es na matriz Copia, 
  // elas s??o todas passadas para a matriz Frame,
  // que estar??, por fim, com a f??sica atualizada

  copia_matriz(matriz_frame, matriz_copia);
}