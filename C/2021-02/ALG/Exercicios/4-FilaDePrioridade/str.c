#include <stdio.h>
#include <stdlib.h>

#include "str.h"

#define BUFFER_SIZE 50

size_t string_length(string_t str) {
    size_t len = 0;

    while (str[len] != '\0') len++;

    return len;
}

void new_line() {
    printf("\n");
}

void new_lines(unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        printf("\n");
    } 
}

void print_string(string_t str) {
    printf("%s", str);
}

void println_string(string_t str) {
    printf("%s\n", str);
}

int compare_strings(string_t str1, string_t str2) {
    int diff = 0;

    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0' && diff == 0) {
        diff += str1[i] - str2[i];
        i++;
    }

    if (diff == 0) {
        diff = string_length(str1) - string_length(str2);
    }

    return diff;
}

void *copy_memory(void *dest, void *src, size_t n_bytes) {
	char *d = (char *)dest;
	char *s = (char *)src;

	for (int i = 0; i < (int)n_bytes; i++) {
		d[i] = s[i];
	}
    
	return dest;
}

string_t read_until(FILE *stream, symbol_t separator) {
    char c;
    unsigned long int n_chars = 0;

    string_t line = NULL;
    
    while ((c = fgetc(stream)) == '\n' || (c == '\r') || (c == separator));

    if (c != EOF) ungetc(c, stream);

    do {
        c = fgetc(stream);

        if (n_chars % BUFFER_SIZE == 0) {
            unsigned long int new_size = (n_chars / BUFFER_SIZE + 1) * BUFFER_SIZE + 1;
            
            line = (string_t)realloc(line, (size_t)new_size * sizeof(symbol_t));
        }
        
        n_chars++;

        if (c != '\n' && c != '\r' && c != separator && c != EOF) {
            *(line + n_chars - 1) = c;
        } else {
            *(line + n_chars - 1) = '\0';
        }
    } while (c != '\n' && c != '\r' && c != separator && c != EOF);

    line = (string_t)realloc(line, (size_t)(n_chars + 1));

    return line;
}

string_t read_line(FILE *stream) {
    char c;
    unsigned long int n_chars = 0;

    string_t line = NULL;
    
    while ((c = fgetc(stream)) == '\n' || (c == '\r'));

    if (c != EOF) ungetc(c, stream);

    do {
        c = fgetc(stream);

        if (n_chars % BUFFER_SIZE == 0) {
            int new_size = (n_chars / BUFFER_SIZE + 1) * BUFFER_SIZE + 1; 
            
            line = (string_t)realloc(line, (size_t)new_size * sizeof(symbol_t));
        }
        
        n_chars++;

        if (c != '\n' && c != '\r' && c != EOF) {
            *(line + n_chars - 1) = c;
        } else {
            *(line + n_chars - 1) = '\0';
        }
    } while (c != '\n' && c != '\r' && c != EOF);

    line = (string_t)realloc(line, (size_t)(n_chars + 1));

    return line;
}

void destroy_string(string_t str) {
    if (str) free(str);
}
