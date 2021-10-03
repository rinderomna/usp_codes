/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|--------| Exercicio 02: Crivo de Eratostenes |--------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

typedef int bool;
#define FALSE 0
#define TRUE 1

int main() {
    list_t *list;

    list = create_list();

    for (int i = 2; i <= 10000; i++) {
        append_to_list(list, i);
    }

    int n_primes;
    int prime_factor;

    scanf(" %d", &n_primes);

    bool was_any_erased = TRUE;

    for (int index = 0; was_any_erased; index++) {
        was_any_erased = FALSE;

        access_datum(list, index, &prime_factor);

        for (int i = index + 1; i < get_list_size(list); i++) {
            int cur_number;
            access_datum(list, i, &cur_number);

            if (cur_number % prime_factor == 0) {
                remove_from_list(list, i);
                was_any_erased = TRUE;
            }
        }
    }

    for (int i = 0; i < n_primes; i++) {
        int index;
        scanf(" %d", &index);

        index--;

        int prime;
        access_datum(list, index, &prime);
        printf("%d", prime);

        if (i < n_primes - 1) printf(" ");
    }

    destroy_list(&list);

    return EXIT_SUCCESS;
}