#include <stdio.h>
#include "display.h"

#define STAR_LINE_WIDTH 76
#define RED   "\033[31m"
#define BLUE  "\033[34m"
#define RESET "\033[0m"

/* Prints a box owner letter: A in red, B in blue, anything else as-is. */
static void print_owner(char owner) {
    if (owner == 'A')
        printf(RED "A" RESET);
    else if (owner == 'B')
        printf(BLUE "B" RESET);
    else
        putchar(owner);
}

static void print_star_line(void) {
    for (int i = 0; i < STAR_LINE_WIDTH; i++)
        putchar('*');
    putchar('\n');
}

void display_board(const Board *b) {
    /* header: two spaces, then column numbers */
    printf("  ");
    for (int c = 0; c < DOT_COLS; c++)
        printf(c == DOT_COLS - 1 ? "%d\n" : "%d ", c);

    for (int r = 0; r < DOT_ROWS; r++) {
        /* dot row: row number, then dots with '-' between joined dots */
        printf("%d ", r);
        for (int c = 0; c < DOT_COLS; c++) {
            putchar('.');
            if (c < DOT_COLS - 1)
                putchar(b->h[r][c] ? '-' : ' ');
        }
        putchar('\n');

        /* line under the dot row: '|' under dots, box owner between them */
        if (r < DOT_ROWS - 1) {
            printf("  ");
            for (int c = 0; c < DOT_COLS; c++) {
                putchar(b->v[r][c] ? '|' : ' ');
                if (c < DOT_COLS - 1)
                    print_owner(b->box[r][c]);
            }
            putchar('\n');
        }
    }
}

void display_scores(const Board *b) {
    print_star_line();
    printf("Player A score: %d\n", board_score(b, 'A'));
    printf("Player B score: %d\n", board_score(b, 'B'));
    print_star_line();
}

void display_prompt(char player) {
    printf("Player %c's turn. Enter the row and column of the first dot "
           "(e.g., A0 -> 0 0) and second dot: ", player);
    fflush(stdout);   /* prompt has no newline, make sure it appears */
}

void display_invalid_move(void) {
    printf("Invalid move. The dots must be neighbours (no diagonals), "
           "on the grid, and the line must not already be drawn.\n");
}

void display_winner(const Board *b, char winner) {
    display_scores(b);
    if (winner == 'T')
        printf("It's a tie!\n");
    else
        printf("Player %c wins!\n", winner);
}
