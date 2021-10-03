#include <stdio.h>
#include <stdlib.h>

int string_length(const char *str) {
    int string_len = -1;

    while (str[++string_len] != '\0');

    return string_len;
}


char *string_copy(char *dest, const char *src) {
        
}


int main(void) {
    char my_string[] = "abcdefghijklmnopqrstuvwxyz";

    printf("%s\n%d\n", my_string, string_length(my_string));

    return EXIT_SUCCESS;
}