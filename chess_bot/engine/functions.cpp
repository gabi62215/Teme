#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <ctime>
#include <climits>
#include <algorithm>
#include "variables.h"
#include "definitions.h"
#include "functions.h"

using namespace std;

void init_board() {
    color = init_color;
    piece = init_piece;
    castle.assign(4, 1);
    ep_sq = -1;
    side = WHITE;
    engine_side = BLACK;
}

char *moveStringFromInt(int from, int to) {
    // Invalid move
    if (from < 0 || from >= 64 || to < 0 || to >= 64)
        return nullptr;
    char *result = (char *) (calloc(5, sizeof(char)));
    result[0] = from % 8 + 'a';
    result[1] = 8 - from / 8 + '0';
    result[2] = to % 8 + 'a';
    result[3] = 8 - to / 8 + '0';
    result[4] = '\0';
    return result;
}

int in_check(int side) {
    for (int i = 0; i < 64; i++)
        // Find square where king is situated
        if (piece[i] == KING && color[i] == side)
            // Check if square is under attack by opposite side
            return attack(i, !side);
    return 1;
}

void insert_move(int from, int to) {
    moves.emplace_back(from, to, move_score(from, to));
}

void generate_move() {
    moves.clear();
    for (int i = 0; i < 64; i++) {
        if (color[i] == side) {
            // Castling
            if (piece[i] == KING) {
                if (side == WHITE) {
                    if (castle[0] == 1)
                        // Queen side white castling
                        if (!in_check(WHITE) &&
                            piece[D1] == EMPTY && !attack(D1, BLACK) &&
                            piece[C1] == EMPTY && !attack(C1, BLACK) &&
                            piece[B1] == EMPTY && !attack(B1, BLACK))
                            insert_move(i, i - 2);

                    if (castle[1] == 1)
                        // King side white castling
                        if (!in_check(WHITE) &&
                            piece[F1] == EMPTY && !attack(F1, BLACK) &&
                            piece[G1] == EMPTY && !attack(G1, BLACK))
                            insert_move(i, i + 2);
                }
                if (side == BLACK) {
                    if (castle[2] == 1)
                        // Queen side black castling
                        if (!in_check(BLACK) &&
                            piece[D8] == EMPTY && !attack(D8, WHITE) &&
                            piece[C8] == EMPTY && !attack(C8, WHITE) &&
                            piece[B8] == EMPTY && !attack(B8, WHITE))
                            insert_move(i, i - 2);
                    if (castle[3] == 1)
                        // King side black castling
                        if (!in_check(BLACK) &&
                            piece[F8] == EMPTY && !attack(F8, WHITE) &&
                            piece[G8] == EMPTY && !attack(G8, WHITE))
                            insert_move(i, i + 2);
                }
            }

            // Pawn moves, including en passant
            if (piece[i] == PAWN) {
                if (side == WHITE) {
                    if (CHECK_BOUNDS(i - 9) &&
                        (color[i - 9] == BLACK || ep_sq == i - 9) &&
                        i % 8 != 0)
                        insert_move(i, i - 9);
                    if (CHECK_BOUNDS(i - 7) &&
                        (color[i - 7] == BLACK || ep_sq == i - 7) &&
                        i % 8 != 7)
                        insert_move(i, i - 7);
                    if (CHECK_BOUNDS(i - 8) && color[i - 8] == EMPTY) {
                        insert_move(i, i - 8);
                        if (CHECK_BOUNDS(i - 16) &&
                            color[i - 16] == EMPTY &&
                            piece[i] == init_piece[i])
                            insert_move(i, i - 16);
                    }
                } else if (side == BLACK) {
                    if (CHECK_BOUNDS(i + 9) &&
                        (color[i + 9] == WHITE || ep_sq == i + 9) &&
                        i % 8 != 7)
                        insert_move(i, i + 9);
                    if (CHECK_BOUNDS(i + 7) &&
                        (color[i + 7] == WHITE || ep_sq == i + 7) &&
                        i % 8 != 0)
                        insert_move(i, i + 7);
                    if (CHECK_BOUNDS(i + 8) && color[i + 8] == EMPTY) {
                        insert_move(i, i + 8);
                        if (CHECK_BOUNDS(i + 16) &&
                            color[i + 16] == EMPTY &&
                            piece[i] == init_piece[i])
                            insert_move(i, i + 16);
                    }
                }
            } else {
                // Moves for all pieces except pawns
                // Get each offset in offset array and
                for (int offset : offsets[piece[i]]) {
                    int to = i;
                    while (to != -1) {
                        // Check if current move is on table
                        to = table120[table64[to] + offset];
                        // Invalid move
                        if (to == -1)
                            break;
                        // If current move is over another piece
                        // move generation will be over for sliding pieces
                        // (rook, bishop, queen)
                        if (color[to] != EMPTY) {
                            if (color[to] == !side)
                                insert_move(i, to);
                            break;
                        } else
                            insert_move(i, to);

                        // Since the rook, bishop and queen can move more than
                        // one square in one direction, the knight and the king
                        // are stopped from generating more moves
                        if (piece[i] == KNIGHT || piece[i] == KING)
                            break;
                    }
                }
            }
        }
    }
}

// Similar to generate move, removed moves from pawns which do not capture
int attack(int sq, int side) {
    for (int i = 0; i < 64; ++i) {
        if (color[i] == side) {
            // Check if square is attacked by pawn
            if (piece[i] == PAWN) {
                if (side == WHITE) {
                    if (CHECK_BOUNDS(i - 9) && i % 8 != 0 && i - 9 == sq)
                        return 1;
                    if (CHECK_BOUNDS(i - 7) && i % 8 != 7 && i - 7 == sq)
                        return 1;
                } else {
                    if (CHECK_BOUNDS(i + 7) && i % 8 != 0 && i + 7 == sq)
                        return 1;
                    if (CHECK_BOUNDS(i + 9) && i % 8 != 7 && i + 9 == sq)
                        return 1;
                }
            }
            // Check if square is attacked by any other piece except pawn
            if (piece[i] != PAWN) {
                for (int offset : offsets[piece[i]]) {
                    int to = i;
                    while (to != -1) {
                        to = table120[table64[to] + offset];

                        if (to == -1)
                            break;
                        if (to == sq)
                            return 1;
                        if (color[to] != EMPTY)
                            break;
                        if (piece[i] == KNIGHT || piece[i] == KING)
                            break;
                    }
                }
            }
        }
    }
    return 0;
}

int move_score(int from, int to) {
    int score = 0;
    // Prioritize certain moves, like castling, en passant and pawn promotion
    if (piece[from] == KING && abs(to - from) == 2) {
        score = INT_MAX;
    } else if (piece[from] == PAWN && ep_sq == to) {
        score = INT_MAX - 1;
    } else if (piece[from] == PAWN && (to <= 7 || to >= 56)) {
        score = INT_MAX - 2;
    } else {
        if (piece[to] != EMPTY) {
            if (!attack(to, !side)) {
                // If the destination square isn't defended, it's a good move
                score = (piece[to] + 1) * 20;
            } else {
                // If it's defended, it depends on the piece we sacrifice
                score = (piece[to] - piece[from] + 1) * 10;
            }
        } else {
//            score = EMPTY - piece[from];
            // If this move gets a piece out of the initial position, it's good
            if (piece[from] == init_piece[from] &&
                color[from] == init_color[from]) {
                score += 1;
            }
        }
    }
    return score;
}

int move_compare(Move x, Move y) {
    return x.score > y.score;
}

char *get_move() {
    // Sort moves based on score
    sort(moves.begin(), moves.end(), move_compare);
    // If no moves were generated, return null
    if (moves.size() < 0)
        return nullptr;

    save_undo();
    // Get a random move with the best score
    int stop = 0;
    while (stop < moves.size() && moves[stop].score == moves[0].score) {
        stop++;
    }
    srand(time(0));
    int r = rand() % stop;
    registerMove(moveStringFromInt(moves[r].from, moves[r].to));
    // If it is a legal move, return it, otherwise undo and look for another one
    if (!in_check(side))
        return moveStringFromInt(moves[r].from, moves[r].to);
    else
        undo_move();

    // Look for best legal move
    for (auto move : moves) {
        save_undo();
        registerMove(moveStringFromInt(move.from, move.to));
        if (!in_check(side))
            return moveStringFromInt(move.from, move.to);
        else
            undo_move();
    }
    return nullptr;
}

void undo_move() {
    piece = undo_piece;
    color = undo_color;
    castle = undo_castle;
    ep_sq = undo_ep_sq;
}

void save_undo() {
    undo_piece = piece;
    undo_color = color;
    undo_castle = castle;
    undo_ep_sq = ep_sq;
}

int registerMove(char *move_string) {
    // Verify if it is a valid string
    if (move_string[0] < 'a' || move_string[0] > 'h' ||
        move_string[1] < '0' || move_string[1] > '9' ||
        move_string[2] < 'a' || move_string[2] > 'h' ||
        move_string[3] < '0' || move_string[3] > '9')
        return -1;

    // Get coordinates from string
    int from, to;
    from = move_string[0] - 'a';
    from += 8 * (8 - (move_string[1] - '0'));
    to = move_string[2] - 'a';
    to += 8 * (8 - (move_string[3] - '0'));

    // No piece to be moved from given location, means it is an invalid move
    if (piece[from] == EMPTY || color[from] == EMPTY) {
        return -1;
    }

    // Verify if it is a castle move
    if (piece[from] == KING) {
        // Check if it is valid
        if (from == E1 && to == C1 && castle[0] == 1) {
            // If already in check or if king passes through check or squares
            // are not free, it is an invalid move
            if (in_check(color[from]) ||
                piece[D1] != EMPTY || attack(D1, !color[from]) ||
                piece[C1] != EMPTY || attack(C1, !color[from]) ||
                piece[B1] != EMPTY || attack(B1, !color[from]))
                return -1;
            // Update only rook's position, king will be modified later in function
            piece[A1] = EMPTY;
            color[A1] = EMPTY;
            piece[D1] = ROOK;
            color[D1] = color[from];
        } else if (from == E1 && to == G1 && castle[1] == 1) {
            if (in_check(color[from]) ||
                piece[F1] != EMPTY || attack(F1, !color[from]) ||
                piece[G1] != EMPTY || attack(G1, !color[from]))
                return -1;
            piece[H1] = EMPTY;
            color[H1] = EMPTY;
            piece[F1] = ROOK;
            color[F1] = color[from];
        } else if (from == E8 && to == C8 && castle[2] == 1) {
            if (in_check(color[from]) ||
                piece[D8] != EMPTY || attack(D8, !color[from]) ||
                piece[C8] != EMPTY || attack(C8, !color[from]) ||
                piece[B8] != EMPTY || attack(B8, !color[from]))
                return -1;
            piece[A8] = EMPTY;
            color[A8] = EMPTY;
            piece[D8] = ROOK;
            color[D8] = color[from];
        } else if (from == E8 && to == G8 && castle[3] == 1) {
            if (in_check(color[from]) ||
                piece[F8] != EMPTY || attack(F8, !color[from]) ||
                piece[G8] != EMPTY || attack(G8, !color[from]))
                return -1;
            piece[H8] = EMPTY;
            color[H8] = EMPTY;
            piece[F8] = ROOK;
            color[F8] = color[from];
        }

        // If king has moved, update castling permissions
        if (color[from] == WHITE) {
            castle[0] = 0;
            castle[1] = 0;
        } else if (color[from] == BLACK) {
            castle[2] = 0;
            castle[3] = 0;
        }
    }

    // If rook has moved, update castling permissions
    if (piece[from] == ROOK) {
        switch (from) {
            case A1:
                castle[0] = 0;
                break;
            case H1:
                castle[1] = 0;
                break;
            case A8:
                castle[2] = 0;
                break;
            case H8:
                castle[3] = 0;
                break;
        }
    }

    // If rook was captured, update castling permissions
    if (piece[to] == ROOK) {
        switch (to) {
            case A1:
                castle[0] = 0;
                break;
            case H1:
                castle[1] = 0;
                break;
            case A8:
                castle[2] = 0;
                break;
            case H8:
                castle[3] = 0;
                break;
        }
    }

    // If it is an en passant move, erase the pawn
    if (ep_sq != -1 && piece[from] == PAWN) {
        if (side == WHITE && to == ep_sq) {
            color[ep_sq + 8] = EMPTY;
            piece[ep_sq + 8] = EMPTY;
        }
        if (side == BLACK && to == ep_sq) {
            color[ep_sq - 8] = EMPTY;
            piece[ep_sq - 8] = EMPTY;
        }
    }

    // If a pawn moved, update en passant square
    if (piece[from] == PAWN) {
        if (side == WHITE) {
            if (to == from - 16)
                ep_sq = from - 8;
        } else if (side == BLACK) {
            if (to == from + 16)
                ep_sq = from + 8;
        }
        if (abs(from - to) != 16)
            ep_sq = -1;
    } else {
        ep_sq = -1;
    }

    piece[to] = piece[from];
    color[to] = color[from];

    // If it is a promotion, change the pawn to the given piece
    if (piece[from] == PAWN &&
        (move_string[3] == '8' || move_string[3] == '1')) {
        switch (move_string[4]) {
            case 'n':
                piece[to] = KNIGHT;
                break;
            case 'b':
                piece[to] = BISHOP;
                break;
            case 'r':
                piece[to] = ROOK;
                break;
            default:
                piece[to] = QUEEN; // either not specified or 'q'
        }
    }

    piece[from] = EMPTY;
    color[from] = EMPTY;
    return 1;
}

void printTable() {
    vector <vector<char>> table_char{{'P', 'N', 'B', 'R', 'Q', 'K'},
                                     {'p', 'n', 'b', 'r', 'q', 'k'}};
    for (int i = 0; i < 64; i++) {
        if (color[i] == EMPTY || piece[i] == EMPTY)
            printf(". ");
        else
            printf("%c ", table_char[color[i]][piece[i]]);
        if ((i + 1) % 8 == 0)
            printf("\n");
    }
    printf("\n");
}
