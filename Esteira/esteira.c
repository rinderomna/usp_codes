#include <stdio.h>

int main() {
  char factory[32][32];
  // pos[0]: actual row
  // pos[1]: actual column
  int pos[2] = {0, 0};
  char previous;
  
  char not_junction = 1;

  /*
   * status 0: keep going
   * status 1: Ok!
   * status 2: Infinity Loop
   * status 3: Error
   */
  int status = 0;

  for(int i = 0; i < 32; i++) {
    for(int j = 0; j < 32; j++) {
      factory[i][j] = getchar();
      if (factory[i][j] == '[') {
        pos[0] = i;
        pos[1] = j;
      }
      getchar();
    }
    scanf("%*[^\r\n]s"); 
    scanf("%*[\r\n]s"); 
  }

  char symb = factory[pos[0]][pos[1]];

  while(status == 0) {
    if(symb != '#')
      symb = factory[pos[0]][pos[1]];
    else
      symb = previous;

    switch (symb) {
      case '[':
        pos[1]++;
        previous = '[';
        break;
      case '>':
        if (not_junction)
          factory[pos[0]][pos[1]] = '.';
        not_junction = 1;
        pos[1]++;
        previous = '>';
        break;
      case '<':
        if (not_junction)
          factory[pos[0]][pos[1]] = '.';
        not_junction = 1;
        pos[1]--;
        previous = '<';
        break;
      case '^':
        if (not_junction)
          factory[pos[0]][pos[1]] = '.';
        not_junction = 1;
        pos[0]--;
        previous = '^';
        break;
      case 'v':
        if (not_junction)
          factory[pos[0]][pos[1]] = '.';
        not_junction = 1;
        pos[0]++;
        previous = 'v';
        break;
      case '#':
        symb = '#';
        not_junction = 0;
        break;
      case ']':
        status = 1;
        break;
      case '.':
        status = 2;
        break;
      default:
        status = 3;
        break;
    }
  }

  switch (status) {
    case 1:
      printf("Ok.\n");
      break;
    case 2:
      printf("Loop infinito.\n");
      break;
    case 3:
      printf("Falha na esteira.\n");
      break;
  }

  for(int i = 0; i < 32; i++) {
    for(int j = 0; j < 32; j++) {
      printf("%c ", factory[i][j]);
    }
    printf("\n");
  }

  return 0;
}
