/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|                  [Segundo Semestre de 2021]          |
 *|                                                      |
 *|--------| Exercicio 03: Substituir Palavras |---------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "words.h"

/* |string_to_list|
 * Converts a string to a char list.
 */
list_t *string_to_list(char *str);

/* |print_list|
 * Prints the char list, just as a string.
 */
void print_list(list_t *list);

int main() {
    int has_EOF = 0;

    while (!has_EOF) {
        char *phrase = read_line(stdin, &has_EOF);
        char *needle = read_line(stdin, &has_EOF);
        char *substitute = read_line(stdin, &has_EOF);

        int needle_len = strlen(needle);
        int substitute_len = strlen(substitute);

        int n_occurrences = 0;
        int *occur_indexes = occurrence_indexes(needle, phrase, &n_occurrences);

        list_t *str_in_list = string_to_list(phrase);

        for (int i = 0; i < n_occurrences; i++) {
            int insertion_index = occur_indexes[i] + i * (substitute_len - needle_len);

            for (int j = substitute_len - 1; j >= 0; j--) {
                insert_in_list(str_in_list, substitute[j], insertion_index);
            }
        }

        print_list(str_in_list);

        if (!has_EOF) printf("\n");

        destroy_list(&str_in_list);
        free(occur_indexes);
        free(phrase);
        free(needle);
        free(substitute);
    }

    return EXIT_SUCCESS;
}

list_t *string_to_list(char *str) {
    list_t *l = create_list();

    for (int i = 0; i < (int)strlen(str); i++) {
        append_to_list(l, str[i]);
    }

    return l;
}

void print_list(list_t *list) {
    int list_size = get_list_size(list);

    for (int i = 0; i < list_size; i++) {
        char c;

        access_datum(list, i, &c);

        printf("%c", c);
    }
}