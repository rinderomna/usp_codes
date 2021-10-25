/* SCC0201 - Introducao a Ciencia de Computacao II (2021/02)
 * Exercicio 0.1 - Revisando Alocacao Dinamica Recursao e Arquivos
 *
 * Helio Nogueira Cardoso
 * N°USP: 10310227
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WALKED '*'
#define BLOCKED '#'

typedef struct point_ {
    int x;
    int y;
} point_t;

typedef struct labrinth_ {
    char **grid;
    int n_lin;
    int n_col;
    point_t current_point;
} labrinth_t;

char *read_line(void);
void read_labrinth(labrinth_t *labrinth);
void free_labrinth(labrinth_t *labrinth);
bool is_out_of_labrinth(labrinth_t *labrinth, point_t *point);
bool is_free_way(labrinth_t *labrinth, point_t *point);
bool cross_labrinth(labrinth_t *labrinth);
void print_labrinth(labrinth_t *labrinth);
int count_blockers(labrinth_t *labrinth);
int count_freeways(labrinth_t *labrinth);
int count_walkedways(labrinth_t *labrinth);

int main() {
    labrinth_t labrinth;

    read_labrinth(&labrinth);

    int n_blockers = count_blockers(&labrinth);
    int n_initial_freeways = count_freeways(&labrinth);

    cross_labrinth(&labrinth);

    int n_final_walkedways = count_walkedways(&labrinth);
    double exploration = (100 * n_final_walkedways) / n_initial_freeways;

    print_labrinth(&labrinth);

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", n_blockers);
    printf("----Numero total de caminhos validos:   %d\n", n_initial_freeways);
    printf("----Numero total de caminhos visitados: %d\n", n_final_walkedways);
    printf("----Exploracao total do labirinto: %.1lf%%\n", exploration);

    free_labrinth(&labrinth);

    return 0;
}

char *read_line(void) {
    char *line = NULL;
    char c;
    int n_chars = 0;

    while ((c = getchar()) == '\n' || (c == '\r'))
        ;

    if (c != EOF) ungetc(c, stdin);

    do {
        c = getchar();

        n_chars++;
        line = (char *)realloc(line, n_chars);

        if (c != '\n' && c != EOF)
            *(line + n_chars - 1) = c;
        else
            *(line + n_chars - 1) = '\0';

    } while (c != '\n' && c != EOF);

    return line;
}

void read_labrinth(labrinth_t *labrinth) {
    FILE *labrinth_file = NULL;
    char *labrinth_file_name;

    labrinth_file_name = read_line();

    labrinth_file = fopen(labrinth_file_name, "r");

    fscanf(labrinth_file, " %d %d", &labrinth->n_lin, &labrinth->n_col);
    fscanf(labrinth_file, " %d %d", &labrinth->current_point.y, &labrinth->current_point.x);

    labrinth->grid = (char **)malloc(
        labrinth->n_lin * sizeof(char *));

    for (int i = 0; i < labrinth->n_lin; i++) {
        labrinth->grid[i] = (char *)malloc(
            labrinth->n_col * sizeof(char));
    }

    for (int i = 0; i < labrinth->n_lin; i++) {
        for (int j = 0; j < labrinth->n_col; j++) {
            char character;

            do {
                character = fgetc(labrinth_file);
            } while (character == '\n' || character == '\r');

            labrinth->grid[i][j] = character;
        }
    }

    fclose(labrinth_file);
    free(labrinth_file_name);
}

void free_labrinth(labrinth_t *labrinth) {
    for (int i = 0; i < labrinth->n_lin; i++) {
        free(labrinth->grid[i]);
    }
    free(labrinth->grid);
}

bool is_out_of_labrinth(labrinth_t *labrinth, point_t *point) {
    return (
        point->x < 0 || point->x >= labrinth->n_col ||
        point->y < 0 || point->y >= labrinth->n_lin);
}

bool is_free_way(labrinth_t *labrinth, point_t *point) {
    if (is_out_of_labrinth(labrinth, point)) {
        return true;
    }

    return (labrinth->grid[point->y][point->x] != BLOCKED &&
            labrinth->grid[point->y][point->x] != WALKED);
}

bool cross_labrinth(labrinth_t *labrinth) {
    int x = labrinth->current_point.x;
    int y = labrinth->current_point.y;

    labrinth->grid[y][x] = WALKED;

    point_t up, right, down, left;

    up.x = x;
    up.y = y - 1;

    bool was_crossed = false;

    if (is_out_of_labrinth(labrinth, &up) || was_crossed) {
        return true;
    } else if (is_free_way(labrinth, &up)) {
        labrinth->current_point = up;
        was_crossed = cross_labrinth(labrinth);
    }

    right.x = x + 1;
    right.y = y;

    if (is_out_of_labrinth(labrinth, &right) || was_crossed) {
        return true;
    } else if (is_free_way(labrinth, &right)) {
        labrinth->current_point = right;
        was_crossed = cross_labrinth(labrinth);
    }

    down.x = x;
    down.y = y + 1;

    if (is_out_of_labrinth(labrinth, &down) || was_crossed) {
        return true;
    } else if (is_free_way(labrinth, &down)) {
        labrinth->current_point = down;
        was_crossed = cross_labrinth(labrinth);
    }

    left.x = x - 1;
    left.y = y;

    if (is_out_of_labrinth(labrinth, &left) || was_crossed) {
        return true;
    } else if (is_free_way(labrinth, &left)) {
        labrinth->current_point = left;
        was_crossed = cross_labrinth(labrinth);
        return was_crossed;
    } else {
        return false;
    }
}

void print_labrinth(labrinth_t *labrinth) {
    for (int i = 0; i < labrinth->n_lin; i++) {
        for (int j = 0; j < labrinth->n_col; j++) {
            printf("%c", labrinth->grid[i][j]);
        }
        printf("\n");
    }
}

int count_blockers(labrinth_t *labrinth) {
    int n_blockers = 0;

    for (int i = 0; i < labrinth->n_lin; i++) {
        for (int j = 0; j < labrinth->n_col; j++) {
            if (labrinth->grid[i][j] == '#') {
                n_blockers++;
            }
        }
    }

    return n_blockers;
}

int count_freeways(labrinth_t *labrinth) {
    int n_freeways = 0;

    for (int i = 0; i < labrinth->n_lin; i++) {
        for (int j = 0; j < labrinth->n_col; j++) {
            if (labrinth->grid[i][j] == '.') {
                n_freeways++;
            }
        }
    }

    return n_freeways;
}

int count_walkedways(labrinth_t *labrinth) {
    int n_walkedways = 0;

    for (int i = 0; i < labrinth->n_lin; i++) {
        for (int j = 0; j < labrinth->n_col; j++) {
            if (labrinth->grid[i][j] == '*') {
                n_walkedways++;
            }
        }
    }

    return n_walkedways;
}
