#include <stdio.h>

int main(int argc, char *argv[]) {
  long long int a1, r, n;
  long long int an, sum;

  scanf("%lli %lli %lli", &a1, &r, &n);

  an = a1 + r * (n - 1);
  sum = ( (a1 + an) * n ) / 2;

  printf("%lli \n", an);
  printf("%lli \n", sum);

  return 0;
}
