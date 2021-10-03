/* ______________________________________________________
 *|  SCC0201 — Introducao a Ciencias da Computacao II    |
 *|             [Segundo Semestre de 2021]               |
 *|                                                      |
 *|------------| Trabalho 01: Campo Minado |-------------|
 *|                                                      |
 *| Codigo por: Helio Nogueira Cardoso - N°USP: 10310227 |
 *|______________________________________________________|
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOMB '*'
#define WHITE_SPACE '.'
#define HIDDEN_CELL 'X'

// Enum for user commands
enum { PRINT_BOARD = 1, PRINT_WITH_HINTS = 2, PLAY = 3 };

typedef struct cell_ {
  char symbol;
  int line;
  int column;
  bool revealed;
} cell_t;

typedef struct board_ {
  int n_columns;
  int n_lines;
  cell_t **grid;
  char *file_path;
} board_t;

char *read_line(FILE *stream);
void identify_dimensions(board_t *board);
void read_board(board_t *board);
void print_board(board_t *board);
void hide_unrevealed_cells(board_t *board);
bool is_out_of_bounds(board_t *board, cell_t *cell);
cell_t *surroundings(cell_t *cell);
char count_bombs_around(board_t *board, cell_t *cell);
void show_hints(board_t *board);
void recursively_play_board(board_t *board, cell_t *cell);
void play_guess(board_t *board, cell_t *cell);
void free_board(board_t *board);

int main() {
  board_t board;

  board.file_path = NULL;
  board.grid = NULL;

  int command = 0;
  int line, column;

  scanf(" %d", &command);

  read_board(&board);

  switch (command) {
    case PRINT_BOARD:
      break;
    case PRINT_WITH_HINTS:
      show_hints(&board);

      break;
    case PLAY:
      scanf(" %d %d", &line, &column);
      play_guess(&board, &board.grid[line][column]);

      break;
  }

  print_board(&board);

  free_board(&board);

  return EXIT_SUCCESS;
}

/* |read_line|
 * Reads a line from the specified stream, allocating the string in heap memory.
 * Returns the respective pointer to allocated string.
 *
 * @param stream (FILE *): stream from where to read the line.
 * @return (char *): pointer to the first byte of the allocated string.
 */
char *read_line(FILE *stream) {
  char *line = NULL;
  char c;
  int n_chars = 0;

  while ((c = fgetc(stream)) == '\n' || (c == '\r'))
    ;

  if (c != EOF) ungetc(c, stream);

  do {
    c = fgetc(stream);

    n_chars++;
    line = (char *)realloc(line, n_chars * sizeof(char) + 1);

    if (c != '\n' && c != EOF)
      *(line + n_chars - 1) = c;
    else
      *(line + n_chars - 1) = '\0';
  } while (c != '\n' && c != EOF);

  return line;
}

/* |identify_dimensions|
 * Fills the dimensions of the board passed by reference.
 *
 * @param board (board_t *): pointer to the board whose dimensions will be
 * identified.
 */
void identify_dimensions(board_t *board) {
  FILE *board_file = NULL;

  board_file = fopen(board->file_path, "r");

  // Counting number of columns
  char *line = read_line(board_file);

  // Assign to number of columns the length of the first
  board->n_columns = strlen(line);

  // Counting number of lines
  board->n_lines = 1;

  // Incrementing number of lines after reading each line
  while (fgets(line, board->n_columns + 2, board_file) != NULL) {
    (board->n_lines)++;
  }

  fclose(board_file);
  free(line);
}

/* |read_board|
 * Fills the passed board grid, readind its file_path from stdin.
 *
 * @param board (board_t *): pointer to the board whose dimensions will be
 * identified.
 */
void read_board(board_t *board) {
  FILE *board_file = NULL;

  // Open board file
  board->file_path = read_line(stdin);
  board_file = fopen(board->file_path, "r");

  // Identify board grid dimensions
  identify_dimensions(board);

  // Allocate board grid in Heap Memory
  board->grid = (cell_t **)malloc(board->n_lines * sizeof(cell_t *));

  for (int i = 0; i < board->n_lines; i++) {
    board->grid[i] = (cell_t *)malloc(board->n_columns * sizeof(cell_t));
  }

  // Load board grid from file
  for (int i = 0; i < board->n_lines; i++) {
    for (int j = 0; j < board->n_columns; j++) {
      board->grid[i][j].symbol = fgetc(board_file);
      board->grid[i][j].line = i;
      board->grid[i][j].column = j;
      board->grid[i][j].revealed = false;  // unrevealed by default
    }
    fgetc(board_file);  // Consume '\n' at the end of each line
  }

  // Close file
  fclose(board_file);
}

/* |print_board|
 * Prints the passed board grid onto stdout.
 *
 * @param board (board_t *): pointer to the board to be printed.
 */
void print_board(board_t *board) {
  for (int i = 0; i < board->n_lines; i++) {
    for (int j = 0; j < board->n_columns; j++) {
      printf("%c", board->grid[i][j].symbol);
    }
    printf("\n");
  }
}

/* |hide_unrevealed_cells|
 * Hide the cells of a board with status revealed equal to false.
 * "Hiding" means to assing a 'X' char to cell symbol.
 *
 * @param board (board_t *): pointer to the board where the unrevealed cells
 * will be hidden.
 */
void hide_unrevealed_cells(board_t *board) {
  for (int i = 0; i < board->n_lines; i++) {
    for (int j = 0; j < board->n_columns; j++) {
      if (!board->grid[i][j].revealed) {
        board->grid[i][j].symbol = HIDDEN_CELL;
      }
    }
  }
}

/* |is_out_of_bounds|
 * Checks whether the specified cell is out of the passed board grid.
 *
 * @param board (board_t *): pointer to the board where to check.
 * @param cell (cell_t *): pointer to cell to be checked.
 * @return (bool): true if the cell is out of the passed board grid bounds.
 */
bool is_out_of_bounds(board_t *board, cell_t *cell) {
  return (cell->column < 0 || cell->column >= board->n_columns) ||
         (cell->line < 0 || cell->line >= board->n_lines);
}

/* |surroundings|
 * Allocates a vector of cells and assigns to it the 8 cells in the surrounding
 * positions of the specified cell.
 *
 * @param cell (cell_t *): pointer to cell whose surroundings will be saved to
 * the vector to be returned.
 * @return (cell_t *): pointer to the first byte of the allocated vector of
 * cells around the specified cell.
 */
cell_t *surroundings(cell_t *cell) {
  cell_t up, up_right, right, down_right, down, down_left, left, up_left;

  up.column = cell->column;
  up.line = cell->line - 1;

  up_right.column = cell->column + 1;
  up_right.line = cell->line - 1;

  right.column = cell->column + 1;
  right.line = cell->line;

  down_right.column = cell->column + 1;
  down_right.line = cell->line + 1;

  down.column = cell->column;
  down.line = cell->line + 1;

  down_left.column = cell->column - 1;
  down_left.line = cell->line + 1;

  left.column = cell->column - 1;
  left.line = cell->line;

  up_left.column = cell->column - 1;
  up_left.line = cell->line - 1;

  cell_t *cells_around;

  cells_around = (cell_t *)malloc(8 * sizeof(cell_t));

  cells_around[0] = up;
  cells_around[1] = up_right;
  cells_around[2] = right;
  cells_around[3] = down_right;
  cells_around[4] = down;
  cells_around[5] = down_left;
  cells_around[6] = left;
  cells_around[7] = up_left;

  return cells_around;
}

/* |count_bombs_around|
 * Counts the bombs within the the specified cell neighborhood; Returns an ASCII
 * character from '0' to '8'.
 *
 * @param board (board_t *): pointer to the board where to check.
 * @param cell (cell_t *): pointer to cell whose neighborhood will be checked.
 *
 * @return (char): ASCII character from '0' to '8' representing the numbers of
 * bombs around the specified cell on the board grid.
 */
char count_bombs_around(board_t *board, cell_t *cell) {
  cell_t *cells_around = surroundings(cell);

  int n_bombs_around = 0;

  for (int i = 0; i < 8; i++) {
    if (!is_out_of_bounds(board, &cells_around[i])) {
      if (board->grid[cells_around[i].line][cells_around[i].column].symbol ==
          BOMB) {
        n_bombs_around++;
      }
    }
  }

  free(cells_around);

  return ('0' + n_bombs_around);
}

/* |show_hints|
 * Changes the passed board grid symbols in order to show the numerical hints
 * that represent the number of bombs around each cell (which is not a bomb)
 * with 1 or more bombs around it.
 *
 * @param board (board_t *): pointer to the board where to check.
 * @param cell (cell_t *): pointer to cell whose neighborhood will be checked.
 */
void show_hints(board_t *board) {
  for (int i = 0; i < board->n_lines; i++) {
    for (int j = 0; j < board->n_columns; j++) {
      cell_t cur_cell;

      cur_cell.line = i;
      cur_cell.column = j;

      char char_to_show = count_bombs_around(board, &cur_cell);

      if (board->grid[i][j].symbol == BOMB) {
        char_to_show = BOMB;
      } else if (char_to_show == '0') {
        char_to_show = WHITE_SPACE;
      }

      board->grid[i][j].symbol = char_to_show;
    }
  }
}

/* |recursively_play_board|
 * Since a white space has been selected, the board must be recursively
 * revealed. The first cell passed is a white space cell. The revelation is made
 * by changing the revealed status of each current cell (false, by default) to
 * true. There are 3 stopping conditions:
 *  1. Current cell is out of the board grid bounds;
 *  2. Current cell revealed status is true (meaning it has already been
 * checked);
 *  3. Current cell symbol is a numerical hint (changes current revealed status
 * to true before returning, though).
 *
 * The recursive step consists on changing the revealed status of the current
 * cell to true and call this function recusively for the 8 surrounding cells.
 *
 * @param board (board_t *): pointer to the board to play.
 * @param cell (cell_t *): pointer to the current cell to be checked.
 */
void recursively_play_board(board_t *board, cell_t *cell) {
  if (is_out_of_bounds(board, cell)) {
    return;
  }

  if (board->grid[cell->line][cell->column].revealed) {
    return;
  }

  board->grid[cell->line][cell->column].revealed = true;

  char current_char = board->grid[cell->line][cell->column].symbol;

  if (current_char >= '1' && current_char <= '8') {
    return;
  }

  cell_t *cells_around = surroundings(cell);

  for (int i = 0; i < 8; i++) {
    recursively_play_board(board, &cells_around[i]);
  }

  free(cells_around);

  return;
}

/* |play_guess|
 * Plays the passed board on the specified cell. That means one out of three
 * things, depending on the selected cell symbol:
 *  1. Bomb: reveals the whole board with hints;
 *  2. White Space: plays the board recursively from select cell, revealing
 * cells within the area delimited by numerical hints and the board grid bounds;
 *  3. Numerical Hint: reveals only the selected cell with the numerical hint
 *     and hide the rest of the board.
 *
 * @param board (board_t *): pointer to the board to play.
 * @param cell (cell_t *): pointer to the selected cell to be played.
 */
void play_guess(board_t *board, cell_t *cell) {
  show_hints(board);

  char selected_char = board->grid[cell->line][cell->column].symbol;

  if (selected_char == BOMB) {
    return;
  } else if (selected_char == WHITE_SPACE) {
    recursively_play_board(board, cell);
  } else {  // Numerical Hint
    board->grid[cell->line][cell->column].revealed = true;
  }

  hide_unrevealed_cells(board);
}

/* |free_board|
 * Frees all allocated memory related to the specified board; Asserts that each
 * respective pointer is not NULL before freeing.
 *
 * @param board (board_t *): pointer to the board to be freed from memory.
 */
void free_board(board_t *board) {
  if (board->file_path) {
    free(board->file_path);
  }

  if (board->grid) {
    for (int i = 0; i < board->n_lines; i++) {
      if (board->grid[i]) {
        free(board->grid[i]);
      }
    }

    free(board->grid);
  }
}
