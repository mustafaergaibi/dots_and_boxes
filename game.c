#include "game.h"
#include "board.h"
#include "display.h"
#include "input.h"

static char other_player(char p) {
    return p == 'A' ? 'B' : 'A';
}

void game_run(void) {
    Board b;
    char player = 'A';
    int r1, c1, r2, c2;

    board_init(&b);
    display_board(&b);

    while (!board_game_over(&b)) {
        display_prompt(player);

        int status = read_move(&r1, &c1, &r2, &c2);
        if (status == INPUT_EOF)          /* input closed: quit cleanly */
            return;
        if (status == INPUT_BAD || !board_is_valid_move(&b, r1, c1, r2, c2)) {
            display_invalid_move();
            continue;                     /* same player tries again */
        }

        int gained = board_apply_move(&b, r1, c1, r2, c2, player);
        display_scores(&b);
        display_board(&b);

        if (gained == 0)                  /* completing a box = extra turn */
            player = other_player(player);
    }

    display_winner(&b, board_winner(&b));
}
