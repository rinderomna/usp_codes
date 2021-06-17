#include <stdio.h>

#define BOOL char
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
  long long int x1[2], w1[2];
  long long int x2[2], w2[2];
  long long int intlim[2][2];

  BOOL hit[2];

  scanf("%lli %lli %lli %lli", &x1[0], &x1[1], &w1[0], &w1[1]); 
  scanf("%lli %lli %lli %lli", &x2[0], &x2[1], &w2[0], &w2[1]);
  
  if (x1[0] <= x2[0]) {
    if (x1[0] + w1[0] < x2[0]) {
      hit[0] = FALSE;
    } else if (x2[0] <= x1[0] + w1[0] && x1[0] + w1[0] <= x2[0] + w2[0]) {
      hit[0] = TRUE;
      intlim[0][0] = x2[0];
      intlim[1][0] = x1[0] + w1[0] - x2[0];
    } else {
      hit[0] = TRUE;
      intlim[0][0] = x2[0];
      intlim[1][0] = w2[0];
    }                               
  } else {
    if (x2[0] + w2[0] < x1[0]) {
      hit[0] = FALSE;
    } else if (x2[0] <= x2[0] + w2[0] && x2[0] + w2[0] <= x1[0] + w1[0]) {
      hit[0] = TRUE;
      intlim[0][0] = x1[0];
      intlim[1][0] = x2[0] + w2[0] - x1[0];
    } else {
      hit[0] = TRUE;
      intlim[0][0] = x1[0];
      intlim[1][0] = w1[0];
    }
  }

//----------------------------------------------

  if (x1[1] <= x2[1]) {
    if (x1[1] + w1[1] < x2[1]) {
      hit[1] = FALSE;
    } else if (x2[1] <= x1[1] + w1[1] && x1[1] + w1[1] <= x2[1] + w2[1]) {
      hit[1] = TRUE;
      intlim[0][1] = x2[1];
      intlim[1][1] = x1[1] + w1[1] - x2[1];
    } else {
      hit[1] = TRUE;
      intlim[0][1] = x2[1];
      intlim[1][1] = w2[1];
    }                               
  } else {
    if (x2[1] + w2[1] < x1[1]) {
      hit[1] = FALSE;
    } else if (x2[1] <= x2[1] + w2[1] && x2[1] + w2[1] <= x1[1] + w1[1]) {
      hit[1] = TRUE;
      intlim[0][1] = x1[1];
      intlim[1][1] = x2[1] + w2[1] - x1[1];
    } else {
      hit[1] = TRUE;
      intlim[0][1] = x1[1];
      intlim[1][1] = w1[1];
    }
  }

  if (hit[0] && hit[1]) {
    printf("HIT: %lli %lli %lli %lli\n", intlim[0][0], intlim[0][1], intlim[1][0], intlim[1][1]);
  } else {
    printf("MISS\n");
  }

  return 0;
}
