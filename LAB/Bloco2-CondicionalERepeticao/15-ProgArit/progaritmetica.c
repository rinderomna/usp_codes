#include <stdio.h>

int main(int argc, char *argv[]) {
  long long int a1, r, n;
  long long int an, sum;

  scanf("%lli %lli %lli", &a1, &r, &n);

  an = a1;
  sum = a1;

  for (int i = 1; i < n; i++) {
    an = an + r;
    sum = sum + an;
  }

  printf("%lli \n", an);
  printf("%lli \n", sum);

  return 0;
}
