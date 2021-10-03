typedef struct elem elem_t;
typedef struct p_queue p_queue_t;

/* |create_priority_queue|
 * Returns a pointer to an allocated priority queue, also allocating a list of elements.
 * Initializes size with 0, all other pointers with NULL and datum_size with the passed value.
 * 
 * @param datum_size (int): size in bytes of the datum that will be added to the priority queue.
 * @return (p_queue_t *): pointer to the allocated priority queue.
 */
p_queue_t *create_priority_queue(int datum_size);

/* |get_priority_queue_size|
 * Returns the number of elements in the specified priority queue.
 * 
 * @param q (p_queue_t *): priority queue whose size is being checked.
 * @return (int): number of elements in the specified priority queue.
 */
int get_priority_queue_size(p_queue_t *q);

/* |add_to_priority_queue|
 * Adds the passed datum to the priority queue, according to its priority.
 * A lower number means a higher priority.
 *
 * @param q (p_queue_t *): pointer to the priority queue in which the datum passed will be added.
 * @param datum (void *): pointer to the datum to be added to the priority queue. 
 * @param priority (int): priority with which the datum will be added to the priority queue.
 */
void add_to_priority_queue(p_queue_t *q, void *datum, int priority);

/* |remove_from_priority_queue|
 * Removes the element from the start of the passed priority queue.
 * Stores the removed element datum at the specified datum pointer.
 *
 * @param q (list_t *): pointer to the priority queue from which to remove the element at its start.
 * @param datum (void *): pointer that will receive the removed element datum.
 */
void remove_from_priority_queue(p_queue_t *q, void *datum);

/* |destroy_priority_queue|
 * Frees all memory related to the specified priority queue.
 *
 * @param q (p_queue_t **): address of the pointer to the priority queue to be freed. 
 */
void destroy_priority_queue(p_queue_t **q);