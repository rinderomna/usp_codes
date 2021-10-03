#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "words.h"

struct word {
    char *text;
    int length;
    int frequency;
};

struct wordlist {
    word_t *words;
    int n_words;
};

char *read_line(FILE *stream, int *has_EOF) {
    char *line = NULL;
    char c;
    int n_chars = 0;

    *has_EOF = 0;

    while ((c = fgetc(stream)) == '\n' || (c == '\r'));

    if (c != EOF) ungetc(c, stream);

    do {
        c = fgetc(stream);

        n_chars++;
        line = (char *)realloc(line, (n_chars + 1) * sizeof(char));

        if (c != '\n' && c != '\r' && c != EOF) {
            *(line + n_chars - 1) = c;
        } else {
            *(line + n_chars - 1) = '\0';

            if (c == EOF) {
                *has_EOF = 1;
            }
        }
    } while (c != '\n' && c != '\r' && c != EOF);

    return line;
}

int *occurrence_indexes(char *word_to_remove, char *phrase, int *n_occurences) {
    int *occur_indexes = NULL;

    int tamanho_word_to_remove = strlen(word_to_remove);

    (*n_occurences) = 0;

    char *occurence = NULL;
    int n_removals = 0;

    do {
        occurence = strstr(phrase, word_to_remove);

        if (occurence != NULL) {
            (*n_occurences)++;
            occur_indexes = (int *)realloc(occur_indexes, (*n_occurences) * sizeof(int));

            occur_indexes[(*n_occurences) - 1] = occurence - phrase + tamanho_word_to_remove * (n_removals);

            // length_until_end counts occurence length until just before the '\0'
            int length_until_end = strlen(occurence);

            // remaining_length counts length from just after the word_to_remove, including the '\0'.
            int remaining_length = length_until_end - tamanho_word_to_remove + 1;

            memmove(occurence, occurence + tamanho_word_to_remove, remaining_length);

            n_removals++;
        }
    } while (occurence != NULL);

    return occur_indexes;
}

wordlist_t *create_wordlist() {
    wordlist_t *w = (wordlist_t *)malloc(sizeof(wordlist_t));

    w->n_words = 0;
    w->words = NULL;

    return w;
}

int get_n_word_in_wordlist(wordlist_t *wordlist) {
    return wordlist->n_words;
}

char *get_word_text_in_wordlist(wordlist_t *wordlist, int index) {
    return wordlist->words[index].text;
}

int get_word_frequency_in_wordlist(wordlist_t *wordlist, int index) {
    return wordlist->words[index].frequency;
}

void append_to_wordlist(wordlist_t *wordlist, word_t *word) {
    wordlist->words = (word_t *)realloc(
        wordlist->words,
        (++wordlist->n_words) * sizeof(word_t));

    wordlist->words[wordlist->n_words - 1] = *word;
}

void append_to_word(word_t *word, char c) {
    word->text = (char *)realloc(
        word->text,
        (++word->length) * sizeof(char));

    word->text[word->length - 1] = c;
}

void add_if_unique(wordlist_t *wordlist, word_t *word) {
    int is_unique = 1;
    word->frequency = 1;

    if (wordlist->words) {
        for (int i = 0; i < wordlist->n_words; i++) {
            if (strcmp(word->text, wordlist->words[i].text) == 0) {
                is_unique = 0;
                wordlist->words[i].frequency++;
            }
        }
    }

    if (is_unique) {
        append_to_wordlist(wordlist, word);
    } else {
        if (word->text) free(word->text);
    }
}

void fill_wordlist(wordlist_t *wordlist, char *phrase) {
    int i = 0;
    while (i < strlen(phrase)) {
        word_t cur_word;
        cur_word.text = NULL;
        cur_word.length = 0;

        while (phrase[i] != ' ' && phrase[i] != '\0') {
            append_to_word(&cur_word, phrase[i]);
            i++;

            if (phrase[i] == ' ' || phrase[i] == '\0') {
                append_to_word(&cur_word, '\0');

                add_if_unique(wordlist, &cur_word);
            }
        }

        while ((phrase[i] == ' ') && (i < strlen(phrase))) i++;
    }
}

int goes_first_than(word_t word1, word_t word2) {
    int word1_goes_first = 0;

    if (word1.frequency < word2.frequency) {
        word1_goes_first = 1;
    } else if (word1.frequency == word2.frequency) {
        if (strcmp(word1.text, word2.text) > 0) {
            word1_goes_first = 1;
        }
    }

    return word1_goes_first;
}

void sort_wordlist(wordlist_t *wordlist) {
    for (int j = 1; j < wordlist->n_words; j++) {
        word_t chave = wordlist->words[j];
        int i = j - 1;

        int cur_word_goes_first = goes_first_than(wordlist->words[i], chave);

        while (i >= 0 && cur_word_goes_first) {
            wordlist->words[i + 1] = wordlist->words[i];
            i--;

            if (i >= 0) {
                cur_word_goes_first = goes_first_than(wordlist->words[i], chave);
            }
        }

        wordlist->words[i + 1] = chave;
    }
}

void destroy_wordlist(wordlist_t **wordlist) {
    if (wordlist) {
        if ((*wordlist)->words) {
            for (int i = 0; i < (*wordlist)->n_words; i++) {
                free((*wordlist)->words[i].text);
            }

            free((*wordlist)->words);
            (*wordlist)->words = NULL;
        }
    }

    free(*wordlist);
    *wordlist = NULL;
}