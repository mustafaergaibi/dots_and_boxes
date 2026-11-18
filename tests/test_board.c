/* Unit tests for board.c — compile with:
 *   gcc -Wall -Wextra -g -I. tests/test_board.c board.c -o test_board
 */
#include <stdio.h>
#include "board.h"

static int failures = 0;
#define CHECK(cond) do { if (!(cond)) { printf("FAIL line %d: %s\n", __LINE__, #cond); failures++; } } while (0)

static void test_validation(void) {
    Board b; board_init(&b);
    CHECK(board_is_valid_move(&b, 0, 4, 0, 3));   /* horizontal, any order */
    CHECK(board_is_valid_move(&b, 0, 3, 0, 4));
    CHECK(board_is_valid_move(&b, 0, 4, 1, 4));   /* vertical */
    CHECK(!board_is_valid_move(&b, 0, 0, 1, 1));  /* diagonal */
    CHECK(!board_is_valid_move(&b, 0, 0, 0, 2));  /* too long */
    CHECK(!board_is_valid_move(&b, 0, 0, 0, 0));  /* same dot */
    CHECK(!board_is_valid_move(&b, 4, 5, 5, 5));  /* off the grid */
    CHECK(!board_is_valid_move(&b, -1, 0, 0, 0));
    board_apply_move(&b, 0, 4, 0, 3, 'A');
    CHECK(!board_is_valid_move(&b, 0, 3, 0, 4));  /* already drawn */
}

static void test_single_box(void) {
    Board b; board_init(&b);
    CHECK(board_apply_move(&b, 0, 0, 0, 1, 'A') == 0);
    CHECK(board_apply_move(&b, 1, 0, 1, 1, 'B') == 0);
    CHECK(board_apply_move(&b, 0, 0, 1, 0, 'A') == 0);
    CHECK(board_apply_move(&b, 1, 1, 0, 1, 'B') == 1); /* reversed dots */
    CHECK(b.box[0][0] == 'B');
    CHECK(board_score(&b, 'B') == 1 && board_score(&b, 'A') == 0);
}

static void test_double_box(void) {
    Board b; board_init(&b);
    /* two boxes side by side, (0,0) and (0,1), leave the shared middle line */
    board_apply_move(&b, 0, 0, 0, 1, 'A');
    board_apply_move(&b, 0, 1, 0, 2, 'A');
    board_apply_move(&b, 1, 0, 1, 1, 'A');
    board_apply_move(&b, 1, 1, 1, 2, 'A');
    board_apply_move(&b, 0, 0, 1, 0, 'A');
    board_apply_move(&b, 0, 2, 1, 2, 'A');
    CHECK(board_apply_move(&b, 0, 1, 1, 1, 'B') == 2);
    CHECK(board_score(&b, 'B') == 2);
}

static void test_full_game(void) {
    Board b; board_init(&b);
    for (int r = 0; r < DOT_ROWS; r++)
        for (int c = 0; c < DOT_COLS - 1; c++)
            board_apply_move(&b, r, c, r, c + 1, 'A');
    CHECK(!board_game_over(&b));
    for (int r = 0; r < DOT_ROWS - 1; r++)
        for (int c = 0; c < DOT_COLS; c++)
            board_apply_move(&b, r, c, r + 1, c, 'B');
    CHECK(board_game_over(&b));
    CHECK(board_score(&b, 'B') == TOTAL_BOXES);
    CHECK(board_winner(&b) == 'B');
}

int main(void) {
    test_validation();
    test_single_box();
    test_double_box();
    test_full_game();
    if (failures == 0) printf("All board tests passed.\n");
    return failures != 0;
}
