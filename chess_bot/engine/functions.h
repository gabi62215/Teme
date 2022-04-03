#ifndef PROIECT_FUNCTIONS_H
#define PROIECT_FUNCTIONS_H

/*
 * Initializes internal chess table and resets variables such as castling
 * permissions to allow castling, engine_side to black
 */
void init_board();

/*
 * Receives two integers indicating the coordinates from where the piece is
 * taken and to where it is moved
 * Returns a string with the format "e2e4"
 */
char *moveStringFromInt(int from, int to);

/* Generates all pseudo-legal moves and stores them in the moves array */
void generate_move();

/* Checks if given side is in check */
int in_check(int side);

/* Checks if given square could be attacked by given side
 * Returns 1 if square is attacked by given side
 *         0 if not
 */
int attack(int square, int side);

/* Takes the coordinates of a move and returns its score */
int move_score(int from, int to);


/*
 * Picks randomly a legal move from the moves with the best score
 * Returns a string, representing the move
 */
char *get_move();

/* Save current board state */
void save_undo();

/* Get last board state */
void undo_move();

/*
 * Receives a move as a string with the format "e2e4" or "e7e8q" (promotion)
 * and updates the internal chess table
 * Returns -1 if it is an invalid move according to the internal chess table
 *          1 if it is a valid move
 */
int registerMove(char *move);

/* Prints to stdout the representation of the current internal chess table */
void printTable();

#endif //PROIECT_FUNCTIONS_H
