typedef struct _IO_FILE FILE;
typedef __SIZE_TYPE__ size_t;
typedef unsigned char symbol_t;
typedef symbol_t * string_t;

size_t string_length(string_t str);
void new_line();
void new_lines(unsigned n);
void print_string(string_t str);
void println_string(string_t str);
int compare_strings(string_t str1, string_t str2);
void *copy_memory(void *dest, void *src, size_t n_bytes);
string_t read_until(FILE *stream, symbol_t separator);
string_t read_line(FILE *stream);
void destroy_string(string_t str);