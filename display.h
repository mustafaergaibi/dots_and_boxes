#ifndef DISPLAY_H
#define DISPLAY_H

#include "board.h"

/* ---- Implemented by teammate in display.c ---- */

/* Prints the grid like the sample run:
 *     0 1 2 3 4 5
 *   0 . . . .-. .
 *           |A| |
 * Reads b->h, b->v and b->box. */
void display_board(const Board *b);

/* Prints the ***** line, "Player A score: x", "Player B score: y", ***** line. */
void display_scores(const Board *b);

/* "Player A's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:" */
void display_prompt(char player);

/* Tells the player the move was invalid. */
void display_invalid_move(void);

/* Final result. winner is 'A', 'B', or 'T' for a tie. */
void display_winner(const Board *b, char winner);

#endif
