#include <stdio.h>
#include <stdbool.h>

int main() {
  char board[3][3];
  char filled = true;
  // N means no one won (yet)
  char winner = 'N';
  char candidate;

  // Read the board and check whether it is filled or not
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      scanf("%c", &board[i][j]);
      if (board[i][j] == '-')
        filled = false;
      scanf("%*[ \r\n]s");
    }
  }

  // Check rows
  for (int row = 0; row < 3; row++) {
    candidate = board[row][0];
    if (candidate != '-')
      if (board[row][1] == candidate && board[row][2] == candidate)
        winner = candidate;
  }

  // Check columns
  for (int column = 0; column < 3; column++) {
    candidate = board[0][column];
    if (candidate != '-')
      if (board[1][column] == candidate && board[2][column] == candidate)
        winner = candidate;
  }
  
  // Check diagonals
  candidate = board[1][1];

  if (candidate != '-') {
    if (board[0][0] == candidate && board[2][2] == candidate)
      winner = candidate;
    else if (board[0][2] == candidate && board[2][0] == candidate)
      winner = candidate;
  }

  // Determine match state
  if (winner == 'N')
    if (filled)
      printf("empate\n");
    else
      printf("em jogo\n");
  else
    printf("%c ganhou\n", winner);

  return 0;
}
