#include <stdio.h>

int main() {
  char board[3][3];
  char filled = 1;
  // n means no one won (yet)
  char winner = 'n';
  char candidate;

  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      scanf("%c", &board[i][j]);
      if(board[i][j] == '-')
        filled = 0;
      scanf("%*[ \r\n]s");
    }
  }

  for(int row = 0; row < 3; row++) {
    candidate = board[row][0];
    if(candidate != '-')
      if(board[row][1] == candidate && board[row][2] == candidate)
        winner = candidate;
  }

  for(int column = 0; column < 3; column++) {
    candidate = board[0][column];
    if(candidate != '-')
      if(board[1][column] == candidate && board[2][column] == candidate)
        winner = candidate;
  }
  
  candidate = board[1][1];

  if(candidate != '-') {
    if(board[0][0] == candidate && board[2][2] == candidate)
      winner = candidate;
    else if(board[0][2] == candidate && board[2][0] == candidate)
      winner = candidate;
  }

  if(winner == 'n')
    if(filled)
      printf("empate\n");
    else
      printf("em jogo\n");
  else
    printf("%c ganhou\n", winner);

  return 0;
}
