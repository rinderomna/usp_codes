#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct name_ {
    char *name;
    int n_chars;
} Name;

typedef struct names_list_ {
    Name *names;
    int n_names;
} Names_List;

char *read_line(int *n_chars);
void fill_names_list(Names_List *nameslist_);
void add_last_name(Name *dest_name_, Name *source_name_);
void change_names_list(Names_List *nameslist_);
void print_names_list(Names_List nameslist);
void free_names_list(Names_List nameslist);

int main() {
    Names_List nameslist;

    nameslist.names = NULL;
    nameslist.n_names = 0;    
    
    fill_names_list(&nameslist);
    change_names_list(&nameslist);
    print_names_list(nameslist);
    free_names_list(nameslist);
    
    return 0;
}

char *read_line(int *n_chars) {
  char *line = NULL;
  char c;
  *n_chars = 0;

  while ((c = getchar()) == '\n' || (c == '\r'));

  if (c != EOF) ungetc(c, stdin);
  
  do {
    c = getchar();
    
    (*n_chars)++;
    line = (char *) realloc(line, *n_chars);

    if (c != '\n')
      *(line + *n_chars - 1) = c;
    else
      *(line + *n_chars - 1) = '\0';

  } while (c != '\n');

  return line;
}

void fill_names_list(Names_List *nameslist_) {
    bool is_end;

    nameslist_->names = (Name *) realloc(
            nameslist_->names, 
            ++nameslist_->n_names * sizeof(Name) 
        );

    int current_name_index = nameslist_->n_names - 1;
    nameslist_->names[current_name_index].name = read_line(
        &nameslist_->names[current_name_index].n_chars
    );

    if (nameslist_->names[current_name_index].name == NULL) {
        is_end = true;
        nameslist_->n_names--;
    } else {
        int last_letter_index = nameslist_->names[current_name_index].n_chars - 2;
        if (nameslist_->names[current_name_index].name[last_letter_index] == '$') {
            is_end = true;
            nameslist_->names[current_name_index].n_chars--;
            nameslist_->names[current_name_index].name[last_letter_index] = '\0';
        } else {
            is_end = false;
        }
    }

    if (!is_end) fill_names_list(nameslist_);
}

void add_last_name(Name *dest_name_, Name *source_name_) {
    char *last_name;
    last_name = source_name_->name;

    for (int i = 0; i < source_name_->n_chars - 1; i++) {
        if (source_name_->name[i] == ' ') {
            last_name = &source_name_->name[i + 1];
        }
    }

    int prev_n_chars = dest_name_->n_chars;
    int last_name_n_chars = strlen(last_name) + 1;

    dest_name_->n_chars += last_name_n_chars;
    dest_name_->name = (char *) realloc(
        dest_name_->name,
        dest_name_->n_chars * sizeof(char)
    );

    dest_name_->name[prev_n_chars - 1] = ' ';
    memcpy(&dest_name_->name[prev_n_chars], last_name, last_name_n_chars);
}

void change_names_list(Names_List *nameslist_) {
    for (int i = 0; i < nameslist_->n_names; i += 2) {
        if (i + 1 < nameslist_->n_names) {
            add_last_name(&nameslist_->names[i + 1], &nameslist_->names[i]);
        }
    }
}

void print_names_list(Names_List nameslist) {
    for (int i = 0; i < nameslist.n_names; i++) {
        printf("%s\n", nameslist.names[i].name);
    }
}

void free_names_list(Names_List nameslist) {
    for (int i = 0; i < nameslist.n_names; i++) {
        free(nameslist.names[i].name);
    }
    free(nameslist.names);
} 