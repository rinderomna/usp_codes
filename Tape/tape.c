#include <stdio.h>

enum {
  HLT, ADD, MUL, CLT, CEQ, JMP, JEQ, CPY, PUT, PTN
};

int main() {
  int tape[512] = {};
  int cur_idx = 0;

  for(int i = 0; i < 512; i++) {
    scanf("%d", &tape[i]);
  }

  printf("Saida do programa:\n");

  int arg1, arg2, arg3;
  while(tape[cur_idx] != HLT) {
    switch(tape[cur_idx]) {
      case ADD:
        arg1 = tape[cur_idx + 1];
        arg2 = tape[cur_idx + 2];
        arg3 = tape[cur_idx + 3];

        tape[arg3] = tape[arg1] + tape[arg2];
        cur_idx += 4;
        break;
      case MUL:
        arg1 = tape[cur_idx + 1];
        arg2 = tape[cur_idx + 2];
        arg3 = tape[cur_idx + 3];

        tape[arg3] = tape[arg1] * tape[arg2];
        cur_idx += 4;
        break;
      case CLT:
        arg1 = tape[cur_idx + 1];
        arg2 = tape[cur_idx + 2];
        arg3 = tape[cur_idx + 3];

        tape[arg3] = (tape[arg1] < tape[arg2]);
        cur_idx += 4;
        break;
      case CEQ:
        arg1 = tape[cur_idx + 1];
        arg2 = tape[cur_idx + 2];
        arg3 = tape[cur_idx + 3];

        tape[arg3] = (tape[arg1] == tape[arg2]);
        cur_idx += 4;
        break;
      case JMP:
        arg1 = tape[cur_idx + 1];

        cur_idx = tape[arg1];
        break;
      case JEQ:
        arg1 = tape[cur_idx + 1];
        arg2 = tape[cur_idx + 2];

        if(tape[arg1])
          cur_idx = tape[arg2];
        else
          cur_idx += 3;
        break;
      case CPY:
        arg1 = tape[cur_idx + 1];
        arg2 = tape[cur_idx + 2];

        tape[arg2] = tape[arg1];
        cur_idx += 3;
        break;
      case PUT: 
        arg1 = tape[cur_idx + 1];
        
        printf("%c", tape[arg1]);
        cur_idx += 2;
        break;
      case PTN: 
        arg1 = tape[cur_idx + 1];

        printf("%d", tape[arg1]);
        cur_idx += 2;
        break;
      default:
        break;
    }
  }

  printf("\n");
  printf("Estado final da fita:\n");

  for(int i = 0; i < 512; i++) {
    printf("%d\n", tape[i]);
  }

  return 0;
}
