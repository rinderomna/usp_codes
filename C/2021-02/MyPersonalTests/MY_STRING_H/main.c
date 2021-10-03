#include <stdio.h>

#include "str.h"

int main() {
    symbol_t str1[] = "abacate";
    symbol_t str2[] = "observação";

    printf("abacate e observação: %d\n", compare_strings(str1, str2));

    printf("\n\nEntre duas palavras separadas por espaço: ");

    string_t s1, s2;

    s1 = read_string(stdin, ' ');
    s2 = read_string(stdin, ' ');

    new_line();
    println_string(s1);
    println_string(s2);
    new_lines(2);

    printf("Comparando: %d\n", compare_strings(s1, s2));

    destroy_string(s1);
    destroy_string(s2);   

    return 0;
}