#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
  double a, b;
  double result;

  scanf("%lf %lf", &a, &b);
  result = pow(a, b);

  printf("%.4f \n", result);

  return 0;
}
