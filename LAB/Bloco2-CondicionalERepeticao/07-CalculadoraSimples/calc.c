#include <stdio.h>

int main(int argc, char *argv[]) {
  double a, b, resultado;
  char op;
  
  scanf("%lf %c %lf", &a, &op, &b);

  switch (op) {
    case '+':
      resultado = a + b;
      break;
    case '-':
      resultado = a - b;
      break;
    case '*':
      resultado = a * b;
      break;
    case '/':
      resultado = a / b;
      break;
    case '%':
      resultado = 100 * a / b; 
  }

  printf("%lf \n", resultado);

  return 0;
}
