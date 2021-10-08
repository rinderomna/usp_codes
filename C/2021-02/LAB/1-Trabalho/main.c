/* ________________________________________________________________________
 *|     SCC0220 - Laboratorio de Introducao a Ciencia da Computacao II     |
 *|                      [Segundo Semestre de 2021]                        |
 *|                                                                        |
 *|---------------| Exercicio 01: Ordenacao Aconchegante |-----------------|
 *|                                                                        |
 *|         Codigo por: Helio Nogueira Cardoso - N°USP: 10310227           |
 *|________________________________________________________________________|
 */
#include <stdio.h>
#include <stdlib.h>

#include "str.h"

typedef struct shell {
    double diameter;
    string_t colour;
    string_t texture;
} shell_t;

typedef struct shell_list {
    shell_t *shells;
    int n_shells;
} shell_list_t;

/* |print_shell_list|
 * Prints shell list information in specified format:
 *      <diameter> <colour> <texture>
 *      (one line per shell)
 */
void print_shell_list(shell_list_t *shell_list);

/* |insertion_sort_shells|
 * Sorts a sublist of the shell_list in-place, beginning at first_index such that
 * each next element is one step forward in the original list.
 */
void insertion_sort_shells(shell_list_t *shell_list, int first_index, int step);

/* |shell_sort|
 * Sorts the specified shell list recursively, using the control parameter n, in a
 * way that the original list is divided in n / 2 (integer division) virtual sub-
 * lists. An element at position k belongs to the same sublist as other elements 
 * whose indexes i are such that (i % (n / 2)) == (k % (n / 2)). At each step, the
 * parameter n is divided by half (integer division), until it is 1.
 */
void shell_sort(shell_list_t *shell_list, int n);

/* |read_shell_list|
 * Reads shell list information from stdin in specified format.
 */
void read_shell_list(shell_list_t *shell_list);

/* |free_shell_list|
 * Frees all allocated memory related to the specified shell list.
 */
void free_shell_list(shell_list_t *shell_list);

int main(void) {
    shell_list_t shell_list;

    read_shell_list(&shell_list);
    shell_sort(&shell_list, shell_list.n_shells);
    print_shell_list(&shell_list);
    free_shell_list(&shell_list);

    return EXIT_SUCCESS;
}

void print_shell_list(shell_list_t *shell_list) {
    for (int i = 0; i < shell_list->n_shells; i++) {
        printf("%.3lf ", shell_list->shells[i].diameter);
        print_string(shell_list->shells[i].colour);
        printf(" ");
        print_string(shell_list->shells[i].texture);

        new_line();
    }
}

void insertion_sort_shells(shell_list_t *shell_list, int first_index, int step) {
    int N = shell_list->n_shells;
    int i = first_index + step;

    while (i < N) {
        shell_t key = shell_list->shells[i];
        int j = i - step;

        while (j >= first_index && key.diameter < shell_list->shells[j].diameter) {
            shell_list->shells[j + step] = shell_list->shells[j];
            j -= step;
        }

        shell_list->shells[j + step] = key;

        i += step;
    }
}

void shell_sort(shell_list_t *shell_list, int n) {
    if (n == 1) return;

    n /= 2;

    for (int i = 0; i < n; i++) {
        insertion_sort_shells(shell_list, i, n);
    }

    shell_sort(shell_list, n);
}

void read_shell_list(shell_list_t *shell_list) {
    scanf(" %d", &shell_list->n_shells);

    shell_list->shells = (shell_t *)malloc(shell_list->n_shells * sizeof(shell_t));

    for (int i = 0; i < shell_list->n_shells; i++) {
        scanf(" %lf", &shell_list->shells[i].diameter);
        shell_list->shells[i].colour = read_string(stdin, ' ');
        shell_list->shells[i].texture = read_string(stdin, ' ');
    }
}

void free_shell_list(shell_list_t *shell_list) {
    for (int i = 0; i < shell_list->n_shells; i++) {
        destroy_string(shell_list->shells[i].colour);
        destroy_string(shell_list->shells[i].texture);
    }

    free(shell_list->shells);
}
