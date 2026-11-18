#include "board.h"

static int player_index(char player) {
    return player == 'A' ? 0 : 1;
}

static int dot_on_grid(int r, int c) {
    return r >= 0 && r < DOT_ROWS && c >= 0 && c < DOT_COLS;
}

static int abs_int(int x) {
    return x < 0 ? -x : x;
}

/* Orders the two dots so (r1,c1) is the top/left one.
 * This makes "0 4 0 3" and "0 3 0 4" mean the same line. */
static void normalize(int *r1, int *c1, int *r2, int *c2) {
    if (*r2 < *r1 || (*r2 == *r1 && *c2 < *c1)) {
        int tr = *r1, tc = *c1;
        *r1 = *r2; *c1 = *c2;
        *r2 = tr;  *c2 = tc;
    }
}

void board_init(Board *b) {
    for (int r = 0; r < DOT_ROWS; r++)
        for (int c = 0; c < DOT_COLS - 1; c++)
            b->h[r][c] = 0;
    for (int r = 0; r < DOT_ROWS - 1; r++)
        for (int c = 0; c < DOT_COLS; c++)
            b->v[r][c] = 0;
    for (int r = 0; r < BOX_ROWS; r++)
        for (int c = 0; c < BOX_COLS; c++)
            b->box[r][c] = EMPTY_BOX;
    b->score[0] = 0;
    b->score[1] = 0;
}

int board_is_valid_move(const Board *b, int r1, int c1, int r2, int c2) {
    if (!dot_on_grid(r1, c1) || !dot_on_grid(r2, c2))
        return 0;
    if (abs_int(r1 - r2) + abs_int(c1 - c2) != 1)   /* must be neighbours */
        return 0;
    normalize(&r1, &c1, &r2, &c2);
    if (r1 == r2)                 /* horizontal line */
        return !b->h[r1][c1];
    return !b->v[r1][c1];         /* vertical line */
}

int board_box_complete(const Board *b, int r, int c) {
    return b->h[r][c] && b->h[r + 1][c] && b->v[r][c] && b->v[r][c + 1];
}

/* Gives box (r,c) to player if it is complete and still unclaimed. */
static int try_claim(Board *b, int r, int c, char player) {
    if (r < 0 || r >= BOX_ROWS || c < 0 || c >= BOX_COLS)
        return 0;
    if (b->box[r][c] != EMPTY_BOX || !board_box_complete(b, r, c))
        return 0;
    b->box[r][c] = player;
    b->score[player_index(player)]++;
    return 1;
}

/* A line touches at most two boxes, so only those two are checked: O(1). */
int board_apply_move(Board *b, int r1, int c1, int r2, int c2, char player) {
    int gained = 0;
    normalize(&r1, &c1, &r2, &c2);

    if (r1 == r2) {               /* horizontal: box above and box below */
        b->h[r1][c1] = 1;
        gained += try_claim(b, r1 - 1, c1, player);
        gained += try_claim(b, r1,     c1, player);
    } else {                      /* vertical: box to the left and to the right */
        b->v[r1][c1] = 1;
        gained += try_claim(b, r1, c1 - 1, player);
        gained += try_claim(b, r1, c1,     player);
    }
    return gained;
}

int board_game_over(const Board *b) {
    return b->score[0] + b->score[1] == TOTAL_BOXES;
}

char board_winner(const Board *b) {
    if (b->score[0] > b->score[1]) return 'A';
    if (b->score[1] > b->score[0]) return 'B';
    return 'T';
}

int board_score(const Board *b, char player) {
    return b->score[player_index(player)];
}
