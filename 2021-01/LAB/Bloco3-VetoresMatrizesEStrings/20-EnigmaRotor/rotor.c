#include <stdio.h>
#include <ctype.h>

void ler_rotores(int rotor[3][26]);
void rotacionar(int rot[3]);
char decodificar(char c, int rotor[3][26], int rot[3]);

int main() {
  int rotor[3][26];
  int rot[3] = {};

  ler_rotores(rotor);
  
  char c;
  while ((c = getchar()) != EOF)
    printf("%c", decodificar(c, rotor, rot));
  
  return 0;
} 

void ler_rotores(int rotor[3][26]) {
  scanf("%*[^\r\n]s"); 
  scanf("%*[\r\n]s");

  for (int i = 0; i < 3; i++) 
    for (int j = 0; j < 26; j++) 
      scanf("%i", &rotor[i][j]);
    
  scanf("%*[\r\n]s"); 
  scanf("%*[^\r\n]s"); 
  scanf("%*[\r\n]s");
}

void rotacionar(int rot[3]) {
  rot[0]++;
  for (int i = 0; i < 2; i++) {
    rot[i + 1] = rot[i] == 26 ? rot[i + 1] + 1 : rot[i + 1];
    rot[i] %= 26;
  }
  rot[2] %= 26;
}

char decodificar(char c, int rotor[3][26], int rot[3]) {
  if (isalpha(c)) {
    char alpha = isupper(c) ? 'A' : 'a';
    
    int arg1 = (c - alpha + rot[0]) % 26;
    int arg2 = (rotor[0][arg1] + rot[1]) % 26;
    int arg3 = (rotor[1][arg2] + rot[2]) % 26;

    rotacionar(rot);

    return alpha + rotor[2][arg3];
  } else return c;
}