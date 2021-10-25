/* SCC0201 - Introducao a Ciencia de Computacao II (2021/02)
 * Exercicio 0.0 - Revisando Vetores e Funcoes
 *
 * Helio Nogueira Cardoso
 * N°USP: 10310227
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct numberlist_ {
  int n;
  int *numbers;
  int n_unique_numbers;
  int *unique_numbers;
  int *unique_numbers_frequencies;
} numberlist_t;

bool is_in_list(int number, numberlist_t numberlist, int *position);
void read_numberlist(numberlist_t *numberlist);
void free_numberlist(numberlist_t *numberlist);
void print_numberlist_frequencies(numberlist_t numberlist);

int main() {
  numberlist_t numberlist;
  
  read_numberlist(&numberlist);
  print_numberlist_frequencies(numberlist);
  free_numberlist(&numberlist);

  return 0;
}

bool is_in_list(int number, numberlist_t numberlist, int *position) {
  bool is_in_list = false;

  for (int i = 0; i < numberlist.n; i++) {
    if (number == numberlist.numbers[i]) {
      is_in_list = true;
      *position = i;
      return true;
    }
  }

  return is_in_list;
}

void read_numberlist(numberlist_t *numberlist) {
  char c;
  int new_number;
    
  numberlist->n = 0;
  numberlist->numbers = NULL;
  numberlist->n_unique_numbers = 0;
  numberlist->unique_numbers = NULL;
  numberlist->unique_numbers_frequencies = NULL;
  
  do {
    c = getchar();

    if (c != EOF && c != ' ') {
      ungetc(c, stdin);

      scanf(" %d", &new_number);

      int position = -1;

      if (is_in_list(new_number, *numberlist, &position)) {
        numberlist->unique_numbers_frequencies[position]++;
      } else {
        numberlist->unique_numbers = (int *) realloc(
          numberlist->unique_numbers, 
          ++(numberlist->n_unique_numbers) * sizeof(int)
        );

        numberlist->unique_numbers_frequencies = (int *) realloc(
          numberlist->unique_numbers_frequencies, 
          numberlist->n_unique_numbers * sizeof(int)
        );

        numberlist->unique_numbers[numberlist->n_unique_numbers - 1] = new_number;
        numberlist->unique_numbers_frequencies[numberlist->n_unique_numbers - 1] = 1;
      }

      numberlist->numbers = (int *) realloc(
        numberlist->numbers, 
        ++(numberlist->n) * sizeof(int)
      );
      
      numberlist->numbers[numberlist->n - 1] = new_number;
    }
  } while (c != EOF);
}

void free_numberlist(numberlist_t *numberlist) {
  free(numberlist->numbers);
  free(numberlist->unique_numbers);
  free(numberlist->unique_numbers_frequencies);
}

void print_numberlist_frequencies(numberlist_t numberlist) {
  for (int i = 0; i < numberlist.n_unique_numbers; i++) {
    printf("%d (%d)", numberlist.unique_numbers[i], numberlist.unique_numbers_frequencies[i]);
    if (i < numberlist.n_unique_numbers - 1) {
      printf("\n");
    }
  }
}