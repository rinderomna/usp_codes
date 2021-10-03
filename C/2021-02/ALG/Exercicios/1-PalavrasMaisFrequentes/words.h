typedef struct word word_t;
typedef struct wordlist wordlist_t;

/* |read_line|
 * Reads a line from the specified stream, allocating the string in Heap Memory.
 * Returns the respective pointer to allocated string. Also changes by reference a
 * bool integer that indicates 1 (true) if an EOF has been read and 0, otherwise.
 * 
 * @param stream (FILE *): stream from where to read the line.
 * @param has_EOF (int *): pointer to a bool integer that will indicate if an EOF
 * was read.
 * @return (char *): pointer to the first byte of the allocated string.
 */
char *read_line(FILE *stream, int *has_EOF);

/* |occurrence_indexes|
 * Changes by reference the passed phrase, removing all the occurences of the word
 * to remove in it. Also changes by reference an occurrences counter. Returns an
 * allocated vector with the indexes of each occurrence first position on the original
 * phrase.
 *  
 * @param word_to_remove (char *): string to be search on the phrase and removed.
 * @param phrase (char *): larger string in which to search the word_to_remove and
 * remove.
 * @param n_occurrences (int *): pointer to a counter of occurrences of the word to
 * remove on the phrase.
 * @return (int *): pointer to the first byte of an allocated vector with the occurrence
 * indexes of the word to remove in the original phrase.
 */
int *occurrence_indexes(char *word_to_remove, char *phrase, int *n_occurences);

/* |create_wordlist|
 * Returns an allocated wordlist, whose words vector and n_words are initialized with
 * NULL and 0, respectively.
 * 
 * return (wordlist_t *): pointer to the wordlist allocated.
 */
wordlist_t *create_wordlist();

/* |get_word_text_in_wordlist|
 * Returns the string of the word in the wordlist at the specified index.
 *
 * @param worlist (wordlist_t *): pointer to the wordlist in which to search the word.
 * @param index (int): index of the word whose text is being checked.
 * @return (char *): wanted word text.
 */
char *get_word_text_in_wordlist(wordlist_t *wordlist, int index);

/* |get_word_frequency_in_wordlist|
 * Returns the string of the word in the wordlist at the specified index.
 *
 * @param worlist (wordlist_t *): pointer to the wordlist in which to search the word.
 * @param index (int): index of the word whose frequency is being checked.
 * @return (char *): wanted word frequency.
 */
int get_word_frequency_in_wordlist(wordlist_t *wordlist, int index);

/* |get_n_words_in_wordlist|
 * Returns the number of words in a wordlist.
 * 
 * @param wordlist (wordlist_t *): pointer to the wordlist whose number of words
 * will be checked.
 */
int get_n_words_in_wordlist(wordlist_t *wordlist);

/* |append_to_wordlist|
 * Appends the specified word to the end of the passed wordlist.
 * 
 * @param wordlist (wordlist_t *): pointer to the wordlist in whose end the word
 * will be added.
 * @param word (word_t *): pointer to the word that will be added at the end of 
 * the wordlist.
 */
void append_to_wordlist(wordlist_t *wordlist, word_t *word);

/* |append_to_word|
 * Appends the specified character to the end of the passed word.
 * 
 * @param word (word_t *): pointer to the word in whose end the character
 * will be added.
 * @param c (char): charact to be added in the end of the word.
 */
void append_to_word(word_t *word, char c);

/* |add_if_unique|
 * Checks whether the specified word is in the wordlist. If it is not, then it
 * is added to the wordlist. If, otherwise, it already exists in the list, the
 * frequency of that word is increased by one.
 * 
 * @param wordlist (wordlist_t *): pointer to the wordlist in which to check the
 * existence of the passed word and perhaps add it, if it is unique.
 * @param word (word_t *): pointer to the word tha may be added to the wodlist.
 */
void add_if_unique(wordlist_t *wordlist, word_t *word);

/* |fill_wordlist|
 * Fills a wordlist with words in a certain phrase. The word are sepated by a space
 * character.
 * 
 * @param wordlist (wordlist_t *): pointer to the wordlist to be filled.
 * @param phrase (char *): string that contains the space separated words to be added
 * in the wordlist. 
 */
void fill_wordlist(wordlist_t *wordlist, char *phrase);

/* |sort_wordlist|
 * Sorts the specified wordlist, using Insertion Sort, in descending order of frequency
 * and, when with same frequency, in ascending alphabetic order.
 *
 * @param wordlist (wordlist_t *): pointer to the wordlist to be sorted. 
 */
void sort_wordlist(wordlist_t *wordlist);

/* |destroy_wordlist|
 * Frees all allocated memory related to the specified wordlist.
 *
 * @param wordlist (wordlist_t **): pointer to the pointer the wordlist 
 * to be freed.
 */
void destroy_wordlist(wordlist_t **wordlist);