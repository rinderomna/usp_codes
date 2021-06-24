#include <stdio.h>

int main() {
  // Values vector stores the appearence of each color:
    // Its elements are either 0, 1, 2, 3 or 4 (the colors)  
  int values[25];

  // Counter vector counts the frequencies of each color:
    // Each color is represented by an index (0, 1, 2, 3 or 4) 
  int counter[5] = {0, 0, 0, 0, 0};
 
  // Read values vector from entry and count frequencies
  for (int i = 0; i < 25; i++) {
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
  
  // Make a copy of counter vector
  int copy[5];
  for (int i = 0; i < 5; i++) {
    copy[i] = counter[i];
  }
  
  // Sort the copy array in descending order
  int temp;
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 4; i++) {
      if (copy[i + 1] > copy[i]) {
        temp = copy[i];
        copy[i] = copy[i + 1];
        copy[i + 1] = temp;
      }
    }
  }
  
  // Find the most frequent (greater)
  int greater = 0;
  for (int i = 0; i < 5; i++) {
    if (counter[i] == copy[0])
      greater = i;
  }
  
  // Print the histogram
  for (int i = 0; i < 5; i++) {
    printf("%i: |", i);
    for (int j = 0; j < counter[i]; j++)
      printf("#");
    printf("\n");
  }
  
  // Print the positions where the greater appears
  for (int i = 0; i < 25; i++) {
    if (values[i] == greater)
    printf("%i\n", i);
  }

  return 0;
}