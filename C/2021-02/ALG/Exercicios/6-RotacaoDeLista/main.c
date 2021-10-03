/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|----------| Exercicio 06: Rotacao de Lista |----------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>

#include "generic_linked_list.h"

/* |print_list|
 *  Prints inline the numbers in specified list separated by space.
 */
void print_list(list_t *l);

int main() {
    int n_test_cases;
    scanf("%d", &n_test_cases);

    for (int i = 0; i < n_test_cases; i++) {
        list_t *l = create_list(sizeof(int));

        int cur_list_size;
        scanf("%d", &cur_list_size);

        int n_rotations;
        scanf("%d", &n_rotations);

        for (int j = 0; j < cur_list_size; j++) {
            int num;
            scanf("%d", &num);

            append_to_list(l, &num);
        }

        right_rotate_list(l, n_rotations);

        print_list(l);
        
        if (i < n_test_cases - 1) printf("\n");

        destroy_list(&l);
    }

    return 0;
}

void print_list(list_t *l) {
    int list_size = get_list_size(l);

    for (int i = 0; i < list_size; i++) {
        int num;
        access_element(l, i, &num);

        printf("%d", num);

        if (i < list_size - 1) printf(" ");
    }
}