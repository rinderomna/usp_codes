#include <stdio.h>
#include <ctype.h>

int main() {
  int rotor[3][26];
  char c;
  int rot0 = 0;
  int rot1 = 0;
  int rot2 = 0;

  scanf("%*[^\r\n]s"); // Ignora tudo até o final da linha
  scanf("%*[\r\n]s"); // Ignora o pula linha

  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 26; j++) {
      scanf("%i", &rotor[i][j]);
    } 
  }

  scanf("%*[\r\n]s"); // Ignora o pula linha
  scanf("%*[^\r\n]s"); // Ignora tudo até o final da linha
  scanf("%*[\r\n]s"); // Ignora o pula linha
  
  while(1) {
    c = getchar();
    if(c == EOF)
      break;
    if (isupper(c)) {
      printf("%c", rotor[2][(rotor[1][(rotor[0][(c - 65 + rot0) % 26] + rot1) % 26] + rot2) % 26]);
    } else if (islower(c)) {
      printf("%c", rotor[2][(rotor[1][(rotor[0][(c - 97 + rot0) % 26] + rot1) % 26] + rot2) % 26]);
    } else {
      printf("%c", c);
    }
    
    rot0++;
    if (rot0 % 26 == 0) {
      rot1++;
      rot0 = 0;
    }
    if (rot1 % 26 == 0) {
      rot2++;
      rot1 = 0;
    }
    if (rot2 % 26 == 0) {
      rot2 = 0;
    }
  } 
  
  return 0;
}
