/* ______________________________________________________
 *|    SCC0202 - Algoritmos e Estruturas de Dados I      |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|------| Exercicio 01: Palavras Mais Frequentes |------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "words.h"

typedef int bool;
#define FALSE 0;
#define TRUE 1;

/* |print_most_freq_words|
 * Prints the k most frequent words in the wordlist.
 * The tiebreaker is the alphabetic order.
 */
void print_most_freq_words(wordlist_t *wordlist, int k);

int main() {
    bool has_EOF = FALSE;

    do {
        char *phrase = NULL;

        wordlist_t *wordlist = create_wordlist();

        phrase = read_line(stdin, &has_EOF);

        // k is first read as a string just to identify EOF.
        char *k = read_line(stdin, &has_EOF);
        int k_more_freq_words = atoi(k);

        if (strlen(phrase) > 0) {
            fill_wordlist(wordlist, phrase);

            sort_wordlist(wordlist);

            print_most_freq_words(wordlist, k_more_freq_words);

            if (!has_EOF) printf("\n\n");

            destroy_wordlist(&wordlist);
        }

        if (phrase) {
            free(phrase);
            phrase = NULL;
        }

        if (k) {
            free(k);
            k = NULL;
        }
    } while (!has_EOF);

    return EXIT_SUCCESS;
}

void print_most_freq_words(wordlist_t *wordlist, int k) {
    int n = get_n_words_in_wordlist(wordlist);
    if (k > n) k = n;

    for (int i = 0; i < k; i++) {
        char *cur_word_text = get_word_text_in_wordlist(wordlist, i);
        int cur_word_frequency = get_word_frequency_in_wordlist(wordlist, i);

        printf("%s %d", cur_word_text, cur_word_frequency);
        if (i < k - 1) printf("\n");
    }
}