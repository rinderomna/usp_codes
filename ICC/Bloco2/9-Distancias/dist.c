#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double diagonal(double x_i, double x_f, double y_i, double y_f); 
double contorno(double x_i, double x_f, double y_i, double y_f); 
double dist_euclides(int ponto_i[3], int ponto_f[3]);
double dist_hermann(int ponto_i[3], int ponto_f[3]);
void error(void);

int main() {
  int N;
  double hermann = 0, euclides = 0, diferenca;
  int baldio_ctr = 0;
  int residencial_ctr = 0;
  int parque_ctr = 0;
  
  scanf("%d", &N);

  if (N <= 0)
    error();

  int pontos[N][3];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      scanf("%d", &pontos[i][j]);

      if (j == 2 && (pontos[i][j] > 1 || pontos[i][j] < -1))
        error();
    }
  }

  for(int i = 0; i < N; i++) {
    int final;

    if (i == N - 1) 
      final = 0;
    else
      final = i + 1;
  
    if (pontos[i][2] == -1)
      baldio_ctr++;
    else if (pontos[i][2] == 0)
      residencial_ctr++;
    else
      parque_ctr++;

    euclides += dist_euclides(pontos[i], pontos[final]);
    hermann += dist_hermann(pontos[i], pontos[final]);
  }

  diferenca = sqrt(pow(euclides - hermann, 2));

  printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n", baldio_ctr, residencial_ctr, parque_ctr);
  printf("A diferenca total de distancia percorrida foi de %.2f metros.\n", diferenca);
  
  return 0;
}

double diagonal(double x_i, double x_f, double y_i, double y_f) {
    double distancia;
    distancia = sqrt(pow(x_f - x_i, 2) + pow(y_f - y_i, 2));

    return distancia;
}

double contorno(double x_i, double x_f, double y_i, double y_f) {
  double distancia;
  distancia = sqrt(pow(x_f - x_i, 2)) + sqrt(pow(y_f - y_i, 2));

  return distancia;
}

double dist_euclides(int ponto_i[3], int ponto_f[3]) {
  double distancia;
  double x_i = (double) ponto_i[0];
  double x_f = (double) ponto_f[0];
  double y_i = (double) ponto_i[1];
  double y_f = (double) ponto_f[1];

  if (ponto_i[2] == 0)
    distancia = contorno(x_i, x_f, y_i, y_f);
  else
    distancia = diagonal(x_i, x_f, y_i, y_f);

  return distancia;
}

double dist_hermann(int ponto_i[3], int ponto_f[3]) {
  double distancia;
  double x_i = (double) ponto_i[0];
  double x_f = (double) ponto_f[0];
  double y_i = (double) ponto_i[1];
  double y_f = (double) ponto_f[1];

  if (ponto_i[2] == -1)
    distancia = diagonal(x_i, x_f, y_i, y_f);
  else
    distancia = contorno(x_i, x_f, y_i, y_f);

  return distancia;
}

void error(void) {
  printf("Falha no processamento dos dados.\n");
  exit(0);
}
