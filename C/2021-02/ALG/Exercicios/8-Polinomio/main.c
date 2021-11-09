/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|------------| Exercicio 08: Polinômios |--------------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>
#include <stdlib.h>

#include "generic_linked_list.h"
#include "str.h"

// Sums 2 polynomials,destroying them and allocating a new one to return.
list_t *pol_sum(list_t *pol1, list_t *pol2);

// Reads n_pols polynomials from stdin, sums them (and destroys) and returns the sum.
list_t *read_and_sum_n_pols(int n_pols);

// Prints the polynomial in specified format.
// Also receives a boolean to indicate whether to add a new line at the end or not.
void print_pol(list_t *pol, int add_new_line);

int main() {
    int n_test_cases = 0;

    scanf(" %d", &n_test_cases);

    for (int i = 0; i < n_test_cases; i++) {
        int n_pols;
        scanf(" %d", &n_pols);

        list_t *pol = read_and_sum_n_pols(n_pols);

        print_pol(pol, (i < n_test_cases - 1));
        destroy_list(&pol);
    }

    return EXIT_SUCCESS;
}

list_t *pol_sum(list_t *pol1, list_t *pol2) {
    list_t *pol_res = create_list(sizeof(int));

    // pol1 will be greater or equal in degree to pol2
    if (pol1->size < pol2->size) {
        list_t *aux;
        aux = pol1;
        pol1 = pol2;
        pol2 = aux;
    }

    for (int i = 0; i < pol2->size; i++) {
        int cur_num1;
        int cur_num2;

        access_element(pol1, i, &cur_num1);
        access_element(pol2, i, &cur_num2);

        cur_num1 += cur_num2;

        append_to_list(pol_res, &cur_num1);
    }

    for (int i = pol2->size; i < pol1->size; i++) {
        int cur_num;

        access_element(pol1, i, &cur_num);
        append_to_list(pol_res, &cur_num);
    }

    destroy_list(&pol1);
    destroy_list(&pol2);

    return pol_res;
}

list_t *read_and_sum_n_pols(int n_pols) {
    list_t *pol = create_list(sizeof(int));

    for (int j = 0; j < n_pols; j++) {
        list_t *cur_pol = create_list(sizeof(int));

        char c;

        while ((c = getchar()) != ')') {
            if (c != ',' && c != '(' && c != '\r' && c != '\n') {
                ungetc(c, stdin);

                int cur_coeff;

                scanf(" %d", &cur_coeff);

                append_to_list(cur_pol, &cur_coeff);
            }
        }

        pol = pol_sum(cur_pol, pol);
    }

    return pol;
}

void print_pol(list_t *pol, int add_new_line) {
    printf("(");

    for (int i = 0; i < pol->size; i++) {
        int cur_coeff = 0;

        access_element(pol, i, &cur_coeff);
        printf("%d", cur_coeff);

        if (i < pol->size - 1)
            printf(",");
        else
            printf(")");
    }

    if (add_new_line) new_line();
}