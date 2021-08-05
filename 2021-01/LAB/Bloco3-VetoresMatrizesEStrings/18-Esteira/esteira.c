#include <stdio.h>
#include <stdbool.h>

enum {
  KEEP_GOING,
  OK,
  INFINITY_LOOP,
  ERROR
};

int main() {
  char factory[32][32];
  // pos[0]: current row
  // pos[1]: current column
  int pos[2] = {0, 0};
  char previous;
  
  bool not_junction = true;
  int status = KEEP_GOING;

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
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

  while (status == KEEP_GOING) {
    if (symb != '#')
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
        not_junction = true;
        pos[1]++;
        previous = '>';
        break;
      case '<':
        if (not_junction)
          factory[pos[0]][pos[1]] = '.';
        not_junction = true;
        pos[1]--;
        previous = '<';
        break;
      case '^':
        if (not_junction)
          factory[pos[0]][pos[1]] = '.';
        not_junction = true;
        pos[0]--;
        previous = '^';
        break;
      case 'v':
        if (not_junction)
          factory[pos[0]][pos[1]] = '.';
        not_junction = true;
        pos[0]++;
        previous = 'v';
        break;
      case '#':
        symb = '#';
        not_junction = false;
        break;
      case ']':
        status = OK;
        break;
      case '.':
        status = INFINITY_LOOP;
        break;
      default:
        status = ERROR;
        break;
    }
  }

  switch (status) {
    case OK:
      printf("Ok.\n");
      break;
    case INFINITY_LOOP:
      printf("Loop infinito.\n");
      break;
    case ERROR:
      printf("Falha na esteira.\n");
      break;
  }

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      printf("%c ", factory[i][j]);
    }
    printf("\n");
  }

  return 0;
}
