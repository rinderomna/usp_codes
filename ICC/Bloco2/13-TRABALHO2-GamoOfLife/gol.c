// Hélio Nogueira Cardoso - N°USP: 10310227
// Trabalho 2 - SCC0221 - Introdução à Ciência de Computação I (2021.01)

#include <stdio.h>
#include <stdlib.h>

#define MOORE 'M'
#define VON_NEUMANN 'N'

#define ALIVE 'x'
#define DEAD '.'

typedef struct board {
    int n_lines;
    int n_columns;
    char neighborhood;
    char **cells;
} Board;

void copy_board(Board *destination_board, Board original_board);
void which_neighbors(Board *board_, int i, int j, char neighbors[8]);
void update_board(Board *board_);
void error();

int main() {
    Board board;
    scanf("%i %i", &board.n_lines, &board.n_columns);
    if (board.n_lines <= 0 || board.n_columns <= 0) error();

    int n_gen;
    scanf(" %i\n", &n_gen);
    if (n_gen <= 0) error();

    board.neighborhood = getchar();
    if (board.neighborhood != MOORE && board.neighborhood != VON_NEUMANN) error();

    char **Board_Cells = (char **) malloc(board.n_lines * sizeof(char *));
    board.cells = Board_Cells;
    for (int i = 0; i < board.n_lines; i++) 
        board.cells[i] = (char *) malloc(board.n_columns * sizeof(char));

    for (int i = 0; i < board.n_lines; i++)
        for (int j = 0; j < board.n_columns; j++)
            scanf(" %c", &board.cells[i][j]);

    for (int g = 0; g < n_gen; g++) update_board(&board);

    for (int i = 0; i < board.n_lines; i++) {
        for (int j = 0; j < board.n_columns; j++) printf("%c", board.cells[i][j]);
        printf("\n");
    }

    for (int i = 0; i < board.n_lines; i++) free(board.cells[i]);
    free(board.cells);

    return 0;
}

void copy_board(Board *destination_board_, Board original_board) {
    destination_board_->n_lines = original_board.n_lines;
    destination_board_->n_columns = original_board.n_columns;

    for (int i = 0; i < destination_board_->n_lines; i++)
        for (int j = 0; j < destination_board_->n_columns; j++)
            destination_board_->cells[i][j] = original_board.cells[i][j];
}

// Change by reference an array of 8 chars (neighbors).
//  These will be the 8 neighbors of a (i,j) cell of the board,
//  depending on the type of neighborhood (Moore or Von Neumann)
void which_neighbors(Board *board_, int i, int j, char neighbors[8]) {
    int n_lin = board_->n_lines;
    int n_col = board_->n_columns;

    if (board_->neighborhood == MOORE) {
        neighbors[0] = board_->cells[i][(j + 1) % n_col];
        neighbors[1] = board_->cells[(i + 1) % n_lin][(j + 1) % n_col];
        neighbors[2] = board_->cells[(i + 1) % n_lin][j];
        neighbors[3] = board_->cells[(i + 1) % n_lin][(n_col + j - 1) % n_col];
        neighbors[4] = board_->cells[i][(n_col + j - 1) % n_col];
        neighbors[5] = board_->cells[(n_lin + i - 1) % n_lin][(n_col + j - 1) % n_col];
        neighbors[6] = board_->cells[(n_lin + i - 1) % n_lin][j];
        neighbors[7] = board_->cells[(n_lin + i - 1) % n_lin][(j + 1) % n_col];
    } else if (board_->neighborhood == VON_NEUMANN) {
        neighbors[0] = board_->cells[i][(j + 1) % n_col];
        neighbors[1] = board_->cells[i][(j + 2) % n_col];
        neighbors[2] = board_->cells[(i + 1) % n_lin][j];
        neighbors[3] = board_->cells[(i + 2) % n_lin][j];
        neighbors[4] = board_->cells[i][(n_col + j - 1) % n_col];
        neighbors[5] = board_->cells[i][(n_col + j - 2) % n_col];
        neighbors[6] = board_->cells[(n_lin + i - 1) % n_lin][j];
        neighbors[7] = board_->cells[(n_lin + i - 2) % n_lin][j];
    }
}

// Update the Board 1 generation, depending on the neighborhood type specified
void update_board(Board *board_) {
    Board new_board;
    new_board.n_lines = board_->n_lines;
    new_board.n_columns = board_->n_columns;

    char **new_board_cells = (char **) malloc(new_board.n_lines * sizeof(char *));
    new_board.cells = new_board_cells;
    for (int i = 0; i < new_board.n_lines; i++)
        new_board.cells[i] = (char *) malloc(new_board.n_columns * sizeof(char));

    char neighbors[8];

    for (int i = 0; i < board_->n_lines; i++) {
        for (int j = 0; j < board_->n_columns; j++) {
            int n_alive = 0;

            which_neighbors(board_, i, j, neighbors);

            for (int k = 0; k < 8; k++)
                if (neighbors[k] == ALIVE) n_alive++;

            if (board_->cells[i][j] == ALIVE)
              new_board.cells[i][j] = (n_alive < 2 || n_alive > 3) ? DEAD : ALIVE;
            else if (board_->cells[i][j] == DEAD)
              new_board.cells[i][j] = (n_alive == 3) ? ALIVE : DEAD;
        } 
  }
    copy_board(board_, new_board);

    for (int i = 0; i < board_->n_lines; i++) free(new_board.cells[i]);
    free(new_board.cells);
}

void error() {
    printf("Dados de entrada apresentam erro.\n");
    exit(0);
}