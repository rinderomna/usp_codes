typedef struct node node_t;
typedef struct list list_t;

/* |create_list|
 * Returns an allocated list and inicialize size with, 0 and all pointers
 * with NULL and the element_size with the value passed.
 * 
 * @param elem_size (int): size in bytes of the elements that will be added
 * to the list. 
 * @return (list_t *): pointer to the allocated list.
 */
list_t *create_list(int elem_size);

/* |get_list_size|
 * Return the number of elements in the specified list.
 *
 * @param l (list_t *): list whose size is being checked.
 * @return (int): number of elements in the specified list.
 */
int get_list_size(list_t *l);

/* |append_to_list|
 * Add the passed element to the end of the list.
 *
 * @param l (list_t *): pointer to the list in whose end the element
 * will be added.
 * @param datum (void *): pointer to the element to be appended to the list. 
 */
void append_to_list(list_t *l, void *datum);

/* |insert_in_list|
 * Insert the passed element in the specified list at the determined
 * index.
 * 
 * @param l (list_t *): pointer to the list in which the element will
 * be inserted.
 * @param datum (void *): pointer to the element to be inserted in the list.
 * @param index (int): list index where to insert the element.
 */
void insert_in_list(list_t *l, void *datum, int index);

/* |access_datum|
 * Changes by reference an element with the datum in the list at the
 * specified index.
 * 
 * @param l (list_t *): pointer to the list to be accessed.
 * @param index (int): list index where to access the datum.
 * @param datum (void *): pointer to the element that will receive the datum
 */
void access_datum(list_t *l, int index, void *datum);

/* |remove_from_list|
 * Remove the element at the specified index from the passed list.
 *
 * @param l (list_t *): pointer to the list from which to remove the specified
 * element.
 * @param index (int): list index where to remove the element.
 */
void remove_from_list(list_t *l, int index);

/* |invert_list|
 * Invert the specified list in-place.
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
 * @param l (list_t **): pointer to the pointer to the list to be freed. 
 */
void destroy_list(list_t **l);