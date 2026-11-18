#ifndef BOARD_H
#define BOARD_H

/* Grid size: 5 x 6 dots  ->  4 x 5 boxes */
#define DOT_ROWS 5
#define DOT_COLS 6
#define BOX_ROWS (DOT_ROWS - 1)
#define BOX_COLS (DOT_COLS - 1)
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS)

#define EMPTY_BOX ' '

typedef struct {
    int  h[DOT_ROWS][DOT_COLS - 1];  /* h[r][c] = 1 if line (r,c)-(r,c+1) is drawn */
    int  v[DOT_ROWS - 1][DOT_COLS];  /* v[r][c] = 1 if line (r,c)-(r+1,c) is drawn */
    char box[BOX_ROWS][BOX_COLS];    /* EMPTY_BOX, 'A' or 'B' */
    int  score[2];                   /* score[0] = A, score[1] = B */
} Board;

/* Resets every line, box and score. */
void board_init(Board *b);

/* 1 if (r1,c1)-(r2,c2) is a legal move: both dots on the grid,
 * the dots are adjacent (no diagonals), and the line is not drawn yet. */
int board_is_valid_move(const Board *b, int r1, int c1, int r2, int c2);

/* Draws the line for `player` ('A' or 'B') and awards any boxes it completes.
 * Assumes the move is valid. Returns how many boxes were completed (0, 1 or 2). */
int board_apply_move(Board *b, int r1, int c1, int r2, int c2, char player);

/* 1 if box (r,c) has all four sides drawn. */
int board_box_complete(const Board *b, int r, int c);

/* 1 when every box has been claimed. */
int board_game_over(const Board *b);

/* 'A', 'B', or 'T' for a tie. Only meaningful when the game is over. */
char board_winner(const Board *b);

/* Score of player 'A' or 'B'. */
int board_score(const Board *b, char player);

#endif
