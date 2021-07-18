#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

char *create_string_copy(char *str);
bool is_valid_char(char c);
char *readline_clean(void);
void remove_extremes(char **msg);
void remove_spaces_and_bars(char **msg);
bool is_palindrome(char **msg);

int main() {
    char *msg;
    char *msg_without_spaces_and_bars;
    
    msg = readline_clean();   
    
    msg_without_spaces_and_bars = create_string_copy(msg);
    
    remove_spaces_and_bars(&msg_without_spaces_and_bars);

    if (is_palindrome(&msg)) {
        printf("Palindromo direto\n");
    } else if (is_palindrome(&msg_without_spaces_and_bars)) {
        printf("Palindromo indireto\n");
    } else {
        printf("Nao eh um palindromo\n");
    }

    free(msg);
    free(msg_without_spaces_and_bars);

    return 0;
}

char *create_string_copy(char *str) {
    int str_len = strlen(str);
    char *new_str;

    new_str = malloc((str_len + 1) * sizeof(char));

    strcpy(new_str, str);

    return new_str;
}
 
bool is_valid_char(char c) {
    bool is_valid_char;
    
    if (isalnum(c)) 
        is_valid_char = true;
    else if (c == ' ' || c == '/')
        is_valid_char = true;
    else if (c == '\n')
        is_valid_char = true;
    else 
        is_valid_char = false;

    return is_valid_char;
}

char *readline_clean(void) {
  char *line = NULL;
  char c;
  int n_chars = 0;

  while ((c = getchar()) == '\n' || (c == '\r'));

  if (c != EOF) ungetc(c, stdin);
  
  do {
    c = tolower(getchar());

    if (is_valid_char(c)) {
        n_chars++;
        line = (char *) realloc(line, n_chars);

        if (c != '\n')
        *(line + n_chars - 1) = c;
        else
        *(line + n_chars - 1) = '\0';
    }
  } while (c != '\n');

  return line;
}

void remove_extremes(char **msg) {
    int msg_len = strlen(*msg);
    
    (*msg)[msg_len - 1] = '\0';
    msg_len = strlen((*msg) + 1);

    char *new_msg;
    new_msg = malloc((msg_len + 1) * sizeof(char));
    strcpy(new_msg, *(msg) + 1);
    free(*msg);

    *msg = new_msg;
}

bool is_palindrome(char **msg) {
    int last_index = strlen(*msg) - 1;
    
    if (last_index < 1) {    
        return true;
    } else if ((*msg)[0] == (*msg)[last_index]) {
        remove_extremes(msg);
        return is_palindrome(msg);
    } else {
        return false;
    }
}

void remove_spaces_and_bars(char **msg) {
    int msg_len = strlen(*msg);
    char *new_msg;

    new_msg = malloc((msg_len + 1) * sizeof(char));
    
    int counter = 0;
    for (int i = 0; i < msg_len; i++) {
        if ((*msg)[i] != ' ' && (*msg)[i] != '/') {
            new_msg[counter] = (*msg)[i];
            counter++;
        }
    }
    new_msg[counter] = '\0';

    new_msg = realloc(new_msg, (counter + 1) * sizeof(char));

    free(*msg);

    *msg = new_msg;
}
