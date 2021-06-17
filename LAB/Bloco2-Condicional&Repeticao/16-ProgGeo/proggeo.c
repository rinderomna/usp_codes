#include <stdio.h>

int main(int argc, char *argv[]) {
  double a1, an, sn, q, qn = 1.0, qnm1 = 1.0;
  int n;

  scanf("%lf %lf %i", &a1, &q, &n);

  for (int i = 0; i < n; i++) {
    qn *= q;
  }

  for (int i = 0; i < n - 1; i++) {
    qnm1 *= q;
  }
  
  an = a1 * qnm1;
  
  if (q == 1.0) {
    sn = n * a1;
  } else {
    sn = a1 * ((qn - 1.0)/(q - 1));
  }

  printf("%.2f \n%.2f \n", an, sn);

  return 0;
}
