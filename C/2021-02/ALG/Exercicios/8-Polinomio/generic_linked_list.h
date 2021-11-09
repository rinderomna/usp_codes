typedef struct node node_t;
typedef struct list list_t;

struct list {
    node_t *start;
    node_t *end;
    int size;
    int elem_size;
};

/* |create_list|
 * Returns a pointer to an allocated list of elements, which can be of any type the user wants.
 * Initializes size with 0, all other pointers with NULL and elem_size with the passed value.
 * 
 * @param elem_size (int): size in bytes of the elements that will be added to the list. 
 * @return (list_t *): pointer to the allocated list.
 */
list_t *create_list(int elem_size);

/* |get_list_size|
 * Returns the number of elements in the specified list.
 *
 * @param l (list_t *): list whose size is being checked.
 * @return (int): number of elements in the specified list.
 */
int get_list_size(list_t *l);

/* |append_to_list|
 * Adds the passed element to the end of the list.
 *
 * @param l (list_t *): pointer to the list in whose end the element will be added.
 * @param elem (void *): pointer to the element to be appended to the list. 
 */
void append_to_list(list_t *l, void *elem);

/* |insert_in_list|
 * Inserts the passed element in the specified list at the determined index.
 * 
 * @param l (list_t *): pointer to the list in which the element will be inserted.
 * @param elem (void *): pointer to the element to be inserted in the list.
 * @param index (int): list index where to insert the element.
 */
void insert_in_list(list_t *l, void *elem, int index);

/* |access_element|
 * Accesses the element in the passed list at the specified index.
 * Returns that value by storing its information at a specified element pointer. 
 * 
 * @param l (list_t *): pointer to the list to be accessed.
 * @param index (int): list index where to access the element.
 * @param elem (void *): pointer to the element that will receive the information accessed.
 */
void access_element(list_t *l, int index, void *elem);

/* |remove_from_list|
 * Removes the element at the specified index from the passed list.
 *
 * @param l (list_t *): pointer to the list from which to remove the specified element.
 * @param index (int): list index where to remove the element.
 */
void remove_from_list(list_t *l, int index);

/* |invert_list|
 * Inverts the specified list in-place.
 *
 * @param l (list_l): pointer to the list to be inverted.
 */
void invert_list(list_t *l);

/* |right_rotate_list|
 * Right rotates the specified list n times.
 *
 * @param l (list_t *): pointer to the list to be right rotated.
 * @param n (int): number of times to right rotate the list.
 */
void right_rotate_list(list_t *l, int n);

/* |destroy_list|
 * Frees all memory related to the specified list.
 *
 * @param l (list_t **): address of the pointer to the list to be freed. 
 */
void destroy_list(list_t **l);