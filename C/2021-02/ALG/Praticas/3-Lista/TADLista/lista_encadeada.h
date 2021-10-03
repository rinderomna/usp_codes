typedef struct node node_t;
typedef struct list list_t;

list_t *create_list(int max_size);
int get_list_size(list_t *list);
void append_to_list(list_t *l, int number);
void access_data(list_t *l, int index, int *number);
void remove_from_list(list_t *l, int index);
void destroy_list(list_t **l);