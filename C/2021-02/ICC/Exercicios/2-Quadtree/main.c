/* ______________________________________________________
 *|  SCC0201 — Introducao a Ciencias da Computacao II    |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|------------| Exercicio 02: Quad-Tree |---------------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct image {
    unsigned char **values;
    int n_rows;
    int n_cols;
} image_t;

unsigned char **alloc_matrix(int n_rows, int n_cols);
image_t *read_image(int n_rows, int n_cols);
void free_image(image_t **image);
bool all_are_equal(image_t *image, int i_i, int i_f, int j_i, int j_f);
void recursive_quad_tree(image_t *image, int i_i, int i_f, int j_i, int j_f);
void quad_tree(image_t *image);

int main() {
    int n_rows, n_cols;
    scanf(" %d %d", &n_rows, &n_cols);

    image_t *image = read_image(n_rows, n_cols);

    quad_tree(image);
    free_image(&image);

    return EXIT_SUCCESS;
}

/* |alloc_matrix|
 * Allocates an 8-bits unsigned integers (0 to 255) matrix with the specified dimensions.
 * 
 * @param n_rows (int): number of rows in the matrix.
 * @param n_cols (int): number of columns in the matrix.
 * @return (unsigned char **): allocated matrix pointer.
 */
unsigned char **alloc_matrix(int n_rows, int n_cols) {
    unsigned char **mat = (unsigned char **)malloc(n_rows * sizeof(unsigned char *));

    for (int i = 0; i < n_rows; i++) {
        mat[i] = (unsigned char *)malloc(n_cols * sizeof(unsigned char));
    }

    return mat;
}

/* |read_image|
 * Fills image information:
 *  - The dimensions with specified values
 *  - The allocated matrix values from stdin
 * 
 * @param n_rows (int): number of rows in the values matrix.
 * @param n_cols (int): number of columns in the values matrix.
 * @return (image_t *): pointer to the filled allocated image.
 */
image_t *read_image(int n_rows, int n_cols) {
    image_t *image = (image_t *)malloc(1 * sizeof(image_t));

    image->values = alloc_matrix(n_rows, n_cols);

    image->n_rows = n_rows;
    image->n_cols = n_cols;

    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            scanf(" %hhd", &image->values[i][j]);
        }
    }

    return image;
}

/* |free_image|
 * Frees all memory related to the specified image. Assign NULL to its pointer.
 *
 * @param image (image **): address of the pointer to the image to be freed.
 */
void free_image(image_t **image) {
    if (!*image) return;

    if (!(*image)->values) {
        free(*image);

        return;
    }

    for (int i = 0; i < (*image)->n_rows; i++) {
        if ((*image)->values[i]) {
            free((*image)->values[i]);
        }
    }

    free((*image)->values);
    free(*image);

    *image = NULL;
}

/* |all_are_equal|
 * Checks whether the image matrix values in the specified region are all equal.
 * 
 * @param image (image *): pointer to the image whose values will be checked.
 * @param i_i (int): initial row index.
 * @param i_f (int): final row index.
 * @param j_i (int): initial column index.
 * @param j_f (int): final column index.
 * @return (bool): true if all the values in the region are equal. False, otherwise.
 */
bool all_are_equal(image_t *image, int i_i, int i_f, int j_i, int j_f) {
    bool are_equal = true;
    unsigned char candidate = image->values[i_i][j_i];

    int i = i_i;
    int j = j_i + 1;

    while (i <= i_f && are_equal) {
        while (j <= j_f && are_equal) {
            are_equal = (image->values[i][j] == candidate);
            j++;
        }

        j = j_i;
        i++;
    }

    return are_equal;
}

/* |recursive_quad_tree|
 * Prints the Quad-Tree of the specified region in the matrix of the passed image (in a single line).
 * 
 * @param image (image *): pointer to the image.
 * @param i_i (int): initial row index.
 * @param i_f (int): final row index.
 * @param j_i (int): initial column index.
 * @param j_f (int): final column index.
 */
void recursive_quad_tree(image_t *image, int i_i, int i_f, int j_i, int j_f) {
    if (all_are_equal(image, i_i, i_f, j_i, j_f)) {
        printf("%d ", image->values[i_i][j_i]);
    } else {
        printf("-1 ");

        int n_rows = i_f - i_i + 1;
        int n_cols = j_f - j_i + 1;

        // Recursive Call for Quadrant 1 (Upper-Left)
        if (n_rows > 1 && n_cols > 1) {
            recursive_quad_tree(image, i_i, i_i + n_rows / 2 - 1, j_i, j_i + n_cols / 2 - 1);
        }

        // Recursive Call for Quadrant 2 (Upper-Right)
        if (n_rows > 1 && n_cols > 0) {
            recursive_quad_tree(image, i_i, i_i + n_rows / 2 - 1, j_i + n_cols / 2, j_f);
        }

        // Recursive Call for Quadrant 3 (Lower-Left)
        if (n_rows > 0 && n_cols > 1) {
            recursive_quad_tree(image, i_i + n_rows / 2, i_f, j_i, j_i + n_cols / 2 - 1);
        }

        // Recursive Call for Quadrant 4 (Lower-Right)
        if (n_rows > 0 && n_cols > 0) {
            recursive_quad_tree(image, i_i + n_rows / 2, i_f, j_i + n_cols / 2, j_f);
        }
    }
}

/* |quad_tree|
 * Prints the Quad-Tree of the specified image values matrix (in a single line).
 * 
 * @param image (image *): pointer to the image whose values matrix Quad-Tree will be printed.
 */
void quad_tree(image_t *image) {
    recursive_quad_tree(image, 0, image->n_rows - 1, 0, image->n_cols - 1);
    printf("\n");
}