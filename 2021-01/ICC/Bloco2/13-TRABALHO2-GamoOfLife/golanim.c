#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MOORE 'M'
#define VON_NEUMANN 'N'

#define ALIVE 'x'
#define DEAD '.'

#define TEMPO 200

typedef struct board {
    int lines;
    int columns;
    char **cells;
} Board;

/* msleep(): Sleep for the requested number of milliseconds. */
void msleep(long msec) {
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

void show_cell(char particula) {
    switch (particula) {
        case ALIVE:
            printf("\033[0;100m");
            break;
        case DEAD:
            printf("\033[0;107m");
            break;
    }
    printf(" \033[0m");
}

void copy_board(Board *destination_board, Board original_board);
void which_neighbors(Board *board_, int i, int j, char neighborhood, char *neighbors[8]);
void update_board(Board *board_, char neighborhood);
void error();

int main(int argc, char *argv[]) {
    Board board;
    scanf("%i %i", &board.lines, &board.columns);
    if (board.lines <= 0 || board.columns <= 0) error();

    int n_gen;
    scanf(" %i\n", &n_gen);
    if (n_gen <= 0) error();

    char neighborhood ;
    neighborhood  = getchar();

    char **Board_Cells = (char **) malloc(board.lines * sizeof(char *));
    board.cells = Board_Cells;
    for (int i = 0; i < board.lines; i++)
        board.cells[i] = (char *) malloc(board.columns * sizeof(char));

    for (int i = 0; i < board.lines; i++)
        for (int j = 0; j < board.columns; j++) {
            scanf(" %c", &board.cells[i][j]);
            char c = getchar();
            if (c == EOF && !(i == board.lines - 1 && j == board.columns - 1))
                error();
            else if (c != EOF) 
                ungetc(c, stdin);
        }

    system("clear");

    for(int g = 0; g < n_gen; g++) {
        for (int i = 0; i < board.lines; i++) {
            for (int j = 0; j < board.columns; j++)
                show_cell(board.cells[i][j]);
            printf("\n");
        }

        msleep(TEMPO);

        update_board(&board, neighborhood);

        system("clear");
    }

    for (int i = 0; i < board.lines; i++)
        free(board.cells[i]);
    free(board.cells);

    return 0;
}

void copy_board(Board *destination_board_, Board original_board) {
    destination_board_->lines = original_board.lines;
    destination_board_->columns = original_board.columns;

    for (int i = 0; i < destination_board_->lines; i++)
        for (int j = 0; j < destination_board_->columns; j++)
            destination_board_->cells[i][j] = original_board.cells[i][j];
}

// Return by reference a vector of 8 char pointers (neighbors).
//  These pointers will point to the 8 neighbors of a (i,j)
//  cell of the Board, depending on the type of neighborhood
void which_neighbors(Board *board_, int i, int j, char neighborhood, char *neighbors[8]) {
    if (neighborhood == MOORE) {
        neighbors[0] = &board_->cells[i][(j + 1) % board_->columns];
        neighbors[1] = &board_->cells[(i + 1) % board_->lines][(j + 1) % board_->columns];
        neighbors[2] = &board_->cells[(i + 1) % board_->lines][j];
        neighbors[3] = &board_->cells[(i + 1) % board_->lines][(board_->columns + j - 1) % board_->columns];
        neighbors[4] = &board_->cells[i][(board_->columns + j - 1) % board_->columns];
        neighbors[5] = &board_->cells[(board_->lines + i - 1) % board_->lines][(board_->columns + j - 1) % board_->columns];
        neighbors[6] = &board_->cells[(board_->lines + i - 1) % board_->lines][j];
        neighbors[7] = &board_->cells[(board_->lines + i - 1) % board_->lines][(j + 1) % board_->columns];
    } else if (neighborhood == VON_NEUMANN) {
        neighbors[0] = &board_->cells[i][(j + 1) % board_->columns];
        neighbors[1] = &board_->cells[i][(j + 2) % board_->columns];
        neighbors[2] = &board_->cells[(i + 1) % board_->lines][j];
        neighbors[3] = &board_->cells[(i + 2) % board_->lines][j];
        neighbors[4] = &board_->cells[i][(board_->columns + j - 1) % board_->columns];
        neighbors[5] = &board_->cells[i][(board_->columns + j - 2) % board_->columns];
        neighbors[6] = &board_->cells[(board_->lines + i - 1) % board_->lines][j];
        neighbors[7] = &board_->cells[(board_->lines + i - 2) % board_->lines][j];
    }
}

// Update the Board 1 generation, depending on the neighborhood type specified
void update_board(Board *board_, char neighborhood) {
    Board new_board;
    new_board.lines = board_->lines;
    new_board.columns = board_->columns;

    char **New_Board_Cells = (char **) malloc(new_board.lines * sizeof(char *));
    new_board.cells = New_Board_Cells;
    for (int i = 0; i < new_board.lines; i++)
        new_board.cells[i] = (char *) malloc(new_board.columns * sizeof(char));

    char *neighbors[8];

    for (int i = 0; i < board_->lines; i++) {
        for (int j = 0; j < board_->columns; j++) {
            int n_alives = 0;

            which_neighbors(board_, i, j, neighborhood, neighbors);

            for (int k = 0; k < 8; k++)
                if (*neighbors[k] == ALIVE) n_alives++;

            if (board_->cells[i][j] == ALIVE) {
                if (n_alives < 2 || n_alives > 3) 
                    new_board.cells[i][j] = DEAD;
                else
                    new_board.cells[i][j] = ALIVE;
            } else if (board_->cells[i][j] == DEAD) {
                if (n_alives == 3)
                    new_board.cells[i][j] = ALIVE;
                else
                    new_board.cells[i][j] = DEAD;
            }
        }
    }

    copy_board(board_, new_board);

    for (int i = 0; i < board_->lines; i++)
        free(new_board.cells[i]);
    free(new_board.cells);
}

void error() {
    printf("Dados de entrada apresentam erro.\n");
    exit(0);
}