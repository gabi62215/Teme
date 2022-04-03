#include "definitions.h"
#include <vector>

#ifndef PROIECT_VARIABLES_H
#define PROIECT_VARIABLES_H
using namespace std;

/* Global variables definitions to use in any source file */

/* Board representation */
extern vector<int> color;
extern vector<int> piece;

/* Current side */
extern int side;

/* Side engine is playing */
extern int engine_side;

/*
 * castle[0] == 1 => white can castle queen side
 * castle[1] == 1 => white can castle king side
 * castle[2] == 1 => black can castle queen side
 * castle[3] == 1 => black can castle king side
 */
extern vector<int> castle;

/*
 * En passant square, if a pawn is moved two squares,
 * the value will be the square in the middle (if white moves e2e4, ep_sq = e3)
 */
extern int ep_sq;

/*
 * Array which will contain all pseudo-legal moves for the current
 * state of the table
 */
extern vector<struct Move> moves;

/*
 * Matrix which stores offsets from a given square to which a piece can be moved
 * offsets[BISHOP] will be an array containing -11, -9, 9, 11 meaning that
 * the bishop can move down-left, down-right, up-right, up-left
 */
extern vector <vector<int>> offsets;

/* Arrays used for edge detection */
extern vector<int> table120;
extern vector<int> table64;


/* Undo move */
extern vector<int> undo_color;
extern vector<int> undo_piece;
extern vector<int> undo_castle;
extern int undo_ep_sq;

/* Initial board state */
extern vector<int> init_color;
extern vector<int> init_piece;

#endif //PROIECT_VARIABLES_H
