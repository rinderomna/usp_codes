#include <stdio.h>

int main(int argc, char *argv[]) {
  char keys[49];
  int n;

  for (int i = 0 ; i < 49; i++) {
    scanf("%c", &keys[i]);
    getchar();
  }

  scanf("%i", &n);

  for (int i = 0; i < n; i++) {
    int aux;
    scanf("%i", &aux);
    
    switch (keys[aux]) {
      case '_':
        printf(" ");
        break;
      case 'E':
        printf("\n");
        break;
      default:
        printf("%c", keys[aux]);
        break;
    }
  }

  return 0;
}
