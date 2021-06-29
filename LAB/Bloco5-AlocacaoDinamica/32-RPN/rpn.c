#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack {
  double *values;
  int top_index;
} Stack;

int main() {
  Stack stack;
  stack.values = NULL;
  stack.top_index = 0;

  while (true) {
    bool is_operand = false;
    char c = getchar();

    if (c == EOF || c == '\n') break;
    else if (c == ' ') continue;
    else if (c == '+' || c == '-' || c == '*' || c == '/') is_operand = true;
    else ungetc(c, stdin);

    if (is_operand) {
      double result;

      switch(c) {
        case '+':
          result = stack.values[stack.top_index - 2] + stack.values[stack.top_index - 1];
          break;
        case '-':
          result = stack.values[stack.top_index - 2] - stack.values[stack.top_index - 1];
          break;
        case '*':
          result = stack.values[stack.top_index - 2] * stack.values[stack.top_index - 1];
          break;
        case '/':
          result = stack.values[stack.top_index - 2] / stack.values[stack.top_index - 1];
          break;
    }

      stack.top_index--;
      stack.values = (double *) realloc(stack.values, stack.top_index * sizeof(double));
      stack.values[stack.top_index - 1] = result;
    } else {
      stack.top_index++;
      stack.values = (double *) realloc(stack.values, stack.top_index * sizeof(double));

      scanf("%lf", &stack.values[stack.top_index - 1]);
    }
  }

  printf("Resultado: %lf\n", stack.values[0]);

  free(stack.values);

  return 0;
}