#include <stdio.h>

int main(int argc, char *argv[]) {
  unsigned int number;
  unsigned int counter = 0;
  int dividers[3] = {11, 13, 19};
  int factors[3];
  char *answer = "";

  scanf("%i", &number);

  for (int i = 0; i < 3; i++) {
    if (number % dividers[i] == 0) {
      factors[counter] = dividers[i];
      counter++;
    }
  }

  switch (counter) {
    case 0: 
      printf("%i \n", number);
      break;
    case 1:
      switch (factors[0]) {
        case 11:
          answer = "BaBa\n";
          break;
        case 13:
          answer = "BaDum\n";
          break;
        case 19:
          answer = "BaTss\n";
          break;
      }
      break;
    case 2:
      switch (factors[0]*factors[1]) {
        case 11*13:
          answer = "BaDumDum\n";
          break;
        case 11*19:
          answer = "BaDumTss\n";
          break;
        case 13*19:
          answer = "DumDumTss\n";
          break;
      }
      break;
    case 3:
      answer = "BaDumTssTss\n";
      break;
  }

  if (counter != 0) {
    printf("%s", answer);
  }

  return 0;
}

