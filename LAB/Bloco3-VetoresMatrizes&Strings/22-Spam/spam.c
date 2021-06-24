#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main() {
  bool isSpam = false;
  bool isLetter;

  int char_counter = 0;
  int forbidden_counter = 0;

  char empty[2] = {'\0'};
  char comparator[100];

  strcpy(comparator, empty);

  char forbidden[12][10] = {
    {"gratuito"},
    {"atencao"},
    {"urgente"},
    {"imediato"},
    {"zoombie"},
    {"oferta"},
    {"dinheiro"},
    {"renda"},
    {"fundo"},
    {"limitado"},
    {"ajuda"},
    {"SOS"}
  };

  while (!isSpam) {
    char c[2];
    c[1] = '\0';
    c[0] = getchar();

    char_counter++;

    if (c[0] == EOF) {
      break;
    } else if (isalpha(c[0])) {
      isLetter = true;
    } else if (c[0] == '\n' || c[0] == '\r') {
      isLetter = false;
      char_counter = 0;
    } else {
      isLetter = false;
    }

    if (isLetter) {
      strcat(comparator, c);
    } else {
      for (int i = 0; i < 12; i++) {
        char *ret = NULL;

        if (strlen(comparator) >= strlen(forbidden[i])) {
          ret = strstr(comparator, forbidden[i]);

          if (ret != NULL) {
            forbidden_counter++;
          }
        }
      }
      strcpy(comparator, empty);
    }

    if (char_counter > 76 || forbidden_counter >= 2)
      isSpam = true;
  }

  if (isSpam)
    printf("Spam\n");
  else 
    printf("Inbox\n");

  return 0;
}