#include <stdio.h>

int main() {
  int values[25];
  int counter[5] = {0, 0, 0, 0, 0};
  int copy[5];
  int greater = 0;
  int temp;

  for(int i = 0; i < 25; i++) {
    scanf("%i", &values[i]);
    switch (values[i]) {
      case 0:
        counter[0]++;
        break;
      case 1:
        counter[1]++;
        break;
      case 2:
        counter[2]++;
        break;
      case 3:
        counter[3]++;
        break;
      case 4:
        counter[4]++;
        break;
    }
  }
  

  for(int i = 0; i < 5; i++) {
    copy[i] = counter[i];
  }
  
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i <4; i++) {
      if (copy[i + 1] > copy[i]) {
        temp = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = temp;
      }
    }
  }

  for(int i = 0; i < 5; i++) {
    if(counter[i] == copy[0])
      greater = i;
  }

  for(int i = 0; i < 5; i++) {
    printf("%i: |", i);
    for(int j = 0; j < counter[i]; j++)
      printf("#");
    printf("\n");
  }
  
  for(int i = 0; i < 25; i++) {
    if(values[i] == greater)
    printf("%i\n", i);
  }

  return 0;
}
